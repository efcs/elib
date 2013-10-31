#ifndef ELIB_OPERATIONS_HPP
#define ELIB_OPERATIONS_HPP

# include <elib/config.hpp>
# include <elib/fs/path.hpp>
# include <elib/fs/file_status.hpp>

# include <elib/assert.hpp>

# include <system_error>
# include <chrono>
# include <cstdint>


namespace elib
{
  namespace fs
  {
    
    
    namespace detail
    {
      typedef std::chrono::system_clock clock_type;
      typedef typename clock_type::time_point time_point;
      typedef typename clock_type::duration duration;
    }                                                       // namespace detail

    
    typedef detail::time_point file_time_type;

    
    struct space_info  // returned by space function
    {
      std::uintmax_t capacity;
      std::uintmax_t free; 
      std::uintmax_t available; // free space available to a non-privileged process
    };
  
    
    ////////////////////////////////////////////////////////////////////////////////
    //                   Copy options 
    ////////////////////////////////////////////////////////////////////////////////

    enum class copy_options
    {
      none = 0,
      
      // copy file 
      skip_existing = 1,
      overwrite_existing = 2,
      update_existing = 3,
      
      // copy sub-directories 
      recursive = 8,
      
      //copy symbolic links 
      copy_symlinks = 16,
      skip_symlinks = 32,
      
      // form of copy 
      directories_only = 64,
      create_symlinks = 128,
      create_hard_links = 256
      
    }; // enum class copy_options
    

  } // namespace fs
} // namespace elib 


// insert bitwise operators
# include <elib/fs/detail/copy_options_operators.hpp>


namespace elib
{
  namespace fs
  {
  
    
  ////////////////////////////////////////////////////////////////////////////////
  //                           DETAIL::OPERATIONS                                     
  ////////////////////////////////////////////////////////////////////////////////
    
    
    // operations handling is similar to the boost version
    // both except && no-except function signatures call a wrapper
    namespace detail
    {
    
      path canonical(const path& p, const path& base, 
                     std::error_code *ec=nullptr);
    
      void copy(const path& from, const path& to, copy_options opt, 
                std::error_code *ec=nullptr);
    
      bool copy_file(const path& from, const path& to, 
                     std::error_code *ec=nullptr);
      
      bool copy_file(const path& from, const path& to, copy_options option,
                     std::error_code *ec=nullptr);
    
      void copy_symlink(const path& existing_symlink, const path& new_symlink,
                        std::error_code *ec=nullptr);
    
      bool create_directories(const path& p, std::error_code *ec=nullptr);
    
      bool create_directory(const path& p, std::error_code *ec=nullptr);
    
      void create_directory(const path& p, const path& attributes, 
              std::error_code *ec=nullptr);
    
      void create_directory_symlink(const path& to, const path& new_symlink,
              std::error_code *ec=nullptr);
      
      void create_hard_link(const path& to, const path& new_hard_link,
              std::error_code *ec=nullptr);
          
      void create_symlink(const path& to, const path& new_symlink,
            std::error_code *ec=nullptr);
      
      path current_path(std::error_code *ec=nullptr); 
      void current_path(const path& p, std::error_code *ec=nullptr);
      
      bool equivalent(const path& p1, const path& p2, 
              std::error_code *ec=nullptr);
      
      std::uintmax_t file_size(const path& p, std::error_code *ec=nullptr);
      
      std::uintmax_t hard_link_count(const path& p, std::error_code *ec=nullptr);
      
      bool is_empty(const path& p, std::error_code *ec=nullptr);
      
      file_time_type last_write_time(const path& p, std::error_code *ec=nullptr);
      
      void last_write_time(const path& p, file_time_type new_time,
              std::error_code *ec=nullptr);
      
      void permissions(const path& p,  perms prms,  std::error_code *ec=nullptr);
      
      path read_symlink(const path& p, std::error_code *ec=nullptr);
      
      bool remove(const path& p, std::error_code *ec=nullptr);
      
      std::uintmax_t remove_all(const path& p, std::error_code *ec=nullptr);
      
      void rename(const path& from, const path& to, std::error_code *ec=nullptr);
      
      void resize_file(const path& p, uintmax_t size, std::error_code *ec=nullptr);
      
      space_info space(const path& p, std::error_code *ec=nullptr);
      
      file_status status(const path& p, std::error_code *ec=nullptr);
      
      file_status symlink_status(const path& p, std::error_code *ec=nullptr);
      
      path system_complete(const path& p, std::error_code *ec=nullptr);
      
      path temp_directory_path(std::error_code *ec=nullptr);
      
      path unique_path(const path& model, std::error_code *ec=nullptr);
      
      
    } // namespace detail 
    
    
  ////////////////////////////////////////////////////////////////////////////////
  //                       OPERATIONS                                              
  ////////////////////////////////////////////////////////////////////////////////
    
    // forward declarations
    path current_path();
    bool status_known(file_status s) noexcept;
    
    
    path absolute(const path& p, const path& base=current_path());
    
    inline path canonical(const path& p, const path& base = current_path())
      { return detail::canonical(p, base); }
      
    inline path canonical(const path& p, std::error_code& ec)
      { return detail::canonical(p, current_path(), &ec); }
      
    inline path canonical(const path& p, const path& base, std::error_code& ec)
      { return detail::canonical(p, base, &ec); }
    
    
    inline void copy(const path& from, const path& to)
      { detail::copy(from, to, copy_options::none); }
      
    inline void copy(const path& from, const path& to, std::error_code& ec) noexcept
      { detail::copy(from, to, copy_options::none, &ec); }
      
    inline void copy(const path& from, const path& to, copy_options option)
      { detail::copy(from, to, option); }
      
    inline void copy(const path& from, const path& to, copy_options option, 
                     std::error_code& ec) noexcept
      { detail::copy(from, to, option, &ec); }
    
    
    inline bool copy_file(const path& from, const path& to)
      { return detail::copy_file(from, to); }
      
    inline bool copy_file(const path& from, const path& to, 
            std::error_code& ec) noexcept
      { return detail::copy_file(from, to, &ec); }
          
          
    inline bool copy_file(const path& from, const path& to, copy_options option)
      { return detail::copy_file(from, to, option); }
      
    inline bool copy_file(const path& from, const path& to, copy_options option,
              std::error_code& ec) noexcept
      { return detail::copy_file(from, to, option, &ec); }
    
    
    inline void copy_symlink(const path& existing_symlink, const path& new_symlink)
      { detail::copy_symlink(existing_symlink, new_symlink); }
      
    inline void copy_symlink(const path& existing_symlink, const path& new_symlink,
              std::error_code& ec) noexcept
      { detail::copy_symlink(existing_symlink, new_symlink, &ec); }
    
    
    inline bool create_directories(const path& p)
      { return detail::create_directories(p); }
      
    inline bool create_directories(const path& p, std::error_code& ec) noexcept
      { return detail::create_directories(p, &ec); }
    
    
    inline bool create_directory(const path& p)
      { return detail::create_directory(p); }
      
    inline bool create_directory(const path& p, std::error_code& ec) noexcept
      { return detail::create_directory(p, &ec); }
    
    
    inline void create_directory(const path& p, const path& attributes)
      { detail::create_directory(p, attributes); }
      
    inline void create_directory(const path& p, const path& attributes, 
            std::error_code& ec) noexcept
      { detail::create_directory(p, attributes, &ec); }
    
    
    inline void create_directory_symlink(const path& to, const path& new_symlink)
      { detail::create_directory_symlink(to, new_symlink); }
      
    inline void create_directory_symlink(const path& to, const path& new_symlink,
            std::error_code& ec) noexcept
      { detail::create_directory_symlink(to, new_symlink, &ec); }
    
    
    inline void create_hard_link(const path& to, const path& new_hard_link)
      { detail::create_hard_link(to, new_hard_link); }
      
    inline void create_hard_link(const path& to, const path& new_hard_link,
            std::error_code& ec) noexcept
      { detail::create_hard_link(to, new_hard_link, &ec); }
        
    inline void create_symlink(const path& to, const path& new_symlink)
      { detail::create_symlink(to, new_symlink); }
      
    inline void create_symlink(const path& to, const path& new_symlink,
          std::error_code& ec) noexcept
      { detail::create_symlink(to, new_symlink, &ec); }
    
    
    inline path current_path()
      { return detail::current_path(); }
      
    inline path current_path(std::error_code& ec)
      { return detail::current_path(&ec); }
      
      
    inline void current_path(const path& p)
      { detail::current_path(p); }

    inline void current_path(const path& p, std::error_code& ec) noexcept
      { detail::current_path(p, &ec); }
    
    inline bool exists(file_status s) noexcept
      { return status_known(s) && s.type() != file_type::not_found; }
      
    inline bool exists(const path& p)
      { return exists(detail::status(p)); }
      
    inline bool exists(const path& p, std::error_code& ec) noexcept
      { return exists(detail::status(p, &ec)); }
    
    
    inline bool equivalent(const path& p1, const path& p2)
      { return detail::equivalent(p1, p2); }
      
    inline bool equivalent(const path& p1, const path& p2, 
            std::error_code& ec) noexcept
      { return detail::equivalent(p1, p2, &ec); }
    
    
    inline std::uintmax_t file_size(const path& p)
      { return detail::file_size(p); }
      
    inline std::uintmax_t file_size(const path& p, std::error_code& ec) noexcept
      { return detail::file_size(p, &ec); }
    
    
    inline std::uintmax_t hard_link_count(const path& p)
      { return detail::hard_link_count(p); }
      
    inline std::uintmax_t hard_link_count(const path& p, std::error_code& ec) noexcept
      { return detail::hard_link_count(p, &ec); }
    
    
    inline bool is_block_file(file_status s) noexcept
      { return s.type() == file_type::block; }
      
    inline bool is_block_file(const path& p)
      { return is_block_file(detail::status(p)); }
    
    inline bool is_block_file(const path& p, std::error_code& ec) noexcept
      { return is_block_file(detail::status(p, &ec)); }
    
    
    inline bool is_character_file(file_status s) noexcept
      { return s.type() == file_type::character; }
      
    inline bool is_character_file(const path& p)
      { return is_character_file(detail::status(p)); }
      
    inline bool is_character_file(const path& p, std::error_code& ec) noexcept
      { return is_character_file(detail::status(p, &ec)); }
    
    
    inline bool is_regular_file(file_status s) noexcept
      { return s.type() == file_type::regular; }
    
    inline bool is_regular_file(const path& p)
      { return is_regular_file(detail::status(p)); }
    
    inline bool is_regular_file(const path& p, std::error_code& ec) noexcept
      { return is_regular_file(detail::status(p, &ec)); }
    
    
    inline bool is_directory(file_status s) noexcept
      { return s.type() == file_type::directory; }
      
    inline bool is_directory(const path& p)
      { return is_directory(detail::status(p)); }
    
    inline bool is_directory(const path& p, std::error_code& ec) noexcept
      { return is_directory(detail::status(p, &ec)); }
    
    
    inline bool is_empty(const path& p)
      { return detail::is_empty(p); }
      
    inline bool is_empty(const path& p, std::error_code& ec) noexcept
      { return detail::is_empty(p, &ec); }
    
    
    inline bool is_fifo(file_status s) noexcept
      { return s.type() == file_type::fifo; }
      
    inline bool is_fifo(const path& p)
      { return is_fifo(detail::status(p)); }
      
    inline bool is_fifo(const path& p, std::error_code& ec) noexcept
      { return is_fifo(detail::status(p, &ec)); }
    
    
     inline bool is_socket(file_status s) noexcept
      { return s.type() == file_type::socket; }
      
    inline bool is_socket(const path& p)
      { return is_socket(detail::status(p)); }
      
    inline bool is_socket(const path& p, std::error_code& ec) noexcept
      { return is_socket(detail::status(p, &ec)); }
    
    
    inline bool is_symlink(file_status s) noexcept
      { return s.type() == file_type::symlink; }
      
    inline bool is_symlink(const path& p)
      { return is_symlink(detail::symlink_status(p)); }
    
    inline bool is_symlink(const path& p, std::error_code& ec) noexcept
      { return is_symlink(detail::symlink_status(p, &ec)); }
    
    
    inline bool is_other(file_status s) noexcept
    {
      return (exists(s) && !is_regular_file(s) && !is_directory(s) &&
      !is_symlink(s));
    }
    
    inline bool is_other(const path& p)
      { return is_other(detail::status(p)); }
      
    inline bool is_other(const path& p, std::error_code& ec) noexcept
      { return is_other(detail::status(p, &ec)); }
    
    
    inline file_time_type last_write_time(const path& p)
      { return detail::last_write_time(p); }
      
    inline file_time_type last_write_time(const path& p, std::error_code& ec) noexcept
      { return detail::last_write_time(p, &ec); }
    
    
    inline void last_write_time(const path& p, file_time_type new_time)
      { detail::last_write_time(p, new_time); }
      
    inline void last_write_time(const path& p, file_time_type new_time,
            std::error_code& ec) noexcept
      { detail::last_write_time(p, new_time, &ec); }
    
    inline void permissions(const path& p, perms prms)
      { detail::permissions(p, prms); }
      
    inline void permissions(const path& p,  perms prms,  std::error_code& ec) noexcept
      { detail::permissions(p, prms, &ec); }
    
    inline path read_symlink(const path& p)
      { return detail::read_symlink(p); }
      
    inline path read_symlink(const path& p, std::error_code& ec)
      { return detail::read_symlink(p, &ec); }
    
    
    inline bool remove(const path& p)
      { return detail::remove(p); }
      
    inline bool remove(const path& p, std::error_code& ec) noexcept
      { return detail::remove(p, &ec); }
    
    
    inline std::uintmax_t remove_all(const path& p)
      { return detail::remove_all(p); }
      
    inline std::uintmax_t remove_all(const path& p, std::error_code& ec) noexcept
      { return detail::remove_all(p, &ec); }
    
    
    inline void rename(const path& from, const path& to)
      { detail::rename(from, to); }
      
    inline void rename(const path& from, const path& to, std::error_code& ec) noexcept
      { detail::rename(from, to, &ec); }
    
    
    inline void resize_file(const path& p, uintmax_t size)
      { detail::resize_file(p, size); } 
      
    inline void resize_file(const path& p, uintmax_t size, std::error_code& ec) noexcept
      { detail::resize_file(p, size, &ec); }
    
    
    inline space_info space(const path& p)
      { return detail::space(p); }
      
    inline space_info space(const path& p, std::error_code& ec) noexcept
      { return detail::space(p, &ec); }
    
    inline file_status status(const path& p)
      { return detail::status(p); }
      
    inline file_status status(const path& p, std::error_code& ec) noexcept
      { return detail::status(p, &ec); }
    
    
    inline bool status_known(file_status s) noexcept
      { return s.type() != file_type::none; }
    
    
    inline file_status symlink_status(const path& p)
      { return detail::symlink_status(p); }
    
    inline file_status symlink_status(const path& p, std::error_code& ec) noexcept
      { return detail::symlink_status(p, &ec); }
    
    
    inline path system_complete(const path& p)
      { return detail::system_complete(p); }
      
    inline path system_complete(const path& p, std::error_code& ec)
      { return detail::system_complete(p, &ec); } 
    
    
    inline path temp_directory_path()
      { return detail::temp_directory_path(); }
      
    inline path temp_directory_path(std::error_code& ec)
      { return detail::temp_directory_path(&ec); }
    
    
    inline path unique_path(const path& model="%%%%-%%%%-%%%%-%%%%")
      { return detail::unique_path(model); }
      
    inline path unique_path(const path& model, std::error_code& ec)
      { return detail::unique_path(model, &ec); }

    
  } // namespace fs
} //namespace elib
#endif /* ELIB_OPERATIONS_HPP */
