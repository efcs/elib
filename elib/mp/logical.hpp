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
    struct not_ 
      : bool_<!T::type::value> 
    {};
    
    template <class T>
    using not_t = bool_<!T::type::value>;
    
    template <unsigned long long V>
    struct not_c 
      : bool_<!V>
    {};
    
    template <unsigned long long V>
    using not_c_t = bool_<!V>;

  ////////////////////////////////////////////////////////////////////////////////
  //                          AND                                                   
  ////////////////////////////////////////////////////////////////////////////////
    
    namespace detail
    {
    //-------------------------------- and_impl ---------------------------// 
      
      template <bool Done, bool Val> struct and_impl;
      
      template <class First, class ...Rest>
      using and_impl_apply = typename 
          and_impl< 
              sizeof...(Rest) == 0 || 
                !static_cast<bool>(First::type::value)
            ,  static_cast<bool>(First::type::value)
            >::template apply<Rest...>;
      
      
      template <bool Val>
      struct and_impl<false, Val>
      {
        template <class First, class ...Rest>
        using apply = and_impl_apply<First, Rest...>;
      };
      
      template <bool Val>
      struct and_impl<true, Val>
      {
        template <class ...Args>
        using apply = bool_<Val>;
      };

    }                                                       // namespace detail
    
    template <class P1, class P2, class ...Rest>
    struct and_  
      : detail::and_impl_apply<P1, P2, Rest...>
    {};
    
    
    template <class P1, class P2, class ...Rest>
    using and_t = typename detail::and_impl_apply<P1, P2, Rest...>::type;
    
    
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
    struct and_c
      : detail::and_c_impl<P1, P2, Preds...>
    {};
    
    
    template <bool P1, bool P2, bool ...Preds>
    using and_c_t = detail::and_c_impl<P1, P2, Preds...>;
    
    
  ////////////////////////////////////////////////////////////////////////////////
  //                             OR                                             
  ////////////////////////////////////////////////////////////////////////////////
    
     namespace detail
    {
    //-------------------------------- or_impl ---------------------------// 
      
      template <bool Done, bool Val> struct or_impl;
      
      template <class First, class ...Rest>
      using or_impl_apply = typename 
          or_impl< 
              sizeof...(Rest) == 0 || 
                static_cast<bool>(First::type::value)
            ,  static_cast<bool>(First::type::value)
            >::template apply<Rest...>;
      
      
      template <bool Val>
      struct or_impl<false, Val>
      {
        template <class First, class ...Rest>
        using apply = or_impl_apply<First, Rest...>;
      };
      
      template <bool Val>
      struct or_impl<true, Val>
      {
        template <class ...Args>
        using apply = bool_<Val>;
      };

    }                                                       // namespace detail
    
    template <class P1, class P2, class ...Rest>
    struct or_  
      : detail::or_impl_apply<P1, P2, Rest...>
    {};
    
    
    template <class P1, class P2, class ...Rest>
    using or_t = typename detail::or_impl_apply<P1, P2, Rest...>::type;

    
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
    struct or_c :
      detail::or_c_impl<P1, P2, Rest...>
    {};
    
    
    template <bool P1, bool P2, bool ...Rest>
    using or_c_t = detail::or_c_impl<P1, P2, Rest...>;
    
  }                                                         //  namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_LOGICAL_HPP */