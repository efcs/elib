#ifndef ELIB_LOG_LOG_LEVEL_HPP
#define ELIB_LOG_LOG_LEVEL_HPP

# include <elib/log/config.hpp>
# include <elib/enumeration/basic_enum_traits.hpp>

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


  }                                                         // namespace log
}                                                           // namespace elib

namespace elib
{
  namespace enumeration
  {

    /* level_e can be used with enum_traits */
    template <>
    struct basic_enum_traits<log::level_e> 
    {    
        static constexpr log::level_e ELIB_ENUM_DEFAULT_VALUE = 
          log::default_log_level;
          
        static constexpr log::level_e ELIB_ENUM_FIRST_VALUE = 
          log::level_e::debug;
          
        static constexpr log::level_e ELIB_ENUM_LAST_VALUE = 
          log::level_e::raw_err;
          
        static constexpr bool ELIB_ENUM_IS_CONTIGIOUS = true;
        
        static enum_map_t<log::level_e> name_map;
    };                                             // struct basic_enum_traits
    
  }                                                    // namespace enumeration
}                                                      // namespace elib


#endif /* ELIB_LOG_LOG_LEVEL_HPP */