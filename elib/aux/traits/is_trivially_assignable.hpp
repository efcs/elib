#ifndef ELIB_AUX_TRAITS_IS_TRIVIALLY_ASSIGNABLE_HPP
#define ELIB_AUX_TRAITS_IS_TRIVIALLY_ASSIGNABLE_HPP

#include <elib/config.hpp>
#include <type_traits>

namespace elib { namespace aux
{
    namespace traits
    {
# if !ELIB_WORKAROUND(ELIB_CONFIG_LIBSTDCXX, LIBSTDCXX_LIMITED_TYPE_TRAITS)
        using std::is_trivially_assignable;
        
#   if defined(ELIB_CONFIG_HAS_VARIABLE_TEMPLATES)
        template <class T, class U>
        constexpr bool is_trivially_assignable_v = is_trivially_assignable<T, U>::value;
#   endif
# endif /* LIBSTDCXX_LIMITED_TYPE_TRAITS */
    }                                                       //namespace traits
    
    using namespace traits;
}}                                                           //namespace elib
#endif /* ELIB_AUX_TRAITS_IS_TRIVIALLY_ASSIGNABLE_HPP */
