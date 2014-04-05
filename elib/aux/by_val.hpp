#ifndef ELIB_AUX_BY_VAL_HPP
#define ELIB_AUX_BY_VAL_HPP

# include <elib/aux/common.hpp>

namespace elib { namespace aux
{
    namespace detail
    {
        ////////////////////////////////////////////////////////////////////////
        template <class T>
        constexpr auto by_val_impl(T & t, int)
        ELIB_AUTO_RETURN_NOEXCEPT( T(t) )

        template <class T>
        constexpr auto by_val_impl(T const& t, int)
        ELIB_AUTO_RETURN_NOEXCEPT( T(t) )

        template <class T>
        constexpr auto by_val_impl(T && t, int)
        ELIB_AUTO_RETURN_NOEXCEPT( T(static_cast<T &&>(t)) )

        // TODO
        // does it make sense to have this? 
        template <class T>
        constexpr auto by_val_impl(T const& t, long)
        ELIB_AUTO_RETURN_NOEXCEPT(t)
    }                                                   // namespace detail

    ////////////////////////////////////////////////////////////////////////
    struct by_val_
    {
        template <class T>
        constexpr auto operator()(T && t) const
        ELIB_AUTO_RETURN_NOEXCEPT(
            detail::by_val_impl(static_cast<T &&>(t), 1)
        )
    };

    constexpr const by_val_ by_val{};
}}                                                          // namespace elib
#endif /* ELIB_AUX_BY_VAL_HPP */