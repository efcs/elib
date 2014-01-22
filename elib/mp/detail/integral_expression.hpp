#ifndef ELIB_MP_DETAIL_INTEGRAL_EXPRESSION_NEW_HPP
#define ELIB_MP_DETAIL_INTEGRAL_EXPRESSION_NEW_HPP
# 
# include <elib/mp/integral_constant.hpp>
# include <elib/pp/overload.hpp>
# 
# define ELIB_MP_CHUNK_SIZE 10
# 
# define ELIB_MP_EXPAND(op, ...) \
    ELIB_PP_OVERLOAD(ELIB_MP_EXPAND_, __VA_ARGS__)(op, __VA_ARGS__)
# 
# define ELIB_MP_EXPAND_1(op, A1) A1::type::value
# 
# define ELIB_MP_EXPAND_2(op, A1, A2) A1::type::value op A2::type::value
# 
# define ELIB_MP_EXPAND_3(op, A1, A2, A3) \
    ELIB_MP_EXPAND_2(op, A1, A2) op A3::type::value
# 
# define ELIB_MP_EXPAND_4(op, A1, A2, A3, A4)                    \
    ELIB_MP_EXPAND_2(op, A1, A2) op ELIB_MP_EXPAND_2(op, A3, A4)
# 
# define ELIB_MP_EXPAND_5(op, A1, A2, A3, A4, A5) \
    ELIB_MP_EXPAND_4(op, A1, A2, A3, A4) op A5::type::value
# 
# define ELIB_MP_EXPAND_6(op, A1, A2, A3, A4, A5, A6) \
    ELIB_MP_EXPAND_3(op, A1, A2, A3) op ELIB_MP_EXPAND_3(op, A4, A5, A6)
# 
# define ELIB_MP_EXPAND_7(op, A1, A2, A3, A4, A5, A6, A7) \
    ELIB_MP_EXPAND_4(op, A1, A2, A3, A4) op ELIB_MP_EXPAND_3(op, A5, A6, A7)
# 
# define ELIB_MP_EXPAND_8(op, A1, A2, A3, A4, A5, A6, A7, A8) \
    ELIB_MP_EXPAND_4(op, A1, A2, A3, A4) op ELIB_MP_EXPAND_4(op, A5, A6, A7, A8)
# 
# define ELIB_MP_EXPAND_9(op, A1, A2, A3, A4, A5, A6, A7, A8, A9) \
    ELIB_MP_EXPAND_8(op, A1, A2, A3, A4, A5, A6, A7, A8) op A9::type::value
# 
# define ELIB_MP_EXPAND_10(op, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10) \
    ELIB_MP_EXPAND_5(op, A1, A2, A3, A4, A5) op ELIB_MP_EXPAND_5(op, A6, A7, A8, A9, A10)
# 
# 
# define ELIB_MP_LEFT_ASSOC_INTEGRAL_EXPR_IMPL(name, op)                                     \
    template <bool Done, class ValType, ValType Val>                                         \
    struct name                                                                              \
    {                                                                                        \
        template <class ...Empty>                                                            \
        struct apply : ::elib::mp::integral_constant<ValType, Val>                           \
        {};                                                                                  \
                                                                                             \
        template <class A1>                                                                  \
        struct apply<A1>                                                                     \
          : ELIB_MP_AUTO_INTC(Val op ELIB_MP_EXPAND(op, A1))                                    \
        {};                                                                                  \
                                                                                             \
        template <class A1, class A2>                                                        \
        struct apply<A1, A2>                                                                 \
          : ELIB_MP_AUTO_INTC(Val op ELIB_MP_EXPAND(op, A1, A2))                                \
        {};                                                                                  \
                                                                                             \
        template <class A1, class A2, class A3>                                              \
        struct apply<A1, A2, A3>                                                             \
          : ELIB_MP_AUTO_INTC(Val op ELIB_MP_EXPAND(op, A1, A2, A3))                            \
        {};                                                                                  \
                                                                                             \
        template <class A1, class A2, class A3, class A4>                                    \
        struct apply<A1, A2, A3, A4>                                                         \
          : ELIB_MP_AUTO_INTC(Val op ELIB_MP_EXPAND(op, A1, A2, A3, A4))                        \
        {};                                                                                  \
                                                                                             \
        template <class A1, class A2, class A3, class A4, class A5>                          \
        struct apply<A1, A2, A3, A4, A5>                                                     \
          : ELIB_MP_AUTO_INTC(Val op ELIB_MP_EXPAND(op, A1, A2, A3, A4, A5))                    \
        {};                                                                                  \
                                                                                             \
        template <                                                                           \
            class A1, class A2, class A3, class A4, class A5                                 \
          , class A6                                                                         \
        >                                                                                    \
        struct apply<A1, A2, A3, A4, A5, A6>                                                 \
          : ELIB_MP_AUTO_INTC(Val op                                                            \
                ELIB_MP_EXPAND(op, A1, A2, A3, A4, A5, A6)                                   \
            )                                                                                \
        {};                                                                                  \
                                                                                             \
        template <                                                                           \
            class A1, class A2, class A3, class A4, class A5                                 \
          , class A6, class A7                                                               \
        >                                                                                    \
        struct apply<A1, A2, A3, A4, A5, A6, A7>                                             \
          : ELIB_MP_AUTO_INTC(Val op                                                            \
                ELIB_MP_EXPAND(op, A1, A2, A3, A4, A5, A6, A7)                               \
            )                                                                                \
        {};                                                                                  \
                                                                                             \
        template <                                                                           \
            class A1, class A2, class A3, class A4, class A5                                 \
          , class A6, class A7, class A8                                                     \
        >                                                                                    \
        struct apply<A1, A2, A3, A4, A5, A6, A7, A8>                                         \
          : ELIB_MP_AUTO_INTC(Val op                                                            \
                ELIB_MP_EXPAND(op, A1, A2, A3, A4, A5, A6, A7, A8)                           \
            )                                                                                \
        {};                                                                                  \
                                                                                             \
        template <                                                                           \
            class A1, class A2, class A3, class A4, class A5                                 \
          , class A6, class A7, class A8, class A9                                           \
        >                                                                                    \
        struct apply<A1, A2, A3, A4, A5, A6, A7, A8, A9>                                     \
          : ELIB_MP_AUTO_INTC(Val op                                                            \
                ELIB_MP_EXPAND(op, A1, A2, A3, A4, A5, A6, A7, A8, A9)                       \
            )                                                                                \
        {};                                                                                  \
    };                                                                                       \
                                                                                             \
    template <class ValType, ValType Val>                                                    \
    struct name<false, ValType, Val>                                                         \
    {                                                                                        \
        template <                                                                           \
            class A1, class A2, class A3, class A4, class A5                                 \
          , class A6, class A7, class A8, class A9, class A10                                \
          , class ...Rest                                                                    \
        >                                                                                    \
        using apply = typename                                                               \
            name<                                                                            \
                sizeof...(Rest) < 10                                                         \
              , decltype(Val op ELIB_MP_EXPAND(op, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10)) \
              , Val op ELIB_MP_EXPAND(op, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10)           \
            >::template apply<Rest...>;                                                      \
    };                                                                                       \
                                                                                             \
    template <class T, class ...Rest>                                                        \
    using name##_apply = typename                                                            \
        name<                                                                                \
            sizeof...(Rest) < 10                                                             \
          , typename T::type::value_type                                                              \
          , T::type::value                                                                   \
        >::template apply<Rest...>::type
# 
# 
# define ELIB_MP_LEFT_ASSOC_INTEGRAL_EXPR_ALIAS(name, alias, impl) \
    template <class A0, class A1, class ...Rest>                       \
    struct name : detail::impl##_apply<A0, A1, Rest...>                \
    {};                                                                \
                                                                       \
    template <class A0, class A1, class ...Rest>                       \
    using alias = typename detail::impl##_apply<A0, A1, Rest...>
# 
    
# define ELIB_MP_LEFT_ASSOC_INTEGRAL_EXPR(name, alias, impl, op) \
    namespace detail {                                               \
        ELIB_MP_LEFT_ASSOC_INTEGRAL_EXPR_IMPL(impl, op);  \
    }                                                                \
                                                                     \
    ELIB_MP_LEFT_ASSOC_INTEGRAL_EXPR_ALIAS(name, alias, impl)
    
# 
#endif /* ELIB_MP_DETAIL_INTEGRAL_EXPRESSION_NEW_HPP */