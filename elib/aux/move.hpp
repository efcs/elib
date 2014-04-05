#ifndef ELIB_AUX_MOVE_HPP
#define ELIB_AUX_MOVE_HPP

# include <elib/aux/traits/conditional.hpp>
# include <elib/aux/traits/is_copy_constructible.hpp>
# include <elib/aux/traits/is_nothrow_move_constructible.hpp>
# include <elib/aux/traits/remove_reference.hpp>

namespace elib { namespace aux
{
    ////////////////////////////////////////////////////////////////////////
    // move
    template <class T>
    constexpr typename aux::remove_reference<T>::type&& 
    move(T&& t) noexcept
    {
        return static_cast<typename aux::remove_reference<T>::type &&>(t);
    }
            
    /////////////////////////////////////////////////////////////////////////
    // move_if_noexcept
    template <class T> 
    constexpr 
        aux::conditional_t<
            ! aux::is_nothrow_move_constructible<T>::value 
            && aux::is_copy_constructible<T>::value
        , const T&
        , T&&
        >
    move_if_noexcept(T& x) noexcept
    {
        return aux::move(x);
    }
}}                                                          // namespace elib
namespace elib
{
    using aux::move;
    using aux::move_if_noexcept;
}                                                           // namespace elib
#endif /* ELIB_AUX_MOVE_HPP */