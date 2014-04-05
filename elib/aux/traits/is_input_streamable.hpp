#ifndef ELIB_AUX_TRAITS_IS_INPUT_STREAMABLE_HPP
#define ELIB_AUX_TRAITS_IS_INPUT_STREAMABLE_HPP

# include <elib/config.hpp>
# include <elib/aux/integral_constant.hpp>
# include <elib/aux/enable_if.hpp>
# include <elib/aux/declval.hpp>
# include <iosfwd>

namespace elib { namespace aux
{
    namespace traits
    {
        namespace traits_detail
        {
            template <
                class T
              , ELIB_ENABLE_IF_VALID_EXPR(
                    elib::declval<std::basic_istream<char> &>() >> elib::declval<T &>()
                  )
              >
            elib::true_ is_input_streamable_impl(int);
            
            template <class>
            elib::false_ is_input_streamable_impl(long);
        }                                            // namespace traits_detail
        
        template <class T>
        using is_input_streamable = decltype(
            traits_detail::is_input_streamable_impl<T>(0)
        );
        
# if defined(ELIB_CONFIG_HAS_VARIABLE_TEMPLATES)
        template <class T>
        constexpr bool is_input_streamable_v = is_input_streamable<T>::value;
# endif
    }                                                       // namespace traits
    
    using namespace traits;
}}                                                          // namespace elib
#endif /* ELIB_AUX_TRAITS_IS_INPUT_STREAMABLE_HPP */