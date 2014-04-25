#include <elib/config.hpp>
#include <elib/fs/operations.hpp>
#include <elib/fs/directory_entry.hpp>
#include <elib/fs/directory_iterator.hpp>
#include <elib/fs/filesystem_error.hpp>

#include <elib/aux.hpp>
#include <elib/make_unique.hpp>

#include <cstdlib>
#include <climits>
#include <fstream>
#include <type_traits>
#include <random>  /* for unique_path */

#include <unistd.h>
#include <utime.h>
#include <sys/stat.h>
#include <sys/statvfs.h>
#include <fcntl.h>  /* values for fchmodat */

namespace elib { namespace fs
{
    
////////////////////////////////////////////////////////////////////////////////
//                       POSIX HELPERS                                                 
////////////////////////////////////////////////////////////////////////////////
    namespace detail { namespace  
    {
        using value_type = path::value_type;
        using string_type = path::string_type;
        
        
        // NOTE: The below functions are marked as inline so that they
        // do not set off the "-Wmissing-prototypes" warning
        
        ////////////////////////////////////////////////////////////////////////
        // set the permissions as described in stat
        inline perms posix_get_perms(const struct ::stat & st) noexcept
        {
            perms pmask = perms::none;
            auto const mode = st.st_mode;
            if (S_IRUSR & mode) pmask |= perms::owner_read;
            if (S_IWUSR & mode) pmask |= perms::owner_write;
            if (S_IXUSR & mode) pmask |= perms::owner_exec;
            if (S_IRGRP & mode) pmask |= perms::group_read;
            if (S_IWGRP & mode) pmask |= perms::group_write;
            if (S_IXGRP & mode) pmask |= perms::group_exec;
            if (S_IROTH & mode) pmask |= perms::others_read;
            if (S_IWOTH & mode) pmask |= perms::others_write;
            if (S_IXOTH & mode) pmask |= perms::others_exec;
            if (S_ISUID & mode) pmask |= perms::set_uid;
            if (S_ISGID & mode) pmask |= perms::set_gid;
            if (S_ISVTX & mode) pmask |= perms::sticky_bit;
            return pmask;
        }
        
        ////////////////////////////////////////////////////////////////////////
        inline ::mode_t posix_convert_perms(perms prms)
        {
            ::mode_t p = 0;
            if ((bool)(prms & perms::owner_read))   p |= S_IRUSR;
            if ((bool)(prms & perms::owner_write))  p |= S_IWUSR;
            if ((bool)(prms & perms::owner_exec))   p |= S_IXUSR;
            if ((bool)(prms & perms::group_read))   p |= S_IRGRP;
            if ((bool)(prms & perms::group_write))  p |= S_IWGRP;
            if ((bool)(prms & perms::group_exec))   p |= S_IXGRP;
            if ((bool)(prms & perms::others_read))  p |= S_IROTH;
            if ((bool)(prms & perms::others_write)) p |= S_IWOTH;
            if ((bool)(prms & perms::others_exec))  p |= S_IXOTH;
            if ((bool)(prms & perms::set_uid))      p |= S_ISUID;
            if ((bool)(prms & perms::set_gid))      p |= S_ISGID;
            if ((bool)(prms & perms::sticky_bit))   p |= S_ISVTX;
            return p;
        }
        
        ////////////////////////////////////////////////////////////////////////
        inline file_status posix_stat(
            path const & p
          , struct ::stat & path_stat
          , std::error_code* ec
          )
        {
            std::error_code m_ec;
            
            if (::stat(p.c_str(), &path_stat) == -1) {
                m_ec = detail::capture_errno();
            }
            
            if (ec) *ec = m_ec;
                
            if (m_ec && (m_ec.value() == ENOENT || m_ec.value() == ENOTDIR)) {
                return file_status(file_type::not_found);
            } 
            else if (m_ec && not ec) {
                throw filesystem_error("elib::fs::posix_stat", p, m_ec);
            }
            else if (m_ec) {
                return file_status(file_type::none);
            }
            // else
            
            file_status fs_tmp;
            auto const mode = path_stat.st_mode;
            if      (S_ISREG(mode))  fs_tmp.type(file_type::regular);
            else if (S_ISDIR(mode))  fs_tmp.type(file_type::directory);
            else if (S_ISBLK(mode))  fs_tmp.type(file_type::block);
            else if (S_ISCHR(mode))  fs_tmp.type(file_type::character);
            else if (S_ISFIFO(mode)) fs_tmp.type(file_type::fifo);
            else if (S_ISSOCK(mode)) fs_tmp.type(file_type::socket);
            else                     fs_tmp.type(file_type::unknown);
            
            fs_tmp.permissions(detail::posix_get_perms(path_stat));
    
            return fs_tmp;
        }
                    
        ////////////////////////////////////////////////////////////////////////
        inline file_status posix_lstat(
            path const & p
          , struct ::stat & path_stat
          , std::error_code* ec
          )
        {
            std::error_code m_ec;
            
            if (::lstat(p.c_str(), &path_stat) == -1) {
                m_ec = detail::capture_errno();
            }
            if (ec) *ec = m_ec;
            
            if (m_ec && (m_ec.value() == ENOENT || m_ec.value() == ENOTDIR)) {
                return file_status(file_type::not_found);
            }
            else if (m_ec && not ec) {
                throw filesystem_error("elib::fs::status", p, m_ec);
            }
            else if (m_ec) {
                return file_status(file_type::none);
            }
            // else
            
            file_status fs_tmp;
            auto const mode = path_stat.st_mode;
            if      (S_ISLNK(mode))  fs_tmp.type(file_type::symlink);
            else if (S_ISREG(mode))  fs_tmp.type(file_type::regular);
            else if (S_ISDIR(mode))  fs_tmp.type(file_type::directory);
            else if (S_ISBLK(mode))  fs_tmp.type(file_type::block);
            else if (S_ISCHR(mode))  fs_tmp.type(file_type::character);
            else if (S_ISFIFO(mode)) fs_tmp.type(file_type::fifo);
            else if (S_ISSOCK(mode)) fs_tmp.type(file_type::socket);
            else                     fs_tmp.type(file_type::unknown);
            
            // TODO symbolic link
            fs_tmp.permissions(detail::posix_get_perms(path_stat));
            return fs_tmp;
        }
        
        ////////////////////////////////////////////////////////////////////////
        inline bool posix_statvfs(
            path const & p
          , struct ::statvfs & sv
          , std::error_code *ec
          )
        {
            std::error_code m_ec;
            if (statvfs(p.c_str(), &sv) == -1)  {
                m_ec = detail::capture_errno();
            }
            if (ec) *ec = m_ec;
            
            if (m_ec && not ec) {
                throw filesystem_error("elib::fs::posix_statvfs", p, m_ec);
            }
            
            return !bool(m_ec);
        }
        
        ////////////////////////////////////////////////////////////////////////
        inline path posix_realpath(const path& p, 
                        std::error_code *ec)
        {
           
            char buff[PATH_MAX];
            char *ret = ::realpath(p.c_str(), buff);
            
            std::error_code m_ec;
            if (not ret) {
                m_ec = detail::capture_errno();
                ELIB_ASSERT(m_ec);
            }
            if (ec) *ec = m_ec;
                
            if (m_ec && not ec) { 
                throw filesystem_error("elib::fs::posix_realpath", p, m_ec);
            }
            else if (m_ec) {
                return path{};
            } else {
                return path{ret};
            }
        }
        
        ////////////////////////////////////////////////////////////////////////
        inline string_type posix_getcwd(std::error_code *ec)
        {
            auto size = pathconf(".", _PC_PATH_MAX);
            ELIB_ASSERT(size >= 0);
            
            auto buff = elib::make_unique<char[]>( 
                static_cast<std::size_t>(size) 
              );
            
            char* ret = ::getcwd(buff.get(), static_cast<size_t>(size));
            
            std::error_code m_ec;
            if (not ret) {
                m_ec = detail::capture_errno();
            }
            if (ec) *ec = m_ec;
            
            if (m_ec && not ec) {
                throw filesystem_error("elib::fs::posix_getcwd", m_ec);
            }
            else if (m_ec) {
                return string_type{};
            } else {
                return string_type{buff.get()};
            }
        }
        
        ////////////////////////////////////////////////////////////////////////
        inline bool posix_chdir(const string_type& s, std::error_code *ec)
        {
            std::error_code m_ec;
            if (::chdir(s.c_str()) == -1) {
                m_ec = detail::capture_errno();
            }
            if (ec) *ec = m_ec;
                
            if (m_ec && not ec) {
                throw filesystem_error("elib::fs::posix_chdir", path{s}, m_ec);
            }
            
            return !m_ec;
        }
        
        
        ////////////////////////////////////////////////////////////////////////
        inline bool posix_utime(
            const string_type& s
          , const ::utimbuf & ut
          , std::error_code *ec
          )
        {
            std::error_code m_ec;
            if (::utime(s.c_str(), &ut) == -1) {
                m_ec = detail::capture_errno();
                ELIB_ASSERT(m_ec);
            }
            if (ec) *ec = m_ec;
            
            if (m_ec && not ec) {
                throw filesystem_error("elib::fs::posix_utime", path{s}, m_ec);
            }
            
            return !m_ec;
        }
        
        ////////////////////////////////////////////////////////////////////////
        inline bool posix_symlink(
            const string_type& from
          , const string_type& to
          , std::error_code *ec
          )
        {
            std::error_code m_ec;
            if (::symlink(from.c_str(), to.c_str()) == -1) {
                m_ec = detail::capture_errno();
                ELIB_ASSERT(m_ec);
            }
            if (ec) *ec = m_ec;
                
            if (m_ec && not ec) {
                throw filesystem_error(
                    "elib::fs::posix_symlink"
                  , path{from}, path{to}, m_ec
                );
            }
            
            return !m_ec;
        }
        
        ////////////////////////////////////////////////////////////////////////
        inline bool posix_link(
            const string_type& from
          , const string_type& to
          , std::error_code *ec)
        {
            std::error_code m_ec;
            if (::link(from.c_str(), to.c_str()) == -1) {
                m_ec = detail::capture_errno();
            }
            if (ec) *ec = m_ec;
            
            if (m_ec && not ec) {
                throw filesystem_error("elib::fs::posix_link"
                  , path{from}, path{to}, m_ec
                  );
            }
            
            return !m_ec;
        }
        
        ////////////////////////////////////////////////////////////////////////
        inline string_type posix_readlink(
            const string_type& s
          , std::error_code *ec
          )
        {
            
            char buff[PATH_MAX];
            std::error_code m_ec;
            if (::readlink(s.c_str(), buff, PATH_MAX) == -1) {
                m_ec = detail::capture_errno();
            }
            if (ec) *ec = m_ec;
            
            if (m_ec && not ec) {
                throw filesystem_error("elib::fs::posix_readlink", path{s}, m_ec);
            }
            else if (m_ec) {
                return string_type{};
            }
            else {
                return string_type{buff};
            }
        }
        
        ////////////////////////////////////////////////////////////////////////
        inline bool posix_truncate(const string_type& s, std::uintmax_t size, 
                            std::error_code *ec)
        {
            std::error_code m_ec;
            if (::truncate(s.c_str(), static_cast<long>(size)) == -1) {
                m_ec = detail::capture_errno();
            }
            if (ec) *ec = m_ec;
            
            if (m_ec && not ec) {
                throw filesystem_error("elib::fs::posix_truncate", path{s}, m_ec);
            }
            
            return not m_ec;
        }
        
        ////////////////////////////////////////////////////////////////////////
        inline bool posix_rename(
            const string_type& from
          , const string_type& to
          , std::error_code *ec
          )
        {
            std::error_code m_ec;
            if (::rename(from.c_str(), to.c_str()) == -1) {
                m_ec = detail::capture_errno();
            }
            if (ec) *ec = m_ec;
            
            if (m_ec && not ec) {
                throw filesystem_error("elib::fs::posix_rename"
                    , path{from}, path{to}, m_ec
                  );
            }
            
            return !m_ec;
        }
        
        ////////////////////////////////////////////////////////////////////////
        inline bool posix_remove(const string_type& s, std::error_code *ec)
        {
            std::error_code m_ec;
            if (::remove(s.c_str()) == -1) {
                m_ec = detail::capture_errno();
            }
            if (ec) *ec = m_ec;
            
            if (m_ec && not ec) {
                throw filesystem_error("elib::fs::posix_remove", path{s}, m_ec);
            }
            return !m_ec;
        }
        
        ////////////////////////////////////////////////////////////////////////
        inline bool posix_mkdir(const string_type& s, mode_t m, std::error_code *ec)
        {
            std::error_code m_ec;
            if (::mkdir(s.c_str(), m) == -1) {
                m_ec = detail::capture_errno();
            }
            if (ec) *ec = m_ec;
                
            if (m_ec && not ec) {
                throw filesystem_error("elib::fs::posix_mkdir", path{s}, m_ec);
            }
            return !m_ec;
        }
        
        ////////////////////////////////////////////////////////////////////////
        inline bool posix_chmod(const string_type& s, ::mode_t mode,
                std::error_code *ec)
        {
            std::error_code m_ec;
            if (::chmod(s.c_str(), mode) == -1) {
                m_ec = detail::capture_errno();
            }
            if (ec) *ec = m_ec;
            
            if (m_ec && not ec) {
                throw filesystem_error("elib::fs::posix_chmod", path{s}, m_ec);
            }
            return !m_ec;
        }
        
    }}                                                      // namespace detail
////////////////////////////////////////////////////////////////////////////////
//                           DETAIL::MISC                                           
////////////////////////////////////////////////////////////////////////////////
        
    namespace detail { namespace 
    {
#if defined(__clang__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wunused-function"
#endif
        ////////////////////////////////////////////////////////////////////////
        inline bool verify_copy_options(copy_options& opt) noexcept
        {
            if (opt == copy_options::none) return true;
            copy_options g1 = copy_options::skip_existing | 
                            copy_options::overwrite_existing |
                            copy_options::update_existing;
                            
            copy_options g2 = copy_options::recursive;
            
            copy_options g3 = copy_options::copy_symlinks |
                            copy_options::skip_symlinks;
            
            copy_options g4 = copy_options::directories_only |
                            copy_options::create_symlinks |
                            copy_options::create_hard_links;
                            
            int gcount = 0;
            if (static_cast<bool>(opt & g1)) ++gcount;
            if (static_cast<bool>(opt & g2)) ++gcount;
            if (static_cast<bool>(opt & g3)) ++gcount;
            if (static_cast<bool>(opt & g4)) ++gcount;
            
            return (gcount <= 1);
        }
        
        ////////////////////////////////////////////////////////////////////////
        inline bool verify_exists(const path& p)
        {
            std::error_code ec;
            auto fst = detail::status(p, &ec);
            return (status_known(fst) && exists(fst));
        }
        
        ////////////////////////////////////////////////////////////////////////
        inline bool copy_file_impl(
            const path& from, const path& to
          , std::error_code *ec
          )
        {
            detail::clear_error(ec);
            std::ifstream in(from.c_str(), std::ios::binary);
            std::ofstream out(to.c_str(),  std::ios::binary);
            
            if (in.good() && out.good())
            out <<  in.rdbuf();
            
            if (!out.good() || !in.good())
            {
            detail::handle_and_throw_error(std::errc::operation_not_permitted,
                        "elib::fs::copy_file_impl", from, to, ec);
            return false;
            }
            
            return true;
        }
#if defined(__clang__)
# pragma clang diagnostic pop
#endif
    }}                                                       // namespace detail 
  
}}                                                        // namespace elib::fs

////////////////////////////////////////////////////////////////////////////////
//                        DETAIL::OPERATORS DEFINITIONS                                                        
////////////////////////////////////////////////////////////////////////////////

namespace elib { namespace fs { namespace detail
{
    ////////////////////////////////////////////////////////////////////////////
    path canonical(const path& p, const path& base, std::error_code *ec)
    {
        auto ap = absolute(p, base);
        // on failure posix_read_path will throw or
        // return str == "". no need to check further
        return detail::posix_realpath(ap, ec);
    }

    ////////////////////////////////////////////////////////////////////////////
    // TODO
   // void copy(const path& from, const path& to, copy_options options,
     //   std::error_code *ec);
    

    ////////////////////////////////////////////////////////////////////////////
    // TODO
    //bool copy_file(
      //  const path& from, const path& to
      //, copy_options option, std::error_code *ec
      //);
        

    //TODO
    //void copy_symlink(const path& existing_symlink, const path& new_symlink,
      //  std::error_code *ec);

    //TODO
    //bool create_directories(const path& p, std::error_code *ec);


    bool create_directory(const path& p, std::error_code *ec)
    {
        std::error_code m_ec;
        detail::posix_mkdir(p.native(), S_IRWXU|S_IRWXG|S_IRWXO, &m_ec);
        if (ec) *ec = m_ec;
        
        if (not m_ec) return true;
            
        std::error_code tmp_ec;
        if (m_ec.value() == EEXIST && fs::is_directory(p, tmp_ec)) {
            if (ec) ec->clear();
            return true;
        }
        else if (not ec) {
            throw filesystem_error("elib::fs::create_directory", p, m_ec);
        } else {
            return false;
        }
    }

    //TODO
    //void create_directory(const path& p, const path& attributes, 
      //  std::error_code *ec);

    ////////////////////////////////////////////////////////////////////////////
    void create_directory_symlink(
        const path& to, const path& new_symlink,
        std::error_code *ec
      )
    {
        detail::posix_link(to.native(), new_symlink.native(), ec);
    }
    
    ////////////////////////////////////////////////////////////////////////////
    void create_hard_link(
        const path& to, const path& new_hard_link,
        std::error_code *ec
      )
    {
        detail::posix_link(to.native(), new_hard_link.native(), ec);
    }

    ////////////////////////////////////////////////////////////////////////////
    void create_symlink(
        const path& to, const path& new_symlink
      , std::error_code *ec
      )
    {
        detail::posix_symlink(to.native(), new_symlink.native(), ec);
    }

    ////////////////////////////////////////////////////////////////////////////
    path current_path(std::error_code *ec)
    {
        return path{detail::posix_getcwd(ec)};
    }

    ////////////////////////////////////////////////////////////////////////////
    void current_path(const path& p, std::error_code *ec)
    {
        detail::posix_chdir(p.native(), ec);
    }

    ////////////////////////////////////////////////////////////////////////////
    // TODO
    bool equivalent(
        const path& p1, const path& p2, 
        std::error_code *ec)
    {
        std::error_code ec1, ec2;
        struct ::stat st1, st2;
        detail::posix_stat(p1.native(), st1, &ec1);
        detail::posix_stat(p2.native(), st2, &ec2);
        
        if (ec1 && ec2) {
            if (ec) ec->clear();
            return false;
        }
        else if (ec1 || ec2) {
            if (ec) {
                *ec = ec1 ? ec1 : ec2;
                return false;
            } else {
                throw filesystem_error(
                    "elib::fs::equivalent"
                , p1, p2
                , ec1 ? ec1 : ec2
                );
            }
        } else {
            if (ec) ec->clear();
            return (st1.st_dev == st2.st_dev && st1.st_ino == st2.st_ino);
        }
    }

    ////////////////////////////////////////////////////////////////////////////
    // TODO
    std::uintmax_t file_size(const path& p, std::error_code *ec)
    {
        std::error_code m_ec;
        struct ::stat st;
        file_status fst = detail::posix_stat(p, st, &m_ec);
        if (fs::exists(fst) && fs::is_regular_file(fst)) {
            ELIB_ASSERT(not m_ec);
            if (ec) ec->clear();
            return static_cast<std::uintmax_t>(st.st_size);
        }
        else if (m_ec && not ec) {
            throw filesystem_error("elib::fs::file_size", p, m_ec);
        }
        else if (m_ec) {
            *ec = m_ec;
            return static_cast<std::uintmax_t>(-1);
        }
        else if (not fs::is_regular_file(fst)) {
            std::error_code tmp_ec{EPERM, std::system_category()};
            if (ec) {
                *ec = tmp_ec;
                return static_cast<std::uintmax_t>(-1);
            } else {
                throw filesystem_error("elib::fs::file_size", p, tmp_ec);
            }
        } else {
            ELIB_ASSERT(false);
            throw "TODO";
        }
    }

    ////////////////////////////////////////////////////////////////////////////
    // TODO
    std::uintmax_t hard_link_count(const path& p, std::error_code *ec)
    {
        std::error_code m_ec;
        struct ::stat st;
        detail::posix_stat(p, st, &m_ec);
        if (ec) *ec = m_ec;
        if (m_ec && not ec) {
            throw filesystem_error("elib::fs::hard_link_count", p, m_ec);
        } 
        else if (m_ec && ec) {
            return static_cast<std::uintmax_t>(-1);
        } else {
            return static_cast<std::uintmax_t>(st.st_nlink);
        }
    }

    ////////////////////////////////////////////////////////////////////////////
    //TODO
    bool is_empty(const path& p, std::error_code *ec)
    {
        auto is_dir = is_directory(detail::status(p, ec));
        return (is_dir ? directory_iterator(p) == directory_iterator()
          : detail::file_size(p, ec) == 0); 
    }

    ////////////////////////////////////////////////////////////////////////////
    std::time_t last_write_time(const path& p, std::error_code *ec)
    {
        std::error_code m_ec;
        struct ::stat st;
        detail::posix_stat(p, st, &m_ec);
        if (ec) *ec = m_ec;
            
        if (m_ec && not ec) {
            throw filesystem_error("elib::fs::last_write_time", p, m_ec);
        } 
        else if (m_ec) {
            return static_cast<std::time_t>(-1);
        } else {
            return static_cast<std::time_t>(st.st_mtime);
        }
    }

    ////////////////////////////////////////////////////////////////////////////
    // TODO
    void last_write_time(
        const path& p
      , std::time_t new_time
      , std::error_code *ec
      )
    {
        std::error_code m_ec;
        struct ::stat st;
        detail::posix_stat(p, st, &m_ec);
        if (ec) *ec = m_ec;
            
        if (m_ec && not ec) {
            throw filesystem_error("elib::fs::last_write_time", p, m_ec);
        }
        else if (m_ec) {
            return;
        }
        
        ::utimbuf tbuf;
        tbuf.actime = st.st_atime;
        tbuf.modtime = new_time;
        
        detail::posix_utime(p.native(), tbuf, &m_ec);
        if (ec) *ec = m_ec;
            
        if (m_ec && not ec) {
            throw filesystem_error("elib::fs::last_write_time", p, m_ec);
        }
    }

    ////////////////////////////////////////////////////////////////////////////
    void permissions(const path& p,  perms prms,  std::error_code *ec)
    {
        detail::posix_chmod(p.string(), detail::posix_convert_perms(prms), ec);
    }

    ////////////////////////////////////////////////////////////////////////////
    path read_symlink(const path& p, std::error_code *ec)
    {
        return path{detail::posix_readlink(p.native(), ec)};
    }

    ////////////////////////////////////////////////////////////////////////////
    bool remove(const path& p, std::error_code *ec)
    {
        return detail::posix_remove(p.native(), ec);
    }


    //TODO
    //std::uintmax_t remove_all(const path& p, std::error_code *ec);

    ////////////////////////////////////////////////////////////////////////////
    void rename(const path& from, const path& to, std::error_code *ec)
    {
        detail::posix_rename(from.native(), to.native(), ec);
    }
    
    ////////////////////////////////////////////////////////////////////////////
    void resize_file(const path& p, uintmax_t size, std::error_code *ec)
    {
        detail::posix_truncate(p, size, ec);
    }
    
    ////////////////////////////////////////////////////////////////////////////
    // TODO
    space_info space(const path& p, std::error_code *ec)
    {
        std::error_code m_ec;
        struct statvfs m_svfs;
        //if we fail but don't throw
        detail::posix_statvfs(p.native(), m_svfs, &m_ec);
        if (ec) *ec = m_ec;
            
        if (m_ec && not ec) {
            throw filesystem_error("elib::fs::space", p, m_ec);
        } 
        else if (m_ec) {
            space_info si;
            si.capacity = si.free = si.available = 
                static_cast<decltype(si.free)>(-1);
            return si;
        } else {
            space_info si;
            si.capacity =   m_svfs.f_blocks * m_svfs.f_frsize;
            si.free =       m_svfs.f_bfree  * m_svfs.f_frsize;
            si.available =  m_svfs.f_bavail * m_svfs.f_frsize;
            return si;
        }
    }

    ////////////////////////////////////////////////////////////////////////////
    file_status status(const path& p, std::error_code *ec)
    {
        struct stat m_stat;
        return detail::posix_stat(p, m_stat, ec);
    }
    
    ////////////////////////////////////////////////////////////////////////////
    file_status symlink_status(const path& p, std::error_code *ec)
    {
        struct stat m_stat;
        return detail::posix_lstat(p, m_stat, ec);
    }

    ////////////////////////////////////////////////////////////////////////////
    path system_complete(const path& p, std::error_code *ec)
    {
        if (ec) ec->clear();
        return absolute(p, current_path());
    }

    ////////////////////////////////////////////////////////////////////////////
    // TODO
    path temp_directory_path(std::error_code *ec)
    {
        const char* env_paths[] = {"TMPDIR", "TMP", "TEMP", "TEMPDIR"};
        path p{};
        std::error_code m_ec;
        detail::clear_error(ec);
        for (auto & ep : env_paths) 
        {
            char *ret = std::getenv(ep);
            if (ret) {
                p = path{ret};
            } else {
                p = path{};
            }
            
            if (fs::is_directory(p, m_ec)) {
                if (ec) ec->clear();
                return p;
            }
        }

        p = path{"/tmp"};
        if (fs::is_directory(p, m_ec)) {
            if (ec) ec->clear();
            return p;
        } 
        // else

        m_ec = std::make_error_code(std::errc::no_such_file_or_directory);
        if (not ec) {
            throw filesystem_error("elib::fs::temp_directory_path", m_ec);
        } else {
            *ec = m_ec;
            return path{};
        }
    }

    namespace 
    {
        ////////////////////////////////////////////////////////////////////////
        inline char to_hex(int ch) noexcept
        {
            if (ch < 10) {
                return static_cast<char>('0' + ch);
            } else {
                return static_cast<char>('a' + (ch - 10));
            }
        }
        
        ////////////////////////////////////////////////////////////////////////
        inline char random_hex_char()
        {
            static std::mt19937 rd { std::random_device{}() };
            static std::uniform_int_distribution<int> mrand{0, 15};
            return to_hex( mrand(rd) );
        }  
    }                                                              // namespace 


    //-------------------------------- unique_path --------------------------------// 


    path unique_path(const path& model, std::error_code *ec)
    {
        std::string tmp_str = model.native();
        for (auto& ch : tmp_str) {
            if (ch == '%') ch = detail::random_hex_char();
        }
        if (ec) ec->clear();
        return path {tmp_str};
    }                                                     // unique_path
      
}}}                                               // namespace elib::fs::detail
    
    
////////////////////////////////////////////////////////////////////////////////
//                      OPERATORS DEFINITION                                                    
////////////////////////////////////////////////////////////////////////////////
namespace elib { namespace fs
{
    
    //since the specification of absolute in the current specification
    // this implementation is designed after the sample implementation
    // using the sample table as a guide
    path absolute(const path& p, const path& base)
    {
      auto root_name = p.root_name();
      auto root_dir = p.root_directory();
    
      if (!root_name.empty() && !root_dir.empty())
        return p;
        
      auto abs_base = base.is_absolute() ? base : absolute(base);
      
      /* !has_root_name && !has_root_dir */
      if (root_name.empty() && root_dir.empty()) 
      {
        return abs_base / p;
      }
      else if (!root_name.empty()) /* has_root_name && !has_root_dir */
      {
        return  root_name / abs_base.root_directory()
                /
                abs_base.relative_path() / p.relative_path();
      }
      else /* !has_root_name && has_root_dir */
      {
        if (abs_base.has_root_name())
          return abs_base.root_name() / p;
        // else p is absolute,  return outside of block
      }
      
      ELIB_ASSERT(p.is_absolute());
      return p;
    }
      
}}                                                          // namespace elib