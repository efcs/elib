#ifndef ELIB_AUX_TRAITS_IS_TRIVIALLY_DESTRUCTIBLE_HPP
#define ELIB_AUX_TRAITS_IS_TRIVIALLY_DESTRUCTIBLE_HPP

#include <elib/config.hpp>
#include <type_traits>

namespace elib { namespace aux
{
    namespace traits
    {
# if !defined(ELIB_CONFIG_LIBSTDCXX_HAS_TRIVIAL_DESTRUCTOR_WORKAROUND)
        using std::is_trivially_destructible;
# else
        template <class T>
        using is_trivially_destructible = std::has_trivial_destructor<T>;
# endif
        
# if defined(ELIB_CONFIG_HAS_VARIABLE_TEMPLATES)
        template <class T>
        constexpr bool is_trivially_destructible_v = is_trivially_destructible<T>::value;
# endif
    }                                                       //namespace traits
    
    using namespace traits;
}}                                                           //namespace elib
#endif /* ELIB_AUX_TRAITS_IS_TRIVIALLY_DESTRUCTIBLE_HPP */
