#ifndef ELIB_AUX_TRAITS_HAS_VALUE_HPP
#define ELIB_AUX_TRAITS_HAS_VALUE_HPP

# include <elib/config.hpp>
# include <elib/aux/integral_constant.hpp>
# include <cstddef>

namespace elib { namespace aux
{
    namespace detail
    {
        template <class T, std::size_t = sizeof(T::value)>
        elib::true_ has_value_impl(int);
        
        template <class>
        elib::false_ has_value_impl(long);
    }                                                       // namespace detail
    
    template <class T>
    using has_value = decltype(detail::has_value_impl<T>(0));
    
# if defined(ELIB_CONFIG_HAS_VARIABLE_TEMPLATES)
    template <class T>
    constexpr bool has_value_v = has_value<T>::value;
# endif
}}                                                          // namespace elib
#endif /* ELIB_AUX_TRAITS_HAS_VALUE_HPP */