#include <elib/log/log_level.hpp>

namespace elib
{
    
#include <elib/pragma/diagnostic_push.hpp>
#include <elib/pragma/ignore_global_constructors.hpp>
#include <elib/pragma/ignore_exit_time_destructors.hpp>
      
  basic_enum_traits<log::level_e>::map_type 
  basic_enum_traits<log::level_e>::name_map =
      { {log::level_e::debug, "debug"},
        {log::level_e::info, "info"},
        {log::level_e::step, "step"},
        {log::level_e::warn, "warn"},
        {log::level_e::err, "err"},
        {log::level_e::fatal, "fatal"},
        {log::level_e::raw_out, "raw_out"},
        {log::level_e::raw_err, "raw_err"}
      };

#include <elib/pragma/diagnostic_pop.hpp>
      
    
} /* namespace elib */