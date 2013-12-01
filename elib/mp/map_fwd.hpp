#ifndef ELIB_MP_MAP_FWD_HPP
#define ELIB_MP_MAP_FWD_HPP

namespace elib 
{
  namespace mp
  {
    
    template <class ...Args> struct map;
    
    namespace detail
    {
      struct map_tag {};
      struct map_iter_tag {};
    }                                                       // namespace detail
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_MAP_FWD_HPP */