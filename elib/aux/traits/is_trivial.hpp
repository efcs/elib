#ifndef ELIB_AUX_TRAITS_IS_TRIVIAL_HPP
#define ELIB_AUX_TRAITS_IS_TRIVIAL_HPP

#include <elib/config.hpp>
#include <type_traits>

namespace elib { namespace aux
{
    using std::is_trivial;
        
# if defined(ELIB_CONFIG_HAS_VARIABLE_TEMPLATES)
    template <class T>
    constexpr bool is_trivial_v = is_trivial<T>::value;
# endif
}}                                                           //namespace elib
#endif /* ELIB_AUX_TRAITS_IS_TRIVIAL_HPP */
