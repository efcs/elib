#ifndef ELIB_MP_BITWISE_HPP
#define ELIB_MP_BITWISE_HPP

# include <elib/mp/detail/integral_expression.hpp>

namespace elib 
{
  namespace mp
  {
    
  //-------------------------------- bitnegate_ -----------------------------// 
  
    template <class T>
    struct bitnegate_ : ELIB_MP_AUTO_INTC( ~ T::type::value )
    {};
    
    template <class T>
    using bitnegate_t = ELIB_MP_AUTO_INTC( ~ T::type::value );
    
  //-------------------------------- bitand_ --------------------------------// 
    
    ELIB_MP_LEFT_ASSOC_INTEGRAL_EXPR(bitand_, bitand_t, bitand_impl, &);
  
  //-------------------------------- bitor_ ---------------------------------// 
    
    ELIB_MP_LEFT_ASSOC_INTEGRAL_EXPR(bitor_, bitor_t, bitor_impl, |);
    
  //-------------------------------- bitxor_ --------------------------------// 
    
    ELIB_MP_LEFT_ASSOC_INTEGRAL_EXPR(bitxor_, bitxor_t, bitxor_impl, ^);
    
  //-------------------------------- shift_left -----------------------------// 
    
    template <class T, class U>
    struct shift_left : ELIB_MP_AUTO_INTC( T::type::value << U::type::value )
    {};
    
    template <class T, class U>
    using shift_left_t = ELIB_MP_AUTO_INTC( T::type::value << U::type::value );
    
  
  //-------------------------------- shift_right ----------------------------// 
  
    template <class T, class U>
    struct shift_right : ELIB_MP_AUTO_INTC( T::type::value >> U::type::value )
    {};
    
    template <class T, class U>
    using shift_right_t = ELIB_MP_AUTO_INTC( T::type::value >> U::type::value );
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_BITWISE_HPP */