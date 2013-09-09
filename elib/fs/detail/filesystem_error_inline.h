#ifndef ELIB_FS_FILESYSTEM_ERROR_INLINE_H
#define ELIB_FS_FILESYSTEM_ERROR_INLINE_H

namespace elib {
namespace fs {
   

inline
filesystem_error::filesystem_error(const std::string& what_arg, 
                                   std::error_code ec)
    : std::system_error(ec), m_what{what_arg}
{ }
    

inline
filesystem_error::filesystem_error(const std::string& what_arg,
                     const path& p1, std::error_code ec)
    : std::system_error(ec), m_what{what_arg}, m_p1{p1}
{ }
    
 
inline
filesystem_error::filesystem_error(const std::string& what_arg,
                     const path& p1, const path& p2, 
                     std::error_code ec)
    : std::system_error(ec), m_what{what_arg}, 
      m_p1{p1}, m_p2{p2}
{ }


inline const path & 
filesystem_error::path1() const noexcept
{
    return m_p1;
}
    
    
inline const path & 
filesystem_error::path2() const noexcept
{
    return m_p2;
}
    
inline const char*
filesystem_error::what() const noexcept
{
    return m_what.c_str();
}
    
    
} /* namespace fs */
} /* namespace elib */
#endif /* ELIB_FS_FILESYSTEM_ERROR_INLINE_H */