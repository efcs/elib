#ifndef ELIB_AUX_ALWAYS_HPP
#define ELIB_AUX_ALWAYS_HPP

# include <elib/aux/integral_constant.hpp>

namespace elib { namespace aux
{
    namespace detail
    {
        template <class Always, class ...Ignored>
        struct always_impl
        {
                using type = Always;
        };
    }                                                   // namespace detail

    template <class ...T>
    using always = typename aux::detail::always_impl<elib::true_, T...>::type;

    template <class ...T>
    using never = typename aux::detail::always_impl<elib::false_, T...>::type;

    template <class ...T>
    using always_void = typename aux::detail::always_impl<void, T...>::type;
}}                                                          // namespace elib
#endif /* ELIB_AUX_ALWAYS_HPP */