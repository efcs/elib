#ifndef ELIB_ENUMERATION_ENUM_CAST_HPP
# define ELIB_ENUMERATION_ENUM_CAST_HPP

# include <elib/config.hpp>

# include <elib/enumeration/v3/enum_helper.hpp>
# include <elib/enumeration/v3/enum_traits.hpp>

# include <elib/CXX14/type_traits.hpp>

# include <stdexcept>

namespace elib 
{
  namespace enumeration
  {
    namespace detail
    {
      
    
      template <class From, class To, class Ret=To>
      using if_enum_to_enum_t = 
        std::enable_if_t<
          std::is_enum<From>::value 
            && std::is_enum<To>::value
            && has_range<To>::value
          , Ret
        >;
        
        
      template <class From, class To, class Ret=To>
      using if_integral_to_enum_t = 
        std::enable_if_t<
          std::is_integral<From>::value 
            && std::is_enum<To>::value
            && has_range<To>::value
          , Ret
        >;
        
   
      template <class From, class To, class Ret=To>
      using if_enum_to_integral_t = 
        std::enable_if_t<
          std::is_enum<From>::value 
            && std::is_integral<To>::value
          , Ret
        >;
        
        
      template <class From, class To, class Ret=To>
      using if_enum_to_string_t = 
        std::enable_if_t<
          std::is_enum<From>::value
            && has_name_map<From>::value
            && std::is_same<std::string, To>::value
          , Ret
        >;
          
        
      template <class S>
      using string_decay_t =
        std::remove_reference_t<
          std::decay_t<S>
        >;
        
      template <class From, class To, class Ret=To>
      using if_string_to_enum_t =
        std::enable_if_t<
            (std::is_same<string_decay_t<From>, const char*>::value
              || std::is_same<string_decay_t<From>, std::string>::value)
            && std::is_enum<To>::value
            && has_name_map<To>::value
          , Ret 
        >;
        
      
    }                                                       // namespace detail
    
    
    class bad_enum_cast : public std::runtime_error
    {
      using std::runtime_error::runtime_error;
    };
    
    template <class To, class From>
    detail::if_enum_to_enum_t<From, To>
    enum_cast(From v)
    {
      To tmp = static_cast<To>(v);
      if (in_range(tmp))
        return tmp;
      throw bad_enum_cast{"bad enum cast"};
    }
    
    
    template <class To, class From>
    constexpr detail::if_enum_to_integral_t<From, To>
    enum_cast(From v) noexcept
    {
      return static_cast<To>(v);
    }
    
    
    template <class To, class From>
    detail::if_integral_to_enum_t<From, To>
    enum_cast(From v)
    {
      To tmp = static_cast<To>(v);
      if (in_range(tmp))
        return tmp;
      throw bad_enum_cast{"bad enum cast"};
    }
    
    
    template <class To, class From>
    detail::if_string_to_enum_t<From, To>
    enum_cast(From&& v)
    {
      static_assert(has_name_map<To>::value, "must have name map");
      for (auto& kv : basic_enum_traits<To>::name_map)
      {
        if (kv.second == v)
          return kv.first;
      }
      throw bad_enum_cast{"bad enum cast"};
    }
    
    
    template <class To, class From>
    detail::if_enum_to_string_t<From, To>
    enum_cast(From v)
    {
      static_assert(has_name_map<From>::value, "must have name map");
      auto pos = basic_enum_traits<From>::name_map.find(v);
      if (pos != basic_enum_traits<From>::name_map.end())
        return pos->second;
      throw bad_enum_cast{"bad enum cast"};
    }
    
    
    
    
  }                                                    // namespace enumeration
}                                                           // namespace elib
#endif /* ELIB_ENUMERATION_ENUM_CAST_HPP */