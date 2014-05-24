#ifndef ELIB_AUX_TRAITS_HAS_IMPLICIT_CONVERSION_HPP
#define ELIB_AUX_TRAITS_HAS_IMPLICIT_CONVERSION_HPP

# include <elib/config.hpp>
# include <elib/aux/integral_constant.hpp>
# include <elib/aux/traits/is_convertible.hpp>

namespace elib { namespace aux
{
    template <class From, class To>
    using has_implicit_conversion = is_convertible<From, To>;
        
# if defined(ELIB_CONFIG_HAS_VARIABLE_TEMPLATES)
    template <class From, class To>
    constexpr bool has_implicit_conversion_v = 
        has_implicit_conversion<From, To>::value;
# endif
}}                                                            // namespace elib
#endif /* ELIB_AUX_TRAITS_HAS_IMPLICIT_CONVERSION_HPP */