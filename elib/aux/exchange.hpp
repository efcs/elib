#ifndef ELIB_AUX_EXCHANGE_HPP
#define ELIB_AUX_EXCHANGE_HPP

# include <elib/aux/forward.hpp>
# include <elib/aux/move.hpp>

namespace elib { namespace aux
{
    template <class T, class U>
    T exchange(T & obj, U && new_val) 
    {
        T old_val = elib::move(obj);
        obj = elib::forward<U>(new_val);
        return old_val;
    }
}}                                                          // namespace elib
namespace elib
{
    using aux::exchange;
}                                                           // namespace elib
#endif /* ELIB_AUX_EXCHANGE_HPP */