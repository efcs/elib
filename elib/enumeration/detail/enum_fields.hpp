#ifndef ELIB_ENUMERATION_DETAIL_ENUM_FIELDS_HPP
#define ELIB_ENUMERATION_DETAIL_ENUM_FIELDS_HPP

# include <elib/config.hpp>
# include <elib/CXX14/type_traits.hpp>


namespace elib 
{
  namespace enumeration
  {
    namespace detail
    {
      
      
      template <bool Found, class FieldT>
      struct extracted_field : FieldT
      {
        static constexpr bool found = Found;
      };
    
  
      template <class T, template <class> class FieldType, class Default>
      struct _field_extractor
      {
      private:
        
        template <class T_>
        static extracted_field<true, FieldType<T_>> test(FieldType<T_>*);
        
        template <class>
        static extracted_field<false, Default> test(...);
        
      public:
        
        typedef decltype(test<T>(0)) type;
      
      };
      
      
      template <class T, template <class U> class FieldType, class Default>
      struct field_extractor : _field_extractor<T, FieldType, Default>::type
      { };
      
      
      template <class T>
      using default_value_field_t = 
        std::integral_constant<decltype(T::ELIB_ENUM_DEFAULT_VALUE),
          T::ELIB_ENUM_DEFAULT_VALUE
        >;
      
      
      template <class T>
      using error_value_field_t = 
        std::integral_constant<decltype(T::ELIB_ENUM_ERROR_VALUE), 
          T::ELIB_ENUM_ERROR_VALUE
        >;
    
    
      template <class T>
      using first_value_field_t = 
        std::integral_constant<decltype(T::ELIB_ENUM_FIRST_VALUE), 
          T::ELIB_ENUM_FIRST_VALUE
        >;
      
      
      template <class T>
      using last_value_field_t = 
        std::integral_constant<decltype(T::ELIB_ENUM_LAST_VALUE), 
          T::ELIB_ENUM_LAST_VALUE
        >;
      
      
      template <class T>
      using is_contigious_field_t = 
        std::integral_constant<bool, 
          static_cast<bool>(T::ELIB_ENUM_IS_CONTIGIOUS)
        >;
               
               
      template <class T>
      using is_bitmask_field_t = 
        std::integral_constant<bool, 
          static_cast<bool>(T::ELIB_ENUM_IS_BITMASK)
        >;
           
           
      template <class T>
      using is_arithmetic_field_t = 
        std::integral_constant<bool, 
          static_cast<bool>(T::ELIB_ENUM_IS_ARITHMETIC)
        >;
        
      template <class T>
      using is_logical_field_t =
        std::integral_constant<bool, 
          static_cast<bool>(T::ELIB_ENUM_IS_LOGICAL)
        >;
           
      template <class T>
      using is_mixed_comparible_field_t =
        std::integral_constant<bool, 
          static_cast<bool>(T::ELIB_ENUM_IS_MIXED_COMPARIBLE)
        >;
       
    }                                                       // namespace detail
  }                                                    // namespace enumeration
}                                                           // namespace elib
#endif /* ELIB_ENUMERATION_DETAIL_ENUM_FIELDS_HPP */
