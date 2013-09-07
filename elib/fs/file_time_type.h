#ifndef ELIB_FS_FILE_TIME_TYPE_H
#define ELIB_FS_FILE_TIME_TYPE_H

#include <chrono>

namespace elib {
namespace fs {
    
    
typedef std::chrono::time_point<std::chrono::system_clock>  file_time_type;
    

} /* namespace fs */
} /* namespace elib */
#endif /* ELIB_FS_FILE_TIME_TYPE_H */
