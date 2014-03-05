#include "elib/log/log_level.hpp"

namespace elib
{
  namespace enumeration
  {

# if defined(__clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wexit-time-destructors"
#   pragma clang diagnostic ignored "-Wglobal-constructors"
# endif
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
          
# if defined(__clang__)
#   pragma clang diagnostic pop
# endif
    
  }                                                    // namespace enumeration
}                                                           // namespace elib