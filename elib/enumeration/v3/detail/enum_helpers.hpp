#ifndef ELIB_ENUMERATION_ENUM_HELPERS_HPP
# define ELIB_ENUMERATION_ENUM_HELPERS_HPP

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
      
      template <typename T, bool=std::is_enum<T>::value>
      struct enum_if
      { };
      
      template <typename T>
      struct enum_if<T, true>
      {
        typedef T enum_type;
        typedef std::underlying_type_t<T> underlying_type;
      };
      
    }                                                       // namespace detail
    
    
  }                                                    // namespace enumeration
}                                                           // namespace elib
#endif /* ELIB_ENUMERATION_ENUM_HELPERS_HPP */