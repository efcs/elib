#ifndef ELIB_MP_GET_IMPL_HPP
#define ELIB_MP_GET_IMPL_HPP

# include <elib/mp/tag_dispatch.hpp>

namespace elib 
{
  namespace mp
  {
    
    
    template <class T>
    struct get_impl : tag_dispatch<T>
    {};
    
    
    template <class T>
    using get_impl_t = typename get_impl<T>::type;
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_GET_IMPL_HPP */