#ifndef ELIB_MP_VARIADIC_DETAIL_LIST_ADVANCE_IMPL_HPP
#define ELIB_MP_VARIADIC_DETAIL_LIST_ADVANCE_IMPL_HPP

# include <elib/mp/variadic/fwd.hpp>
# include <elib/mp/identity.hpp>
# include <cstddef>

namespace elib 
{
  namespace mp
  {
    namespace detail
    {
      
      template <class It, std::size_t N>
      struct variadic_list_advance_impl;
      
      
      template <template <class...> class It
        , class ...Args
        >
      struct variadic_list_advance_impl< It<Args...>, 0>
        : identity< It<Args...> >
      {};
      
      template <template <class...> class It
        , class A1, class ...Rest
        >
      struct variadic_list_advance_impl< It<A1, Rest...>, 1>
        : identity< It<Rest...> >
      {};
        
        
      template <template <class...> class It
        , class A1, class A2, class ...Rest
        >
      struct variadic_list_advance_impl< It<A1, A2, Rest...>, 2>
        : identity< It<Rest...> >
      {};
      
      
      template <template <class...> class It
        , class A1, class A2, class A3, class ...Rest
        >
      struct variadic_list_advance_impl< It<A1, A2, A3, Rest...>, 3>
        : identity< It<Rest...> >
      {};
      
      
      template <template <class...> class It
        , class A1, class A2, class A3, class A4, class ...Rest
        >
      struct variadic_list_advance_impl< It<A1, A2, A3, A4, Rest...>, 4>
        : identity< It<Rest...> >
      {};
      
      
      template <template <class...> class It
        , class A1, class A2, class A3, class A4, class A5, class ...Rest
        >
      struct variadic_list_advance_impl< It<A1, A2, A3, A4, A5, Rest...>, 5>
        : identity< It<Rest...> >
      {};
      
      
      template <template <class...> class It
        , class A1, class A2, class A3, class A4, class A5, class A6
        , class ...Rest
        , std::size_t N
        >
      struct variadic_list_advance_impl< It<A1, A2, A3, A4, A5, A6, Rest...>, N>
        : variadic_list_advance_impl< It<A6, Rest...>, N - 5>
      {};
      
    }                                                       // namespace detail
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_VARIADIC_DETAIL_LIST_ADVANCE_IMPL_HPP */
