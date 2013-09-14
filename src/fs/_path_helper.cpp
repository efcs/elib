#include "elib/fs/detail/path_helper.hpp"

namespace elib {
    
#ifdef ELIB_FS_DEBUG

basic_enum_traits<fs::detail::path_part_e>::map_type
basic_enum_traits<fs::detail::path_part_e>::name_map =
    { {fs::detail::path_part_e::none, "none"},
      {fs::detail::path_part_e::name, "name"},
      {fs::detail::path_part_e::root_name, "root_name"},
      {fs::detail::path_part_e::delim, "delim"},
      {fs::detail::path_part_e::root_delim, "root_delim"},
      {fs::detail::path_part_e::trailing_delim, "trailing_delim"},
      {fs::detail::path_part_e::dot, "dot"},
      {fs::detail::path_part_e::double_dot, "double_dot"}
    };
    
#endif
    
} /* namespace elib */