#ifndef ELIB_MP_SIZEOF_HPP
#define ELIB_MP_SIZEOF_HPP

# include <elib/mp/detail/integral_constant.hpp>

namespace elib 
{
  namespace mp
  {
    
    template <class T>
    using sizeof_ = integral_constant< decltype(sizeof(T)) , sizeof(T) >;
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_SIZEOF_HPP */