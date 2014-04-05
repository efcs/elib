#ifndef ELIB_AUX_TRAITS_IS_IMPLICITLY_CASTABLE_HPP
#define ELIB_AUX_TRAITS_IS_IMPLICITLY_CASTABLE_HPP

# include <elib/config.hpp>
# include <elib/aux/traits/is_convertible.hpp>

namespace elib { namespace aux
{
    namespace traits
    {
        template <class From, class To>
        using is_implicitly_castable = is_convertible<From, To>;
        
# if defined(ELIB_CONFIG_HAS_VARIABLE_TEMPLATES)
        template <class From, class To>
        constexpr bool is_implicitly_castable_v = 
            is_implicitly_castable<From, To>::value;
# endif
    }                                                       // namespace traits
    
    using namespace traits;
}}                                                          // namespace elib
#endif /* ELIB_AUX_TRAITS_IS_IMPLICITLY_CASTABLE_HPP */