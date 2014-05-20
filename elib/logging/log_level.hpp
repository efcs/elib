#ifndef ELIB_LOGGING_LOG_LEVEL_HPP
#define ELIB_LOGGING_LOG_LEVEL_HPP

# include <elib/enumeration/basic_traits.hpp>
# include <elib/enumeration/cast.hpp>
# include <string>

namespace elib { namespace logging { inline namespace v1
{
        
    /* log_level is used to define what log functions are on/off
    * a log level is on if it is >= the current level, it is off otherwise.
    * only levels debug-fatal are valid logging levels 
    * raw levels are not affected by the level */
    enum class level_e 
    {
        debug,
        step,
        info,
        warn,
        err,
        fatal,
        raw_out,
        raw_err
    };

    /* the default logging level */
    constexpr level_e default_log_level = level_e::info;

}}}                                                         // namespace elib
namespace elib { namespace enumeration
{
    /* level_e can be used with enum_traits */
    template <>
    struct basic_enum_traits< ::elib::logging::level_e> 
    {    
        static constexpr ::elib::logging::level_e ELIB_ENUM_DEFAULT_VALUE = 
          ::elib::logging::default_log_level;
          
        static constexpr ::elib::logging::level_e ELIB_ENUM_FIRST_VALUE = 
          ::elib::logging::level_e::debug;
          
        static constexpr ::elib::logging::level_e ELIB_ENUM_LAST_VALUE = 
          ::elib::logging::level_e::raw_err;
          
        static constexpr bool ELIB_ENUM_IS_CONTIGIOUS = true;
        
        static const std::map< ::elib::logging::level_e, std::string> name_map;
    };
}}                                                          // namespace elib
namespace elib { namespace logging { inline namespace v1
{
    inline std::string to_string(level_e lv)
    {
        return enumeration::enum_cast<std::string>(lv);
    }
}}}                                                          // namespace elib
#endif /* ELIB_LOG_LOG_LEVEL_HPP */