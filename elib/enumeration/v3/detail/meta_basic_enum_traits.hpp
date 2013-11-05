#ifndef ELIB_ENUMERATION_META_BASIC_ENUM_TRAITS_HPP
# define ELIB_ENUMERATION_META_BASIC_ENUM_TRAITS_HPP

# include <elib/config.hpp>
# include <elib/enumeration/v3/basic_enum_traits.hpp>
# include <elib/enumeration/v3/enum_helper.hpp>
# include <elib/enumeration/v3/detail/enum_fields.hpp>


namespace elib 
{
  namespace enumeration
  {
    namespace detail
    {
      
      
      template <class T, bool=has_basic_enum_traits<T>::value>
      struct meta_basic_enum_traits
      {
      private:
        
        static constexpr T BAD_VALUE = static_cast<T>(-1);
        
      public:
        
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
        
        static constexpr bool has_is_logical = false;
        static constexpr bool is_logical = false;
        
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
                                
        using m_is_logical = field_extractor<basic_enum_traits<T>,
                                  is_logical_field_t, std::false_type>;
        
      public:
        
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
        
        static constexpr bool has_is_logical = m_is_logical::found;
        static constexpr bool is_logical = m_is_logical::value;
        
      };
      
    }                                                       // namespace detail
    
  }                                                    // namespace enumeration
}                                                           // namespace elib
#endif /* ELIB_ENUMERATION_META_BASIC_ENUM_TRAITS_HPP */