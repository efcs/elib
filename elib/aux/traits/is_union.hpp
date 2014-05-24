#ifndef ELIB_AUX_TRAITS_IS_UNION_HPP
#define ELIB_AUX_TRAITS_IS_UNION_HPP

#include <elib/config.hpp>
#include <type_traits>

namespace elib { namespace aux
{
    using std::is_union;
        
# if defined(ELIB_CONFIG_HAS_VARIABLE_TEMPLATES)
    template <class T>
    constexpr bool is_union_v = is_union<T>::value;
# endif
}}                                                           //namespace elib
#endif /* ELIB_AUX_TRAITS_IS_UNION_HPP */
