#ifndef ELIB_MP_ARITHMETIC_HPP
#define ELIB_MP_ARITHMETIC_HPP

# include <elib/mp/detail/integral_expression.hpp>

namespace elib 
{
  namespace mp
  {
    
  //-------------------------------- negate --------------------------------// 

    ELIB_MP_UNARY_INTEGRAL_EXPR(negate, negate_t, -);

  //-------------------------------- add ------------------------------------// 
   
    ELIB_MP_LEFT_ASSOC_INTEGRAL_EXPR(add, add_t, add_impl, +);
    
# if ELIB_MP_BOOST_COMPATIBLE_NAMES
    ELIB_MP_LEFT_ASSOC_INTEGRAL_EXPR_ALIAS(plus, plus_t, add_impl);
# endif 
    
  //-------------------------------- subtract --------------------------------// 
    

    ELIB_MP_LEFT_ASSOC_INTEGRAL_EXPR(subtract, subtract_t, subtract_impl, -);
    
# if ELIB_MP_BOOST_COMPATIBLE_NAMES
    ELIB_MP_LEFT_ASSOC_INTEGRAL_EXPR_ALIAS(minus, minus_t, subtract_impl);
# endif
    
  //-------------------------------- multiply --------------------------------// 
    
    ELIB_MP_LEFT_ASSOC_INTEGRAL_EXPR(multiply, multiply_t, multiply_impl, *);
    
# if ELIB_MP_BOOST_COMPATIBLE_NAMES
    ELIB_MP_LEFT_ASSOC_INTEGRAL_EXPR_ALIAS(times, times_t, multiply_impl);
# endif
  
  //-------------------------------- divide --------------------------------// 
  
   ELIB_MP_LEFT_ASSOC_INTEGRAL_EXPR(divide, divide_t, divide_impl, /);
    
# if ELIB_MP_BOOST_COMPATIBLE_NAMES
    ELIB_MP_LEFT_ASSOC_INTEGRAL_EXPR_ALIAS(divides, divides_t, divide_impl);
# endif
  
  //-------------------------------- modulus --------------------------------// 
  
    ELIB_MP_BINARY_INTEGRAL_EXPR(modulus, modulus_t, %);
  
  
  //-------------------------------- increment --------------------------------// 
    
    template <class T>
    using increment = integral_constant< typename T::value_type, T::value + 1 >;
    
    template <class T>
    using increment_t = increment<T>;
    
  //-------------------------------- decrement --------------------------------// 
  
    template <class T>
    using decrement = integral_constant< typename T::value_type, T::value - 1 >;
    
    template <class T>
    using decrement_t = decrement<T>;
  
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_ARITHMETIC_HPP */