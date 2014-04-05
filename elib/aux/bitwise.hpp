#ifndef ELIB_AUX_BITWISE_HPP
#define ELIB_AUX_BITWISE_HPP

# include <elib/aux/integral_constant.hpp>
# include <elib/aux/left_associative_expression.hpp>

namespace elib { namespace aux
{
    namespace detail
    {
        ELIB_AUX_LEFT_ASSOC_EXPR(bitand_apply, bitand_impl, &);
        ELIB_AUX_LEFT_ASSOC_EXPR(bitor_apply, bitor_impl, |);
        ELIB_AUX_LEFT_ASSOC_EXPR(bitxor_apply, bitxor_impl, ^);
    }                                                   // namespace detail

    ////////////////////////////////////////////////////////////////////////////
    // bitnegate_
    template <class T>
    struct bitnegate_ : ELIB_AUTO_INTC( ~ T::type::value ) {};

    template <class T>
    using bitnegate_t = ELIB_AUTO_INTC( ~ T::type::value );

    ////////////////////////////////////////////////////////////////////////////
    // bitand_
    template <class A0, class A1, class ...Args>
    struct bitand_ : detail::bitand_apply<A0, A1, Args...> {};

    template <class A0, class A1, class ...Args>
    using bitand_t = typename detail::bitand_apply<A0, A1, Args...>::type;

    ////////////////////////////////////////////////////////////////////////////
    // bitor_
    template <class A0, class A1, class ...Args>
    struct bitor_ : detail::bitor_apply<A0, A1, Args...> {};

    template <class A0, class A1, class ...Args>
    using bitor_t = typename detail::bitor_apply<A0, A1, Args...>::type;

    ////////////////////////////////////////////////////////////////////////////
    // bitxor_
    template <class A0, class A1, class ...Args>
    struct bitxor_ : detail::bitxor_apply<A0, A1, Args...> {};

    template <class A0, class A1, class ...Args>
    using bitxor_t = typename detail::bitxor_apply<A0, A1, Args...>::type;

    ////////////////////////////////////////////////////////////////////////////
    // shift_left
    template <class T, class U>
    struct shift_left : ELIB_AUTO_INTC(T::type::value << U::type::value) {};

    template <class T, class U>
    using shift_left_t = ELIB_AUTO_INTC( T::type::value << U::type::value );

    ////////////////////////////////////////////////////////////////////////////
    // shift_right
    template <class T, class U>
    struct shift_right : ELIB_AUTO_INTC(( T::type::value >> U::type::value )) {};

    template <class T, class U>
    using shift_right_t = ELIB_AUTO_INTC(( T::type::value >> U::type::value ));
}}                                                          // namespace elib
#endif /* ELIB_AUX_BITWISE_HPP */