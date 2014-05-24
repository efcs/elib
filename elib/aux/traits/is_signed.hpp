#ifndef ELIB_AUX_TRAITS_IS_SIGNED_HPP
#define ELIB_AUX_TRAITS_IS_SIGNED_HPP

#include <elib/config.hpp>
#include <type_traits>

namespace elib { namespace aux
{
    using std::is_signed;
        
# if defined(ELIB_CONFIG_HAS_VARIABLE_TEMPLATES)
    template <class T>
    constexpr bool is_signed_v = is_signed<T>::value;
# endif
}}                                                           //namespace elib
#endif /* ELIB_AUX_TRAITS_IS_SIGNED_HPP */
