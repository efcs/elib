#ifndef ELIB_MP_GET_IMPL_HPP
#define ELIB_MP_GET_IMPL_HPP

namespace elib 
{
  namespace mp
  {
   
    // overload either get_impl or tag_dispatcher
    template <class T> struct get_impl;
    
    // we only use tag dispatch when get_impl hasn't been overloaded
    template <class T>
    struct get_impl {};
    
    
    template <class T>
    using get_impl_t = typename get_impl<T>::type;
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_GET_IMPL_HPP */