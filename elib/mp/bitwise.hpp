#ifndef ELIB_MP_BITWISE_HPP
#define ELIB_MP_BITWISE_HPP

# include <elib/mp/detail/integral_expression.hpp>

namespace elib 
{
  namespace mp
  {
    
  //-------------------------------- bitnegate_ -----------------------------// 
  
    ELIB_MP_UNARY_INTEGRAL_EXPR(bitnegate_, bitnegate_t, ~);
    
  //-------------------------------- bitand_ --------------------------------// 
    
    ELIB_MP_LEFT_ASSOC_INTEGRAL_EXPR(bitand_, bitand_t, bitand_impl, &);
  
  //-------------------------------- bitor_ ---------------------------------// 
    
    ELIB_MP_LEFT_ASSOC_INTEGRAL_EXPR(bitor_, bitor_t, bitor_impl, |);
    
  //-------------------------------- bitxor_ --------------------------------// 
    
    ELIB_MP_LEFT_ASSOC_INTEGRAL_EXPR(bitxor_, bitxor_t, bitxor_impl, ^);
    
  //-------------------------------- shift_left -----------------------------// 
    
    ELIB_MP_BINARY_INTEGRAL_EXPR(shift_left, shift_left_t, <<);
  
  //-------------------------------- shift_right ----------------------------// 
  
    ELIB_MP_BINARY_INTEGRAL_EXPR(shift_right, shift_right_t, >>);
  
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_BITWISE_HPP */