#include <elib/log/log_level.hpp>
#include <elib/pragma.hpp>

namespace elib
{
  namespace enumeration
  {
      
#ifdef ELIB_CONFIG_LIB_ENUMERATION

      ELIB_PRAGMA_DIAG_PUSH()
      ELIB_PRAGMA_IGNORE_GLOBAL_CONSTRUCTORS()
      ELIB_PRAGMA_IGNORE_EXIT_TIME_DESTRUCTORS()
      
      enum_map_t<log::level_e>
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
          
      ELIB_PRAGMA_DIAG_POP()
      
# endif
    
  }                                                    // namespace enumeration
}                                                           // namespace elib