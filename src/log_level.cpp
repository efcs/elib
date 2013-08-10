#include "elib/log_level.h"

namespace elib {
    
    
basic_enum_traits<level_e>::map_type basic_enum_traits<level_e>::name_map =
    { {level_e::debug, "debug"},
      {level_e::info, "info"},
      {level_e::step, "step"},
      {level_e::warn, "warn"},
      {level_e::err, "err"},
      {level_e::fatal, "fatal"},
      {level_e::raw_out, "raw_out"},
      {level_e::raw_err, "raw_err"}
    };
    
} /* namespace elib */