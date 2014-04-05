#ifndef ELIB_AUX_TRAITS_IS_MOVE_ASSIGNABLE_HPP
#define ELIB_AUX_TRAITS_IS_MOVE_ASSIGNABLE_HPP

#include <elib/config.hpp>
#include <type_traits>

namespace elib { namespace aux
{
    namespace traits
    {
        using std::is_move_assignable;
        
# if defined(ELIB_CONFIG_HAS_VARIABLE_TEMPLATES)
        template <class T>
        constexpr bool is_move_assignable_v = is_move_assignable<T>::value;
# endif
    }                                                       //namespace traits
    
    using namespace traits;
}}                                                           //namespace elib
#endif /* ELIB_AUX_TRAITS_IS_MOVE_ASSIGNABLE_HPP */
