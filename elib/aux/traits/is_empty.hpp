#ifndef ELIB_AUX_TRAITS_IS_EMPTY_HPP
#define ELIB_AUX_TRAITS_IS_EMPTY_HPP

#include <elib/config.hpp>
#include <type_traits>

namespace elib { namespace aux
{
    namespace traits
    {
        using std::is_empty;
        
# if defined(ELIB_CONFIG_HAS_VARIABLE_TEMPLATES)
        template <class T>
        constexpr bool is_empty_v = is_empty<T>::value;
# endif
    }                                                       //namespace traits
    
    using namespace traits;
}}                                                           //namespace elib
#endif /* ELIB_AUX_TRAITS_IS_EMPTY_HPP */
