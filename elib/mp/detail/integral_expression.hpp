#ifndef ELIB_MP_DETAIL_INTEGRAL_EXPRESSION_HPP
#define ELIB_MP_DETAIL_INTEGRAL_EXPRESSION_HPP
#
# include <elib/mp/detail/integral_constant.hpp>
#
# define ELIB_MP_LEFT_ASSOC_INTEGRAL_EXPR_IMPL(name, op)                     \
  template <class ...> struct name;                                          \
                                                                             \
  template <class A>                                                         \
  struct name<A> : A {};                                                     \
                                                                             \
  template <class A1, class A2>                                              \
  struct name<A1, A2>                                                        \
    : ELIB_MP_AUTO_INTC( A1::value op A2::value )                            \
  {};                                                                        \
                                                                             \
  template <class A1, class A2, class A3>                                    \
  struct name<A1, A2, A3>                                                    \
    : ELIB_MP_AUTO_INTC( A1::value op A2::value op A3::value )               \
  {};                                                                        \
                                                                             \
  template <class A1, class A2, class A3, class A4>                          \
  struct name<A1, A2, A3, A4>                                                \
    : ELIB_MP_AUTO_INTC( A1::value op A2::value op A3::value op A4::value )  \
  {};                                                                        \
                                                                             \
  template <class A1, class A2, class A3, class A4, class A5>                \
  struct name<A1, A2, A3, A4, A5>                                            \
    : ELIB_MP_AUTO_INTC( A1::value op A2::value op A3::value op A4::value    \
                         op A5::value )                                      \
  {};                                                                        \
                                                                             \
  template <class A1, class A2, class A3, class A4, class A5, class A6>      \
  struct name<A1, A2, A3, A4, A5, A6>                                        \
    : ELIB_MP_AUTO_INTC( A1::value op A2::value op A3::value op A4::value    \
                         op A5::value op A6::value )                         \
  {};                                                                        \
                                                                             \
  template <class A1, class A2, class A3, class A4, class A5                 \
    , class A6, class A7                                                     \
  >                                                                          \
  struct name<A1, A2, A3, A4, A5, A6, A7>                                    \
    : ELIB_MP_AUTO_INTC( A1::value op A2::value op A3::value op A4::value    \
                         op A5::value op A6::value op A7::value )            \
  {};                                                                        \
                                                                             \
  template <class A1, class A2, class A3, class A4, class A5                 \
    , class A6, class A7, class A8                                           \
  >                                                                          \
  struct name<A1, A2, A3, A4, A5, A6, A7, A8>                                \
    : ELIB_MP_AUTO_INTC( A1::value op A2::value op A3::value op A4::value    \
                         op A5::value op A6::value op A7::value              \
                         op A8::value )                                      \
  {};                                                                        \
                                                                             \
  template <class A1, class A2, class A3, class A4, class A5                 \
    , class A6, class A7, class A8, class A9                                 \
  >                                                                          \
  struct name<A1, A2, A3, A4, A5, A6, A7, A8, A9>                            \
    : ELIB_MP_AUTO_INTC( A1::value op A2::value op A3::value op A4::value    \
                         op A5::value op A6::value op A7::value              \
                         op A8::value op A9::value)                          \
  {};                                                                        \
                                                                             \
  template <class A1, class A2, class A3, class A4, class A5                 \
    , class A6, class A7, class A8, class A9, class A10                      \
  >                                                                          \
  struct name<A1, A2, A3, A4, A5, A6, A7, A8, A9, A10>                       \
    : ELIB_MP_AUTO_INTC( A1::value op A2::value op A3::value op A4::value    \
                         op A5::value op A6::value op A7::value              \
                         op A8::value op A9::value op A10::value)            \
  {};                                                                        \
                                                                             \
  template <class A1, class A2, class A3, class A4, class A5                 \
    , class A6, class A7, class A8, class A9, class A10, class A11           \
    , class ...Rest                                                          \
  >                                                                          \
  struct name<A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, Rest...>         \
    : name<                                                                  \
        ELIB_MP_AUTO_INTC( A1::value op A2::value op A3::value op A4::value  \
                         op A5::value op A6::value op A7::value op A8::value \
                         op A9::value op A10::value op A11::value)           \
      , Rest...                                                              \
      >                                                                      \
  {}
#
# define ELIB_MP_LEFT_ASSOC_INTEGRAL_EXPR_ALIAS(name, tname, impl) \
  template <class A1, class A2, class ...Rest>                     \
  using name = detail::impl<A1, A2, Rest...>;                      \
                                                                   \
  template <class A1, class A2, class ...Rest>                     \
  using tname = typename detail::impl<A1, A2, Rest...>::type 
#
# define ELIB_MP_LEFT_ASSOC_INTEGRAL_EXPR(name, tname, impl, op)  \
  namespace detail {                                 \
    ELIB_MP_LEFT_ASSOC_INTEGRAL_EXPR_IMPL(impl, op); \
  } /* namespace detail */                           \
                                                     \
  ELIB_MP_LEFT_ASSOC_INTEGRAL_EXPR_ALIAS(name, tname, impl)
#
#/* unary expression */
#
# define ELIB_MP_UNARY_INTEGRAL_EXPR(name, tname, op) \
  template <class T>                                  \
  using name = ELIB_MP_AUTO_INTC( op T::value );      \
                                                      \
  template <class T>                                  \
  using tname = ELIB_MP_AUTO_INTC( op T::value )
#
#/* binary expression */
#
# define ELIB_MP_BINARY_INTEGRAL_EXPR(name, tname, op)    \
  template <class T, class U>                             \
  using name = ELIB_MP_AUTO_INTC( T::value op U::value ); \
                                                          \
  template <class T, class U>                             \
  using tname = ELIB_MP_AUTO_INTC( T::value op U::value )
#
#endif /* ELIB_MP_DETAIL_INTEGRAL_EXPRESSION_HPP */