#ifndef ELIB_ENUMERATION_ENUM_HELPER_HPP
#define ELIB_ENUMERATION_ENUM_HELPER_HPP

# include <elib/aux.hpp>

namespace elib { namespace enumeration
{
    
    enum class BAD_ENUM_TYPE { none };              
    
    template <typename T, typename Ret=void>
    using enable_if_enum = aux::enable_if<aux::is_enum<T>, Ret>;
      
    template <typename T, typename Ret=void>
    using enable_if_enum_t = typename enable_if_enum<T, Ret>::type;
    
    template <typename T>
    using underlying_t = aux::underlying_type_t<T>;
    
    namespace detail
    {
        template <typename T, typename Ret=void>
        using enable_if_integral = aux::enable_if<aux::is_integral<T>, Ret>;
        
        template <class T, class Ret=void>
        using enable_if_integral_t = typename enable_if_integral<T, Ret>::type;
        
        template <class T, class=void>
        struct enum_if;
        
        template <class T>
        struct enum_if<T, enable_if_enum_t<T>>
        {
            using enum_type = T;
            using underlying_type = aux::underlying_type_t<T>;
        };
        
        template <class T>
        struct enum_if<T,  enable_if_integral_t<T>>
        {
            using integral_type = T;
        };
      
    }                                                       // namespace detail
    
    /* should be in enum_cast but it is put here to avoid circular dependancies */
    template <typename T, ELIB_ENABLE_IF(aux::is_enum<T>::value)>
    constexpr aux::underlying_type_t<T>
    underlying_cast(T v) noexcept
    {
      return static_cast<aux::underlying_type_t<T>>(v);
    }
    
    template <typename T, ELIB_ENABLE_IF(aux::is_enum<T>::value)>
    constexpr bool bool_cast(T v) noexcept
    {
      return static_cast<bool>(v);
    }
    
    template <class T>
    using opt_cast_t = aux::sfinae_underlying_type_t<T>;
    
    template <class T, ELIB_ENABLE_IF(aux::is_integral_enum<T>::value)>
    constexpr opt_cast_t<T> opt_cast(T t) noexcept
    {
        return static_cast<opt_cast_t<T>>(t);
    }
    
  }                                                    // namespace enumeration
}                                                           // namespace elib
#endif /* ELIB_ENUMERATION_ENUM_HELPER_HPP */