#include <elib/fs/operations.hpp>
#include <elib/fs/filesystem_error.hpp>
#include <elib/debug/assert.hpp>

#include <memory>
#include <cstdlib>
#include <climits>

#include <unistd.h>
#include <utime.h>
#include <sys/stat.h>
#include <sys/statvfs.h>

namespace elib
{
  namespace fs
  {
    namespace detail 
    {
      
      // helper typedefs for interfacing with path strings
      typedef typename path::value_type value_type;
      typedef typename path::string_type string_type;
      
      
      ////////////////////////////////////////////////////////////////////////////////
      //                       POSIX HELPERS                                                 
      ////////////////////////////////////////////////////////////////////////////////
      
      // set the permissions as described in stat
      perms posix_get_perms(const struct stat& st) noexcept
      {
        perms pmask = perms::none;
        const mode_t& mode = st.st_mode;
        if (S_IRUSR & mode)
          pmask |= perms::owner_read;
        if (S_IWUSR & mode)
          pmask |= perms::owner_write;
        if (S_IXUSR & mode)
          pmask |= perms::owner_exec;
        if (S_IRGRP & mode)
          pmask |= perms::group_read;
        if (S_IWGRP & mode)
          pmask |= perms::group_write;
        if (S_IXGRP & mode)
          pmask |= perms::group_exec;
        if (S_IROTH & mode)
          pmask |= perms::others_read;
        if (S_IWOTH & mode)
          pmask |= perms::others_write;
        if (S_IXOTH & mode)
          pmask |= perms::others_exec;
        if (S_ISUID & mode)
          pmask |= perms::set_uid;
        if (S_ISGID & mode)
          pmask |= perms::set_gid;
        if (S_ISVTX & mode)
          pmask |= perms::sticky_bit;
        
        return pmask;
      }
      
      file_status posix_stat(const path& p, struct stat& path_stat,
                      std::error_code* ec)
      {
        file_status fs_tmp{};
        
        detail::clear_error(ec);
        errno = 0;
        if (stat(p.c_str(), &path_stat) == -1) 
        {
          auto m_ec = detail::handle_errno();
          if (m_ec.value() == ENOENT || m_ec.value() == ENOTDIR)
            fs_tmp = file_status(file_type::not_found);
          else
            fs_tmp = file_status(file_type::none);
          
          if (ec) *ec = m_ec;
          if (!ec && fs_tmp.type() == file_type::none)
            throw filesystem_error("elib::fs::status", p, m_ec);
          return fs_tmp;
        }
        
        const mode_t& mode = path_stat.st_mode;
        if (S_ISREG(mode))
          fs_tmp.type(file_type::regular);
        else if (S_ISDIR(mode))
          fs_tmp.type(file_type::directory);
        else if (S_ISBLK(mode))
          fs_tmp.type(file_type::block);
        else if (S_ISCHR(mode))
          fs_tmp.type(file_type::character);
        else if (S_ISFIFO(mode))
          fs_tmp.type(file_type::fifo);
        else if (S_ISSOCK(mode))
          fs_tmp.type(file_type::socket);
        else
          fs_tmp.type(file_type::unknown);
        
        fs_tmp.permissions(detail::posix_get_perms(path_stat));
        return fs_tmp;
      }
                 
                 
      file_status posix_lstat(const path& p, struct stat& path_stat,
                      std::error_code* ec)
      {
        file_status fs_tmp{};
        
        detail::clear_error(ec);
        errno = 0;
        
        if (lstat(p.c_str(), &path_stat) == -1) 
        {
          auto m_ec = detail::handle_errno();
          if (m_ec.value() == ENOENT || m_ec.value() == ENOTDIR)
            fs_tmp = file_status(file_type::not_found);
          else
            fs_tmp = file_status(file_type::none);
          if (ec) *ec = m_ec;
          if (!ec && fs_tmp.type() == file_type::none)
            throw filesystem_error("elib::fs::status", p, m_ec);
          return fs_tmp;
        }
        
        const mode_t& mode = path_stat.st_mode;
        if (S_ISLNK(mode))
          fs_tmp.type(file_type::symlink);
        else if (S_ISREG(mode))
          fs_tmp.type(file_type::regular);
        else if (S_ISDIR(mode))
          fs_tmp.type(file_type::directory);
        else if (S_ISBLK(mode))
          fs_tmp.type(file_type::block);
        else if (S_ISCHR(mode))
          fs_tmp.type(file_type::character);
        else if (S_ISFIFO(mode))
          fs_tmp.type(file_type::fifo);
        else if (S_ISSOCK(mode))
          fs_tmp.type(file_type::socket);
        else
          fs_tmp.type(file_type::unknown);
        
        // TODO symbolic link
        fs_tmp.permissions(detail::posix_get_perms(path_stat));
        return fs_tmp;
      }
      
      bool posix_statvfs(const path& p, struct statvfs& sv, 
                         std::error_code *ec)
      {
        detail::clear_error(ec);
        errno = 0;
        
        if (statvfs(p.c_str(), &sv) == -1) 
        {
          detail::handle_and_throw_errno("elib::fs::posix_statvfs", p, ec);
          return false; // if we didn't throw
        }
        return true;
      }
      
      path posix_realpath(const path& p, 
                      std::error_code *ec)
      {
        detail::clear_error(ec);
        errno = 0;
        char buff[PATH_MAX];
        char *ret = realpath(p.c_str(), buff);
        if (! ret) {
          auto m_ec = detail::handle_errno();
          if (!ec) 
            throw filesystem_error("elib::fs::posix_realpath", p, m_ec);
          //else
          *ec = m_ec;
          return path{};
        }
        
        return path{buff};
      }
      
      string_type posix_getenv(const string_type& s, std::error_code *ec)
      {
        detail::clear_error(ec);
        errno = 0;
        char *ret = getenv(s.c_str());
        if (!ret)
          detail::handle_and_throw_errno("elib::fs::posix_getenv", ec);
        return string_type{ret};
      }
      
      string_type posix_getcwd(std::error_code *ec)
      {
        detail::clear_error(ec);
        errno = 0;
        auto size = pathconf(".", _PC_PATH_MAX);
        std::unique_ptr<char[]> buff{new char[size]};
        char* ret = ::getcwd(buff.get(), static_cast<size_t>(size));
        if (ret == nullptr) 
        {
          detail::handle_and_throw_errno("elib::fs::posix_getcwd", ec);
          return string_type{};
        }
        return string_type{buff.get()};
      }
      
      bool posix_chdir(const string_type& s, std::error_code *ec)
      {
        detail::clear_error(ec);
        errno = 0;
        if (::chdir(s.c_str()) == -1) {
          detail::handle_and_throw_errno("elib::fs::detail::posix_chdir", 
              path{s}, ec);
          return false;
        }
        return true;
      }
      
      
      bool posix_utime(const string_type& s, const struct utimbuf& ut,
              std::error_code *ec)
      {
        detail::clear_error(ec);
        errno = 0;
        if (::utime(s.c_str(), &ut) == -1) {
          detail::handle_and_throw_errno("elib::fs::posix_utime", path{s}, ec);
          return false;
        }
        return true;
      }
      
      string_type posix_readlink(const string_type& s, std::error_code *ec)
      {
        detail::clear_error(ec);
        errno = 0;
        char buff[PATH_MAX];
        if (::readlink(s.c_str(), buff, PATH_MAX) == -1)
        {
          detail::handle_and_throw_errno("elib::fs::posix_readlink", path{s},
                                         ec);
          return string_type{};
        }
        return string_type{buff};
      }
      
      
    ////////////////////////////////////////////////////////////////////////////////
    //                           DETAIL::MISC                                           
    ////////////////////////////////////////////////////////////////////////////////
      
      inline int status_failed_error(file_status fst, std::error_code *ec)
      {
        if (status_known(fst)) return 0;
        if (ec)
        {
          ELIB_ASSERT(ec->value() != 0);
          return ec->value();
        }
        return detail::errc_cast(std::errc::no_such_file_or_directory);
      }
      
      inline bool handle_and_throw_status_error(file_status fst,
                  const string_type& msg, std::error_code* ec)
      {
        if (status_failed_error(fst, ec) != 0) {
          detail::handle_and_throw_error(status_failed_error(fst, ec),
                  msg, ec);
          return true;
        }
        return false;
      }
      
      inline bool handle_and_throw_status_error(file_status fst,
                      const string_type& msg, const path& p1,
                      std::error_code* ec)
      {
        if (status_failed_error(fst, ec) != 0) {
          detail::handle_and_throw_error(status_failed_error(fst, ec),
                                         msg, p1, ec);
          return true;
        }
        return false;
      }
      
      inline bool handle_and_throw_status_error(file_status fst,
                      const string_type& msg, const path& p1,
                      const path& p2, std::error_code* ec)
      {
        if (status_failed_error(fst, ec) != 0) {
          detail::handle_and_throw_error(status_failed_error(fst, ec),
                                         msg, p1, p2, ec);
          return true;
        }
        return false;
      }
      
      
    } // namespace detail 
  
  
    ////////////////////////////////////////////////////////////////////////////////
    //                        OTHER DEFINITIONS                                         
    ////////////////////////////////////////////////////////////////////////////////
    
    
    namespace detail
    {
      ////////////////////////////////////////////////////////////////////////////////
      //                        DETAIL::OPERATORS DEFINITIONS                                                        
      ////////////////////////////////////////////////////////////////////////////////
      
      path canonical(const path& p, const path& base, 
                     std::error_code *ec)
      {
        detail::clear_error(ec);
        auto ap = absolute(p, base);
        // on failure posix_read_path will throw or
        // return str == "". no need to check further
        return detail::posix_realpath(ap, ec);
      }
      
      void copy(const path& from, const path& to, 
                std::error_code *ec); //TODO
      
      void copy_file(const path& from, const path& to, 
                     std::error_code *ec); //TODO
      
      void copy_file(const path& from, const path& to, copy_options option,
                     std::error_code *ec); //TODO
      
      void copy_symlink(const path& existing_symlink, const path& new_symlink,
                        std::error_code *ec); //TODO
      
      bool create_directories(const path& p, std::error_code *ec);
      
      bool create_directory(const path& p, std::error_code *ec);
      
      void create_directory(const path& p, const path& attributes, 
                            std::error_code *ec);
      
      void create_directory_symlink(const path& to, const path& new_symlink,
                                    std::error_code *ec);
      
      void create_hard_link(const path& to, const path& new_hard_link,
                            std::error_code *ec);
      
      void create_symlink(const path& to, const path& new_symlink,
                          std::error_code *ec);
      
      
      path current_path(std::error_code *ec)
      {
        return path{detail::posix_getcwd(ec)};
      }
      
      void current_path(const path& p, std::error_code *ec)
      {
        detail::posix_chdir(p.native(), ec);
      }
      
      bool equivalent(const path& p1, const path& p2, 
                      std::error_code *ec)
      {
        detail::clear_error(ec);
        
        struct stat st1, st2;
        file_status fs1, fs2;
        
        fs1 = detail::posix_stat(p1, st1, ec);
        fs2 = detail::posix_stat(p2, st2, ec);
        
        if ((!exists(fs1) && !exists(fs2)) ||
            (is_other(fs1) && is_other(fs2)))
        {
          detail::handle_and_throw_error(std::errc::no_such_file_or_directory,
                      "elib::fs::equivalent", p1, p2, ec);
          return false;
        }
        if (!exists(fs1) || !exists(fs2)) return false;
        return (st1.st_ino == st2.st_ino && st1.st_dev == st2.st_dev);
      }
      
      std::uintmax_t file_size(const path& p, std::error_code *ec)
      {
        detail::clear_error(ec);
        struct stat st;
        auto fst = detail::posix_stat(p, st, ec);
        if (!status_known(fst)) {
          if (ec)
            detail::handle_and_throw_error(static_cast<std::errc>(ec->value()),
                        "elib::fs::file_size", p, ec);
          else
            detail::handle_and_throw_error(std::errc::bad_file_descriptor,
                    "elib::fs::file_size", p, ec);
          return static_cast<std::uintmax_t>(-1);
        }
        if (!exists(fst) || !is_regular_file(fst))
        {
          detail::handle_and_throw_error(std::errc::bad_file_descriptor,
                  "elib::fs::file_size", p, ec);
          return static_cast<std::uintmax_t>(-1);
        }
        return static_cast<uintmax_t>(st.st_size);
      }
      
      std::uintmax_t hard_link_count(const path& p, std::error_code *ec)
      {
        detail::clear_error(ec);
        struct stat st;
        auto fst = detail::posix_stat(p, st, ec);
        if (!status_known(fst))
        {
          int xerrno;
          ec ? xerrno = ec->value() 
             : xerrno = detail::errc_cast(std::errc::no_such_file_or_directory);
          ELIB_ASSERT(xerrno != 0);
          detail::handle_and_throw_error(xerrno, "elib::fs::hard_link_count",
                      p, ec);
          return static_cast<std::uintmax_t>(-1);
        }
        return static_cast<std::uintmax_t>(st.st_nlink);
      }
      
      bool is_empty(const path& p, std::error_code *ec);
      
      file_time_type last_write_time(const path& p, std::error_code *ec)
      {
        detail::clear_error(ec);
        struct stat st;
        auto fst = detail::posix_stat(p, st, ec);
        if (!status_known(fst))
        {
          int xerrno;
          ec ? xerrno = ec->value()
             : xerrno = detail::errc_cast(std::errc::no_such_file_or_directory);
          detail::handle_and_throw_error(xerrno, "elib::fs::last_write_time",
                  p, ec);
          return file_time_type::max();
        }
        
        if (!exists(fst)) {
          detail::handle_and_throw_error(std::errc::no_such_file_or_directory,
                  "elib::fs::last_write_time", p, ec);
          return file_time_type::max();
        }
        
        return detail::from_time_t(st.st_mtime);
      }
      
      void last_write_time(const path& p, file_time_type new_time,
                           std::error_code *ec)
      {
        detail::clear_error(ec);
        struct stat st;
        auto fst = detail::posix_stat(p, st, ec);
        if (detail::handle_and_throw_status_error(fst, 
              "elib::fs::last_write_time", p, ec))
        {
          return;
        }
        
        if (!exists(fst)) {
          detail::handle_and_throw_error(std::errc::no_such_file_or_directory,
                      "elib::fs::last_write_time", p, ec);
          return;
        }
          
        struct utimbuf tbuff;
        tbuff.actime = st.st_atime;
        tbuff.modtime = detail::to_time_t(new_time);
        
        detail::posix_utime(p.native(), tbuff, ec);
        
      }
      
      path read_symlink(const path& p, std::error_code *ec)
      {
        detail::clear_error(ec);
        return path{detail::posix_readlink(p.native(), ec)};
      }
      
      bool remove(const path& p, std::error_code *ec);
      
      std::intmax_t remove_all(const path& p, std::error_code *ec);
      
      void rename(const path& from, const path& to, std::error_code *ec);
      
      void resize_file(const path& p, uintmax_t size, std::error_code *ec);
      
      space_info space(const path& p, std::error_code *ec)
      {
        struct statvfs m_svfs;
        //if we fail but don't throw
        if (! detail::posix_statvfs(p, m_svfs, ec)) 
        {
          constexpr std::uintmax_t size_npos = static_cast<std::uintmax_t>(-1);
          return space_info{size_npos, size_npos, size_npos};
        }
        
        space_info si;
        si.capacity =   m_svfs.f_blocks * m_svfs.f_frsize;
        si.free =       m_svfs.f_bfree  * m_svfs.f_frsize;
        si.available =  m_svfs.f_bavail * m_svfs.f_frsize;
        return si;
      }
      
      file_status status(const path& p, std::error_code *ec)
      {
        struct stat m_stat;
        return detail::posix_stat(p, m_stat, ec);
      }
      
      file_status symlink_status(const path& p, std::error_code *ec)
      {
        struct stat m_stat;
        return detail::posix_lstat(p, m_stat, ec);
      }
      
      path system_complete(const path& p, std::error_code *ec)
      {
        detail::clear_error(ec);
        return absolute(p, current_path());
      }
      
      path temp_directory_path(std::error_code *ec)
      {
        const char* env_paths[] = {"TMPDIR", "TMP", "TEMP", "TEMPDIR"};
        path p{};
        std::error_code m_ec;
        detail::clear_error(ec);
        for (auto& ep : env_paths) 
        {
          p = path{detail::posix_getenv(ep, &m_ec)};
          if (!m_ec && is_directory(p, m_ec))
            return p;
        }
        
        if (is_directory(p, m_ec))
          return path{"/tmp"};
        
        m_ec = std::make_error_code(std::errc::no_such_file_or_directory);
        if (!ec)
          throw filesystem_error("elib::fs::temp_directory_path", m_ec);
        //else
        *ec = m_ec;
        return path{};
      }
      
      path unique_path(const path& model, std::error_code *ec);
      
      
    } // namespace detail
    
    
    ////////////////////////////////////////////////////////////////////////////////
    //                      OPERATORS DEFINITION                                                    
    ////////////////////////////////////////////////////////////////////////////////
  
    //currently only absolute is not forwarded through detail
    path absolute(const path& p, const path& base)
    {
      if (p.has_root_name())
      {
        if (p.has_root_directory()) return p;
        //else
        return (p.root_name() / absolute(base).root_directory()
            / absolute(base).relative_path() / p.relative_path());
      }
      //else
      if (p.has_root_directory()) return absolute(base).root_name() / p;
      else return absolute(base) / p;
    }
    
  } // namespace fs
} // namespace elib 