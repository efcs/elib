#ifndef ELIB_AUX_TRAITS_IS_INCOMPLETE_HPP
#define ELIB_AUX_TRAITS_IS_INCOMPLETE_HPP

# include <elib/config.hpp>
# include <elib/aux/integral_constant.hpp>
# include <cstddef>

namespace elib { namespace aux
{
    namespace detail
    {
        template <class T, std::size_t = sizeof(T)>
        elib::false_ is_incomplete_test(int);
        
        template <class T>
        elib::true_ is_incomplete_test(long);
    }                                                       // namespace detail
    
    template <class T>
    struct is_incomplete : decltype(detail::is_incomplete_test<T>(0)) {};
    
    template <>
    struct is_incomplete<void> : elib::true_ {};
    
# if defined(ELIB_CONFIG_HAS_VARIABLE_TEMPLATES)
    template <class T>
    constexpr bool is_incomplete_v = is_incomplete<T>::value;
# endif
    
}}                                                          // namespace elib
#endif /* ELIB_AUX_TRAITS_IS_INCOMPLETE_HPP */