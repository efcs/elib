#ifndef ELIB_MP_VARIADIC_DETAIL_TAKE_IMPL_HPP
#define ELIB_MP_VARIADIC_DETAIL_TAKE_IMPL_HPP

# include <elib/mp/variadic/fwd.hpp>
# include <cstddef>

namespace elib 
{
  namespace mp
  {
    namespace detail
    {
      
      template <
          template <class...> class S
        , class ...ToArgs
        , class ...FromArgs
        >
      struct variadic_take_impl<
          S<ToArgs...>
        , S<FromArgs...>
        , 0
        >
      {
        using type = S<ToArgs...>;
      };
      
      
      template <
          template <class...> class S
        , class ...ToArgs
        , class A1, class ...Rest
        >
      struct variadic_take_impl<
          S<ToArgs...>
        , S<A1, Rest...>
        , 1
        >
      {
        using type = S<ToArgs..., A1>;
      };
      
      
      template <
          template <class...> class S
        , class ...ToArgs
        , class A1, class A2, class ...Rest
        >
      struct variadic_take_impl<
          S<ToArgs...>
        , S<A1, A2, Rest...>
        , 2
        >
      {
        using type = S<ToArgs..., A1, A2>;
      };
      
      
      template <
          template <class...> class S
        , class ...ToArgs
        , class A1, class A2, class A3, class ...Rest
        >
      struct variadic_take_impl<
          S<ToArgs...>
        , S<A1, A2, A3, Rest...>
        , 3
        >
      {
        using type = S<ToArgs..., A1, A2, A3>;
      };
      
      
      template <
          template <class...> class S
        , class ...ToArgs
        , class A1, class A2, class A3, class A4, class ...Rest
        >
      struct variadic_take_impl<
          S<ToArgs...>
        , S<A1, A2, A3, A4, Rest...>
        , 4
        >
      {
        using type = S<ToArgs..., A1, A2, A3, A4>;
      };
      
      
      template <
          template <class...> class S
        , class ...ToArgs
        , class A1, class A2, class A3, class A4, class A5, class ...Rest
        >
      struct variadic_take_impl<
          S<ToArgs...>
        , S<A1, A2, A3, A4, A5, Rest...>
        , 5
        >
      {
        using type = S<ToArgs..., A1, A2, A3, A4, A5>;
      };
      
      
      template <
          template <class...> class S
        , class ...ToArgs
        , class A1, class A2, class A3, class A4, class A5, class A6
        , class ...Rest
        , std::size_t N
        >
      struct variadic_take_impl<
          S<ToArgs...>
        , S<A1, A2, A3, A4, A5, A6, Rest...>
        , N
        > 
        : variadic_take_impl<
              S<ToArgs..., A1, A2, A3, A4, A5>
            , S<A6, Rest...>
            , N - 5
            >
        {};
      
      
    }                                                       // namespace detail
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_VARIADIC_DETAIL_TAKE_IMPL_HPP */