#ifndef ELIB_FS_DIRECTORY_ITERATOR_HPP
#define ELIB_FS_DIRECTORY_ITERATOR_HPP

# include <elib/fs/config.hpp>
# include <elib/fs/path.hpp>
# include <elib/fs/file_status.hpp>
# include <elib/fs/operations.hpp>

# include <memory>
# include <iterator>
# include <stack>
# include <system_error>

# include <dirent.h>

namespace elib { namespace fs
{

    ////////////////////////////////////////////////////////////////////////////
    enum class directory_options
    {
        none,
        follow_directory_symlink,
        skip_permission_denied
    };
    
    ////////////////////////////////////////////////////////////////////////////
    class directory_entry
    {
    public:
        //ctor & dtor
        explicit directory_entry(
            const fs::path & p
          , file_status st=file_status()
          , file_status symlink_st=file_status()
          )
            : m_path{p}, m_status{st}, m_symlink_status{symlink_st}
        {}
        
        directory_entry() = default;
        directory_entry(const directory_entry&) = default;
        directory_entry(directory_entry&&) noexcept = default;
        directory_entry& operator=(const directory_entry&) = default;
        directory_entry& operator=(directory_entry&&) noexcept = default;
        ~directory_entry() = default; 
        
        ////////////////////////////////////////////////////////////////////////
        void assign(
            const fs::path & p
          , file_status st=file_status()
          , file_status symlink_st=file_status()
          )
        {
            m_path = p;
            m_status = st;
            m_symlink_status = symlink_st;
        }
        
        ////////////////////////////////////////////////////////////////////////
        void replace_filename(
            const fs::path& p
          , file_status st = file_status()
          , file_status symlink_st = file_status()
          )
        {
            m_path.replace_filename(p);
            m_status = st;
            m_symlink_status = symlink_st;
        }
        
        ////////////////////////////////////////////////////////////////////////
        fs::path const & path() const noexcept
        { return m_path; }
         
        ////////////////////////////////////////////////////////////////////////
        file_status status() const
        { return m_get_status();}
        
        file_status status(std::error_code & ec) const noexcept
        { return m_get_status(&ec); }
        
        ////////////////////////////////////////////////////////////////////////
        file_status symlink_status() const
        { return m_get_symlink_status(); }
        
        file_status symlink_status(std::error_code& ec) const noexcept
        { return m_get_symlink_status(&ec); }
        
    private:
        friend bool operator==(directory_entry const &, directory_entry const &);
        friend bool operator< (directory_entry const &, directory_entry const &);
        
    private:
        ////////////////////////////////////////////////////////////////////////
        // These don't need to be inline,  but they are for now.
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
        
        ////////////////////////////////////////////////////////////////////////
        //
        file_status m_get_symlink_status(std::error_code *ec=nullptr) const
        {
            if (!status_known(m_symlink_status))
            m_symlink_status = ec ? fs::symlink_status(m_path, *ec)
                                    : fs::symlink_status(m_path);
            return m_symlink_status;
        }
        
        ////////////////////////////////////////////////////////////////////////
        //
        fs::path m_path {};
        
        // Although these are not atomic to adjust, mutability allows
        // for file status caching as suggested in the standard
        // documentation
        mutable file_status m_status {};
        mutable file_status m_symlink_status {}; 
  
    }; // class directory_entry
      
      
    ////////////////////////////////////////////////////////////////////////////
    inline bool operator==(directory_entry const & lhs, directory_entry const & rhs)
    {
        return lhs.m_path == rhs.m_path;
    }
    
    ////////////////////////////////////////////////////////////////////////////
    inline bool operator!=(directory_entry const & lhs, directory_entry const & rhs)
    {
        return !(lhs == rhs);
    }
    
    ////////////////////////////////////////////////////////////////////////////
    inline bool operator<(directory_entry const & lhs, directory_entry const & rhs)
    {
        return (lhs.m_path < rhs.m_path);
    }
    
    ////////////////////////////////////////////////////////////////////////////
    inline bool operator>(directory_entry const & lhs, directory_entry const & rhs)
    {
        return (rhs < lhs);
    }
    
    ////////////////////////////////////////////////////////////////////////////
    inline bool operator<=(directory_entry const & lhs, directory_entry const & rhs)
    {
        return !(rhs < lhs);
    }
    
    ////////////////////////////////////////////////////////////////////////////
    inline bool operator>=(directory_entry const & lhs, directory_entry const & rhs)
    {
        return !(lhs < rhs);
    }
      
    namespace detail
    {
        ////////////////////////////////////////////////////////////////////////
        // underlying POSIX implementation for directory_iterator
        class dir_stream
        {
        public:
            dir_stream() noexcept = default;
            dir_stream(const path& root, std::error_code *ec=nullptr);
            
            dir_stream(dir_stream&&) noexcept;
            dir_stream& operator=(dir_stream&&) noexcept;
            
            // NO COPYING
            dir_stream(const dir_stream&) = delete;
            dir_stream& operator=(const dir_stream&) = delete;
            
            ~dir_stream() noexcept;
            
            bool good() const noexcept
            { return m_dir_stream != nullptr; }
            
            operator bool() const noexcept
            { return this->good(); }
            
            path advance(std::error_code *ec=nullptr);
            
            void close(std::error_code *ec=nullptr);
            
        private:
            DIR *m_dir_stream{nullptr};
        };                                             
    }                                                       // namespace detail

    ////////////////////////////////////////////////////////////////////////////
    //
    class directory_iterator
      : public std::iterator<std::input_iterator_tag, directory_entry>
    {
    public:
    //ctor & dtor 
        directory_iterator() noexcept
        { }
        
        explicit directory_iterator(const path& p)
            : directory_iterator(p, nullptr)
        { }
        
        directory_iterator(const path& p, std::error_code& ec) noexcept
            : directory_iterator(p, &ec)
        { }
        
        directory_iterator(const directory_iterator&) = default;
        directory_iterator(directory_iterator&&) = default;
        directory_iterator& operator=(const directory_iterator&) = default;
        directory_iterator& operator=(directory_iterator&&) = default;
        ~directory_iterator() = default;
        
        ////////////////////////////////////////////////////////////////////////
        // iterator access
        const directory_entry& operator*() const
            { return m_element; }
            
        const directory_entry* operator->() const
            { return &m_element; }
        
        ////////////////////////////////////////////////////////////////////////
        // iterator modifiers
        directory_iterator& operator++()
            { return m_increment(); }
            
        directory_iterator operator++(int)
        { 
            directory_iterator it{*this}; 
            m_increment();
            return it;
        }
        
        directory_iterator& increment(std::error_code& ec) noexcept
        { return m_increment(&ec); }
        
        ////////////////////////////////////////////////////////////////////////
        //
        bool operator==(const directory_iterator& rhs) const noexcept
        { return m_stream.get() == rhs.m_stream.get(); }
        
        bool operator!=(const directory_iterator& rhs) const noexcept
        { return !(*this == rhs); }
    
    private:
        // recursive_directory_iterator uses this class
        // as its underlying implementation, and therefore it
        // needs access to the methods that take an optional error_code
        friend class recursive_directory_iterator;
        
        // construct the dir_stream
        directory_iterator(const path& p, std::error_code *ec);
        directory_iterator& m_increment(std::error_code *ec=nullptr);
        // convert iterator into end iterator
        void m_make_end();
        
        std::shared_ptr<detail::dir_stream> m_stream{nullptr};
        path m_root_path{};
        directory_entry m_element{};
        
    };                                                 // class directory_entry
    
    ////////////////////////////////////////////////////////////////////////////
    // 
    inline directory_iterator const & 
    begin(directory_iterator const & iter) noexcept
    { 
        return iter; 
    }
    
    inline directory_iterator 
    end(directory_iterator const &) noexcept
    { 
        return directory_iterator{}; 
    }
    
    ////////////////////////////////////////////////////////////////////////////
    //
    class recursive_directory_iterator
      : public std::iterator<std::input_iterator_tag,  directory_entry>
    {
    public:
        // constructors and destructor
        recursive_directory_iterator() noexcept
        { }
        
        explicit recursive_directory_iterator(const path& p,
                    directory_options xoptions = directory_options::none)
            : recursive_directory_iterator(p, xoptions,  nullptr)
        { }

        recursive_directory_iterator(const path& p,
            directory_options xoptions, std::error_code& ec) noexcept
            : recursive_directory_iterator(p, xoptions, &ec)
        { }
        
        recursive_directory_iterator(const path& p, std::error_code& ec) noexcept
            : recursive_directory_iterator(p, directory_options::none,  &ec)
        { }
        
        recursive_directory_iterator(const recursive_directory_iterator&) = default;
        recursive_directory_iterator(recursive_directory_iterator&&) = default;
        
        recursive_directory_iterator & 
        operator=(const recursive_directory_iterator&) = default;
            
        recursive_directory_iterator & 
        operator=(recursive_directory_iterator&&) = default;
            
        ~recursive_directory_iterator() = default;
        
        ////////////////////////////////////////////////////////////////////////
        //
        const directory_entry& operator*() const
        { return *(m_stack_ptr->top()); }
        
        const directory_entry* operator->() const
        { return &(*(m_stack_ptr->top())); }
        
        ////////////////////////////////////////////////////////////////////////
        //
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

        ////////////////////////////////////////////////////////////////////////
        //
        directory_options options() const noexcept
        { return m_options; }
        
        ////////////////////////////////////////////////////////////////////////
        //
        int depth() const
        {
            // m_stack_ptr && m_stack_ptr->size() == 0 should
            // never be true
            return (m_stack_ptr ? static_cast<int>(m_stack_ptr->size() - 1) : 0); 
        }
        
        ////////////////////////////////////////////////////////////////////////
        //
        bool recursion_pending() const noexcept
        { return m_rec; }
           
        ////////////////////////////////////////////////////////////////////////
        // 
        void pop()
        {
            if (!m_stack_ptr) return;
            ELIB_ASSERT(m_stack_ptr->size() > 0);
            m_stack_ptr->top() = directory_iterator{};
            m_increment();
        }
        
        ////////////////////////////////////////////////////////////////////////
        //
        void disable_recursion_pending() noexcept
        { m_rec = false; }
        
        ////////////////////////////////////////////////////////////////////////
        //
        bool operator==(const recursive_directory_iterator& other) const noexcept
        { return m_stack_ptr == other.m_stack_ptr; }
        
        ////////////////////////////////////////////////////////////////////////
        //
        bool operator!=(const recursive_directory_iterator& other) const noexcept
        { return !(*this == other);}
            
    private:
        
        recursive_directory_iterator(const path& p, directory_options opt, 
                                    std::error_code *ec);
        
        void m_make_end();
        
        bool m_try_recursion(std::error_code *ec);
        
        recursive_directory_iterator & 
        m_increment(std::error_code *ec=nullptr);
        
        
        std::shared_ptr<std::stack<directory_iterator>> 
        m_stack_ptr{nullptr};
        
        directory_options 
        m_options{directory_options::none};
        
        bool m_rec{true};
    };                                     // class recursive_directory_iterator
    
    ////////////////////////////////////////////////////////////////////////////
    inline recursive_directory_iterator const & 
    begin(recursive_directory_iterator const & iter) noexcept
    { 
        return iter; 
    }
    
    ////////////////////////////////////////////////////////////////////////////
    inline recursive_directory_iterator 
    end(recursive_directory_iterator const &) noexcept
    { 
        return recursive_directory_iterator{}; 
    }

}}                                                        // namespace elib::fs
# endif                                       // ELIB_FS_DIRECTORY_ITERATOR_HPP