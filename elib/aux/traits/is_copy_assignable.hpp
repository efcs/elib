#ifndef ELIB_AUX_TRAITS_IS_COPY_ASSIGNABLE_HPP
#define ELIB_AUX_TRAITS_IS_COPY_ASSIGNABLE_HPP

#include <elib/config.hpp>
#include <type_traits>

namespace elib { namespace aux
{
    using std::is_copy_assignable;
        
# if defined(ELIB_CONFIG_HAS_VARIABLE_TEMPLATES)
    template <class T>
    constexpr bool is_copy_assignable_v = is_copy_assignable<T>::value;
# endif
}}                                                           //namespace elib
#endif /* ELIB_AUX_TRAITS_IS_COPY_ASSIGNABLE_HPP */
