#ifndef ELIB_AUX_ALWAYS_HPP
#define ELIB_AUX_ALWAYS_HPP

# include <elib/aux/integral_constant.hpp>

/// A set of meta-programming helpers that always evaluate to a given type.
/// They are usualy used as a dummy context to perform SFINAE or to make
/// a static_assert dependant on a template parameter (so it only fires when 
/// the template is instantiated).
/// NOTE: always_void is the same as the void_t type commonly seen in standard
/// proposals
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