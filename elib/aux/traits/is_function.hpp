#ifndef ELIB_AUX_TRAITS_IS_FUNCTION_HPP
#define ELIB_AUX_TRAITS_IS_FUNCTION_HPP

#include <elib/config.hpp>
#include <type_traits>

namespace elib { namespace aux
{
    using std::is_function;
        
# if defined(ELIB_CONFIG_HAS_VARIABLE_TEMPLATES)
    template <class T>
    constexpr bool is_function_v = is_function<T>::value;
# endif
}}                                                           //namespace elib
#endif /* ELIB_AUX_TRAITS_IS_FUNCTION_HPP */
