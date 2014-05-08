#ifndef ELIB_FILESYSTEM_DIRECTORY_ENTRY_HPP
#define ELIB_FILESYSTEM_DIRECTORY_ENTRY_HPP

# include <elib/filesystem/config.hpp>
# include <elib/filesystem/path.hpp>
# include <elib/filesystem/file_status.hpp>
# include <elib/filesystem/operations.hpp>

namespace elib { namespace fs
{
    ////////////////////////////////////////////////////////////////////////////
    class directory_entry
    {
    public:
        //ctor & dtor
        explicit directory_entry(
            const fs::path & p
          , file_status st = file_status()
          , file_status symlink_st = file_status()
          )
            : m_path(p), m_status(st), m_symlink_status(symlink_st)
        {}
        
        directory_entry() = default;
        directory_entry(const directory_entry&) = default;
        directory_entry(directory_entry&&) noexcept = default;
        directory_entry& operator=(const directory_entry&) = default;
        directory_entry& operator=(directory_entry&&) noexcept = default;
        
        ////////////////////////////////////////////////////////////////////////
        void assign(
            const fs::path & p
          , file_status st = file_status()
          , file_status symlink_st = file_status()
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
        
    public:
        
        ////////////////////////////////////////////////////////////////////////
        bool operator==(const directory_entry& rhs) const noexcept
        { return m_path == rhs.m_path; }
            
        bool operator!=(const directory_entry& rhs) const noexcept
        { return m_path != rhs.m_path; }
            
        ////////////////////////////////////////////////////////////////////////
        bool operator< (const directory_entry& rhs) const noexcept
        { return m_path < rhs.m_path; }
            
        bool operator<=(const directory_entry& rhs) const noexcept
        { return m_path <= rhs.m_path; }
            
        bool operator> (const directory_entry& rhs) const noexcept
        { return m_path > rhs.m_path; }
            
        bool operator>=(const directory_entry& rhs) const noexcept
        { return m_path >= rhs.m_path; }
      
    private:
        ////////////////////////////////////////////////////////////////////////
        // These don't need to be inline,  but they are for now.
        file_status m_get_status(std::error_code *ec=nullptr) const
        {
            if (!status_known(m_status)) 
            {
                if (status_known(m_symlink_status) && !is_symlink(m_symlink_status)) {
                    m_status = m_symlink_status; 
                } else {
                    m_status = ec ? fs::status(m_path, *ec) : fs::status(m_path);
                }
            }
            return m_status;
        }
        
        ////////////////////////////////////////////////////////////////////////
        //
        file_status m_get_symlink_status(std::error_code *ec=nullptr) const
        {
            if (!status_known(m_symlink_status)) {
                m_symlink_status = ec ? fs::symlink_status(m_path, *ec)
                                      : fs::symlink_status(m_path);
            }
            return m_symlink_status;
        }
        
        ////////////////////////////////////////////////////////////////////////
        //
        fs::path m_path;
        
        // Although these are not atomic to adjust, mutability allows
        // for file status caching as suggested in the standard
        // documentation
        mutable file_status m_status;
        mutable file_status m_symlink_status; 
  
    }; // class directory_entry
      
    
}}                                                          // namespace elib
#endif /* ELIB_FILESYSTEM_DIRECTORY_ENTRY_HPP */