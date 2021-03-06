#ifndef ELIB_AUX_TRAITS_IS_RVALUE_REFERENCE_HPP
#define ELIB_AUX_TRAITS_IS_RVALUE_REFERENCE_HPP

#include <elib/config.hpp>
#include <type_traits>

namespace elib { namespace aux
{
    using std::is_rvalue_reference;
        
# if defined(ELIB_CONFIG_HAS_VARIABLE_TEMPLATES)
    template <class T>
    constexpr bool is_rvalue_reference_v = is_rvalue_reference<T>::value;
# endif
}}                                                           //namespace elib
#endif /* ELIB_AUX_TRAITS_IS_RVALUE_REFERENCE_HPP */
