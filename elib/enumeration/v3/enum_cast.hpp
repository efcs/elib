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
    
    template <typename From, typename To>
    if_enum_to_enum_t<From, To, To>
    enum_cast(From v)
    {
      To tmp = static_cast<To>(v);
      if (in_range(tmp))
        return tmp;
      throw "TODO";
    }
    
    template <class From, class To>
    constexpr if_enum_to_integral_t<From, To, To>
    enum_cast(From v) noexcept
    {
      return static_cast<To>(v);
    }
    
    template <class From, class To>
    if_integral_to_enum_t<From, To, To>
    enum_cast(From v)
    {
      To tmp = static_cast<To>(v);
      if (in_range(tmp))
        return tmp;
      throw "TODO";
    }
    
    template <class From, class To>
    if_sting_to_enum<From, To, To>
    enum_cast(From v)
    {
      static_assert(has_name_map<To>::value, "must have name map");
      for (auto& kv : basic_enum_traits<To>::name_map)
      {
        if (kv.second == v)
          return kv.first;
      }
      throw "TODO";
    }
    
    
    template <class From, class To>
    if_enum_to_string_t<From, To, To>
    enum_cast(From v)
    {
      static_assert(has_name_map<From>::value, "must have name map");
      auto pos = basic_enum_traits<T>::name_map.find(v);
      if (pos != basic_enum_traits<T>::name_map.end())
        return pos->second;
      throw "TODO";
    }
    
    
    
    
  }                                                    // namespace enumeration
}                                                           // namespace elib
#endif /* ELIB_ENUMERATION_ENUM_CAST_HPP */