#ifndef ELIB_AUX_TRAITS_IS_NOTHROW_COPY_CONSTRUCTIBLE_HPP
#define ELIB_AUX_TRAITS_IS_NOTHROW_COPY_CONSTRUCTIBLE_HPP

#include <elib/config.hpp>
#include <type_traits>

namespace elib { namespace aux
{
    using std::is_nothrow_copy_constructible;
        
# if defined(ELIB_CONFIG_HAS_VARIABLE_TEMPLATES)
    template <class T>
    constexpr bool is_nothrow_copy_constructible_v = is_nothrow_copy_constructible<T>::value;
# endif
}}                                                           //namespace elib
#endif /* ELIB_AUX_TRAITS_IS_NOTHROW_COPY_CONSTRUCTIBLE_HPP */
