#ifndef ELIB_AUX_TRAITS_IS_UNSIGNED_HPP
#define ELIB_AUX_TRAITS_IS_UNSIGNED_HPP

#include <elib/config.hpp>
#include <type_traits>

namespace elib { namespace aux
{
    namespace traits
    {
        using std::is_unsigned;
        
# if defined(ELIB_CONFIG_HAS_VARIABLE_TEMPLATES)
        template <class T>
        constexpr bool is_unsigned_v = is_unsigned<T>::value;
# endif
    }                                                       //namespace traits
    
    using namespace traits;
}}                                                           //namespace elib
#endif /* ELIB_AUX_TRAITS_IS_UNSIGNED_HPP */
