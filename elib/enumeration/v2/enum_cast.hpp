#ifndef ELIB_ENUMERATION_ENUM_CAST_HPP
# define ELIB_ENUMERATION_ENUM_CAST_HPP

# include <elib/config.hpp>
# include <elib/enumeration/v2/enum_traits.hpp>
# include <elib/enumeration/v2/detail/enum_type_traits_helper.hpp>

# include <elib/CXX14/type_traits.hpp>

# include <typeinfo>
# include <exception>

namespace elib 
{
  namespace enumeration
  {
  
  
# ifdef ELIB_ENUMERATION_RUNTIME_ERROR

    class bad_enum_cast : public std::runtime_error
    {
    public:
      bad_enum_cast()
        : std::runtime_error{"bad enum cast"}
      { }
      
    };
    
#   else

  class bad_enum_cast : public std::bad_cast
  {
  public:
    virtual const char* what() const noexcept
    { return "bad enum cast"; }
  };
  
# endif
  
    namespace detail
    {
      
      
      template <typename To, typename From>
      struct can_cast_enum_to_str : public std::integral_constant<bool,
          std::is_enum<From>::value 
          && has_basic_enum_traits<From>::value
          && std::is_same<To, std::string>::value>
      { };
          
      
      template <typename To, typename From>
      struct can_cast_str_to_enum : public std::integral_constant<bool, 
          std::is_enum<To>::value 
          && has_basic_enum_traits<To>::value
          && (std::is_same<const From&, const std::string&>::value
              || std::is_same<const From, const char*>::value)>
      { };

      
    }                                                       // namespace detail
  
    // Safe Unchecked: Enum -> underlying_type
    template <typename From>
    constexpr std::underlying_type_t<From> underlying_cast(From val) noexcept
    {
      return static_cast<std::underlying_type_t<From>>(val);
    }
    
    // Safe Unchecked:
    // Enum -> Integral
    // Integral -> Enum
    template <typename To, typename From>
    constexpr std::enable_if_t<detail::is_enum_integral<To, From>::value
        || detail::is_enum_integral<From, To>::value, To>
    unchecked_enum_cast(From val) noexcept
    {
      return static_cast<To>(val);
    }
    
    
    // Unsafe(safe) (un)Checked: Enum -> Integral
    template <typename To, typename From>
    constexpr std::enable_if_t<detail::is_enum_integral<From, To>::value, To>
    enum_cast(From val) noexcept
    {
      return static_cast<To>(val);
    }
    
    // Unsafe Checked: Integral -> Enum
    template <typename To, typename From>
    std::enable_if_t<detail::is_enum_integral<To, From>::value, To>
    enum_cast(From val)
    {
      auto tmp = static_cast<To>(val);
      if (!valid_enum(tmp))
        throw bad_enum_cast{};
        
      return tmp;
    }
    
    // Unsafe Checked: Enum -> String
    template <typename To, typename From>
    std::enable_if_t<detail::can_cast_enum_to_str<To, From>::value, To>
    enum_cast(From val)
    {
      using bt = basic_enum_traits<From>;
      if (bt::name_map.count(val) == 0)
        throw bad_enum_cast{};
      return bt::name_map[val];
    }
    
    // Unsafe Checked: String -> Enum
    template <typename To, typename From>
    std::enable_if_t<detail::can_cast_str_to_enum<To, From>::value, To>
    enum_cast(const From& str)
    {
      using bt = basic_enum_traits<To>;
      for (auto& p : bt::name_map)
      {
        if (p.second == str) 
          return p.first;
      }
      throw bad_enum_cast{};
    }
    
    
    
    // Safe (un)Checked: Enum -> Integral
    template <typename To, typename From>
    std::enable_if_t<detail::is_enum_integral<From, To>::value, bool>
    safe_enum_cast(From val, To& dest) noexcept
    {
      // cast is unchecked
      dest = static_cast<To>(val);
      return true;
    }
    
    // Safe Checked: Integral -> Enum
    template <typename To, typename From>
    std::enable_if_t<detail::is_enum_integral<To, From>::value, bool>
    safe_enum_cast(From val, To& dest) noexcept
    {
      auto tmp = static_cast<To>(val);
      if (! valid_enum(tmp)) return false;
      dest = tmp;
      return true;
    }
    
    // Safe Checked: Enum -> String
    template <typename To, typename From>
    std::enable_if_t<detail::can_cast_enum_to_str<To, From>::value, bool>
    safe_enum_cast(From val, To& dest) noexcept
    {
      using bt = basic_enum_traits<From>;
      if (bt::name_map.count(val) == 0) return false;
      dest = bt::name_map[val];
      return true;
    }
    
    // Safe Checked: String -> Enum
    template <typename To, typename From>
    std::enable_if_t<detail::can_cast_str_to_enum<To, From>::value, bool>
    safe_enum_cast(const From& val, To& dest) noexcept
    {
      using bt = basic_enum_traits<To>;
      for (auto& p : bt::name_map)
      {
        if (p.second == val)
        {
          dest = p.first;
          return true;
        }
      }
      return false;
    }
  
  
  }                                                    // namespace enumeration
}                                                           // namespace elib
#endif /* ELIB_ENUMERATION_ENUM_CAST_HPP */