#ifndef ELIB_AUX_TRAITS_IS_STRING_TYPE_HPP
#define ELIB_AUX_TRAITS_IS_STRING_TYPE_HPP

# include <elib/aux/integral_constant.hpp>
# include <elib/aux/declval.hpp>
# include <elib/aux/traits/is_same.hpp>
# include <elib/aux/traits/decay.hpp>
# include <string>
# include <utility>

namespace elib { namespace aux
{
    namespace traits
    {
        namespace traits_detail
        {
            auto is_string_type_impl(const char* const) -> true_;
            auto is_string_type_impl(std::string) -> true_;
            auto is_string_type_impl(...) -> false_;
            
            auto is_c_string_impl(const char* const) -> true_;
            auto is_c_string_impl(...) -> false_;
        }
               
        template <class T>
        struct is_c_string 
          : decltype(traits_detail::is_c_string_impl(elib::declval<T>())
        {};
        
        template <>
        struct is_c_string<void> : elib::false_ {};
        
        template <class T>
        struct is_string_type 
          : decltype(traits_detail::is_string_type_impl(elib::declval<T>()))
        {};
        
        template <>
        struct is_string_type<void> : elib::false_ {};
# if defined(ELIB_CONFIG_HAS_VARIABLE_TEMPLATES)
        template <class T>
        constexpr bool is_c_string_v = is_c_string<T>::value;
        
        template <class T>
        constexpr bool is_string_type_v = is_string_type<T>::value;
# endif /* ELIB_CONFIG_HAS_VARIABLE_TEMPLATES */
    }                                                       //namespace traits
    
    using namespace traits;
}}                                                           //namespace elib
#endif /* ELIB_AUX_TRAITS_IS_STRING_TYPE_HPP */
