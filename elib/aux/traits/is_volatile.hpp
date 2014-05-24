#ifndef ELIB_AUX_TRAITS_IS_VOLATILE_HPP
#define ELIB_AUX_TRAITS_IS_VOLATILE_HPP

#include <elib/config.hpp>
#include <type_traits>

namespace elib { namespace aux
{
    using std::is_volatile;
        
# if defined(ELIB_CONFIG_HAS_VARIABLE_TEMPLATES)
    template <class T>
    constexpr bool is_volatile_v = is_volatile<T>::value;
# endif
}}                                                           //namespace elib
#endif /* ELIB_AUX_TRAITS_IS_VOLATILE_HPP */
