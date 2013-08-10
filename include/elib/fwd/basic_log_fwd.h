#ifndef ELIB_BASIC_LOG_FWD_H
#define ELIB_BASIC_LOG_FWD_H

#include "basic_enum_traits_fwd.h"

namespace elib {
    
class basic_log;
class log;
class file_log;
class elog;

enum class level_e;

template <>
class basic_enum_traits<level_e>;

namespace detail {
    
class log_impl;
class file_log_impl;
    
} /* namespace detail */


namespace unit_test {
    
class test_basic_log_impl; 
    
} /* namespace unit_test */


} /* namespace elib */
#endif /* ELIB_BASIC_LOG_FWD_H */