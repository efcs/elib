#ifndef ELIB_AUX_TRAITS_IS_FUNDAMENTAL_HPP
#define ELIB_AUX_TRAITS_IS_FUNDAMENTAL_HPP

#include <elib/config.hpp>
#include <type_traits>

namespace elib { namespace aux
{
    using std::is_fundamental;
        
# if defined(ELIB_CONFIG_HAS_VARIABLE_TEMPLATES)
    template <class T>
    constexpr bool is_fundamental_v = is_fundamental<T>::value;
# endif
}}                                                           //namespace elib
#endif /* ELIB_AUX_TRAITS_IS_FUNDAMENTAL_HPP */
