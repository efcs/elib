#ifndef ELIB_AUX_TRAITS_RANK_HPP
#define ELIB_AUX_TRAITS_RANK_HPP

#include <elib/config.hpp>
#include <type_traits>

namespace elib { namespace aux
{
    using std::rank;
        
# if defined(ELIB_CONFIG_HAS_VARIABLE_TEMPLATES)
    template <class T>
    constexpr bool rank_v = rank<T>::value;
# endif
}}                                                           //namespace elib
#endif /* ELIB_AUX_TRAITS_RANK_HPP */
