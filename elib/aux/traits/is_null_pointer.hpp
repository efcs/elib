#ifndef ELIB_AUX_TRAITS_IS_NULL_POINTER_HPP
#define ELIB_AUX_TRAITS_IS_NULL_POINTER_HPP

#include <elib/config.hpp>
# if __cplusplus >= 201303L
#   include <type_traits>
# else
#   include <elib/aux/traits/is_same.hpp>
# endif

namespace elib { namespace aux
{
# if __cplusplus >= 201303L
    using std::is_null_pointer;
# else
    template <class T>
    using is_null_pointer = is_same<T, decltype(nullptr)>;
# endif
  
# if defined(ELIB_CONFIG_HAS_VARIABLE_TEMPLATES)
    template <class T>
    constexpr bool is_null_pointer_v = is_null_pointer<T>::value;
# endif
}}                                                           //namespace elib
#endif /* ELIB_AUX_TRAITS_IS_NULL_POINTER_HPP */
