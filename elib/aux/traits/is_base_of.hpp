#ifndef ELIB_AUX_TRAITS_IS_BASE_OF_HPP
#define ELIB_AUX_TRAITS_IS_BASE_OF_HPP

#include <elib/config.hpp>
#include <type_traits>

namespace elib { namespace aux
{
    namespace traits
    {
        using std::is_base_of;
        
# if defined(ELIB_CONFIG_HAS_VARIABLE_TEMPLATES)
        template <class T, class U>
        constexpr bool is_base_of_v = is_base_of<T, U>::value;
# endif
    }                                                       //namespace traits
    
    using namespace traits;
}}                                                           //namespace elib
#endif /* ELIB_AUX_TRAITS_IS_BASE_OF_HPP */
