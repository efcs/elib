#ifndef ELIB_AUX_TRAITS_HAS_VIRTUAL_DESTRUCTOR_HPP
#define ELIB_AUX_TRAITS_HAS_VIRTUAL_DESTRUCTOR_HPP

#include <elib/config.hpp>
#include <type_traits>

namespace elib { namespace aux
{
    using std::has_virtual_destructor;
        
# if defined(ELIB_CONFIG_HAS_VARIABLE_TEMPLATES)
    template <class T>
    constexpr bool has_virtual_destructor_v = has_virtual_destructor<T>::value;
# endif
}}                                                           //namespace elib
#endif /* ELIB_AUX_TRAITS_HAS_VIRTUAL_DESTRUCTOR_HPP */
