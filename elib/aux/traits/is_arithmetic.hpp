#ifndef ELIB_AUX_TRAITS_IS_ARITHMETIC_HPP
#define ELIB_AUX_TRAITS_IS_ARITHMETIC_HPP

#include <elib/config.hpp>
#include <type_traits>

namespace elib { namespace aux
{
    using std::is_arithmetic;
        
# if defined(ELIB_CONFIG_HAS_VARIABLE_TEMPLATES)
    template <class T>
    constexpr bool is_arithmetic_v = is_arithmetic<T>::value;
# endif
}}                                                           //namespace elib
#endif /* ELIB_AUX_TRAITS_IS_ARITHMETIC_HPP */
