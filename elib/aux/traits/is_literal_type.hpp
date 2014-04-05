#ifndef ELIB_AUX_TRAITS_IS_LITERAL_TYPE_HPP
#define ELIB_AUX_TRAITS_IS_LITERAL_TYPE_HPP

#include <elib/config.hpp>
#include <type_traits>

namespace elib { namespace aux
{
    namespace traits
    {
        using std::is_literal_type;
        
# if defined(ELIB_CONFIG_HAS_VARIABLE_TEMPLATES)
        template <class T>
        constexpr bool is_literal_type_v = is_literal_type<T>::value;
# endif
    }                                                       //namespace traits
    
    using namespace traits;
}}                                                           //namespace elib
#endif /* ELIB_AUX_TRAITS_IS_LITERAL_TYPE_HPP */
