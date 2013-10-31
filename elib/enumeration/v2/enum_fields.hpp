#ifndef ELIB_ENUMERATION_ENUM_FIELDS_HPP
# define ELIB_ENUMERATION_ENUM_FIELDS_HPP

# include <elib/config.hpp>
# include <elib/pragma.hpp>
# include <elib/CXX14/type_traits.hpp>

namespace elib 
{
  namespace enumeration
  {
    
    enum class enumeration_fields
    {
      ELIB_ENUM_FIRST_VALUE = 0, 
      ELIB_ENUM_LAST_VALUE = 1, 
      ELIB_ENUM_DEFAULT_VALUE = 0, 
      ELIB_ENUM_NPOS_VALUE =
        static_cast<std::underlying_type_t<enumeration_fields>>(-1), 
      
      // properties
      ELIB_ENUM_IS_CONTIGUOUS = true, 
      
      // operator fields
      ELIB_ENUM_ALLOW_BITWISE_OPERATORS = false, 
      ELIB_ENUM_ALLOW_MIXED_BITWISE_OPERATORS = true, 
      
      ELIB_ENUM_ALLOW_LOGICAL_OPERATORS = false, 
      ELIB_ENUM_ALLOW_MIXED_LOGICAL_OPERATORS = true,
      
      ELIB_ENUM_ALLOW_ARITHMETIC_OPERATORS = false, 
      ELIB_ENUM_ALLOW_MIXED_ARITHMETIC_OPERATORS = true,
      
      ELIB_ENUM_ALLOW_STREAM_EXTRACTION_OPERATOR = true, 
      ELIB_ENUM_ALLOW_STREAM_INSERTION_OPERATOR = true, 
      
      // Since we cannot define operator bool(), we have the choice
      // these are hacky work arounds
      // bool indirection defines the operator bool operator*(Enum);
      // underlying dereference defines std::underlying_type operator&(Enum);
      ELIB_ENUM_ALLOW_BOOL_INDIRECTION_OPERATOR = true, 
      ELIB_ENUM_ALLOW_UNDERLYING_DEREFERENCE_OPERATOR = true, 
      
    };                                         // enum class enumeration_fields
    
    namespace detail
    {

      template <typename EnumT, typename T>
      struct transform_integral
      {
        static_assert(std::is_same<EnumT, typename T::value_type>::value, "mest be same");
        typedef EnumT type;
        static constexpr bool good = true;
        static constexpr EnumT value = T::value;
        static constexpr bool bool_value = static_cast<bool>(T::value);
      };

      
      template <typename EnumT>
      struct transform_integral<EnumT, std::false_type>
      {
        typedef EnumT type;
        static constexpr bool good = false;
        static constexpr EnumT value = static_cast<EnumT>(false);
        static constexpr bool bool_value = false;
      };

      
      // special case for when T != Enum
      enum class BAD_ENUM_CLASS {};
      
      template <typename T, template <typename U> class Detector, typename=void>
      struct basic_detector
      {
        typedef transform_integral<BAD_ENUM_CLASS, std::false_type> type;
      };
      


      template <typename T, template <typename U> class Detector>
      struct basic_detector<T, Detector, 
          std::enable_if_t<std::is_enum<T>::value>>
      {
      private:
        static_assert(std::is_enum<T>::value,  "T must be enum");
        
        template <typename U>
        static Detector<U> test(decltype(Detector<U>::value)*);

        template <typename U>
        static std::false_type test(...);

      public:
        typedef transform_integral<T, decltype(test<T>(0))> type;
      };



    }                                                       // namespace detail
      
      
/* the inheritence used below triggers the effc++ warning
 * since none of the base-classes are polymorphic
 */
ELIB_PRAGMA_DIAG_PUSH()
ELIB_PRAGMA_IGNORE_EFFCXX()


    template <typename T> 
    using first_field_type =
      std::integral_constant<T, T::ELIB_ENUM_FIRST_VALUE>;

    template <typename T>
    struct first_field
      : public detail::basic_detector<T, first_field_type>::type
    { };


    template <typename T> 
    using last_field_type =
      std::integral_constant<T, T::ELIB_ENUM_LAST_VALUE>;

    template <typename T>
    struct last_field
      : public detail::basic_detector<T, last_field_type>::type
    { };


    template <typename T> 
    using default_field_type =
      std::integral_constant<T, T::ELIB_ENUM_DEFAULT_VALUE>;

    template <typename T>
    struct default_field
      : public detail::basic_detector<T, default_field_type>::type
    { };


    template <typename T> 
    using npos_field_type =
      std::integral_constant<T, T::ELIB_ENUM_NPOS_VALUE>;

    template <typename T>
    struct npos_field
      : public detail::basic_detector<T, npos_field_type>::type
    { };

    template <typename T> 
    using is_contiguous_field_type =
      std::integral_constant<T, T::ELIB_ENUM_IS_CONTIGUOUS>;

    template <typename T>
    struct is_contiguous_field
      : public detail::basic_detector<T, is_contiguous_field_type>::type
    { };


    template <typename T> 
    using allow_bitwise_operators_field_type =
      std::integral_constant<T, T::ELIB_ENUM_ALLOW_BITWISE_OPERATORS>;

    template <typename T>
    struct allow_bitwise_operators_field
      : public detail::basic_detector<T, allow_bitwise_operators_field_type>::type
    { };


    template <typename T> 
    using allow_mixed_bitwise_operators_field_type =
      std::integral_constant<T, T::ELIB_ENUM_ALLOW_MIXED_BITWISE_OPERATORS>;

    template <typename T>
    struct allow_mixed_bitwise_operators_field
      : public detail::basic_detector<T, allow_mixed_bitwise_operators_field_type>::type
    { };



    template <typename T> 
    using allow_logical_operators_field_type =
      std::integral_constant<T, T::ELIB_ENUM_ALLOW_LOGICAL_OPERATORS>;

    template <typename T>
    struct allow_logical_operators_field
      : public detail::basic_detector<T, allow_logical_operators_field_type>::type
    { };


    template <typename T> 
    using allow_mixed_logical_operators_field_type =
      std::integral_constant<T, T::ELIB_ENUM_ALLOW_MIXED_LOGICAL_OPERATORS>;

    template <typename T>
    struct allow_mixed_logical_operators_field
      : public detail::basic_detector<T, allow_mixed_logical_operators_field_type>::type
    { };

    template <typename T> 
    using allow_arithmetic_operators_field_type =
      std::integral_constant<T, T::ELIB_ENUM_ALLOW_ARITHMETIC_OPERATORS>;

    template <typename T>
    struct allow_arithmetic_operators_field
      : public detail::basic_detector<T, 
          allow_arithmetic_operators_field_type>::type
    { };


    template <typename T> 
    using allow_mixed_arithmetic_operators_field_type =
      std::integral_constant<T, T::ELIB_ENUM_ALLOW_MIXED_ARITHMETIC_OPERATORS>;

    template <typename T>
    struct allow_mixed_arithmetic_operators_field
      : public detail::basic_detector<T, 
          allow_mixed_arithmetic_operators_field_type>::type
    { };



    template <typename T> 
    using allow_stream_extraction_operator_field_type =
      std::integral_constant<T, T::ELIB_ENUM_ALLOW_STREAM_EXTRACTION_OPERATOR>;

    template <typename T>
    struct allow_stream_extraction_operator_field
      : public detail::basic_detector<T, 
          allow_stream_extraction_operator_field_type>::type
    { };


    template <typename T> 
    using allow_stream_insertion_operator_field_type =
      std::integral_constant<T, T::ELIB_ENUM_ALLOW_STREAM_INSERTION_OPERATOR>;

    template <typename T>
    struct allow_stream_insertion_operator_field
      : public detail::basic_detector<T, 
        allow_stream_insertion_operator_field_type>::type
    { };
    
    template <typename T>
    using allow_bool_indirection_operator_field_type =
      std::integral_constant<T, T::ELIB_ENUM_ALLOW_BOOL_INDIRECTION_OPERATOR>;
      
    template <typename T>
    struct allow_bool_indirection_operator_field
      :  public detail::basic_detector<T, 
            allow_bool_indirection_operator_field_type>::type
    { };
    
    template <typename T>
    using allow_underlying_dereference_operator_field_type =
    std::integral_constant<T, T::ELIB_ENUM_ALLOW_UNDERLYING_DEREFERENCE_OPERATOR>;

    template <typename T>
    struct allow_underlying_dereference_operator_field
      :  public detail::basic_detector<T, 
            allow_underlying_dereference_operator_field_type>::type
    { };
    
ELIB_PRAGMA_DIAG_POP()
  
  }                                                    // namespace enumeration
}                                                           // namespace elib
#endif /* ELIB_ENUMERATION_ENUM_FIELDS_HPP */