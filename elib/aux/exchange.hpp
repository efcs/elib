#ifndef ELIB_AUX_EXCHANGE_HPP
#define ELIB_AUX_EXCHANGE_HPP

# include <elib/aux/auto_return.hpp>
# include <elib/aux/declval.hpp>
# include <elib/aux/forward.hpp>
# include <elib/aux/integral_constant.hpp>
# include <elib/aux/move.hpp>

namespace elib { namespace aux
{
    namespace detail
    {
        ////////////////////////////////////////////////////////////////////////
        template <class T, class U>
        inline T exchange_impl(T & obj, U && new_val, elib::true_) 
            noexcept(noexcept(T(elib::move(obj))))
        {
            T old_val = elib::move(obj);
            obj = elib::forward<U>(new_val);
            return old_val;
        }
        
        template <class T, class U>
        inline T exchange_impl(T & obj, U && new_val, elib::false_)
            noexcept(false)
        {
            T old_val = static_cast<T const &>(obj);
            obj = elib::forward<U>(new_val);
            return old_val;
        }
    }                                                       // namespace detail
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class T, class U
      , class IsNoExcept = elib::bool_<noexcept(noexcept(
            elib::declval<T &>() = elib::declval<U>()
          ))>
      >
    inline T exchange(T & obj, U && new_val) 
    ELIB_RETURN_NOEXCEPT(
        detail::exchange_impl(
            obj, elib::forward<U>(new_val)
          , IsNoExcept{}
        ))
        
}}                                                          // namespace elib
namespace elib
{
    using aux::exchange;
}                                                           // namespace elib
#endif /* ELIB_AUX_EXCHANGE_HPP */