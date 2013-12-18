#ifndef ELIB_MP_PACK_FWD_HPP
# define ELIB_MP_PACK_FWD_HPP

# include <cstddef>

namespace elib 
{
  namespace mp
  {
   
    struct pack_tag {};
   
    template <class ...Args>
    struct pack;
    
    template <class Pack, std::size_t Pos>
    struct pack_iterator;
    
    namespace detail
    {
      struct pack_intrinsics;
      struct pack_iterator_intrinsics;
      
      template <class List> 
      struct pack_at_impl;
      
      template <class List> 
      struct pack_drop_impl;
      
      template <std::size_t N, class Pack, class ...Rest>
      struct pack_take_impl;
    }                                                       // namespace detail
    
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_PACK_FWD_HPP */