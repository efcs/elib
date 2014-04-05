#ifndef ELIB_AUX_TRAITS_IS_EXPLICITLY_CASTABLE_HPP
#define ELIB_AUX_TRAITS_IS_EXPLICITLY_CASTABLE_HPP

# include <elib/config.hpp>
# include <elib/aux/integral_constant.hpp>
# include <elib/aux/enable_if.hpp>
# include <elib/aux/declval.hpp>

namespace elib { namespace aux
{
    namespace traits
    {
        namespace traits_detail
        {
            template <
                class From, class To
              , ELIB_ENABLE_IF_VALID_EXPR( static_cast<To>(declval<From>()) )
              >
            elib::true_ is_explicitly_castable_impl(int);
            
            template <class, class>
            elib::false_ is_explicitly_castable_impl(long);
        }                                            // namespace traits_detail
        
        template <class From, class To>
        using is_explicitly_castable = decltype(
            traits_detail::is_explicitly_castable_impl<From, To>(0)
          );
        
# if defined(ELIB_CONFIG_HAS_VARIABLE_TEMPLATES)
        template <class From, class To>
        constexpr bool is_explicitly_castable_v = 
            is_explicitly_castable<From, To>::value;
# endif
    }                                                       // namespace traits
    
    using namespace traits;
}}                                                          // namespace elib
#endif /* ELIB_AUX_TRAITS_IS_EXPLICITLY_CASTABLE_HPP */