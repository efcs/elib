#ifndef ELIB_AUX_TRAITS_IS_CONST_HPP
#define ELIB_AUX_TRAITS_IS_CONST_HPP

#include <elib/config.hpp>
#include <type_traits>

namespace elib { namespace aux
{
    namespace traits
    {
        using std::is_const;
        
# if defined(ELIB_CONFIG_HAS_VARIABLE_TEMPLATES)
        template <class T>
        constexpr bool is_const_v = is_const<T>::value;
# endif
    }                                                       //namespace traits
    
    using namespace traits;
}}                                                           //namespace elib
#endif /* ELIB_AUX_TRAITS_IS_CONST_HPP */
