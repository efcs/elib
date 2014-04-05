#ifndef ELIB_AUX_TRAITS_IS_INTEGRAL_ENUM_HPP
#define ELIB_AUX_TRAITS_IS_INTEGRAL_ENUM_HPP

# include <elib/aux/integral_constant.hpp>
# include <elib/aux/traits/is_enum.hpp>
# include <elib/aux/traits/is_integral.hpp>

namespace elib { namespace aux
{
    namespace traits
    {
        template <class T>
        using is_integral_enum = elib::bool_<
            is_integral<T>::value || is_enum<T>::value
          >;
        
# if defined(ELIB_CONFIG_HAS_VARIABLE_TEMPLATES)
        template <class T>
        constexpr bool is_integral_enum_v = is_integral_enum<T>::value;
# endif
    }                                                       // namespace traits
}}                                                          // namespace elib
#endif /* ELIB_AUX_TRAITS_IS_INTEGRAL_ENUM_HPP */