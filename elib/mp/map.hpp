#ifndef ELIB_MP_MAP_HPP
#define ELIB_MP_MAP_HPP

# include <elib/mp/intrinsic/intrinsic_fwd.hpp>

namespace elib 
{
  namespace mp
  {
    namespace detail
    {
    //-------------------------------- map tags -----------------------------// 
      struct map_tag {};
      struct map_iter_tag {};
    }                                                       // namespace detail
    
    template <class ...Args>
    struct map
    {
      using type = map;
      using tag = detail::map_tag;
    };
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_MAP_HPP */