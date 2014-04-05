#ifndef ELIB_AUX_TRAITS_IS_REFERENCE_HPP
#define ELIB_AUX_TRAITS_IS_REFERENCE_HPP

#include <elib/config.hpp>
#include <type_traits>

namespace elib { namespace aux
{
    namespace traits
    {
        using std::is_reference;
        
# if defined(ELIB_CONFIG_HAS_VARIABLE_TEMPLATES)
        template <class T>
        constexpr bool is_reference_v = is_reference<T>::value;
# endif
    }                                                       //namespace traits
    
    using namespace traits;
}}                                                           //namespace elib
#endif /* ELIB_AUX_TRAITS_IS_REFERENCE_HPP */
