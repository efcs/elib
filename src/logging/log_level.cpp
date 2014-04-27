#include <elib/logging/log_level.hpp>

namespace elib { namespace enumeration
{

# if defined(__clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wexit-time-destructors"
#   pragma clang diagnostic ignored "-Wglobal-constructors"
# endif
    const std::map< ::elib::logging::level_e, std::string>
    basic_enum_traits< ::elib::logging::level_e>::name_map =
      { {::elib::logging::level_e::debug, "debug"},
        {::elib::logging::level_e::step, "step"},
        {::elib::logging::level_e::info, "info"},
        {::elib::logging::level_e::warn, "warn"},
        {::elib::logging::level_e::err, "err"},
        {::elib::logging::level_e::fatal, "fatal"},
        {::elib::logging::level_e::raw_out, "raw_out"},
        {::elib::logging::level_e::raw_err, "raw_err"}
      };
          
# if defined(__clang__)
#   pragma clang diagnostic pop
# endif
    
}}                                                          // namespace elib