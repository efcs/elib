#ifndef ELIB_AUX_FORWARD_HPP
#define ELIB_AUX_FORWARD_HPP

# include <elib/aux/traits/is_lvalue_reference.hpp>
# include <elib/aux/traits/remove_reference.hpp>

namespace elib { namespace aux
{
    ////////////////////////////////////////////////////////////////////////
    // forward
    template <class T>
    constexpr T&& 
    forward(typename aux::remove_reference<T>::type& t) noexcept
    { 
        return static_cast<T&&>(t);
    }

    template <class T>
    constexpr T&& 
    forward(typename aux::remove_reference<T>::type&& t) noexcept
    {
        return static_cast<T &&>(t);
        static_assert(
            !aux::is_lvalue_reference<T>::value
            , "elib::forward called with lvalue reference"
        );
    }
}}                                                          // namespace elib
namespace elib
{
    using aux::forward;
}                                                           // namespace elib
#endif /* ELIB_AUX_FORWARD_HPP */