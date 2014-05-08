#ifndef ELIB_AUX_TRAITS_UNDERLYING_TYPE_HPP
#define ELIB_AUX_TRAITS_UNDERLYING_TYPE_HPP

# include <elib/aux/traits/is_enum.hpp>
# include <type_traits>

namespace elib { namespace aux
{
    namespace traits
    {
        
        namespace traits_detail
        {
            template <
                class T
              , bool IsEnum = is_enum<T>::value
            >
            struct sfinae_underlying_type_impl;
            
            template <class T>
            struct sfinae_underlying_type_impl<T, true>
            {
                using type = typename std::underlying_type<T>::type;
            };
            
            template <class T>
            struct sfinae_underlying_type_impl<T, false>
            {
            };
        }
        
        template <class T>
        struct underlying_type
          : traits_detail::sfinae_underlying_type_impl<T>
        {};
        
        template <class T>
        using underlying_type_t = typename underlying_type<T>::type;
    }                                                       //namespace traits
    
    using namespace traits;
}}                                                           //namespace elib
#endif /* ELIB_AUX_TRAITS_UNDERLYING_TYPE_HPP */
