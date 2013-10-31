#ifndef ELIB_ENUMERATION_ENUM_TYPE_TRAITS_HELPER_HPP
#define ELIB_ENUMERATION_ENUM_TYPE_TRAITS_HELPER_HPP

# include <elib/config.hpp>

# include <elib/CXX14/type_traits.hpp>


namespace elib 
{
  namespace enumeration
  {    
    namespace detail
    {
      
      template <typename EnumT, typename=void>
      struct sfinae_underlying_type 
      {
        typedef void type;
      };

      template <typename EnumT>
      struct sfinae_underlying_type<EnumT, 
          std::enable_if_t<std::is_enum<EnumT>::value>>
      {
        typedef std::underlying_type_t<EnumT> type;
      };
      
      template <typename T>
      using sfinae_underlying_type_t 
        = typename sfinae_underlying_type<T>::type;
      
    
# include <elib/pragma/diagnostic_push.hpp>
# include <elib/pragma/ignore_effcxx.hpp>
    
      template <typename T, typename U>
      struct is_enum_enum 
        : public std::integral_constant<bool, 
            std::is_enum<T>::value && std::is_enum<U>::value>
      { };
      
      template <typename T, typename U>
      struct is_enum_integral
        : public std::integral_constant<bool, 
            std::is_enum<T>::value && std::is_integral<U>::value>
      { };
      
      template <typename T, typename U>
      struct is_integral_integral 
        : public std::integral_constant<bool,
            std::is_integral<T>::value && std::is_integral<U>::value>
      { };
 
      
      template <typename T, typename U, typename Ret=void>
      struct enable_if_enum_enum 
        : public std::enable_if<is_enum_enum<T, U>::value, Ret>
      { };
      
      template <typename T, typename U, typename Ret=void>
      struct enable_if_integral_integral
        : public std::enable_if<is_integral_integral<T, U>::value, Ret>
      { };
      
      template <typename T, typename U, typename Ret=void>
      struct enable_if_enum_integral
        : public std::enable_if<is_enum_integral<T, U>::value, Ret>
      { };
      
      template <typename T, typename U, typename Ret=void>
      using enable_if_enum_enum_t = 
        typename enable_if_enum_enum<T, U, Ret>::type;
        
      template <typename T, typename U, typename Ret=void>
      using enable_if_integral_integral_t =
        typename enable_if_integral_integral<T, U, Ret>::type;
        
      template <typename T, typename U, typename Ret=void>
      using enable_if_enum_integral_t =
        typename enable_if_enum_integral<T, U, Ret>::type;

      
      template <typename T, typename Ret=void>
      using enable_if_integral_t = 
        std::enable_if_t<std::is_integral<T>::value, Ret>;
        
# include <elib/pragma/diagnostic_pop.hpp>
      
    }                                                       // namespace detail
  }                                                    // namespace enumeration
}                                                           // namespace elib
#endif /* ELIB_ENUMERATION_ENUM_TYPE_TRAITS_HELPER_HPP */