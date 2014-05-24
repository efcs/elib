#ifndef ELIB_AUX_TRAITS_IS_EXPLICITLY_CONVERTIBLE_HPP
#define ELIB_AUX_TRAITS_IS_EXPLICITLY_CONVERTIBLE_HPP

# include <elib/config.hpp>
# include <elib/aux/integral_constant.hpp>
# include <elib/aux/enable_if.hpp>
# include <elib/aux/declval.hpp>

namespace elib { namespace aux
{
    namespace detail
    {
        template <
            class From, class To
          , ELIB_ENABLE_IF_VALID_EXPR( static_cast<To>(declval<From>()) )
          >
        elib::true_ is_explicitly_convertible_impl(int);
            
        template <class, class>
        elib::false_ is_explicitly_convertible_impl(long);
    }                                                       // namespace detail
        
    template <class From, class To>
    using is_explicitly_convertible = 
        decltype( detail::is_explicitly_convertible_impl<From, To>(0) );
        
# if defined(ELIB_CONFIG_HAS_VARIABLE_TEMPLATES)
    template <class From, class To>
    constexpr bool is_explicitly_convertible_v = 
        is_explicitly_convertible<From, To>::value;
# endif
}}                                                          // namespace elib
#endif /* ELIB_AUX_TRAITS_IS_EXPLICITLY_CONVERTIBLE_HPP */