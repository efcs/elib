#ifndef ELIB_MP_GET_IMPL_HPP
#define ELIB_MP_GET_IMPL_HPP

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
    struct get_impl : tag_dispatcher<typename T::tag>
    {};
    
    
    template <class T>
    using get_impl_t = typename get_impl<T>::type;
    
  ////////////////////////////////////////////////////////////////////////////////
  //                            tag_dispatch                                              
  ////////////////////////////////////////////////////////////////////////////////
    
    // no default impl
    template <class T> struct tag_dispatcher;
  
    template <class T>
    using tag_dispatch = tag_dispatcher<typename T::tag>;
    
    template <class T>
    using tag_dispatch_t = typename tag_dispatch<T>::type;
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_GET_IMPL_HPP */