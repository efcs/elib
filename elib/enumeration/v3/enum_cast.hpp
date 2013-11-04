#ifndef ELIB_ENUMERATION_ENUM_CAST_HPP
# define ELIB_ENUMERATION_ENUM_CAST_HPP

# include <elib/config.hpp>

# include <elib/enumeration/v3/enum_helper.hpp>
# include <elib/enumeration/v3/enum_traits.hpp>

# include <elib/CXX14/type_traits.hpp>

namespace elib 
{
  namespace enumeration
  {
    namespace detail
    {
      
    
      template <class From, class To, class Ret=void>
      using if_enum_to_enum_t = 
        std::enable_if_t<
          std::is_enum<From>::value 
            && std::is_enum<To>::value
            && has_range<To>::value
          , Ret
        >;
        
      template <class From, class To, class Ret=void>
      using if_integral_to_enum_t = 
        std::enable_if_t<
          std::is_integral<From>::value 
            && std::is_enum<To>::value
            && has_range<To>::value
          , Ret
        >;
        
   
      template <class T, class U, class Ret=void>
      using if_enum_to_integral_t = 
        std::enable_if_t<
          std::is_enum<T>::value 
            && std::is_integral<U>::value
          , Ret
        >;
        
      template <class T, class U, class Ret=void>
      using if_enum_to_string_t = 
        std::enable_if_t<
          std::is_enum<T>::value
            && has_name_map<T>::value
            && std::is_same<std::string, U>::value
          , Ret
        >;
          
        
      template <class T, class U, class Ret=void>
      using if_string_to_enum_t =
        std::enable_if_t<
            (std::is_same<T, const char*>::value
              || std::is_same<T, const std::string>
              || std::is_name<T, const std::string&>)
            && std::is_enum<U>::value
            && has_name_map<U>::value
          , Ret 
        >;
      
      
      
      
    }                                                       // namespace detail
    
    template <typename T>
    typename detail::enum_if<T>::underlying_type
    underlying_cast(T v) noexcept
    {
      return static_cast<underlying_t<T>>(v);
    }
    
    template <class From, class To>
    detail::if_enum_to_enum<From, To>
    
    
    
    
    
    
  }                                                    // namespace enumeration
}                                                           // namespace elib
#endif /* ELIB_ENUMERATION_ENUM_CAST_HPP */