#include <elib/filesystem/operations.hpp>
#include <elib/filesystem/directory_entry.hpp>
#include <elib/filesystem/directory_iterator.hpp>
#include <elib/filesystem/filesystem_error.hpp>

#include <elib/memory/make_unique.hpp>

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

namespace elib { namespace fs { inline namespace v1
{
    
////////////////////////////////////////////////////////////////////////////////
//                       POSIX HELPERS                                                 
////////////////////////////////////////////////////////////////////////////////
    namespace detail { namespace  
    {
        using value_type = path::value_type;
        using string_type = path::string_type;
        
        ////////////////////////////////////////////////////////////////////////
        // set the permissions as described in stat
        perms posix_get_perms(const struct ::stat & st) noexcept
        {
            return static_cast<perms>(st.st_mode) & perms::mask;
        }
        
        ////////////////////////////////////////////////////////////////////////
        ::mode_t posix_convert_perms(perms prms)
        {
            return static_cast<::mode_t>(
                prms & perms::mask
              );
        }
        
        ////////////////////////////////////////////////////////////////////////
        file_status posix_stat(
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
        file_status posix_lstat(
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
                throw filesystem_error("elib::fs::posix_lstat", p, m_ec);
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

    }}                                                      // namespace detail
////////////////////////////////////////////////////////////////////////////////
//                           DETAIL::MISC                                           
////////////////////////////////////////////////////////////////////////////////
        
    namespace detail { namespace 
    {
        ////////////////////////////////////////////////////////////////////////
        // TODO
        bool copy_file_impl(
            const path& from, const path& to
          , std::error_code *ec
          )
        {
            if (ec) { ec->clear(); }
                
            std::ifstream in(from.c_str(), std::ios::binary);
            std::ofstream out(to.c_str(),  std::ios::binary);
            
            if (in.good() && out.good()) {
                out << in.rdbuf();
            }
            
            if (out.fail() || in.fail()) {
                std::error_code m_ec(
                    static_cast<int>(std::errc::operation_not_permitted)
                  , std::system_category()
                  );
           
                if (ec) {
                    *ec = m_ec;
                    return false;
                } else {
                    throw filesystem_error("fs::copy_file_impl", from, to, m_ec);
                }
            }
            
            return true;
        }

    }}                                                       // namespace detail 
  
}}}                                                        // namespace elib::fs

////////////////////////////////////////////////////////////////////////////////
//                        DETAIL::OPERATORS DEFINITIONS                                                        
////////////////////////////////////////////////////////////////////////////////

namespace elib { namespace fs { inline namespace v1 { namespace detail
{
    ////////////////////////////////////////////////////////////////////////////
    path canonical(path const & orig_p, const path& base, std::error_code *ec)
    {
        path p = absolute(orig_p, base);
        
        char buff[PATH_MAX + 1];
        char *ret = ::realpath(p.c_str(), buff);
            
        std::error_code m_ec;
        if (not ret) {
            m_ec = detail::capture_errno();
            ELIB_ASSERT(m_ec);
        }
        if (ec) *ec = m_ec;
                
        if (m_ec && not ec) { 
            throw filesystem_error("elib::fs::canonical", orig_p, m_ec);
        }
        else if (m_ec) {
            return {};
        } else {
            return {ret};
        }
    }

    ////////////////////////////////////////////////////////////////////////////
    // TODO
    void copy(
        const path& from, const path& to
      , copy_options options
      , std::error_code *ec
      )
    {
        const bool sym_status = bool(options & 
            (copy_options::create_symlinks | copy_options::skip_symlinks));
        
        std::error_code m_ec;
        struct ::stat f_st;
        const file_status f = sym_status ? detail::posix_lstat(from, f_st, &m_ec)
                                         : detail::posix_stat(from, f_st, &m_ec);
        
        if (m_ec && ec) {
            *ec = m_ec;
            return;
        } else if (m_ec) {
            throw filesystem_error("fs::copy", from, m_ec);
        }
        
        
        struct ::stat t_st;
        const file_status t = sym_status ? detail::posix_lstat(to, t_st, &m_ec)
                                         : detail::posix_stat(to, t_st, &m_ec);
        
        if (!status_known(t)) {
            if (ec) {
                *ec = m_ec;
                return;
            } else {
                throw filesystem_error("elib::fs::copy", from, to, m_ec);
            }
        }
        
        if ((f_st.st_dev == t_st.st_dev && f_st.st_ino == t_st.st_ino)
          || is_other(f) || is_other(t) 
          || (is_directory(f) && is_regular_file(t)))
        {
            const std::error_code mec(
                static_cast<int>(std::errc::function_not_supported)
              , std::system_category()
              );
            if (ec) {
                *ec = mec;
                return;
            } else {
                throw filesystem_error("fs::copy", from, to, mec);
            }
        }
        
        if (ec) { ec->clear(); }
            
        if (is_symlink(f)) {
            if (bool(copy_options::skip_symlinks & options)) {
                return;
            }
            else if (not exists(t)) {
                detail::copy_symlink(from, to, ec);
                return;
            } else {
                const std::error_code mec(
                    static_cast<int>(std::errc::file_exists)
                  , std::system_category()
                  );
                if (ec) {
                    *ec = mec;
                    return;
                }
                // else
                throw filesystem_error("fs::copy", from, to, mec);
            }
            ELIB_ASSERT(false);
        }
        else if (is_regular_file(f)) {
            if (bool(copy_options::directories_only & options)) {
                // do nothing
            }
            else if (bool(copy_options::create_symlinks & options)) {
                detail::create_symlink(from, to, ec);
            }
            else if (bool(copy_options::create_hard_links & options)) {
                detail::create_hard_link(from, to, ec);
            }
            else if (is_directory(t)) {
                detail::copy_file(from, to/from.filename(), options, ec);
            } else {
                detail::copy_file(from, to, options, ec);
            }
            return;
        }
        else if (is_directory(f)) {
            if (not bool(copy_options::recursive & options) &&
                bool(copy_options::detail_in_recursive_copy & options))
            {
                return;
            }
            
            if (!exists(t)) {
                // create directory to with attributes from 'from'.
                detail::create_directory(to, from, ec);
                if (ec && *ec) { return; }
            }
            directory_iterator it = ec ? directory_iterator(from, *ec) 
                                       : directory_iterator(from);
            if (ec && *ec) { return; }
            for (; it != directory_iterator(); ++it) {
                detail::copy(it->path(), to / it->path().filename()
                  , options | copy_options::detail_in_recursive_copy
                  , ec
                  );
                if (ec && *ec) { return; }
            }
            return;
        } else {
            // TODO shouldn't be here
            ELIB_ASSERT(false);
        }

    }
    

    ////////////////////////////////////////////////////////////////////////////
    // TODO
    bool copy_file(
        const path& from, const path& to
      , copy_options options, std::error_code *ec
      )
    {
        if (ec) ec->clear();
            
        std::error_code m_ec;
        const bool good_from = fs::is_regular_file(from, m_ec);
        if (not good_from) {
            if (not m_ec) {
                m_ec = std::error_code(
                    static_cast<int>(std::errc::no_such_file_or_directory)
                    , std::system_category()
                    );
            }
                
            if (ec) {
                *ec = m_ec;
                return false;
            } else {
                throw filesystem_error(
                    "elib::fs::copy_file source file is not a regular file"
                , from, to, m_ec
                );
            }
        }
        
        const bool to_exists = fs::exists(to, m_ec);
        
        if (to_exists && not bool(options & 
            (copy_options::skip_existing 
            | copy_options::update_existing 
            | copy_options::overwrite_existing))) 
        {
            const std::error_code mec(
                static_cast<int>(std::errc::file_exists)
              , std::system_category()
              );
            if (ec) {
                *ec = mec;
                return false;
            } else {
                throw filesystem_error("fs::copy_file", from, to, mec);
            }
        }
        else if (to_exists && bool(copy_options::skip_existing & options)) {
            return false;
        }
        else if (to_exists && bool(copy_options::update_existing & options)) {
            auto from_time = detail::last_write_time(from, ec);
            if (ec && *ec) { return false; }
            auto to_time = detail::last_write_time(to, ec);
            if (ec && *ec) { return false; }
            if (from_time <= to_time) {
                return false;
            }
        }
        return detail::copy_file_impl(from, to, ec);
    }
        

    void copy_symlink(
        const path& existing_symlink, const path& new_symlink
      , std::error_code *ec)
    {
        const path real_path(detail::read_symlink(existing_symlink, ec));
        if (ec && *ec) { return; }
        
        // TODO proposal says you should detect if you should call
        // create_symlink or create_directory_symlink. I don't think this
        // is needed with POSIX
        detail::create_symlink(real_path, new_symlink, ec);
    }


    bool create_directories(const path& p, std::error_code *ec)
    {
        std::error_code mec;
        auto const st = fs::status(p, mec);
        
        if (is_directory(st)) {
            if (ec) ec->clear();
            return false;
        }
        
        const path parent = p.parent_path();
        if (!parent.empty()) {
            const file_status parent_st = fs::status(parent, mec);
            if (not exists(parent_st)) {
                fs::create_directories(parent, mec);
                if (mec && ec) {
                    *ec = mec;
                    return false;
                } 
                else if (mec) {
                    throw filesystem_error("fs::create_directories", parent, mec);
                }
            }
        }
        
        return detail::create_directory(p, ec);
    }


    bool create_directory(const path& p, std::error_code *ec)
    {
        std::error_code m_ec;
        if (::mkdir(p.c_str(), S_IRWXU|S_IRWXG|S_IRWXO) == -1) {
            m_ec = detail::capture_errno();
        }
        if (ec) *ec = m_ec;
        
        if (not m_ec) return true;
            
        if (m_ec.value() == EEXIST && fs::is_directory(p)) {
            if (ec) ec->clear();
            return false;
        }
        else if (not ec) {
            throw filesystem_error("elib::fs::create_directory", p, m_ec);
        } else {
            return false;
        }
    }

    
    bool create_directory(
        path const & p, path const & attributes
      , std::error_code *ec
      )
    {
        struct ::stat attr_stat;
        std::error_code mec;
        detail::posix_stat(attributes, attr_stat, &mec);
        if (mec && ec) {
            *ec = mec;
            return false;
        }
        else if (mec) {
            throw filesystem_error("fs::create_directory", p, attributes, mec);
        }
    
        if (ec) ec->clear();
            
        if (::mkdir(p.c_str(), attr_stat.st_mode) == -1) {
            mec = std::error_code(errno, std::system_category());
            if (mec.value() == EEXIST && fs::is_directory(p)) {
                return false;
            }
            else if (ec) {
                *ec = mec;
                return false;
            } else {
                throw filesystem_error("fs::create_directory", p, attributes, mec);
            }
        }
        return true;
    }

    ////////////////////////////////////////////////////////////////////////////
    void create_directory_symlink(
        path const & from, path const & to
      , std::error_code *ec
      )
    {
        std::error_code m_ec;
        if (::symlink(from.c_str(), to.c_str()) != 0) {
            m_ec = detail::capture_errno();
            ELIB_ASSERT(m_ec);
        }
        if (ec) *ec = m_ec;
                
        if (m_ec && not ec) {
            throw filesystem_error(
                "elib::fs::create_directory_symlink"
              , from, to, m_ec
              );
        }
    }
    
    ////////////////////////////////////////////////////////////////////////////
    void create_hard_link(
        const path& from, const path& to,
        std::error_code *ec
      )
    {
        std::error_code m_ec;
        if (::link(from.c_str(), to.c_str()) == -1) {
            m_ec = detail::capture_errno();
        }
        if (ec) *ec = m_ec;
            
        if (m_ec && not ec) {
            throw filesystem_error("elib::fs::create_hard_link", from, to, m_ec);
        }
    }

    ////////////////////////////////////////////////////////////////////////////
    void create_symlink(
        path const & from, path const & to
      , std::error_code *ec
      )
    {
        std::error_code m_ec;
        if (::symlink(from.c_str(), to.c_str()) != 0) {
            m_ec = detail::capture_errno();
            ELIB_ASSERT(m_ec);
        }
        if (ec) *ec = m_ec;
                
        if (m_ec && not ec) {
            throw filesystem_error("elib::fs::create_symlink", from, to, m_ec);
        }
    }

    ////////////////////////////////////////////////////////////////////////////
    path current_path(std::error_code *ec)
    {
        auto size = ::pathconf(".", _PC_PATH_MAX);
        ELIB_ASSERT(size >= 0);
            
        auto buff = elib::make_unique<char[]>( 
            static_cast<std::size_t>(size + 1) 
            );
            
        char* ret = ::getcwd(buff.get(), static_cast<size_t>(size));
            
        std::error_code m_ec;
        if (not ret) {
                m_ec = detail::capture_errno();
        }
        if (ec) *ec = m_ec;
            
        if (m_ec && not ec) {
            throw filesystem_error("elib::fs::current_path", m_ec);
        }
        else if (m_ec) {
            return {};
        } else {
            return {buff.get()};
        }
    }

    ////////////////////////////////////////////////////////////////////////////
    void current_path(const path& p, std::error_code *ec)
    {
        std::error_code m_ec;
        if (::chdir(p.c_str()) == -1) {
            m_ec = detail::capture_errno();
        }
        if (ec) *ec = m_ec;
                
        if (m_ec && not ec) {
            throw filesystem_error("elib::fs::current_path", p, m_ec);
        }

    }

    ////////////////////////////////////////////////////////////////////////////
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
            std::error_code tmp_ec(EPERM, std::system_category());
            if (ec) {
                *ec = tmp_ec;
                return static_cast<std::uintmax_t>(-1);
            } else {
                throw filesystem_error("elib::fs::file_size", p, tmp_ec);
            }
        } else {
            ELIB_ASSERT_ALWAYS(!bool("TODO"));
            return static_cast<std::uintmax_t>(-1);
        }
    }

    ////////////////////////////////////////////////////////////////////////////
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
    file_time_type last_write_time(const path& p, std::error_code *ec)
    {
        using Clock = std::chrono::system_clock;
        
        std::error_code m_ec;
        struct ::stat st;
        detail::posix_stat(p, st, &m_ec);
        if (ec) *ec = m_ec;
            
        if (m_ec && not ec) {
            throw filesystem_error("elib::fs::last_write_time", p, m_ec);
        } 
        else if (m_ec) {
            return Clock::from_time_t(
                static_cast<std::time_t>(-1)
              );
        } else {
            return Clock::from_time_t(
                static_cast<std::time_t>(st.st_mtime)
              );
        }
    }

    ////////////////////////////////////////////////////////////////////////////
    // TODO
    void last_write_time(
        const path& p
      , file_time_type new_time
      , std::error_code *ec
      )
    {
        using Clock = std::chrono::system_clock;
        
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
        tbuf.modtime = Clock::to_time_t(new_time);
        
        if (::utime(p.c_str(), &tbuf) == -1) {
            m_ec = detail::capture_errno();
        }
        if (ec) *ec = m_ec;
            
        if (m_ec && not ec) {
            throw filesystem_error("elib::fs::last_write_time", p, m_ec);
        }
    }

    ////////////////////////////////////////////////////////////////////////////
    void permissions(
        const path& p, perms prms, permissions_options opts
      , std::error_code *ec
      )
    {
        ELIB_ASSERT(not (bool(permissions_options::add_bits & opts) 
                     && bool(permissions_options::remove_bits & opts)));
                     
        // TODO not supported
        ELIB_ASSERT(not bool(permissions_options::follow_symlinks & opts));
          
        file_status st = detail::status(p, ec);
        if (!exists(st)) {
            if (ec && *ec) { return; }
            std::error_code m_ec(
                static_cast<int>(std::errc::no_such_file_or_directory)
              , std::system_category()
              );
            throw filesystem_error("elib::fs::permissions", p, m_ec);
        }
          
        if (bool(permissions_options::add_bits & opts)) {
            prms |= st.permissions();
        }
        else if (bool(permissions_options::remove_bits & opts)) {
            prms = st.permissions() & ~prms;
        }
        if (::chmod(p.c_str(), detail::posix_convert_perms(prms)) == -1) {
            std::error_code m_ec = detail::capture_errno();
            if (ec) {
                *ec = m_ec;
                return;
            } else {
                throw filesystem_error("elib::fs::permissions", p, m_ec);
            }
        } 
        if (ec) ec->clear();
    }

    ////////////////////////////////////////////////////////////////////////////
    path read_symlink(const path& p, std::error_code *ec)
    {
        char buff[PATH_MAX + 1];
        std::error_code m_ec;
        ::ssize_t ret;
        if ((ret = ::readlink(p.c_str(), buff, PATH_MAX)) == -1) {
            m_ec = detail::capture_errno();
        } else {
            ELIB_ASSERT(ret <= PATH_MAX);
            ELIB_ASSERT(ret > 0);
            buff[ret] = 0;
        }
        if (ec) *ec = m_ec;
            
        if (m_ec && not ec) {
            throw filesystem_error("elib::fs::read_symlink", p, m_ec);
        }
        else if (m_ec) {
            return {};
        } else {
            return path(buff);
        }
    }

    ////////////////////////////////////////////////////////////////////////////
    bool remove(const path& p, std::error_code *ec)
    {
        std::error_code m_ec;
        if (::remove(p.c_str()) == -1) {
            m_ec = detail::capture_errno();
        }
        if (ec) *ec = m_ec;
            
        if (m_ec && not ec) {
            throw filesystem_error("elib::fs::remove", p, m_ec);
        }
        return !m_ec;
    }

    namespace
    {
        ////////////////////////////////////////////////////////////////////////
        std::uintmax_t remove_all_impl(
            path const & p, file_status const & st
        , std::error_code *ec)
        {
            static constexpr std::uintmax_t npos = static_cast<std::uintmax_t>(-1);
            std::uintmax_t count = 1;
            if (is_directory(st)) {
                for (directory_iterator it(p); it != directory_iterator(); ++it) {
                    const file_status fst = detail::symlink_status(it->path(), ec);
                    if (ec && *ec) {
                        return npos;
                    }
                    const std::uintmax_t other_count = 
                        detail::remove_all_impl(it->path(), fst, ec);
                    if ((ec && *ec) || other_count == npos) {
                        return npos;
                    }
                    count += other_count;
                }
            }
            const bool ret = detail::remove(p, ec);
            ELIB_ASSERT(ret); ((void)ret);
            if (ec && *ec) {
                return npos;
            
            } else {
                return count;
            }
        }
    }
    
    ////////////////////////////////////////////////////////////////////////////
    std::uintmax_t remove_all(const path& p, std::error_code *ec)
    {
        std::error_code mec;
        const file_status st = detail::symlink_status(p, &mec);
        if (not status_known(st)) {
            if (ec) {
                ELIB_ASSERT(mec);
                *ec = mec;
                return static_cast<std::uintmax_t>(-1);
            } 
            throw filesystem_error("fs::remove_all", p, mec);
        }
        
        if (exists(st)) {
            return detail::remove_all_impl(p, st, ec);
        } else {
            return 0;
        }
    }

    ////////////////////////////////////////////////////////////////////////////
    void rename(const path& from, const path& to, std::error_code *ec)
    {
        std::error_code m_ec;
        if (::rename(from.c_str(), to.c_str()) == -1) {
            m_ec = detail::capture_errno();
        }
        if (ec) *ec = m_ec;
            
        if (m_ec && not ec) {
            throw filesystem_error("elib::fs::rename", from, to, m_ec);
        }
    }
    
    ////////////////////////////////////////////////////////////////////////////
    void resize_file(const path& p, std::uintmax_t size, std::error_code *ec)
    {
        std::error_code m_ec;
        if (::truncate(p.c_str(), static_cast<long>(size)) == -1) {
            m_ec = detail::capture_errno();
        }
        if (ec) *ec = m_ec;
        
        if (m_ec && not ec) {
            throw filesystem_error("elib::fs::resize_file", p, m_ec);
        }
    }
    
    ////////////////////////////////////////////////////////////////////////////
    // TODO
    space_info space(const path& p, std::error_code *ec)
    {
        std::error_code m_ec;
        struct statvfs m_svfs;
        //if we fail but don't throw
        if (::statvfs(p.c_str(), &m_svfs) == -1)  {
            m_ec = detail::capture_errno();
        }
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
        path p("/tmp");
        std::error_code m_ec;
            
        for (auto & ep : env_paths) 
        {
            char const* ret = std::getenv(ep);
            if (ret) {
                p = ret;
                break;
            }
        }

        if (fs::is_directory(p, m_ec)) {
            if (ec) ec->clear();
            return p;
        } 

        m_ec = std::error_code(
            static_cast<int>(std::errc::no_such_file_or_directory)
          , std::system_category()
          );
        
        if (not ec) {
            throw filesystem_error("elib::fs::temp_directory_path", m_ec);
        } else {
            *ec = m_ec;
            return {};
        }
    }

    namespace 
    {
        ////////////////////////////////////////////////////////////////////////
        char to_hex(int ch) noexcept
        {
            if (ch < 10) {
                return static_cast<char>('0' + ch);
            } else {
                return static_cast<char>('a' + (ch - 10));
            }
        }
        
        ////////////////////////////////////////////////////////////////////////
        char random_hex_char()
        {
            static std::mt19937 rd { std::random_device{}() };
            static std::uniform_int_distribution<int> mrand{0, 15};
            return to_hex( mrand(rd) );
        }  
    }                                                              // namespace 

    path unique_path(const path& model, std::error_code *ec)
    {
        std::string tmp_str = model.native();
        for (auto & ch : tmp_str) {
            if (ch == '%') ch = detail::random_hex_char();
        }
        if (ec) ec->clear();
        return tmp_str;
    }                                                     // unique_path
      
}}}}                                          // namespace elib::fs::v1::detail
    
////////////////////////////////////////////////////////////////////////////////
//                      OPERATORS DEFINITION                                                    
////////////////////////////////////////////////////////////////////////////////
namespace elib { namespace fs { inline namespace v1
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
      
}}}                                                          // namespace elib