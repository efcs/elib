#ifndef ELIB_AUX_TRAITS_IS_INTEGRAL_HPP
#define ELIB_AUX_TRAITS_IS_INTEGRAL_HPP

#include <elib/config.hpp>
#include <type_traits>

namespace elib { namespace aux
{
    using std::is_integral;
        
# if defined(ELIB_CONFIG_HAS_VARIABLE_TEMPLATES)
    template <class T>
    constexpr bool is_integral_v = is_integral<T>::value;
# endif
}}                                                           //namespace elib
#endif /* ELIB_AUX_TRAITS_IS_INTEGRAL_HPP */
