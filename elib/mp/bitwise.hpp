#ifndef ELIB_MP_BITWISE_HPP
# define ELIB_MP_BITWISE_HPP

# include <elib/mp/config.hpp>

# include <elib/CXX14/type_traits.hpp>

namespace elib 
{
  namespace mp
  {
    
    template <class T>
    struct bitnegate_ 
      : std::integral_constant<
          decltype( ~ T::value )
          , ~ T::value  
        >
    {};
    
  ////////////////////////////////////////////////////////////////////////////////
  //                       BITAND                                                   
  ////////////////////////////////////////////////////////////////////////////////
    
    template <class ...Args>
    struct bitand_;
    
    template <class T>
    struct bitand_<T> : T
    {};
    
    template <class A1, class A2>
    struct bitand_<A1, A2> 
      : std::integral_constant<
          decltype( A1::value & A2::value)
          , A1::value & A2::value
        >
    {};
    
    template <class A1, class A2, class A3, class ...Args>
    struct bitand_<A1, A2, A3, Args...>
      : bitand_<
          bitand_<A1, A2>
          , bitand_<A3, Args...>
        >
    {};
    
  ////////////////////////////////////////////////////////////////////////////////
  //                           BITOR                                               
  ////////////////////////////////////////////////////////////////////////////////
    
    
    template <class ...Args>
    struct bitor_;
    
    template <class T>
    struct bitor_<T> : T
    {};
    
    template <class A1, class A2>
    struct bitor_<A1, A2> 
      : std::integral_constant<
          decltype( A1::value | A2::value)
          , A1::value | A2::value
        >
    {};
    
    template <class A1, class A2, class A3, class ...Args>
    struct bitor_<A1, A2, A3, Args...>
      : bitor_<
          bitor_<A1, A2>
          , bitor_<A3, Args...>
        >
    {};
    
    
  ////////////////////////////////////////////////////////////////////////////////
  //                               BITXOR                                           
  ////////////////////////////////////////////////////////////////////////////////
    
    
    template <class ...Args>
    struct bitxor_;
    
    template <class T>
    struct bitxor_<T> : T
    {};
    
    template <class A1, class A2>
    struct bitxor_<A1, A2> 
      : std::integral_constant<
          decltype( A1::value ^ A2::value)
          , A1::value ^ A2::value
        >
    {};
    
    template <class A1, class A2, class A3, class ...Args>
    struct bitxor_<A1, A2, A3, Args...>
      : bitxor_<
          bitxor_<A1, A2>
          , bitxor_<A3, Args...>
        >
    {};
    
    
  ////////////////////////////////////////////////////////////////////////////////
  //                          SHIFT LEFT                                                
  ////////////////////////////////////////////////////////////////////////////////
  
  
    template <class ...Args>
    struct shift_left;
    
    template <class T>
    struct shift_left<T> : T
    {};
    
    template <class A1, class A2>
    struct shift_left<A1, A2> 
      : std::integral_constant<
          decltype( A1::value << A2::value)
          , (A1::value << A2::value)
        >
    {};
    
    template <class A1, class A2, class A3, class ...Args>
    struct shift_left<A1, A2, A3, Args...>
      : shift_left<
          shift_left<A1, A2>
          , shift_left<A3, Args...>
        >
    {};
    
  ////////////////////////////////////////////////////////////////////////////////
  //                         SHIFT RIGHT                                                 
  ////////////////////////////////////////////////////////////////////////////////
  
    
    template <class ...Args>
    struct shift_right;
    
    template <class T>
    struct shift_right<T> : T
    {};
    
    template <class A1, class A2>
    struct shift_right<A1, A2> 
      : std::integral_constant<
          decltype( A1::value >> A2::value)
          , (A1::value >> A2::value)
        >
    {};
    
    template <class A1, class A2, class A3, class ...Args>
    struct shift_right<A1, A2, A3, Args...>
      : shift_right<
          shift_right<A1, A2>
          , shift_right<A3, Args...>
        >
    {};
  
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_BITWISE_HPP */