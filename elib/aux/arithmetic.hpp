#ifndef ELIB_AUX_ARITHMETIC_HPP
#define ELIB_AUX_ARITHMETIC_HPP

# include <elib/aux/integral_constant.hpp>

# define AUTO_FN(...) decltype(__VA_ARGS__), __VA_ARGS__

namespace elib { namespace aux
{
    namespace detail
    {
        template <bool Done, class ValType, ValType Val>
        struct add_impl;
        
        template <class ValType, ValType Val>
        struct add_impl<true, ValType, Val>
        {
            template <class ...Args>
            struct apply : integral_constant<ValType, Val>
            {};
            
            template <class A0>
            struct apply<A0> : ELIB_AUTO_INTC(Val + A0::type::value)
            {};
            
            template <class A0, class A1>
            struct apply<A0, A1> 
              : ELIB_AUTO_INTC(Val + A0::type::value + A1::type::value)
            {};
            
            template <class A0, class A1, class A2>
            struct apply<A0, A1, A2> 
              : ELIB_AUTO_INTC(Val + A0::type::value + A1::type::value + A2::type::value)
            {};
            
            template <class A0, class A1, class A2, class A3>
            struct apply<A0, A1, A2, A3> 
              : ELIB_AUTO_INTC(Val + A0::type::value + A1::type::value 
                                   + A2::type::value + A3::type::value)
            {};
            
            template <class A0, class A1, class A2, class A3, class A4>
            struct apply<A0, A1, A2, A3, A4> 
              : ELIB_AUTO_INTC(Val + A0::type::value + A1::type::value 
                                   + A2::type::value + A3::type::value
                                   + A4::type::value)
            {};
            
            template <class A0, class A1, class A2, class A3, class A4, class A5>
            struct apply<A0, A1, A2, A3, A4, A5> 
              : ELIB_AUTO_INTC(Val + A0::type::value + A1::type::value 
                                   + A2::type::value + A3::type::value
                                   + A4::type::value + A5::type::value)
            {};
            
            template <
                class A0, class A1, class A2, class A3, class A4, class A5
              , class A6>
            struct apply<A0, A1, A2, A3, A4, A5, A6> 
              : ELIB_AUTO_INTC(Val + A0::type::value + A1::type::value 
                                   + A2::type::value + A3::type::value
                                   + A4::type::value + A5::type::value
                                   + A6::type::value)
            {};
            
            template <
                class A0, class A1, class A2, class A3, class A4, class A5
              , class A6, class A7>
            struct apply<A0, A1, A2, A3, A4, A5, A6, A7> 
              : ELIB_AUTO_INTC(Val + A0::type::value + A1::type::value 
                                   + A2::type::value + A3::type::value
                                   + A4::type::value + A5::type::value
                                   + A6::type::value + A7::type::value)
            {};
            
            template <
                class A0, class A1, class A2, class A3, class A4, class A5
              , class A6, class A7, class A8>
            struct apply<A0, A1, A2, A3, A4, A5, A6, A7, A8> 
              : ELIB_AUTO_INTC(Val + A0::type::value + A1::type::value 
                                   + A2::type::value + A3::type::value
                                   + A4::type::value + A5::type::value
                                   + A6::type::value + A7::type::value
                                   + A8::type::value)
            {};
            
        };
        
        template <class ValType, ValType Val>
        struct add_impl<false, ValType, Val>
        {
            template <
                class A0, class A1, class A2, class A3, class A4, class A5
              , class A6, class A7, class A8, class A9
              , class ...Rest>
            using apply = typename
                add_impl<
                      sizeof...(Rest) < 10
                    , AUTO_FN( Val + A0::type::value + A1::type::value 
                                   + A2::type::value + A3::type::value
                                   + A4::type::value + A5::type::value
                                   + A6::type::value + A7::type::value
                                   + A8::type::value + A9::type::value)
                    >::template apply<Rest...>;
        };
    }                                                       // namespace detail
    
    template <class T, class ...Rest>
    struct add 
      : detail::add_impl<
            sizeof...(Rest) < 10
          , typename T::type::value_type
          , T::type::value
        >::template apply<Rest...>::type
    {};
}}                                                          // namespace elib
#endif /* ELIB_AUX_ARITHMETIC_HPP */