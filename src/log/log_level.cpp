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
      const enum_map_t<::elib::log::level_e>
      basic_enum_traits<::elib::log::level_e>::name_map =
          { {::elib::log::level_e::debug, "debug"},
            {::elib::log::level_e::info, "info"},
            {::elib::log::level_e::step, "step"},
            {::elib::log::level_e::warn, "warn"},
            {::elib::log::level_e::err, "err"},
            {::elib::log::level_e::fatal, "fatal"},
            {::elib::log::level_e::raw_out, "raw_out"},
            {::elib::log::level_e::raw_err, "raw_err"}
          };
          
# if defined(__clang__)
#   pragma clang diagnostic pop
# endif
    
  }                                                    // namespace enumeration
}                                                           // namespace elib