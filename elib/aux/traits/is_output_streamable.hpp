#ifndef ELIB_AUX_TRAITS_IS_OUTPUT_STREAMABLE_HPP
#define ELIB_AUX_TRAITS_IS_OUTPUT_STREAMABLE_HPP

# include <elib/config.hpp>
# include <elib/aux/integral_constant.hpp>
# include <elib/aux/enable_if.hpp>
# include <elib/aux/declval.hpp>
# include <iosfwd>

namespace elib { namespace aux
{
    namespace detail
    {
        template <
            class T
          , ELIB_ENABLE_IF_VALID_EXPR(
                elib::declval<std::basic_ostream<char> &>() <<  elib::declval<T &>()
            )
          >
        elib::true_ is_output_streamable_impl(int);
            
        template <class>
        elib::false_ is_output_streamable_impl(long);
    }                                                       // namespace detail
        
    template <class T>
    using is_output_streamable = decltype(
        detail::is_output_streamable_impl<T>(0)
    );
        
# if defined(ELIB_CONFIG_HAS_VARIABLE_TEMPLATES)
    template <class T>
    constexpr bool is_output_streamable_v = is_output_streamable<T>::value;
# endif
}}                                                          // namespace elib
#endif /* ELIB_AUX_TRAITS_IS_OUTPUT_STREAMABLE_HPP */