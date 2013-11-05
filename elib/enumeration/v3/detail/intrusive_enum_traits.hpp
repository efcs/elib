#ifndef ELIB_ENUMERATION_INTRUSIVE_ENUM_TRAITS_HPP
# define ELIB_ENUMERATION_INTRUSIVE_ENUM_TRAITS_HPP

# include <elib/config.hpp>
# include <elib/enumeration/v3/enum_helper.hpp>
# include <elib/enumeration/v3/detail/enum_fields.hpp>

# include <elib/CXX14/type_traits.hpp>


namespace elib 
{
  namespace enumeration
  {
    namespace detail
    {
      
      template <class T, class=enable_if_enum<T>>
      struct intrusive_enum_traits
      {
      private:
          
        using bad_enum_t = std::integral_constant<T, static_cast<T>(-1)>;
          
        using m_default_value = 
          field_extractor<T, default_value_field_t, bad_enum_t>;
                                      
        using m_error_value = 
          field_extractor<T,error_value_field_t, bad_enum_t>;
                                      
        using m_first_value = 
          field_extractor<T, first_value_field_t, bad_enum_t>;
                                      
        using m_last_value = 
          field_extractor<T, last_value_field_t, bad_enum_t>;
                                      
        using m_is_contigious = 
          field_extractor<T, is_contigious_field_t, std::false_type>;
                                    
        using m_is_bitmask = 
          field_extractor<T, is_bitmask_field_t, std::false_type>;
                                    
        using m_is_arithmetic = 
          field_extractor<T, is_arithmetic_field_t, std::false_type>;
          
        using m_is_logical =
          field_extractor<T, is_logical_field_t, std::false_type>;
          
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
#endif /* ELIB_ENUMERATION_INTRUSIVE_ENUM_TRAITS_HPP */