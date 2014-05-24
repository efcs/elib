#ifndef ELIB_AUX_TRAITS_HAS_TYPE_HPP
#define ELIB_AUX_TRAITS_HAS_TYPE_HPP

# include <elib/config.hpp>
# include <elib/aux/integral_constant.hpp>

namespace elib { namespace aux
{
    namespace detail
    {
        template <class T, class = typename T::type>
        elib::true_ has_type_impl(int);
        
        template <class>
        elib::false_ has_type_impl(long);
    }                                                       // namespace detail
    
    template <class T>
    using has_type = decltype(detail::has_type_impl<T>(0));
    
# if defined(ELIB_CONFIG_HAS_VARIABLE_TEMPLATES)
    template <class T>
    constexpr bool has_type_v = has_type<T>::value;
# endif
}}                                                          // namespace elib
#endif /* ELIB_AUX_TRAITS_HAS_TYPE_HPP */