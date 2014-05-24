#ifndef ELIB_AUX_TRAITS_REMOVE_VOLATILE_HPP
#define ELIB_AUX_TRAITS_REMOVE_VOLATILE_HPP

#include <type_traits>

namespace elib { namespace aux
{
    using std::remove_volatile;
        
    template <class T>
    using remove_volatile_t = typename remove_volatile<T>::type;
}}                                                           //namespace elib
#endif /* ELIB_AUX_TRAITS_REMOVE_VOLATILE_HPP */
