#ifndef ELIB_FS_DIRECTORY_ENTRY_DEF_H
#define ELIB_FS_DIRECTORY_ENTRY_DEF_H

namespace elib {
namespace fs {
    
inline
directory_entry::directory_entry(const fs::path& p, file_status st,
                                 file_status symlink_st)
    : m_path{p}, m_status{st}, m_symlink_status{symlink_st}
{ }


inline void 
directory_entry::assign(const fs::path& p, file_status st,
                        file_status symlink_st)
{
    m_path = p;
    m_status = st;
    m_symlink_status = symlink_st;
}
    
inline void 
directory_entry::replace_filename(const fs::path& p, file_status st,
                                  file_status symlink_st)
{
    //TODO
    m_path.replace_filename(p);
    m_status = st;
    m_symlink_status = symlink_st;
}

// observers
inline const fs::path &
directory_entry::path() const noexcept
{
    return m_path;
}
    
inline file_status
directory_entry::status() const
{
    //TODO
    return m_status;
}
    
inline file_status
directory_entry::status(std::error_code& ec) const noexcept
{
    //TODO
    ((void)ec);
    return m_status;
}
    
inline file_status
directory_entry::symlink_status() const
{
    //TODO
    return m_symlink_status; 
}
    
inline file_status
directory_entry::symlink_status(std::error_code& ec) const noexcept
{
    //TODO
    ((void)ec);
    return m_symlink_status;
}
    
inline bool 
directory_entry::operator==(const directory_entry& rhs) const noexcept
{
    return (m_path == rhs.m_path);
}
    
inline bool 
directory_entry::operator!=(const directory_entry& rhs) const noexcept
{
    return (m_path != rhs.m_path);
}
    
inline bool 
directory_entry::operator< (const directory_entry& rhs) const noexcept
{
    return (m_path < rhs.m_path);
}
    
inline bool 
directory_entry::operator<=(const directory_entry& rhs) const noexcept
{
    return (m_path <= rhs.m_path);
}
    
inline bool 
directory_entry::operator> (const directory_entry& rhs) const noexcept
{
    return (m_path > rhs.m_path);
}
    
inline bool 
directory_entry::operator>=(const directory_entry& rhs) const noexcept
{
    return (m_path >= rhs.m_path);
}

    
} /* namespace fs */
} /* namespace elib */
#endif /* ELIB_FS_DIRECTORY_ENTRY_DEF_H */
