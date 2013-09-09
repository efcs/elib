#ifndef ELIB_FS_FILESYSTEM_ERROR_H
#define ELIB_FS_FILESYSTEM_ERROR_H

#include <elib/fs/config.h>
#include <elib/fs/path.h>

#include <system_error>
#include <string>


namespace elib {
namespace fs {
    

class filesystem_error : public std::system_error {
public:
    filesystem_error(const std::string& what_arg, std::error_code ec);
    
    filesystem_error(const std::string& what_arg,
                     const path& p1, std::error_code ec);
    
    filesystem_error(const std::string& what_arg,
                     const path& p1, const path& p2, 
                     std::error_code ec);

    const path & 
    path1() const noexcept;
    
    const path & 
    path2() const noexcept;
    
    const char*
    what() const noexcept;
private:
    std::string m_what;
    path m_p1{};
    path m_p2{};
};  

    
} /* namespace fs */
} /* namespace elib */


#ifdef ELIB_FS_DEFINITIONS_INLINE
#   include <elib/fs/detail/filesystem_error_def.h>
#endif

#endif /* ELIB_FS_FILESYSTEM_ERROR_H */