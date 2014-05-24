#ifndef ELIB_AUX_TRAITS_IS_POLYMORPHIC_HPP
#define ELIB_AUX_TRAITS_IS_POLYMORPHIC_HPP

#include <elib/config.hpp>
#include <type_traits>

namespace elib { namespace aux
{
    using std::is_polymorphic;
        
# if defined(ELIB_CONFIG_HAS_VARIABLE_TEMPLATES)
    template <class T>
    constexpr bool is_polymorphic_v = is_polymorphic<T>::value;
# endif
}}                                                           //namespace elib
#endif /* ELIB_AUX_TRAITS_IS_POLYMORPHIC_HPP */
