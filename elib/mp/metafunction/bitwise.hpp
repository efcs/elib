#ifndef ELIB_MP_METAFUNCTION_BITWISE_HPP
#define ELIB_MP_METAFUNCTION_BITWISE_HPP

# include <elib/mp/config.hpp>
# include <elib/CXX14/type_traits.hpp>

namespace elib 
{
  namespace mp
  {
    
  ////////////////////////////////////////////////////////////////////////////////
  //                            BITNEGATE
  ////////////////////////////////////////////////////////////////////////////////
    
    template <class T>
    struct bitnegate_ 
      : std::integral_constant<
          decltype( ~T::value )
          , ~T::value  
        >
    {};
    
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
        : std::integral_constant<
            decltype( A1::value & A2::value)
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
    struct bitand_ : detail::bitand_impl<A1, A2, Rest...>
    {};
    
    
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
        : std::integral_constant<
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
    struct bitor_ : detail::bitor_impl<A1, A2, Rest...>
    {};
    
    
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
        : std::integral_constant<
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
    struct bitxor_ : detail::bitxor_impl<A1, A2, Rest...>
    {};
    
  ////////////////////////////////////////////////////////////////////////////////
  //                          SHIFT LEFT                                                
  ////////////////////////////////////////////////////////////////////////////////
  
  
   template <class C, class Shift>
   struct shift_left 
     : std::integral_constant<
        decltype(C::value << Shift::value)
        , (C::value << Shift::value)
      >
  {};
    
  ////////////////////////////////////////////////////////////////////////////////
  //                         SHIFT RIGHT                                                 
  ////////////////////////////////////////////////////////////////////////////////
  
    
    template <class C, class Shift>
    struct shift_right 
      : std::integral_constant<
          decltype(C::value >> Shift::value)
          , (C::value >> Shift::value) 
        >
    {};
  
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_METAFUNCTION_BITWISE_HPP */