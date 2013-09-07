#ifndef ELIB_ELIB_FS_FILE_STATUS_H
#define ELIB_ELIB_FS_FILE_STATUS_H

#include <elib/fs/file_type.h>
#include <elib/fs/perms.h>

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


#include <elib/fs/detail/file_status_inline.h>

#endif /* ELIB_ELIB_FS_FILE_STATUS_H */