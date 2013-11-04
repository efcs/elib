#ifndef ELIB_ENUM_BASIC_ENUM_TRAITS_HPP
# define ELIB_ENUM_BASIC_ENUM_TRAITS_HPP

# include <elib/config.hpp>
# include <elib/enumeration/v3/enum_helper.hpp>
# include <elib/etl/basic_detector.hpp>

# include <elib/CXX14/type_traits.hpp>

# include <string>
# include <map>

namespace elib 
{
  namespace enumeration
  {
    
    
    template <typename T>
    using enum_map_t = const std::map<T, std::string>;
    
    
    template <typename T>
    struct basic_enum_traits
    {
      static_assert(std::is_enum<T>::value, "T must be an enumeration type");
      
      /* when implementing replace BAD_ENUM_TYPE with your type T, 
       * BAD_ENUM_TYPE is used to check for default instatiations
       */
      static enum_map_t<BAD_ENUM_TYPE> name_map;
      
      static constexpr BAD_ENUM_TYPE ELIB_ENUM_DEFAULT_VALUE = 
        BAD_ENUM_TYPE::none;
      static constexpr BAD_ENUM_TYPE ELIB_ENUM_ERROR_VALUE = 
        BAD_ENUM_TYPE::none;
      
      static constexpr BAD_ENUM_TYPE ELIB_ENUM_FIRST_VALUE = 
        BAD_ENUM_TYPE::none;
      static constexpr BAD_ENUM_TYPE ELIB_ENUM_LAST_VALUE = 
        BAD_ENUM_TYPE::none;
      
      static constexpr bool ELIB_ENUM_IS_CONTIGIOUS = false;
      static constexpr bool ELIB_ENUM_IS_BITMASK = false;
      static constexpr bool ELIB_ENUM_IS_ARITHMETIC = false;
      
      // this is used purely to determine if the default
      // instatiation (ie this one) is being used
      static constexpr bool ELIB_ENUM_IS_DEFAULT_ENUM_TRAITS = true;
      
    };
      
    namespace detail
    {
     
      template <class T>
      using traits_is_default_detector 
        = decltype(&basic_enum_traits<T>::ELIB_ENUM_IS_DEFAULT_ENUM_TRAITS);
        
      template <class T>
      using traits_name_map_detector = decltype(&basic_enum_traits<T>::name_map);
      
    }                                                       // namespace detail
    
    template <class T>
    struct has_basic_enum_traits 
      : std::integral_constant<bool, 
          !etl::basic_detector<T, detail::traits_is_default_detector>::value
        >
    {};
    
    template <class T>
    struct has_name_map
      : std::integral_constant<bool, 
          has_basic_enum_traits<T>::value
          && etl::basic_detector<T, detail::traits_name_map_detector>::value
        >
    {};
    
      
  }                                                    // namespace enumeration
}                                                           // namespace elib
#endif /* ELIB_ENUM_BASIC_ENUM_TRAITS_HPP */
