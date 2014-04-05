#ifndef ELIB_AUX_TRAITS_IS_ASSIGNABLE_HPP
#define ELIB_AUX_TRAITS_IS_ASSIGNABLE_HPP

#include <elib/config.hpp>
#include <type_traits>

namespace elib { namespace aux
{
    namespace traits
    {
        using std::is_assignable;
        
# if defined(ELIB_CONFIG_HAS_VARIABLE_TEMPLATES)
        template <class T, class U>
        constexpr bool is_assignable_v = is_assignable<T, U>::value;
# endif
    }                                                       //namespace traits
    
    using namespace traits;
}}                                                           //namespace elib
#endif /* ELIB_AUX_TRAITS_IS_ASSIGNABLE_HPP */
