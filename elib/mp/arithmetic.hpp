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
    struct negate 
      : integral_c<
          decltype( -T::value )
          , -T::value
        >
    {};
    
    
    template <class T>
    using negate_t = typename negate<T>::type;
    
  //-------------------------------- add --------------------------------// 
  
    namespace detail
    {
      
      template <class ...Args>
      struct add_impl;
      
      
      template <class Arg>
      struct add_impl<Arg> : Arg
      {};
        
        
      template <class Arg1, class Arg2>
      struct add_impl<Arg1, Arg2>
        : integral_c<
            decltype(Arg1::value + Arg2::value)
            , Arg1::value + Arg2::value 
          >
      {};
      
      
      template <class Arg1, class Arg2, class Arg3, class ...Args>
      struct add_impl<Arg1, Arg2, Arg3, Args...>
        : add_impl<
            add_impl<Arg1, Arg2>
            , add_impl<Arg3, Args...> 
          >
      {};
      
    }                                                       // namespace detail
  
    
    
    template <class LHS, class RHS, class ...Rest>
    struct add : detail::add_impl<LHS, RHS, Rest...>
    {};
    
    template <class LHS, class RHS, class ...Rest>
    using add_t = typename add<LHS, RHS, Rest...>::type;
    
    
# if ELIB_MP_BOOST_COMPATIBLE_NAMES
    template <class ...Args>
    using plus = add<Args...>;
# endif                                     // ELIB_MP_BOOST_COMPATIBLE_NAMES
    
  //-------------------------------- subtract ------------------------------// 
    
    namespace detail
    {
      
      template <class ...Args>
      struct subtract_impl;
        
      template <class Arg>
      struct subtract_impl<Arg> : Arg
      {};
        
      template <class Arg1, class Arg2>
      struct subtract_impl<Arg1, Arg2>
        : integral_c<
            decltype(Arg1::value - Arg2::value)
            , Arg1::value - Arg2::value 
          >
      {};
        
      template <class Arg1, class Arg2, class Arg3, class ...Args>
      struct subtract_impl<Arg1, Arg2, Arg3, Args...>
        : subtract_impl<
              subtract_impl<Arg1, Arg2>
            , Arg3, Args...
          >
      {};
      
    }                                                       // namespace detail
    
    
    template <class LHS, class RHS, class ...Rest>
    struct subtract : detail::subtract_impl<LHS, RHS, Rest...>
    {};
    
    template <class LHS, class RHS, class ...Rest>
    using subtract_t = typename subtract<LHS, RHS, Rest...>::type;
    
    
# if ELIB_MP_BOOST_COMPATIBLE_NAMES
    template <class ...Args>
    using minus = subtract<Args...>;
# endif
    
  //-------------------------------- multiply --------------------------------// 
    namespace detail
    {
      
      template <class ...Args>
      struct multiply_impl;
        
        
      template <class Arg>
      struct multiply_impl<Arg> 
        : Arg
      {};
        
        
      template <class Arg1, class Arg2>
      struct multiply_impl<Arg1, Arg2>
        : integral_c<
            decltype(Arg1::value * Arg2::value)
          , Arg1::value * Arg2::value 
          >
      {};
        
        
      template <class Arg1, class Arg2, class Arg3, class ...Args>
      struct multiply_impl<Arg1, Arg2, Arg3, Args...>
        : multiply_impl<
            multiply_impl<Arg1, Arg2>
          , multiply_impl<Arg3, Args...> 
          >
      {};
    
    }                                                         // namespace detail
    
    
    template <class LHS, class RHS, class ...Rest>
    struct multiply : detail::multiply_impl<LHS, RHS, Rest...>
    {};
    
    
    template <class LHS, class RHS, class ...Rest>
    using multiply_t = typename multiply<LHS, RHS, Rest...>::type;
    
    
# if ELIB_MP_BOOST_COMPATIBLE_NAMES
    template <class ...Args>
    using times = multiply<Args...>;
# endif
  
  //-------------------------------- divide --------------------------------// 
  
    namespace detail
    {
      
      template <class ...Args>
      struct divide_impl;
        
      template <class Arg>
      struct divide_impl<Arg> : Arg
      {};
        
      template <class Arg1, class Arg2>
      struct divide_impl<Arg1, Arg2>
        : integral_c<
            decltype(Arg1::value / Arg2::value)
            , Arg1::value / Arg2::value 
          >
      {};
        
      template <class Arg1, class Arg2, class Arg3, class ...Args>
      struct divide_impl<Arg1, Arg2, Arg3, Args...>
        : divide_impl<
            divide_impl<Arg1, Arg2>
            , Arg3, Args...
          >
      {};
      
    }                                                       // namespace detail
    
    
    template <class LHS, class RHS, class ...Rest>
    struct divide : detail::divide_impl<LHS, RHS, Rest...>
    {};
    
    
    template <class LHS, class RHS, class ...Rest>
    using divide_t = typename divide<LHS, RHS, Rest...>::type;
    
    
# if ELIB_MP_BOOST_COMPATIBLE_NAMES
    template <class ...Args>
    using divides = divide<Args...>;
# endif
  
  //-------------------------------- modulus --------------------------------// 
  
    template <class Arg1, class Arg2>
    struct modulus 
      : integral_c<
          decltype(Arg1::value % Arg2::value)
          , Arg1::value % Arg2::value
        >
    {};
    
    
    template <class LHS, class RHS>
    using modulus_t = typename modulus<LHS, RHS>::type;
  
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_ARITHMETIC_HPP */