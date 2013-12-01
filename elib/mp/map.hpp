#ifndef ELIB_MP_MAP_HPP
#define ELIB_MP_MAP_HPP

# include <elib/mp/map_fwd.hpp>
# include <elib/mp/intrinsic/intrinsic_fwd.hpp>

namespace elib 
{
  namespace mp
  {
    template <class ...Args>
    struct map
    {
      using type = map;
      using tag = detail::map_tag;
    };
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_MAP_HPP */