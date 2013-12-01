#ifndef ELIB_MP_LOGICAL_HPP
#define ELIB_MP_LOGICAL_HPP

# include <elib/mp/integral_constant.hpp>
# include <elib/mp/detail/conditional.hpp>

namespace elib 
{
  namespace mp
  {
    
   
  ////////////////////////////////////////////////////////////////////////////////
  //                                 NOT
  ////////////////////////////////////////////////////////////////////////////////
    
    template <class T>
    struct not_ : bool_<!T::type::value>
    {};
    
    template <class T>
    using not_t = typename not_<T>::type;
    
  ////////////////////////////////////////////////////////////////////////////////
  //                            NOT_C                                              
  ////////////////////////////////////////////////////////////////////////////////
  
  
    template <long V>
    struct not_c : bool_<!V>
    {};
    
    
  ////////////////////////////////////////////////////////////////////////////////
  //                          AND                                                   
  ////////////////////////////////////////////////////////////////////////////////
    
    namespace detail
    {
    //-------------------------------- and_impl ---------------------------// 
      
      template <bool B, class ...Rest>
      struct and_impl;
      
      template <class ...Args>
      struct and_impl<false, Args...> : false_
      {};
      
      template <>
      struct and_impl<true> : true_
      {};
      
      template <class First, class ...Rest>
      struct and_impl<true, First, Rest...>
        : and_impl<static_cast<bool>(First::type::value), Rest...>
      {};

    }                                                       // namespace detail
    
    template <class P1, class P2, class ...Rest>
    struct and_ 
      : detail::and_impl<static_cast<bool>(P1::type::value), P2, Rest...>
    {};
    
    
    template <class P1, class P2, class ...Rest>
    using and_t = typename and_<P1, P2, Rest...>::type;
    
  ////////////////////////////////////////////////////////////////////////////////
  //                            AND_C                                              
  ////////////////////////////////////////////////////////////////////////////////
  
    namespace detail
    {
      
      template <class ...Args>
      true_ and_c_test(Args*...);
      
      false_ and_c_test(...);
      
      template <bool ...Preds>
      using and_c_impl = decltype(
        and_c_test(conditional_t<Preds, int*, int>{}...)
      );
      
    }                                                       // namespace detail
    
    
    template <bool P1, bool P2, bool ...Preds>
    struct and_c : detail::and_c_impl<P1, P2, Preds...>
    {};
    
    
  ////////////////////////////////////////////////////////////////////////////////
  //                             OR                                             
  ////////////////////////////////////////////////////////////////////////////////
    
    namespace detail
    {
        
      template <bool B, class ...Args>
      struct or_impl : false_
      {
        static_assert(!B, "B must be false");
      };
      
      template <class ...Args>
      struct or_impl<true, Args...> : true_
      {};
      
      template <class First, class ...Rest>
      struct or_impl<false, First, Rest...> 
        : or_impl<static_cast<bool>(First::type::value), Rest...>
      {};
      
    }                                                       // namespace detail
    
    template <class P1, class P2, class ...Rest>
    struct or_ 
      : detail::or_impl<static_cast<bool>(P1::type::value), P2, Rest...>
    {};
    
    
    template <class P1, class P2, class ...Rest>
    using or_t = typename or_<P1, P2, Rest...>::type;
    
  ////////////////////////////////////////////////////////////////////////////////
  //                            OR_C                                              
  ////////////////////////////////////////////////////////////////////////////////
  
    namespace detail
    {
      
      template <class ...Args>
      false_ or_c_test(Args*...);
      
      true_ or_c_test(...);
      
      template <bool ...Preds>
      using or_c_impl = decltype( 
        or_c_test( conditional_t<Preds, int, int*>{}... )
      );
    }                                                       // namespace detail
    
    
    template <bool P1, bool P2, bool ...Rest>
    struct or_c : detail::or_c_impl<P1, P2, Rest...>
    {};
    
  }                                                         //  namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_LOGICAL_HPP */