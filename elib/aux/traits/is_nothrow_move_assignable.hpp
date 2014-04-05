#ifndef ELIB_AUX_TRAITS_IS_NOTHROW_MOVE_ASSIGNABLE_HPP
#define ELIB_AUX_TRAITS_IS_NOTHROW_MOVE_ASSIGNABLE_HPP

#include <elib/config.hpp>
#include <type_traits>

namespace elib { namespace aux
{
    namespace traits
    {
        using std::is_nothrow_move_assignable;
        
# if defined(ELIB_CONFIG_HAS_VARIABLE_TEMPLATES)
        template <class T>
        constexpr bool is_nothrow_move_assignable_v = is_nothrow_move_assignable<T>::value;
# endif
    }                                                       //namespace traits
    
    using namespace traits;
}}                                                           //namespace elib
#endif /* ELIB_AUX_TRAITS_IS_NOTHROW_MOVE_ASSIGNABLE_HPP */
