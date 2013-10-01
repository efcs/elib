#ifndef ELIB_ENUMERATION_ENUM_CAST_HPP
# define ELIB_ENUMERATION_ENUM_CAST_HPP

# include <elib/config.hpp>
# include <elib/enumeration/v2/enum_traits.hpp>
# include <elib/enumeration/v2/enum_type_traits.hpp>

# include <elib/CXX14/type_traits.hpp>

# include <typeinfo>

namespace elib 
{
  namespace enumeration
  {
  
  
    struct bad_enum_cast : public std::bad_cast
    {
    public:
      const char* what() const noexcept
      { return "bad enum cast"; }
    };
  
  
    namespace detail
    {
      
      template <typename FromEnum, typename To>
      struct can_cast_from_enum
        : public std::integral_constant<bool, 
              std::is_enum<FromEnum>::value
              && (std::is_integral<To>::value
                  || (has_basic_enum_traits<FromEnum>::value
                      && (std::is_same<std::string, To>::value
                          || std::is_same<const char*, To>::value)))>
      { };
      
      template <typename From,  typename ToEnum>
      struct can_cast_to_enum
        : public std::integral_constant<bool,
              std::is_enum<ToEnum>::value
              && ((std::is_integral<From>::value && has_range<ToEnum>::value)
                  || (has_basic_enum_traits<ToEnum>::value
                      && (std::is_same<const From&, const std::string&>::value
                          || std::is_same<const From&, const char*>::value)))>
      { };
      
      
      
      template <typename From, typename To>
      struct can_cast_enum : public std::integral_constant<bool, 
          can_cast_to_enum<From, To>::value 
          || can_cast_from_enum<From, To>::value>
      { };

      
    }                                                       // namespace detail
  
  
  }                                                    // namespace enumeration
}                                                           // namespace elib
#endif /* ELIB_ENUMERATION_ENUM_CAST_HPP */