#ifndef ELIB_AUX_META_LEFT_ASSOCIATIVE_EXPRESSION_HPP
# define ELIB_AUX_META_LEFT_ASSOCIATIVE_EXPRESSION_HPP
# 
# include <elib/aux/integral_constant.hpp>
# 
# define ELIB_AUX_LEFT_ASSOC_EXPR(Entry, Impl, Op)                        \
    template <bool Done, class ValType, ValType Val>                      \
    struct Impl                                                           \
    {                                                                     \
        template <class ...Empty>                                         \
        struct apply : ::elib::integral_constant<ValType, Val> {};        \
                                                                          \
        template <class A1>                                               \
        struct apply<A1> : ELIB_AUTO_INTC(Val Op A1::type::value) {};     \
                                                                          \
        template <class A1, class A2>                                     \
        struct apply<A1, A2>                                              \
          : ELIB_AUTO_INTC(Val Op A1::type::value Op A2::type::value) {}; \
                                                                          \
        template <class A1, class A2, class A3>                           \
        struct apply<A1, A2, A3>                                          \
          : ELIB_AUTO_INTC(Val Op A1::type::value Op A2::type::value      \
                               Op A3::type::value) {};                    \
                                                                          \
        template <class A1, class A2, class A3, class A4>                 \
        struct apply<A1, A2, A3, A4>                                      \
          : ELIB_AUTO_INTC(Val Op A1::type::value Op A2::type::value      \
                               Op A3::type::value Op A4::type::value) {}; \
                                                                          \
        template <class A1, class A2, class A3, class A4, class A5>       \
        struct apply<A1, A2, A3, A4, A5>                                  \
          : ELIB_AUTO_INTC(Val Op A1::type::value Op A2::type::value      \
                               Op A3::type::value Op A4::type::value      \
                               Op A5::type::value) {};                    \
                                                                          \
        template <                                                        \
            class A1, class A2, class A3, class A4, class A5, class A6    \
        >                                                                 \
        struct apply<A1, A2, A3, A4, A5, A6>                              \
          : ELIB_AUTO_INTC(Val Op A1::type::value Op A2::type::value      \
                               Op A3::type::value Op A4::type::value      \
                               Op A5::type::value Op A6::type::value) {}; \
                                                                          \
        template <                                                        \
            class A1, class A2, class A3, class A4, class A5              \
          , class A6, class A7                                            \
        >                                                                 \
        struct apply<A1, A2, A3, A4, A5, A6, A7>                          \
          : ELIB_AUTO_INTC(Val Op A1::type::value Op A2::type::value      \
                               Op A3::type::value Op A4::type::value      \
                               Op A5::type::value Op A6::type::value      \
                               Op A7::type::value) {};                    \
                                                                          \
        template <                                                        \
            class A1, class A2, class A3, class A4, class A5              \
          , class A6, class A7, class A8                                  \
        >                                                                 \
        struct apply<A1, A2, A3, A4, A5, A6, A7, A8>                      \
          : ELIB_AUTO_INTC(Val Op A1::type::value Op A2::type::value      \
                               Op A3::type::value Op A4::type::value      \
                               Op A5::type::value Op A6::type::value      \
                               Op A7::type::value Op A8::type::value) {}; \
                                                                          \
        template <                                                        \
            class A1, class A2, class A3, class A4, class A5              \
          , class A6, class A7, class A8, class A9                        \
        >                                                                 \
        struct apply<A1, A2, A3, A4, A5, A6, A7, A8, A9>                  \
          : ELIB_AUTO_INTC(Val Op A1::type::value Op A2::type::value      \
                               Op A3::type::value Op A4::type::value      \
                               Op A5::type::value Op A6::type::value      \
                               Op A7::type::value Op A8::type::value      \
                               Op A9::type::value)  {};                   \
    };                                                                    \
                                                                          \
    template <class ValType, ValType Val>                                 \
    struct Impl<false, ValType, Val>                                      \
    {                                                                     \
        template <                                                        \
            class A1, class A2, class A3, class A4, class A5              \
          , class A6, class A7, class A8, class A9, class A10             \
          , class ...Rest                                                 \
        >                                                                 \
        using apply = typename                                            \
            Impl<                                                         \
                sizeof...(Rest) < 10                                      \
              , decltype(Val Op A1::type::value Op A2::type::value        \
                             Op A3::type::value Op A4::type::value        \
                             Op A5::type::value Op A6::type::value        \
                             Op A7::type::value Op A8::type::value        \
                             Op A9::type::value Op A10::type::value)      \
              , Val Op A1::type::value Op A2::type::value                 \
                    Op A3::type::value Op A4::type::value                 \
                    Op A5::type::value Op A6::type::value                 \
                    Op A7::type::value Op A8::type::value                 \
                    Op A9::type::value Op A10::type::value                \
            >::template apply<Rest...>;                                   \
    };                                                                    \
                                                                          \
    template <class T, class ...Rest>                                     \
    using Entry = typename                                                \
        Impl<                                                             \
            sizeof...(Rest) < 10                                          \
          , typename T::type::value_type                                  \
          , T::type::value                                                \
        >::template apply<Rest...>::type
# 
# 
#endif /* ELIB_AUX_META_LEFT_ASSOCIATIVE_EXPRESSION_HPP */