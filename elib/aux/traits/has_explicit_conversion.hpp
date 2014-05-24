#ifndef ELIB_AUX_TRAITS_HAS_EXPLICIT_CONVERSION_HPP
#define ELIB_AUX_TRAITS_HAS_EXPLICIT_CONVERSION_HPP

# include <elib/config.hpp>
# include <elib/aux/integral_constant.hpp>
# include <elib/aux/traits/is_convertible.hpp>
# include <elib/aux/traits/is_explicitly_convertible.hpp>


namespace elib { namespace aux
{
    namespace traits
    {
        template <class From, class To>
        using has_explicit_conversion = elib::bool_<
            is_explicitly_convertible<From, To>::value
            && not is_convertible<From, To>::value
          >;
        
# if defined(ELIB_CONFIG_HAS_VARIABLE_TEMPLATES)
        template <class From, class To>
        constexpr bool has_explicit_conversion_v = 
            has_explicit_conversion<From, To>::value;
# endif
    }                                                       // namespace traits
    
    using namespace traits;
}}                                                          // namespace elib
#endif /* ELIB_AUX_TRAITS_HAS_EXPLICIT_CONVERSION_HPP */