#ifndef ELIB_FS_FILE_TIME_TYPE_H
#define ELIB_FS_FILE_TIME_TYPE_H

#include <chrono>

namespace elib {
namespace fs {
    
    
namespace detail {

typedef std::chrono::system_clock clock;
    
} /* namespace detail */
    
    
typedef std::chrono::time_point<detail::clock>  file_time_type;
    

} /* namespace fs */
} /* namespace elib */
#endif /* ELIB_FS_FILE_TIME_TYPE_H */
