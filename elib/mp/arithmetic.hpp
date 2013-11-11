#ifndef ELIB_MP_ARITHMETIC_HPP
# define ELIB_MP_ARITHMETIC_HPP

# include <elib/mp/config.hpp>

# include <elib/CXX14/type_traits.hpp>

namespace elib 
{
  namespace mp
  {
    
    ////////////////////////////////////////////////////////////////////////////////
    //                               NEGATE                                           
    ////////////////////////////////////////////////////////////////////////////////
    
    template <class T>
    struct negate 
      : std::integral_constant<
          decltype( - T::value )
          , - T::value
        >
    {};
    
    
    ////////////////////////////////////////////////////////////////////////////////
    //                      ADDITION                                                         
    ////////////////////////////////////////////////////////////////////////////////
    

    template <class ...Args>
    struct add;
      
    template <class Arg>
    struct add<Arg> : Arg
    {};
      
    template <class Arg1, class Arg2>
    struct add<Arg1, Arg2>
      : std::integral_constant<
          decltype(Arg1::value + Arg2::value)
          , Arg1::value + Arg2::value 
        >
    {};
      
    template <class Arg1, class Arg2, class Arg3, class ...Args>
    struct add<Arg1, Arg2, Arg3, Args...>
      : add<
          add<Arg1, Arg2>
          , add<Arg3, Args...> 
        >
    {};
    
    
    ////////////////////////////////////////////////////////////////////////////////
    //                        SUBTRACTION                                                  
    ////////////////////////////////////////////////////////////////////////////////

  
    template <class ...Args>
    struct subtract;
      
    template <class Arg>
    struct subtract<Arg> : Arg
    {};
      
    template <class Arg1, class Arg2>
    struct subtract<Arg1, Arg2>
      : std::integral_constant<
          decltype(Arg1::value - Arg2::value)
          , Arg1::value - Arg2::value 
        >
    {};
      
    template <class Arg1, class Arg2, class Arg3, class ...Args>
    struct subtract<Arg1, Arg2, Arg3, Args...>
      : subtract<
          subtract<Arg1, Arg2>
          , subtract<Arg3, Args...> 
        >
    {};
    
  ////////////////////////////////////////////////////////////////////////////////
  //                         MULTIPLY                                                   
  ////////////////////////////////////////////////////////////////////////////////

    
    template <class ...Args>
    struct multiply;
      
    template <class Arg>
    struct multiply<Arg> : Arg
    {};
      
    template <class Arg1, class Arg2>
    struct multiply<Arg1, Arg2>
      : std::integral_constant<
          decltype(Arg1::value * Arg2::value)
          , Arg1::value * Arg2::value 
        >
    {};
      
    template <class Arg1, class Arg2, class Arg3, class ...Args>
    struct multiply<Arg1, Arg2, Arg3, Args...>
      : multiply<
          multiply<Arg1, Arg2>
          , multiply<Arg3, Args...> 
        >
    {};
    
  ////////////////////////////////////////////////////////////////////////////////
  //                              DIVIDE                                              
  ////////////////////////////////////////////////////////////////////////////////
  
  
    template <class ...Args>
    struct divide;
      
    template <class Arg>
    struct divide<Arg> : Arg
    {};
      
    template <class Arg1, class Arg2>
    struct divide<Arg1, Arg2>
      : std::integral_constant<
          decltype(Arg1::value / Arg2::value)
          , Arg1::value / Arg2::value 
        >
    {};
      
    template <class Arg1, class Arg2, class Arg3, class ...Args>
    struct divide<Arg1, Arg2, Arg3, Args...>
      : divide<
          divide<Arg1, Arg2>
          , divide<Arg3, Args...> 
        >
    {};
  
  
  ////////////////////////////////////////////////////////////////////////////////
  //                           MODULUS                                         
  ////////////////////////////////////////////////////////////////////////////////
  
  
    template <class Arg1, class Arg2>
    struct modulus 
      : std::integral_constant<
          decltype(Arg1::value % Arg2::value)
          , Arg1::value % Arg2::value
        >
    {};
  
  
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_ARITHMETIC_HPP */