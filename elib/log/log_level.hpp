#ifndef ELIB_LOG_LOG_LEVEL_HPP
#define ELIB_LOG_LOG_LEVEL_HPP

# include <elib/log/config.hpp>
# include <elib/enumeration/basic_enum_traits.hpp>
# include <elib/enumeration/enum_cast.hpp>
# include <string>

namespace elib 
{
  namespace log 
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


  }                                                         // namespace log
}                                                           // namespace elib

namespace elib
{
  namespace enumeration
  {

    /* level_e can be used with enum_traits */
    template <>
    struct basic_enum_traits< ::elib::log::level_e> 
    {    
        static constexpr ::elib::log::level_e ELIB_ENUM_DEFAULT_VALUE = 
          ::elib::log::default_log_level;
          
        static constexpr ::elib::log::level_e ELIB_ENUM_FIRST_VALUE = 
          ::elib::log::level_e::debug;
          
        static constexpr ::elib::log::level_e ELIB_ENUM_LAST_VALUE = 
          ::elib::log::level_e::raw_err;
          
        static constexpr bool ELIB_ENUM_IS_CONTIGIOUS = true;
        
        static const std::map< ::elib::log::level_e, std::string> name_map;
    };                                             // struct basic_enum_traits
    
  }                                                    // namespace enumeration
}                                                      // namespace elib
namespace elib { namespace log
{
    inline std::string to_string(level_e lv)
    {
        return enumeration::enum_cast<std::string>(lv);
    }
}}                                                          // namespace elib
#endif /* ELIB_LOG_LOG_LEVEL_HPP */