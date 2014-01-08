#ifndef ELIB_MP_DETAIL_INTEGRAL_EXPRESSION_HPP
#define ELIB_MP_DETAIL_INTEGRAL_EXPRESSION_HPP
#
# include <elib/mp/integral_constant.hpp>
#
# define ELIB_MP_LEFT_ASSOC_INTEGRAL_EXPR_IMPL(name, op)                                            \
  template <class ...> struct name;                                                                 \
                                                                                                    \
  template <class A>                                                                                \
  struct name<A> : A {};                                                                            \
                                                                                                    \
  template <class A1, class A2>                                                                     \
  struct name<A1, A2>                                                                               \
    : ELIB_MP_AUTO_INTC( A1::type::value op A2::type::value )                                       \
  {};                                                                                               \
                                                                                                    \
  template <class A1, class A2, class A3>                                                           \
  struct name<A1, A2, A3>                                                                           \
    : ELIB_MP_AUTO_INTC( A1::type::value op A2::type::value op A3::type::value )                    \
  {};                                                                                               \
                                                                                                    \
  template <class A1, class A2, class A3, class A4>                                                 \
  struct name<A1, A2, A3, A4>                                                                       \
    : ELIB_MP_AUTO_INTC( A1::type::value op A2::type::value op A3::type::value op A4::type::value ) \
  {};                                                                                               \
                                                                                                    \
  template <class A1, class A2, class A3, class A4, class A5, class ...Rest>                        \
  struct name<A1, A2, A3, A4, A5, Rest...>                                                          \
    : name<                                                                                         \
        ELIB_MP_AUTO_INTC( A1::type::value op A2::type::value                                       \
            op A3::type::value op A4::type::value op A5::type::value )                              \
        , Rest...                                                                                   \
        >                                                                                           \
  {}     
#
# define ELIB_MP_LEFT_ASSOC_INTEGRAL_EXPR_ALIAS(name, tname, impl) \
  template <class A1, class A2, class ...Rest>                     \
  struct name : detail::impl<A1, A2, Rest...> {};                  \
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
  struct name : ELIB_MP_AUTO_INTC( op T::type::value) \
  {};                                                 \
                                                      \
  template <class T>                                  \
  using tname = ELIB_MP_AUTO_INTC( op T::type::value )
#
#/* binary expression */
#
# define ELIB_MP_BINARY_INTEGRAL_EXPR(name, tname, op)                \
  template <class T, class U>                                         \
  struct name : ELIB_MP_AUTO_INTC( T::type::value op U::type::value ) \
  {};                                                                 \
                                                                      \
  template <class T, class U>                                         \
  using tname = ELIB_MP_AUTO_INTC( T::type::value op U::type::value )
#
#endif /* ELIB_MP_DETAIL_INTEGRAL_EXPRESSION_HPP */