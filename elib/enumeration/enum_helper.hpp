#ifndef ELIB_ENUMERATION_ENUM_HELPER_HPP
#define ELIB_ENUMERATION_ENUM_HELPER_HPP

# include <elib/config.hpp>

# include <elib/CXX14/type_traits.hpp>

namespace elib 
{
  namespace enumeration
  {
    
    enum class BAD_ENUM_TYPE { none };              
    
    template <typename T, typename Ret=void>
    struct enable_if_enum : std::enable_if<std::is_enum<T>::value, Ret>
    { };
      
    template <typename T, typename Ret=void>
    using enable_if_enum_t = typename enable_if_enum<T, Ret>::type;
    
    
    template <typename T, bool=std::is_enum<T>::value>
    struct sfinae_underlying_type
    {
      typedef void type;
    };
    
    template <typename T>
    struct sfinae_underlying_type<T, true>
    {
      typedef std::underlying_type_t<T> type;
    };
    
    template <typename T>
    using sfinae_underlying_type_t = typename sfinae_underlying_type<T>::type;
    
    
    template <typename T>
    using underlying_t = std::underlying_type_t<T>;
    
    
    
    
    namespace detail
    {
      
      template <typename T, typename Ret=void>
      using enable_if_integral = std::enable_if<std::is_integral<T>::value, Ret>;
      
      template <class T, class Ret=void>
      using enable_if_integral_t = typename enable_if_integral<T, Ret>::type;
      
      
      template <class T, class=void>
      struct enum_if
      { };
      
      template <class T>
      struct enum_if<T, enable_if_enum_t<T>>
      {
        typedef T enum_type;
        typedef std::underlying_type_t<T> underlying_type;
      };
      
      template <class T>
      struct enum_if<T,  enable_if_integral_t<T>>
      {
        typedef T integral_type;
      };
      
    }                                                       // namespace detail
    
    /* should be in enum_cast but it is put here to avoid circular dependancies */
    template <typename T>
    constexpr typename detail::enum_if<T>::underlying_type
    underlying_cast(T v) noexcept
    {
      return static_cast<underlying_t<T>>(v);
    }
    
    template <typename T>
    constexpr std::enable_if_t<std::is_enum<T>::value, bool>
    bool_cast(T v) noexcept
    {
      return static_cast<bool>(v);
    }
    
    
  }                                                    // namespace enumeration
}                                                           // namespace elib
#endif /* ELIB_ENUMERATION_ENUM_HELPER_HPP */