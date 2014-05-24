#ifndef ELIB_AUX_TRAITS_HAS_CONVERSION_HPP
#define ELIB_AUX_TRAITS_HAS_CONVERSION_HPP

# include <elib/config.hpp>
# include <elib/aux/integral_constant.hpp>
# include <elib/aux/traits/has_explicit_conversion.hpp>
# include <elib/aux/traits/has_implicit_conversion.hpp>

namespace elib { namespace aux
{
    template <class From, class To>
    using has_conversion = elib::bool_<
        has_explicit_conversion<From, To>::value
            || has_implicit_conversion<From, To>::value
        >;
        
# if defined(ELIB_CONFIG_HAS_VARIABLE_TEMPLATES)
    template <class From, class To>
    constexpr bool has_conversion_v = has_conversion<From, To>::value;
# endif
}}                                                          // namespace elib
#endif /* ELIB_AUX_TRAITS_HAS_CONVERSION_HPP */