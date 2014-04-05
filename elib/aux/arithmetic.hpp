#ifndef ELIB_AUX_ARITHMETIC_HPP
#define ELIB_AUX_ARITHMETIC_HPP

# include <elib/aux/integral_constant.hpp>
# include <elib/aux/left_associative_expression.hpp>

namespace elib { namespace aux
{
    namespace detail
    {
        ELIB_AUX_LEFT_ASSOC_EXPR(add_apply, add_impl, +);
        ELIB_AUX_LEFT_ASSOC_EXPR(subtract_apply, subtract_impl, -);
        ELIB_AUX_LEFT_ASSOC_EXPR(multiply_apply, multiply_impl, *);
        ELIB_AUX_LEFT_ASSOC_EXPR(divide_apply, divide_impl, /);
    }                                                   // namespace detail

    ////////////////////////////////////////////////////////////////////////////
    template <class T>
    struct negate : ELIB_AUTO_INTC(- T::type::value ) {};

    template <class T>
    using negate_t = ELIB_AUTO_INTC( - T::type::value );

    ////////////////////////////////////////////////////////////////////////////
    template <class A0, class A1, class ...Args>
    struct add : detail::add_apply<A0, A1, Args...> {};

    template <class A0, class A1, class ...Args>
    using add_t = typename detail::add_apply<A0, A1, Args...>::type;

    ////////////////////////////////////////////////////////////////////////////
    // subtract
    template <class A0, class A1, class ...Args>
    struct subtract : detail::subtract_apply<A0, A1, Args...> {};

    template <class A0, class A1, class ...Args>
    using subtract_t = typename detail::subtract_apply<A0, A1, Args...>::type;

    ////////////////////////////////////////////////////////////////////////////
    // multiply
    template <class A0, class A1, class ...Args>
    struct multiply : detail::multiply_apply<A0, A1, Args...> {};

    template <class A0, class A1, class ...Args>
    using multiply_t = typename detail::multiply_apply<A0, A1, Args...>::type;

    ////////////////////////////////////////////////////////////////////////////
    // divide
    template <class A0, class A1, class ...Args>
    struct divide : detail::divide_apply<A0, A1, Args...> {};

    template <class A0, class A1, class ...Args>
    using divide_t = typename detail::divide_apply<A0, A1, Args...>::type;

    ////////////////////////////////////////////////////////////////////////////
    // modulus
    template <class T, class U>
    struct modulus : ELIB_AUTO_INTC( T::type::value % U::type::value ) {};

    template <class T, class U>
    using modulus_t = ELIB_AUTO_INTC( T::type::value % U::type::value );

    ////////////////////////////////////////////////////////////////////////////
    // increment
    template <class T>
    using increment = integral_constant< typename T::value_type, T::value + 1 >;

    template <class T>
    using increment_t = increment<T>;

    template <class T>
    using decrement = integral_constant< typename T::value_type, T::value - 1 >;

    template <class T>
    using decrement_t = decrement<T>;
}}                                                          // namespace elib
#endif /* ELIB_AUX_ARITHMETIC_HPP */