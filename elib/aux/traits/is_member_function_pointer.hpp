#ifndef ELIB_AUX_TRAITS_IS_MEMBER_FUNCTION_POINTER_HPP
#define ELIB_AUX_TRAITS_IS_MEMBER_FUNCTION_POINTER_HPP

#include <elib/config.hpp>
#include <type_traits>

namespace elib { namespace aux
{
    namespace traits
    {
        using std::is_member_function_pointer;
        
# if defined(ELIB_CONFIG_HAS_VARIABLE_TEMPLATES)
        template <class T>
        constexpr bool is_member_function_pointer_v = is_member_function_pointer<T>::value;
# endif
    }                                                       //namespace traits
    
    using namespace traits;
}}                                                           //namespace elib
#endif /* ELIB_AUX_TRAITS_IS_MEMBER_FUNCTION_POINTER_HPP */
