#ifndef ELIB_AUX_TRAITS_IS_STANDARD_LAYOUT_HPP
#define ELIB_AUX_TRAITS_IS_STANDARD_LAYOUT_HPP

#include <elib/config.hpp>
#include <type_traits>

namespace elib { namespace aux
{
    namespace traits
    {
        using std::is_standard_layout;
        
# if defined(ELIB_CONFIG_HAS_VARIABLE_TEMPLATES)
        template <class T>
        constexpr bool is_standard_layout_v = is_standard_layoutt<T>::value;
# endif
    }                                                       //namespace traits
    
    using namespace traits;
}}                                                           //namespace elib
#endif /* ELIB_AUX_TRAITS_IS_STANDARD_LAYOUT_HPP */
