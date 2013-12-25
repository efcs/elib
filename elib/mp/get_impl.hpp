#ifndef ELIB_MP_GET_IMPL_HPP
#define ELIB_MP_GET_IMPL_HPP

# include <elib/mp/default_impl_dispatch.hpp>

namespace elib 
{
  namespace mp
  {
   
    // overload either get_impl or tag_dispatcher
    template <class T> struct get_impl;
    template <class T> struct tag_dispatcher;
    
  ////////////////////////////////////////////////////////////////////////////////
  //                            GET IMPL                                              
  ////////////////////////////////////////////////////////////////////////////////

    // we only use tag dispatch when get_impl hasn't been overloaded
    template <class T>
    struct get_impl
    {
      using type = default_impl_dispatch;
    };
    
    
    template <class T>
    using get_impl_t = typename get_impl<T>::type;
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_GET_IMPL_HPP */