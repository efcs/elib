#ifndef ELIB_FS_SPACE_INFO_HPP
#define ELIB_FS_SPACE_INFO_HPP


#include <cstdint>


namespace elib {
namespace fs {
    

struct space_info {
    uintmax_t capacity;
    uintmax_t free;
    uintmax_t available;
};
    
    
} /* namespace fs */
} /* namespace elib */
#endif /* ELIB_FS_SPACE_INFO_HPP */
