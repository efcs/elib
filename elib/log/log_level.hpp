#ifndef ELIB_LOG_LOG_LEVEL_H
#define ELIB_LOG_LOG_LEVEL_H


#include <elib/enumeration/basic_enum_traits.hpp>


namespace elib {
namespace log {
    
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

/* the default logging level */
constexpr level_e default_log_level = level_e::step;


} /* namespace log */


/* level_e can be used with enum_traits */
template <>
struct basic_enum_traits<log::level_e> {    
    static constexpr log::level_e default_value = log::default_log_level;
    static constexpr log::level_e first_value = log::level_e::debug;
    static constexpr log::level_e last_value = log::level_e::raw_err;
    
    typedef const std::map<log::level_e, std::string> map_type;
    static map_type name_map;
};
    
} /* namespace elib */
#endif /* ELIB_LOG_LOG_LEVEL_H */