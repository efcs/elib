#ifndef ELIB_AUX_TRAITS_IS_CONVERTIBLE_HPP
#define ELIB_AUX_TRAITS_IS_CONVERTIBLE_HPP

#include <elib/config.hpp>
#include <type_traits>

namespace elib { namespace aux
{
    using std::is_convertible;
        
# if defined(ELIB_CONFIG_HAS_VARIABLE_TEMPLATES)
    template <class T, class U>
    constexpr bool is_convertible_v = is_convertible<T, U>::value;
# endif
}}                                                           //namespace elib
#endif /* ELIB_AUX_TRAITS_IS_CONVERTIBLE_HPP */
