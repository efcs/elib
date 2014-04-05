#ifndef ELIB_AUX_TRAITS_IS_CONSTRUCTIBLE_HPP
#define ELIB_AUX_TRAITS_IS_CONSTRUCTIBLE_HPP

#include <elib/config.hpp>
#include <type_traits>

namespace elib { namespace aux
{
    namespace traits
    {
        using std::is_constructible;
        
# if defined(ELIB_CONFIG_HAS_VARIABLE_TEMPLATES)
        template <class T, class ...Args>
        constexpr bool is_constructible_v = is_constructible<T, Args...>::value;
# endif
    }                                                       //namespace traits
    
    using namespace traits;
}}                                                           //namespace elib
#endif /* ELIB_AUX_TRAITS_IS_CONSTRUCTIBLE_HPP */
