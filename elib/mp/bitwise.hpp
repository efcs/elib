#ifndef ELIB_MP_BITWISE_HPP
#define ELIB_MP_BITWISE_HPP

# include <elib/mp/integral_constant.hpp>

namespace elib 
{
  namespace mp
  {
    
  ////////////////////////////////////////////////////////////////////////////////
  //                            BITNEGATE
  ////////////////////////////////////////////////////////////////////////////////
    
    template <class T>
    using bitnegate_ =
      integral_constant<
        decltype( ~T::value )
        , ~T::value  
      >;
    
  ////////////////////////////////////////////////////////////////////////////////
  //                       BITAND                                                   
  ////////////////////////////////////////////////////////////////////////////////
    
    namespace detail 
    {
      
      template <class ...Args>
      struct bitand_impl;
      
      template <class T>
      struct bitand_impl<T> : T
      {};
      
      template <class A1, class A2>
      struct bitand_impl<A1, A2> 
        : integral_constant<
            decltype(A1::value & A2::value)
            , A1::value & A2::value
          >
      {};
      
      template <class A1, class A2, class A3, class ...Args>
      struct bitand_impl<A1, A2, A3, Args...>
        : bitand_impl<
            bitand_impl<A1, A2>
            , bitand_impl<A3, Args...>
          >
      {};
      
    }                                                       // namespace detail
    
    template <class A1, class A2, class ...Rest>
    using bitand_ = detail::bitand_impl<A1, A2, Rest...>;
    
    
    template <class A1, class A2, class ...Rest>
    using bitand_t = typename detail::bitand_impl<A1, A2, Rest...>;
    
    
  ////////////////////////////////////////////////////////////////////////////////
  //                           BITOR                                               
  ////////////////////////////////////////////////////////////////////////////////
    
    namespace detail
    {
        
      template <class ...Args>
      struct bitor_impl;
      
      template <class T>
      struct bitor_impl<T> : T
      {};
      
      template <class A1, class A2>
      struct bitor_impl<A1, A2> 
        : integral_constant<
            decltype( A1::value | A2::value)
            , A1::value | A2::value
          >
      {};
      
      template <class A1, class A2, class A3, class ...Args>
      struct bitor_impl<A1, A2, A3, Args...>
        : bitor_impl<
            bitor_impl<A1, A2>
            , bitor_impl<A3, Args...>
          >
      {};
      
    }                                                       // namespace detail
    
    
    template <class A1, class A2, class ...Rest>
    using bitor_ = detail::bitor_impl<A1, A2, Rest...>;
    
    template <class A1, class A2, class ...Rest>
    using bitor_t = typename detail::bitor_impl<A1, A2, Rest...>;
    
    
  ////////////////////////////////////////////////////////////////////////////////
  //                               BITXOR                                           
  ////////////////////////////////////////////////////////////////////////////////
    
    namespace detail
    {
      
      template <class ...Args>
      struct bitxor_impl;
      
      template <class T>
      struct bitxor_impl<T> : T
      {};
      
      template <class A1, class A2>
      struct bitxor_impl<A1, A2> 
        : integral_constant<
            decltype( A1::value ^ A2::value)
            , A1::value ^ A2::value
          >
      {};
      
      template <class A1, class A2, class A3, class ...Args>
      struct bitxor_impl<A1, A2, A3, Args...>
        : bitxor_impl<
            bitxor_impl<A1, A2>
            , bitxor_impl<A3, Args...>
          >
      {};
      
    }                                                       // namespace detail
    
    template <class A1, class A2, class ...Rest>
    using bitxor_ = detail::bitxor_impl<A1, A2, Rest...>;
    
    template <class A1, class A2, class ...Rest>
    using bitxor_t = typename detail::bitxor_impl<A1, A2, Rest...>;
    
  ////////////////////////////////////////////////////////////////////////////////
  //                          SHIFT LEFT                                                
  ////////////////////////////////////////////////////////////////////////////////
  
  
    template <class C, class Shift>
    using shift_left =
      integral_constant<
        decltype(C::value << Shift::value)
        , (C::value << Shift::value)
      >;
      
    template <class C, class Shift>
    using shift_left_t = shift_left<C, Shift>;
    
  ////////////////////////////////////////////////////////////////////////////////
  //                         SHIFT RIGHT                                                 
  ////////////////////////////////////////////////////////////////////////////////
  
    
    template <class C, class Shift>
    using shift_right =
      integral_constant<
          decltype(C::value >> Shift::value)
          , (C::value >> Shift::value) 
        >;
        
    template <class C, class Shift>
    using shift_right_t = shift_right<C, Shift>;
  
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_BITWISE_HPP */