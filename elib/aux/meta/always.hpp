#ifndef ELIB_AUX_META_ALWAYS_HPP
#define ELIB_AUX_META_ALWAYS_HPP

# include <elib/aux/integral_constant.hpp>

namespace elib { namespace aux
{
    namespace detail
    {
        template <class Always, class ...Ignored>
        struct _always
        {
                using type = Always;
        };
    }                                                   // namespace detail

    template <class ...T>
    using always = typename aux::detail::_always<true_, T...>::type;

    template <class ...T>
    using never = typename aux::detail::_always<false_, T...>::type;

    template <class ...T>
    using always_void = typename aux::detail::_always<void, T...>::type;
}}                                                          // namespace elib
#endif /* ELIB_AUX_META_ALWAYS_HPP */