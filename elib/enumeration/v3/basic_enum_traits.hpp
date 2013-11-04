#ifndef ELIB_ENUM_BASIC_ENUM_TRAITS_HPP
# define ELIB_ENUM_BASIC_ENUM_TRAITS_HPP

# include <elib/config.hpp>

# include <elib/enumeration/v3/detail/enum_helpers.hpp>
# include <elib/enumeration/v3/enum_fields.hpp>

# include <elib/etl/basic_detector.hpp>
# include <elib/CXX14/type_traits.hpp>

# include <cstddef>
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
    
      
    
    namespace detail
    {
      
      template <class T, bool=has_basic_enum_traits<T>::value>
      struct meta_basic_enum_traits
      {
      private:
        
        static constexpr T BAD_VALUE = static_cast<T>(-1);
        
      public:
        
        static constexpr bool has_basic_enum_traits = false;
        static constexpr bool has_name_map = false;
        
        static constexpr bool has_default_value = false;
        static constexpr T default_value = BAD_VALUE;
        
        static constexpr bool has_error_value = false;
        static constexpr T error_value = BAD_VALUE;
        
        static constexpr bool has_first_value = false;
        static constexpr T first_value = BAD_VALUE;
        
        static constexpr bool has_last_value = false;
        static constexpr T last_value = BAD_VALUE;
        
        static constexpr bool has_is_contigious = false;
        static constexpr bool is_contigious = false;
        
        static constexpr bool has_is_bitmask = false;
        static constexpr bool is_bitmask = false;
        
        static constexpr bool has_is_arithmetic = false;
        static constexpr bool is_arithmetic = false;
        
      };
      
      
      template <typename T>
      struct meta_basic_enum_traits<T, true>
      {
      private:
        
        using bad_enum_t = std::integral_constant<T, static_cast<T>(-1)>;
        
        using m_default_value = field_extractor<basic_enum_traits<T>,
                                    default_value_field_t, bad_enum_t>;
                                    
        using m_error_value = field_extractor<basic_enum_traits<T>,
                                    error_value_field_t, bad_enum_t>;
                                    
        using m_first_value = field_extractor<basic_enum_traits<T>,
                                    first_value_field_t, bad_enum_t>;
                                    
        using m_last_value = field_extractor<basic_enum_traits<T>,
                                    last_value_field_t, bad_enum_t>;
                                    
        using m_is_contigious = field_extractor<basic_enum_traits<T>,
                                  is_contigious_field_t, std::false_type>;
                                  
        using m_is_bitmask = field_extractor<basic_enum_traits<T>,
                                  is_bitmask_field_t, std::false_type>;
                                  
        using m_is_arithmetic = field_extractor<basic_enum_traits<T>,
                                  is_arithmetic_field_t, std::false_type>;
        
      public:
        
        static constexpr bool has_basic_enum_traits = true;
        static constexpr bool has_name_map = has_name_map<T>::value;
        
        static constexpr bool has_default_value = m_default_value::found;
        static constexpr T default_value = m_default_value::value;
        
        static constexpr bool has_error_value = m_error_value::found;
        static constexpr T error_value = m_error_value::value;
        
        static constexpr bool has_first_value = m_first_value::found;
        static constexpr T first_value = m_first_value::value;
        
        static constexpr bool has_last_value = m_last_value::found;
        static constexpr T last_value = m_last_value::value;
        
        static constexpr bool has_is_contigious = m_is_contigious::found;
        static constexpr bool is_contigious = m_is_contigious::value;
        
        static constexpr bool has_is_bitmask = m_is_bitmask::found;
        static constexpr bool is_bitmask = m_is_bitmask::value;
        
        static constexpr bool has_is_arithmetic = m_is_arithmetic::found;
        static constexpr bool is_arithmetic = m_is_arithmetic::value;
        
      };
      
    }                                                       // namespace detail
    
  }                                                    // namespace enumeration
}                                                           // namespace elib
#endif /* ELIB_ENUM_BASIC_ENUM_TRAITS_HPP */
