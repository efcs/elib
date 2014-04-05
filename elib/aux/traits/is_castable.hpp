#ifndef ELIB_AUX_TRAITS_IS_CASTABLE_HPP
# define ELIB_AUX_TRAITS_IS_CASTABLE_HPP

# include <elib/config.hpp>
# include <elib/aux/integral_constant.hpp>
# include <elib/aux/traits/is_implicitly_castable.hpp>
# include <elib/aux/traits/is_explicitly_castable.hpp>

namespace elib { namespace aux
{
    namespace traits
    {
        template <class From, class To>
        using is_castable = elib::bool_<
            is_implicitly_castable<From, To>::value
              || is_explicitly_castable<From, To>::value
          >;
        
# if defined(ELIB_CONFIG_HAS_VARIABLE_TEMPLATES)
        template <class From, class To>
        constexpr bool is_castable_v = is_castable<From, To>::value;
# endif
    }                                                       // namespace traits
}}                                                          // namespace elib
#endif /* ELIB_AUX_TRAITS_IS_CASTABLE_HPP */