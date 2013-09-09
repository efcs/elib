#ifndef ELIB_FS_FILE_STATUS_DEF_H
#define ELIB_FS_FILE_STATUS_DEF_H


namespace elib {
namespace fs {
  
    
inline
file_status::file_status(file_type ft, perms prms) noexcept
    : m_type{ft}, m_perms{prms}
{ }

inline file_type
file_status::type() const noexcept
{
    return m_type;
}

inline perms
file_status::permissions() const noexcept
{
    return m_perms;
}

inline void
file_status::type(file_type ft) noexcept
{
    m_type = ft;
}

inline void
file_status::permissions(perms prms) noexcept
{
    m_perms = prms;
}
    
    
} /* namespace fs */
} /* namespace elib */
#endif /* ELIB_FS_FILE_STATUS_DEF_H */