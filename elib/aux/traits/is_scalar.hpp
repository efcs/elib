#ifndef ELIB_AUX_TRAITS_IS_SCALAR_HPP
#define ELIB_AUX_TRAITS_IS_SCALAR_HPP

#include <elib/config.hpp>
#include <type_traits>

namespace elib { namespace aux
{
    namespace traits
    {
        using std::is_scalar;
        
# if defined(ELIB_CONFIG_HAS_VARIABLE_TEMPLATES)
        template <class T>
        constexpr bool is_scalar_v = is_scalar<T>::value;
# endif
    }                                                       //namespace traits
    
    using namespace traits;
}}                                                           //namespace elib
#endif /* ELIB_AUX_TRAITS_IS_SCALAR_HPP */
