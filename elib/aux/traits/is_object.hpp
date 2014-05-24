#ifndef ELIB_AUX_TRAITS_IS_OBJECT_HPP
#define ELIB_AUX_TRAITS_IS_OBJECT_HPP

#include <elib/config.hpp>
#include <type_traits>

namespace elib { namespace aux
{
    using std::is_object;
        
# if defined(ELIB_CONFIG_HAS_VARIABLE_TEMPLATES)
    template <class T>
    constexpr bool is_object_v = is_object<T>::value;
# endif
}}                                                           //namespace elib
#endif /* ELIB_AUX_TRAITS_IS_OBJECT_HPP */
