#ifndef ELIB_MP_PARAM_PACK_PARAM_PACK_FWD_HPP
#define ELIB_MP_PARAM_PACK_PARAM_PACK_FWD_HPP

# include <cstddef>

namespace elib 
{
  namespace mp
  {
    
    template <class ...Args>
    struct param_pack;
    
    
    template <class Pack, std::size_t N>
    struct param_pack_iterator;
    
    
    namespace detail
    {
      struct param_pack_intrinsics;
      struct param_pack_iterator_intrisics;
    }                                                       // namespace detail
    
    
    template <std::size_t N, class Pack>
    struct get_nth;
    
    template <std::size_t N, class Pack>
    struct drop;
    
    template <std::size_t N, class Pack>
    struct take;
    
    template <std::size_t First, std::size_t Last, class Pack>
    struct slice;
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_PARAM_PACK_PARAM_PACK_FWD_HPP */