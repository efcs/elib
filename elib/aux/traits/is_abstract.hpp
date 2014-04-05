#ifndef ELIB_AUX_TRAITS_IS_ABSTRACT_HPP
#define ELIB_AUX_TRAITS_IS_ABSTRACT_HPP

#include <elib/config.hpp>
#include <type_traits>

namespace elib { namespace aux
{
    namespace traits
    {
        using std::is_abstract;
        
# if defined(ELIB_CONFIG_HAS_VARIABLE_TEMPLATES)
        template <class T>
        constexpr bool is_abstract_v = is_abstract<T>::value;
# endif
    }                                                       //namespace traits
    
    using namespace traits;
}}                                                           //namespace elib
#endif /* ELIB_AUX_TRAITS_IS_ABSTRACT_HPP */
