#ifndef ELIB_MP_ARITHMETIC_HPP
#define ELIB_MP_ARITHMETIC_HPP

# include <elib/mp/config.hpp>
# include <elib/mp/integral_constant.hpp>

namespace elib 
{
  namespace mp
  {
    
  //-------------------------------- negate --------------------------------// 

    template <class T>
     using negate =
      integral_constant<
        decltype( -T::value )
        , -T::value
      >;
    
    
    template <class T>
    using negate_t = negate<T>;
    
  //-------------------------------- add --------------------------------// 
  
    namespace detail
    {
      
      template <class ...As>
      struct add_impl;
      
      
      template <class A>
      struct add_impl<A> : A
      {};
        
        
      template <class A1, class A2>
      struct add_impl<A1, A2>
        : integral_constant<
            decltype(A1::value + A2::value)
            , A1::value + A2::value 
          >
      {};
      
      
      template <class A1, class A2, class A3, class ...As>
      struct add_impl<A1, A2, A3, As...>
        : add_impl<
            add_impl<A1, A2>
            , add_impl<A3, As...> 
          >
      {};
      
    }                                                       // namespace detail

    
    template <class LHS, class RHS, class ...Rest>
    using add = detail::add_impl<LHS, RHS, Rest...>;
    
    template <class LHS, class RHS, class ...Rest>
    using add_t = typename add<LHS, RHS, Rest...>::type;
    
    
# if ELIB_MP_BOOST_COMPATIBLE_NAMES
    template <class ...As>
    using plus = add<As...>;
    
    template <class ...As>
    using plus_t = add_t<As...>;
# endif                                     // ELIB_MP_BOOST_COMPATIBLE_NAMES
    
  //-------------------------------- subtract ------------------------------// 
    
    namespace detail
    {
      
      template <class ...As>
      struct subtract_impl;
        
      template <class A>
      struct subtract_impl<A> : A
      {};
        
      template <class A1, class A2>
      struct subtract_impl<A1, A2>
        : integral_constant<
            decltype(A1::value - A2::value)
            , A1::value - A2::value 
          >
      {};
        
      template <class A1, class A2, class A3, class ...As>
      struct subtract_impl<A1, A2, A3, As...>
        : subtract_impl<
              subtract_impl<A1, A2>
            , A3, As...
          >
      {};
      
    }                                                       // namespace detail
    
    
    template <class LHS, class RHS, class ...Rest>
    using subtract = detail::subtract_impl<LHS, RHS, Rest...>;
    
    template <class LHS, class RHS, class ...Rest>
    using subtract_t = typename subtract<LHS, RHS, Rest...>::type;
    
    
# if ELIB_MP_BOOST_COMPATIBLE_NAMES
    template <class ...As>
    using minus = subtract<As...>;
    
    template <class ...As>
    using minus_t = subtract_t<As...>;
# endif
    
  //-------------------------------- multiply --------------------------------// 
    namespace detail
    {
      
      template <class ...As>
      struct multiply_impl;
        
        
      template <class A>
      struct multiply_impl<A> 
        : A
      {};
        
        
      template <class A1, class A2>
      struct multiply_impl<A1, A2>
        : integral_constant<
            decltype(A1::value * A2::value)
          , A1::value * A2::value 
          >
      {};
        
        
      template <class A1, class A2, class A3, class ...As>
      struct multiply_impl<A1, A2, A3, As...>
        : multiply_impl<
            multiply_impl<A1, A2>
          , multiply_impl<A3, As...> 
          >
      {};
    
    }                                                         // namespace detail
    
    
    template <class LHS, class RHS, class ...Rest>
    using multiply = detail::multiply_impl<LHS, RHS, Rest...>;
    
    
    template <class LHS, class RHS, class ...Rest>
    using multiply_t = typename multiply<LHS, RHS, Rest...>::type;
    
    
# if ELIB_MP_BOOST_COMPATIBLE_NAMES
    template <class ...As>
    using times = multiply<As...>;
    
    template <class ...As>
    using times_t = multiply_t<As...>;
# endif
  
  //-------------------------------- divide --------------------------------// 
  
    namespace detail
    {
      
      template <class ...As>
      struct divide_impl;
        
      template <class A>
      struct divide_impl<A> : A
      {};
        
      template <class A1, class A2>
      struct divide_impl<A1, A2>
        : integral_constant<
            decltype(A1::value / A2::value)
            , A1::value / A2::value 
          >
      {};
        
      template <class A1, class A2, class A3, class ...As>
      struct divide_impl<A1, A2, A3, As...>
        : divide_impl<
            divide_impl<A1, A2>
            , A3, As...
          >
      {};
      
    }                                                       // namespace detail
    
    
    template <class LHS, class RHS, class ...Rest>
    using divide = detail::divide_impl<LHS, RHS, Rest...>;
    
    
    template <class LHS, class RHS, class ...Rest>
    using divide_t = typename divide<LHS, RHS, Rest...>::type;
    
    
# if ELIB_MP_BOOST_COMPATIBLE_NAMES
    template <class ...As>
    using divides = divide<As...>;
    
    template <class ...As>
    using divides_t = divide_t<As...>;
# endif
  
  //-------------------------------- modulus --------------------------------// 
  
    template <class A1, class A2>
    using modulus = 
      integral_constant<
        decltype(A1::value % A2::value)
        , A1::value % A2::value
      >;
    
    
    template <class LHS, class RHS>
    using modulus_t = modulus<LHS, RHS>;
  
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_ARITHMETIC_HPP */