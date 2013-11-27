#ifndef ELIB_MP_TYPES_INTEGRAL_C_HPP
#define ELIB_MP_TYPES_INTEGRAL_C_HPP

# include <elib/CXX14/type_traits.hpp>

namespace elib 
{
  namespace mp
  {
    
    template <class T, T Val>
    using integral_c = std::integral_constant<T, Val>;
    
    template <class T, T Val>
    using intc_ = std::integral_constant<T, Val>;
    
  }                                                           // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_TYPES_INTEGRAL_C_HPP */