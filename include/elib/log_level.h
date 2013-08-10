#ifndef ELIB_LOG_LOG_LEVEL_H
#define ELIB_LOG_LOG_LEVEL_H


#include "basic_enum_traits.h"


namespace elib {

    
/* log_level is used to define what log functions are on/off
 * a log level is on if it is >= the current level, it is off otherwise.
 * only levels debug-fatal are valid logging levels 
 * raw levels are not affected by the level */
enum class level_e {
    debug,
    info,
    step,
    warn,
    err,
    fatal,
    raw_out,
    raw_err
};


constexpr level_e default_log_level = level_e::step;


/* level_e can be used with enum_traits */
template <>
struct basic_enum_traits<level_e> {    
    static constexpr level_e default_value = default_log_level;
    static constexpr level_e first_value = level_e::debug;
    static constexpr level_e last_value = level_e::raw_err;
    
    typedef const std::map<level_e, std::string> map_type;
    static map_type name_map;
};
    
} /* namespace elib */
#endif /* ELIB_LOG_LOG_LEVEL_H */