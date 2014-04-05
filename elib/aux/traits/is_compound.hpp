#ifndef ELIB_AUX_TRAITS_IS_COMPOUND_HPP
#define ELIB_AUX_TRAITS_IS_COMPOUND_HPP

#include <elib/config.hpp>
#include <type_traits>

namespace elib { namespace aux
{
    namespace traits
    {
        using std::is_compound;
        
# if defined(ELIB_CONFIG_HAS_VARIABLE_TEMPLATES)
        template <class T>
        constexpr bool is_compound_v = is_compound<T>::value;
# endif
    }                                                       //namespace traits
    
    using namespace traits;
}}                                                           //namespace elib
#endif /* ELIB_AUX_TRAITS_IS_COMPOUND_HPP */
