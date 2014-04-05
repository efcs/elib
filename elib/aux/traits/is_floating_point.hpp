#ifndef ELIB_AUX_TRAITS_IS_FLOATING_POINT_HPP
#define ELIB_AUX_TRAITS_IS_FLOATING_POINT_HPP

#include <elib/config.hpp>
#include <type_traits>

namespace elib { namespace aux
{
    namespace traits
    {
        using std::is_floating_point;
        
# if defined(ELIB_CONFIG_HAS_VARIABLE_TEMPLATES)
        template <class T>
        constexpr bool is_floating_point_v = is_floating_point<T>::value;
# endif
    }                                                       //namespace traits
    
    using namespace traits;
}}                                                           //namespace elib
#endif /* ELIB_AUX_TRAITS_IS_FLOATING_POINT_HPP */
