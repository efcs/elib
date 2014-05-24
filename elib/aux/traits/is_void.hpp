#ifndef ELIB_AUX_TRAITS_IS_VOID_HPP
#define ELIB_AUX_TRAITS_IS_VOID_HPP

#include <elib/config.hpp>
#include <type_traits>

namespace elib { namespace aux
{
    using std::is_void;
        
# if defined(ELIB_CONFIG_HAS_VARIABLE_TEMPLATES)
    template <class T>
    constexpr bool is_void_v = is_void<T>::value;
# endif
}}                                                           //namespace elib
#endif /* ELIB_AUX_TRAITS_IS_VOID_HPP */
