#ifndef ELIB_ELIB_FS_FILE_STATUS_HPP
#define ELIB_ELIB_FS_FILE_STATUS_HPP

#include <elib/fs/config.hpp>
#include <elib/fs/file_type.hpp>
#include <elib/fs/perms.hpp>

namespace elib {
namespace fs {
    

class file_status {
public:
// constructors
    explicit file_status(file_type ft = file_type::none,
                         perms prms = perms::unknown) noexcept;
                         
    file_status(const file_status&) noexcept = default;
    file_status(file_status&&) noexcept = default;
    ~file_status() = default;

    file_status& operator=(const file_status&) noexcept = default;
    file_status& operator=(file_status&&) noexcept = default;

// observers
    file_type  
    type() const noexcept;
    
    perms
    permissions() const noexcept;

// modifiers
    void       
    type(file_type ft) noexcept;
    
    void       
    permissions(perms prms) noexcept;
private:
    file_type m_type;
    perms m_perms;
};    

    
} /* namespace fs */
} /* namespace elib */


#include <elib/fs/detail/file_status_def.hpp>


#endif /* ELIB_ELIB_FS_FILE_STATUS_HPP */