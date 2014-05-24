#ifndef ELIB_AUX_TRAITS_MAKE_UNSIGNED_HPP
#define ELIB_AUX_TRAITS_MAKE_UNSIGNED_HPP

#include <type_traits>

namespace elib { namespace aux
{
    using std::make_unsigned;
        
    template <class T>
    using make_unsigned_t = typename make_unsigned<T>::type;
}}                                                           //namespace elib
#endif /* ELIB_AUX_TRAITS_MAKE_UNSIGNED_HPP */
