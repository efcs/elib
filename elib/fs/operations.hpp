#ifndef ELIB_OPERATIONS_HPP
#define ELIB_OPERATIONS_HPP

#include <elib/fs/filesystem.hpp>
#include <elib/fs/path.hpp>
#include <elib/fs/detail/directory_stream.hpp>

# include <system_error>
# include <iterator>
# include <stack>
# include <cstdint>


namespace elib 
{
  namespace fs
  {
    
  ////////////////////////////////////////////////////////////////////////////////
  //                enum class file_type                                                           
  ////////////////////////////////////////////////////////////////////////////////
    
    
    enum class file_type
    {
      none = 0,
      not_found = -1,
      regular = 1,
      directory = 2,
      symlink = 3,
      block = 4,
      character = 5,
      fifo = 6,
      socket = 7,
      unknown = 8
    }; // enum class file_type
    
    
  ////////////////////////////////////////////////////////////////////////////////
  //                    enum class perms                                                       
  ////////////////////////////////////////////////////////////////////////////////
    
    
    enum class perms
    {
      none = 0,
      
      owner_read = 0400,
      owner_write = 0200,
      owner_exec = 0100,
      owner_all = 0700,
      
      group_read = 040,
      group_write = 020,
      group_exec = 010,
      group_all = 070,
      
      others_read = 04,
      others_write = 02,
      others_exec = 01,
      others_all = 07,
      
      all = 0777,
      
      set_uid = 04000,
      set_gid = 02000,
      sticky_bit = 01000,
      
      mask = 07777,
      unknown = 0xFFFF,
      symlink_perms = 0x4000
      
    }; // enum class perms
    
    
  } // namespace fs
} // namespace elib


// add bitwise operators inline
# include <elib/fs/detail/perms_operators.hpp>


namespace elib
{
  namespace fs
  {
    
    
  ////////////////////////////////////////////////////////////////////////////////
  //                  class file_status                                                            
  ////////////////////////////////////////////////////////////////////////////////
    
    
    class file_status
    {
    public:
      // constructors
      explicit 
      file_status(file_type ft = file_type::none,
          perms prms = perms::unknown) noexcept
        : m_type{ft}, m_perms{prms}
      { }
      
      file_status(const file_status&) noexcept = default;
      file_status(file_status&&) noexcept = default;
      ~file_status() = default;
      
      file_status& operator=(const file_status&) noexcept = default;
      file_status& operator=(file_status&&) noexcept = default;
      
      // observers
      file_type type() const noexcept { return m_type; }
      perms permissions() const noexcept { return m_perms; }
      
      // modifiers
      void type(file_type ft) noexcept { m_type = ft; }
      void permissions(perms prms) noexcept { m_perms = prms; }
      
      //
    private:
      //
      
      file_type m_type;
      perms m_perms;
      
    }; // class file_status
    
    
  ////////////////////////////////////////////////////////////////////////////////
  //                      class directory_entry                                                     
  ////////////////////////////////////////////////////////////////////////////////
    
    
    class directory_entry
    {
    public:
    //ctor & dtor
      directory_entry() = default;
      directory_entry(const directory_entry&) = default;
      directory_entry(directory_entry&&) noexcept = default;
      
      explicit directory_entry(const fs::path& p, file_status st=file_status(),
                               file_status symlink_st=file_status())
        : m_path{p}, m_status{st}, m_symlink_status{symlink_st}
      { }
      
      ~directory_entry() = default; 
      
    // modifiers
      directory_entry& operator=(const directory_entry&) = default;
      directory_entry& operator=(directory_entry&&) noexcept = default;
      
      void assign(const fs::path& p, file_status st=file_status(),
                  file_status symlink_st=file_status())
      {
        m_path = p;
        m_status = st;
        m_symlink_status = symlink_st;
      }
      
      void replace_filename(const fs::path& p, file_status st=file_status(),
                            file_status symlink_st=file_status())
      {
        m_path.replace_filename(p);
        m_status = st;
        m_symlink_status = symlink_st;
      }
      
    // observers
      const fs::path& path() const noexcept
        { return m_path; }
        
      file_status status() const
      { return m_get_status();}
      
      file_status status(std::error_code& ec) const noexcept
      { return m_get_status(&ec); }
      
      file_status symlink_status() const
      { return m_get_symlink_status(); }
      
      file_status symlink_status(std::error_code& ec) const noexcept
      { return m_get_symlink_status(&ec); }
      
      bool operator==(const directory_entry& rhs) const noexcept
        { return m_path == rhs.m_path; }
        
      bool operator!=(const directory_entry& rhs) const noexcept
        { return m_path != rhs.m_path; }
        
      bool operator< (const directory_entry& rhs) const noexcept
        { return m_path < rhs.m_path; }
        
      bool operator<=(const directory_entry& rhs) const noexcept
        { return m_path <= rhs.m_path; }
        
      bool operator> (const directory_entry& rhs) const noexcept
        { return m_path > rhs.m_path; }
        
      bool operator>=(const directory_entry& rhs) const noexcept
        { return m_path >= rhs.m_path; }
      
      //
    private:
      //
      
      
      file_status m_get_status(std::error_code *ec=nullptr) const
      {
        if (!status_known(m_status))
        {
          if (status_known(m_symlink_status) && !is_symlink(m_symlink_status))
            m_status = m_symlink_status; 
          else
            m_status = ec ? fs::status(m_path, *ec) : fs::status(m_path);
        }
        
        return m_status;
      }
      
      file_status m_get_symlink_status(std::error_code *ec=nullptr) const
      {
        if (!status_known(m_symlink_status))
          m_symlink_status = ec ? fs::symlink_status(m_path, *ec)
                                : fs::symlink_status(m_path);
        return m_symlink_status;
      }
      
      
      
      fs::path m_path;
      mutable file_status m_status;
      mutable file_status m_symlink_status; 
  
    }; // class directory_entry
  
  
  ////////////////////////////////////////////////////////////////////////////////
  //                class directory_iterator                                                                
  ////////////////////////////////////////////////////////////////////////////////
    
    namespace detail
    {
      
      class dir_stream
      {
      public:
        dir_stream() noexcept = default;
        dir_stream(const path& root, std::error_code *ec=nullptr);
        
        dir_stream(dir_stream&&) noexcept;
        dir_stream& operator=(dir_stream&&) noexcept;
        
        dir_stream(const dir_stream&) = delete;
        dir_stream& operator=(const dir_stream&) = delete;
        
        ~dir_stream() noexcept;
        
        bool good() const noexcept
          { return m_dir_stream != nullptr; }
          
        operator bool() const noexcept
          { return this->good(); }
        
        path advance(std::error_code *ec=nullptr);
        
        void close(std::error_code *ec=nullptr);
        
        //
      private:
        //
        
        DIR *m_dir_stream{nullptr};
      
      };                                                     // class dir_stream
    
    
    }                                                       // namespace detail
    
    class directory_iterator
      : public std::iterator<std::input_iterator_tag, directory_entry>
    {
    public:
    //ctor & dtor 
      directory_iterator() noexcept
      { }
      
      explicit directory_iterator(const path& p)
      { 
        m_construct(p);
      }
      
      directory_iterator(const path& p, std::error_code& ec) noexcept
      { 
        m_construct(p, &ec);
      }
      
      directory_iterator(const directory_iterator&) = default;
      directory_iterator(directory_iterator&&) = default;
      ~directory_iterator() = default;
      
    //assignment
      directory_iterator& operator=(const directory_iterator&) = default;
      directory_iterator& operator=(directory_iterator&&) = default;
      
    // iterator access
      const directory_entry& operator*() const
        { return m_element; }
        
      const directory_entry* operator->() const
        { return &m_element; }
    
    // iterator modifiers
      directory_iterator& operator++()
        { return m_increment(); }
        
      directory_iterator operator++(int)
      { 
        directory_iterator it{*this}; 
        m_increment();
        return *this;
      }
      
      directory_iterator& increment(std::error_code& ec) noexcept
      { return m_increment(&ec); }
      
      
      bool operator==(const directory_iterator& rhs) const noexcept
      { return m_stream.get() == rhs.m_stream.get(); }
      
      //
    private:
      //
      
      void m_construct(const path& p, std::error_code *ec=nullptr);
      directory_iterator& m_increment(std::error_code *ec=nullptr);
      void m_make_end();
      
      std::shared_ptr<detail::dir_stream> m_stream{nullptr};
      path m_root_path{};
      directory_entry m_element{};
    
    };                                                 // class directory_entry
    
    
    
    // enable directory_iterator range-based for statements
    const directory_iterator& begin(const directory_iterator& iter) noexcept;
    directory_iterator end(const directory_iterator&) noexcept;
    
    
  ////////////////////////////////////////////////////////////////////////////////
  //                    class recursive_directory_iterator                                                               
  ////////////////////////////////////////////////////////////////////////////////
    
    //TODO
    class recursive_directory_iterator
      : public std::iterator<std::input_iterator_tag,  directory_entry>
    {
    public:
      // constructors and destructor
      recursive_directory_iterator() noexcept
      { }
      
      explicit recursive_directory_iterator(const path& p,
        directory_options options = directory_options::none)
      {
        m_construct(p, options);
      }

      recursive_directory_iterator(const path& p,
        directory_options options, std::error_code& ec) noexcept
      {
        m_construct(p, options, &ec);
      }
      
      recursive_directory_iterator(const path& p, std::error_code& ec) noexcept
      {
        m_construct(p, directory_options::none, &ec);
      }
      
      recursive_directory_iterator(
        const recursive_directory_iterator&) = default;
      
      recursive_directory_iterator(recursive_directory_iterator&&) = default;
      
      ~recursive_directory_iterator() = default;

      // observers
      directory_options options() const
      { return m_options; }
      
      int depth() const
      {
        // m_stack_ptr && m_stack_ptr->size() == 0 should
        // never be true
        if (m_stack_ptr) return m_stack_ptr->size() - 1;
        return 0;
      }
      
      bool recursion_pending() const
        { return m_rec; }

      // modifiers
      recursive_directory_iterator& 
        operator=(const recursive_directory_iterator&) = default;
        
      recursive_directory_iterator& 
        operator=(recursive_directory_iterator&&) = default;
        

      recursive_directory_iterator& operator++()
      { return m_increment(); }
      
      recursive_directory_iterator operator++(int)
      {
        auto cp = *this;
        m_increment();
        return cp;
      }
      
      recursive_directory_iterator& increment(std::error_code& ec)
      { return m_increment(&ec); }

      void pop()
      {
        if (!m_stack_ptr) return;
        m_element.assign("");
        if (depth() == 0)
          m_make_end();
        else
          m_stack_ptr->pop();
      }
      
      void disable_recursion_pending()
        { m_rec = false; }
      
      bool operator==(const recursive_directory_iterator& other) const
      { return m_stack_ptr == other.m_stack_ptr; }
      
      //
    private:
      //
      
      typedef std::stack<directory_iterator> stack_type;
      typedef std::shared_ptr<stack_type> stack_ptr_type;
      
      void m_construct(const path& p, directory_options opt, 
                       std::error_code *ec=nullptr);
      
      void m_make_end();
      
      recursive_directory_iterator& m_increment(std::error_code *ec=nullptr);
      
      bool m_increment_depth(std::error_code *ec);
      
      stack_ptr_type m_stack_ptr{nullptr};
      
      directory_options m_options{directory_options::none};
      
      directory_entry m_element{};
      
      bool m_rec{true};
    };                                     // class recursive_directory_iterator
    
    // enable recursive_directory_iterator range-based for statements
    const recursive_directory_iterator& 
      begin(const recursive_directory_iterator& iter) noexcept;
      
    recursive_directory_iterator 
      end(const recursive_directory_iterator&) noexcept;
  
      
  
    
  ////////////////////////////////////////////////////////////////////////////////
  //                                                                          
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
      
      path read_symlink(const path& p, std::error_code *ec=nullptr);
      
      bool remove(const path& p, std::error_code *ec=nullptr);
      
      std::intmax_t remove_all(const path& p, std::error_code *ec=nullptr);
      
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
    
    //forward
    path current_path();
    
    
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
      { return create_directory(p); }
      
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
      { return exists(status(p)); }
      
    inline bool exists(const path& p, std::error_code& ec) noexcept
      { return exists(status(p, ec)); }
    
    
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
      { return is_block_file(status(p)); }
    
    inline bool is_block_file(const path& p, std::error_code& ec) noexcept
      { return is_block_file(status(p, ec)); }
    
    
    inline bool is_character_file(file_status s) noexcept
      { return s.type() == file_type::character; }
      
    inline bool is_character_file(const path& p)
      { return is_character_file(status(p)); }
      
    inline bool is_character_file(const path& p, std::error_code& ec) noexcept
      { return is_character_file(status(p, ec)); }
    
    
    inline bool is_directory(file_status s) noexcept
      { return s.type() == file_type::directory; }
      
    inline bool is_directory(const path& p)
      { return is_directory(status(p)); }
    
    inline bool is_directory(const path& p, std::error_code& ec) noexcept
      { return is_directory(status(p, ec)); }
    
    
    inline bool is_empty(const path& p)
      { return detail::is_empty(p); }
      
    inline bool is_empty(const path& p, std::error_code& ec) noexcept
      { return detail::is_empty(p, &ec); }
    
    
    inline bool is_fifo(file_status s) noexcept
      { return s.type() == file_type::fifo; }
      
    inline bool is_fifo(const path& p)
      { return is_fifo(status(p)); }
      
    inline bool is_fifo(const path& p, std::error_code& ec) noexcept
      { return is_fifo(status(p, ec)); }
    
    inline bool is_other(file_status s) noexcept
    {
      return (exists(s) && !is_regular_file(s) && !is_directory(s) &&
      !is_symlink(s));
    }
    
    inline bool is_other(const path& p)
      { return is_other(status(p)); }
      
    inline bool is_other(const path& p, std::error_code& ec) noexcept
      { return is_other(status(p, ec)); }
    
    
    inline bool is_regular_file(file_status s) noexcept
    { return s.type() == file_type::regular; }
    
    inline bool is_regular_file(const path& p)
    { return is_regular_file(status(p)); }
    
    inline bool is_regular_file(const path& p, std::error_code& ec) noexcept
    { return is_regular_file(status(p, ec)); }
    
    
    inline bool is_socket(file_status s) noexcept
      { return s.type() == file_type::socket; }
      
    inline bool is_socket(const path& p)
      { return is_socket(status(p)); }
      
    inline bool is_socket(const path& p, std::error_code& ec) noexcept
      { return is_socket(status(p, ec)); }
    
    
    inline bool is_symlink(file_status s) noexcept
      { return s.type() == file_type::symlink; }
      
    inline bool is_symlink(const path& p)
      { return is_symlink(status(p)); }
    
    inline bool is_symlink(const path& p, std::error_code& ec) noexcept
      { return is_symlink(status(p, ec)); }
    
    
    inline file_time_type last_write_time(const path& p)
      { return detail::last_write_time(p); }
      
    inline file_time_type last_write_time(const path& p, std::error_code& ec) noexcept
      { return detail::last_write_time(p, &ec); }
    
    
    inline void last_write_time(const path& p, file_time_type new_time)
      { detail::last_write_time(p, new_time); }
      
    inline void last_write_time(const path& p, file_time_type new_time,
            std::error_code& ec) noexcept
      { detail::last_write_time(p, new_time, &ec); }
    
    
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