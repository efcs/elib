#ifndef ELIB_AUX_TRAITS_EXTENT_HPP
#define ELIB_AUX_TRAITS_EXTENT_HPP

#include <elib/config.hpp>
#include <type_traits>

namespace elib { namespace aux
{
    using std::extent;
        
# if defined(ELIB_CONFIG_HAS_VARIABLE_TEMPLATES)
    template <class T, unsigned N = 0>
    constexpr bool extent_v = extent<T, N>::value;
# endif
}}                                                           //namespace elib
#endif /* ELIB_AUX_TRAITS_EXTENT_HPP */
