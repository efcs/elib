#ifndef ELIB_MP_PACK_PACK_HPP
#define ELIB_MP_PACK_PACK_HPP

# include <elib/mp/pack/fwd.hpp>
# include <elib/mp/integral_constant.hpp>
# include <elib/mp/get_impl.hpp>

namespace elib 
{
  namespace mp
  {
    
    template <class ...Args>
    struct pack
    {
      using type = pack;
    };
    
    
    template <class T, T ...Values>
    using pack_c = pack< integral_constant<T, Values>... >;
    
    
    template <class ...Args>
    struct get_impl< pack<Args...> > 
    {
      using type = detail::pack_intrinsics;
    };
    
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_PACK_PACK_HPP */