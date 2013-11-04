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
      
    
      template <class T, class U, class Ret=void>
      using if_enum_to_enum_t = 
        std::enable_if_t<
          std::is_enum<T>::value && std::is_enum<U>::value,
          Ret
        >;
        
      template <class T, class U, class Ret=void>
      using if_integral_to_enum_t = 
        std::enable_if_t<
          std::is_integral<T>::value && std::is_enum<U>::value,
          Ret
        >;
        
      template <class T, class U, class Ret=void>
      using if_enum_to_integral_t = 
        std::enable_if_t<
          std::is_enum<T>::value && std::is_integral<U>::value, 
          Ret
        >;
        
      template <class T, class U, class Ret=void>
      using if_string_to_enum_t;
      
      template <class T, class U, class Ret=void>
      using if_enum_to_string_t
      
      template <class T, class U,
        std::enable_if_t<std::is_enum<T>::value && std::is_enum>>
      castible_if
      {};
      
      template
      
      
    }                                                       // namespace detail
    
    template <typename T>
    typename detail::enum_if<T>::underlying_type
    underlying_cast(T v) noexcept
    {
      return static_cast<underlying_t<T>>(v);
    }
    
    
    
    
    
    
  }                                                    // namespace enumeration
}                                                           // namespace elib
#endif /* ELIB_ENUMERATION_ENUM_CAST_HPP */