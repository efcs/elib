#ifndef ELIB_FS_DIRECTORY_ENTRY_H
#define ELIB_FS_DIRECTORY_ENTRY_H

#include <elib/fs/config.h>
#include <elib/fs/path.h>
#include <elib/fs/file_status.h>

#include <system_error>


namespace elib {
namespace fs {
    
    
class directory_entry {
public:
    // constructors and destructor
    directory_entry() = default;
    
    directory_entry(const directory_entry&) = default;
    
    directory_entry(directory_entry&&) noexcept = default;
    
    explicit 
    directory_entry(const fs::path& p, file_status st=file_status(),
                    file_status symlink_st=file_status());
    
    ~directory_entry() = default; 

    // modifiers
    directory_entry& 
    operator=(const directory_entry&) = default;
    
    /* causes compile error 
    directory_entry& 
    operator=(directory_entry&&) noexcept = default; */
    
    directory_entry&
    operator=(directory_entry&&) = default;
    
    void 
    assign(const fs::path& p, file_status st=file_status(),
           file_status symlink_st=file_status());
    
    void 
    replace_filename(const fs::path& p, file_status st=file_status(),
                     file_status symlink_st=file_status());

    // observers
    const fs::path&
    path() const noexcept
    { return m_path; }
    
    file_status
    status() const;
    
    file_status
    status(std::error_code& ec) const noexcept;
    
    file_status
    symlink_status() const;
    
    file_status
    symlink_status(std::error_code& ec) const noexcept;

    
    bool 
    operator==(const directory_entry& rhs) const noexcept
    { return (m_path == rhs.m_path); }
    
    bool 
    operator!=(const directory_entry& rhs) const noexcept
    { return (m_path != rhs.m_path); }
    
    bool 
    operator< (const directory_entry& rhs) const noexcept
    { return (m_path < rhs.m_path); }
    
    bool 
    operator<=(const directory_entry& rhs) const noexcept
    { return (m_path <= rhs.m_path); }
    
    bool 
    operator> (const directory_entry& rhs) const noexcept
    { return (m_path > rhs.m_path); }
    
    bool 
    operator>=(const directory_entry& rhs) const noexcept
    { return (m_path >= rhs.m_path); }
    
private:
    fs::path m_path;       // for exposition only
    mutable file_status m_status;     // for exposition only; stat()-like
    mutable file_status m_symlink_status; // for exposition only; lstat()-like
};    

    
} /* namespace fs */
} /* namespace elib */
#endif /* ELIB_FS_DIRECTORY_ENTRY_H */
