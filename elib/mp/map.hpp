#ifndef ELIB_MP_MAP_HPP
# define ELIB_MP_MAP_HPP

# include <elib/mp/config.hpp>
# include <elib/mp/detail/sequence_fwd.hpp>
# include <elib/mp/sequence_metafunctions.hpp>

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