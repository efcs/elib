#ifndef ELIB_ENUMERATION_OPERATORS_HPP
# define ELIB_ENUMERATION_OPERATORS_HPP

# include <elib/config.hpp>
# include <elib/pragma.hpp>
# include <elib/enumeration/v2/enum_fields.hpp>
# include <elib/enumeration/v2/enum_traits.hpp>
# include <elib/enumeration/v2/enum_cast.hpp>

# include <elib/CXX14/type_traits.hpp>

namespace elib 
{
  namespace enumeration
  {
   
ELIB_PRAGMA_DIAG_PUSH()
ELIB_PRAGMA_IGNORE_EFFCXX()

    template <typename T>
    struct has_mixed_bitwise_operators
      : public std::integral_constant<bool, 
          allow_mixed_bitwise_operators_field<T>::bool_value>
    { };
    
    template <typename T>
    struct has_bitwise_operators
      : public std::integral_constant<bool,
          allow_bitwise_operators_field<T>::bool_value ||
          has_mixed_bitwise_operators<T>::value>
    { };
    
    template <typename T>
    struct has_mixed_logical_operators
      : public std::integral_constant<bool, 
          allow_mixed_logical_operators_field<T>::bool_value>
    { };

    template <typename T>
    struct has_logical_operators
      : public std::integral_constant<bool,
          allow_logical_operators_field<T>::bool_value ||
          has_mixed_logical_operators<T>::value>
    { };
    
    template <typename T>
    struct has_mixed_arithmetic_operators
      : public std::integral_constant<bool, 
          allow_mixed_arithmetic_operators_field<T>::bool_value>
    { };

    template <typename T>
    struct has_arithmetic_operators
      : public std::integral_constant<bool,
          allow_arithmetic_operators_field<T>::bool_value ||
          has_mixed_arithmetic_operators<T>::value>
    { };
    
    template <typename T>
    struct has_stream_extraction_operator
      : public std::integral_constant<bool, 
          allow_stream_extraction_operator_field<T>::bool_value>
    { };
    
    template <typename T>
    struct has_stream_insertion_operator
      : public std::integral_constant<bool, 
          allow_stream_insertion_operator_field<T>::bool_value>
    { };
    
    template <typename T>
    struct has_bool_indirection_operator
      : public std::integral_constant<bool, 
          allow_bool_indirection_operator_field<T>::bool_value>
    { };
    
    template <typename T>
    struct has_underlying_dereference_operator
      : public std::integral_constant<bool, 
          allow_underlying_dereference_operator_field<T>::bool_value>
    { };
    
ELIB_PRAGMA_DIAG_POP()
    
  ////////////////////////////////////////////////////////////////////////////////
  //                        PURE BITWISE OPERATORS                                                  
  ////////////////////////////////////////////////////////////////////////////////
    
    namespace operators
    {
      
      
      template <typename T>
      constexpr std::enable_if_t<has_bitwise_operators<T>::value, T>
      operator~(T op) noexcept
      {
        return static_cast<T>( ~ underlying_cast(op) );
      }
      
      template <typename T>
      constexpr std::enable_if_t<has_bitwise_operators<T>::value, T>
      operator&(T lhs, T rhs) noexcept
      {
        return static_cast<T>(underlying_cast(lhs) & underlying_cast(rhs));
      }
      
      template <typename T>
      constexpr std::enable_if_t<has_bitwise_operators<T>::value, T>
      operator|(T lhs, T rhs) noexcept
      {
        return static_cast<T>(underlying_cast(lhs) | underlying_cast(rhs));
      }
      
      template <typename T>
      constexpr std::enable_if_t<has_bitwise_operators<T>::value, T>
      operator^(T lhs, T rhs) noexcept
      {
        return static_cast<T>(underlying_cast(lhs) ^ underlying_cast(rhs));
      }
      
      template <typename T>
      constexpr std::enable_if_t<has_bitwise_operators<T>::value, T>
      operator<<(T lhs, T rhs) noexcept
      {
        return static_cast<T>(underlying_cast(lhs) << underlying_cast(rhs));
      }
      
      template <typename T>
      constexpr std::enable_if_t<has_bitwise_operators<T>::value, T>
      operator>>(T lhs, T rhs) noexcept
      {
        return static_cast<T>(underlying_cast(lhs) >> underlying_cast(rhs));
      }
      
      // Compound bitwise operators
      template <typename T>
      std::enable_if_t<has_bitwise_operators<T>::value, T>&
      operator&=(T& lhs, T rhs) noexcept
      {
        return (lhs = lhs & rhs);
      }
      
      template <typename T>
      std::enable_if_t<has_bitwise_operators<T>::value, T>&
      operator|=(T& lhs, T rhs) noexcept
      {
        return (lhs = lhs | rhs);
      }
      
      template <typename T>
      std::enable_if_t<has_bitwise_operators<T>::value, T>&
      operator^=(T& lhs, T rhs) noexcept
      {
        return (lhs = lhs ^ rhs);
      }
      
      template <typename T>
      std::enable_if_t<has_bitwise_operators<T>::value, T>&
      operator<<=(T& lhs, T rhs) noexcept
      {
        return (lhs = lhs << rhs);
      }
      
      template <typename T>
      std::enable_if_t<has_bitwise_operators<T>::value, T>&
      operator>>=(T& lhs, T rhs) noexcept
      {
        return (lhs = lhs >> rhs);
      }
      
      
    ////////////////////////////////////////////////////////////////////////////////
    //                         MIXED BITWISE OPERATORS                                              
    ////////////////////////////////////////////////////////////////////////////////
      
      // LHS = Enum & RHS = Integral
      
      template <typename T, typename Int>
      constexpr std::enable_if_t<detail::is_enum_integral<T, Int>::value
        && has_mixed_bitwise_operators<T>::value, T>
      operator&(T lhs, Int rhs) noexcept
      {
        return static_cast<T>(underlying_cast(lhs) & rhs);
      }
      
      template <typename T, typename Int>
      constexpr std::enable_if_t<detail::is_enum_integral<T, Int>::value
        && has_mixed_bitwise_operators<T>::value, T>
      operator|(T lhs, Int rhs) noexcept
      {
        return static_cast<T>(underlying_cast(lhs) | rhs);
      }
      
      template <typename T, typename Int>
      constexpr std::enable_if_t<detail::is_enum_integral<T, Int>::value
        && has_mixed_bitwise_operators<T>::value, T>
      operator^(T lhs, Int rhs) noexcept
      {
        return static_cast<T>(underlying_cast(lhs) ^ rhs);
      }
      
      template <typename T, typename Int>
      constexpr std::enable_if_t<detail::is_enum_integral<T, Int>::value
        && has_mixed_bitwise_operators<T>::value, T>
      operator>>(T lhs, Int rhs) noexcept
      {
        return static_cast<T>(underlying_cast(lhs) >> rhs);
      }
      
      template <typename T, typename Int>
      constexpr std::enable_if_t<detail::is_enum_integral<T, Int>::value
        && has_mixed_bitwise_operators<T>::value, T>
      operator<<(T lhs, Int rhs) noexcept
      {
        return static_cast<T>(underlying_cast(lhs) << rhs);
      }
      
      // Compound LHS = Enum & RHS = Integral
      template <typename T, typename Int>
      std::enable_if_t<detail::is_enum_integral<T, Int>::value
        && has_mixed_bitwise_operators<T>::value, T>&
      operator&=(T& lhs, Int rhs) noexcept
      {
        return (lhs = lhs & rhs);
      }
      
      template <typename T, typename Int>
      std::enable_if_t<detail::is_enum_integral<T, Int>::value
        && has_mixed_bitwise_operators<T>::value, T>&
      operator|=(T& lhs, Int rhs) noexcept
      {
        return (lhs = lhs | rhs);
      }
      
      template <typename T, typename Int>
      std::enable_if_t<detail::is_enum_integral<T, Int>::value
        && has_mixed_bitwise_operators<T>::value, T>&
      operator^=(T& lhs, Int rhs) noexcept
      {
        return (lhs = lhs ^ rhs);
      }
      
      template <typename T, typename Int>
      std::enable_if_t<detail::is_enum_integral<T, Int>::value
        && has_mixed_bitwise_operators<T>::value, T>&
      operator>>=(T& lhs, Int rhs) noexcept
      {
        return (lhs = lhs >> rhs);
      }
      
      template <typename T, typename Int>
      std::enable_if_t<detail::is_enum_integral<T, Int>::value
        && has_mixed_bitwise_operators<T>::value, T>&
      operator<<=(T& lhs, Int rhs) noexcept
      {
        return (lhs = lhs << rhs);
      }
      
      // LHS MIXED BITWISE OPERATORS
      
      template <typename Int, typename T>
      constexpr std::enable_if_t<detail::is_enum_integral<T, Int>::value
        && has_mixed_bitwise_operators<T>::value, Int>
      operator&(Int lhs, T rhs) noexcept
      {
        return (lhs & underlying_cast(rhs));
      }

      template <typename Int, typename T>
      constexpr std::enable_if_t<detail::is_enum_integral<T, Int>::value
        && has_mixed_bitwise_operators<T>::value, Int>
      operator|(Int lhs, T rhs) noexcept
      {
        return (lhs | underlying_cast(rhs));
      }

      template <typename Int, typename T>
      constexpr std::enable_if_t<detail::is_enum_integral<T, Int>::value
        && has_mixed_bitwise_operators<T>::value, Int>
      operator^(Int lhs, T rhs) noexcept
      {
        return (lhs ^ underlying_cast(rhs));
      }

      template <typename Int, typename T>
      constexpr std::enable_if_t<detail::is_enum_integral<T, Int>::value
        && has_mixed_bitwise_operators<T>::value, Int>
      operator>>(Int lhs, T rhs) noexcept
      {
        return (lhs >> underlying_cast(rhs));
      }

      template <typename Int, typename T>
      constexpr std::enable_if_t<detail::is_enum_integral<T, Int>::value
        && has_mixed_bitwise_operators<T>::value, Int>
      operator<<(Int lhs, T rhs) noexcept
      {
        return (lhs << underlying_cast(rhs));
      }

      // Compound LHS = Enum & RHS = Integral
      template <typename Int, typename T>
      std::enable_if_t<detail::is_enum_integral<T, Int>::value
        && has_mixed_bitwise_operators<T>::value, Int>&
      operator&=(Int& lhs, T rhs) noexcept
      {
        return (lhs = lhs & underlying_cast(rhs));
      }

      template <typename Int, typename T>
      std::enable_if_t<detail::is_enum_integral<T, Int>::value
        && has_mixed_bitwise_operators<T>::value, Int>&
      operator|=(Int& lhs, T rhs) noexcept
      {
        return (lhs = lhs | underlying_cast(rhs));
      }

      template <typename Int, typename T>
      std::enable_if_t<detail::is_enum_integral<T, Int>::value
        && has_mixed_bitwise_operators<T>::value, Int>&
      operator^=(Int& lhs, T rhs) noexcept
      {
        return (lhs = lhs ^ underlying_cast(rhs));
      }

      template <typename Int, typename T>
      std::enable_if_t<detail::is_enum_integral<T, Int>::value
        && has_mixed_bitwise_operators<T>::value, Int>&
      operator>>=(Int& lhs, T rhs) noexcept
      {
        return (lhs = lhs >> underlying_cast(rhs));
      }

      template <typename Int, typename T>
      std::enable_if_t<detail::is_enum_integral<T, Int>::value
        && has_mixed_bitwise_operators<T>::value, Int>&
      operator<<=(Int& lhs, T rhs) noexcept
      {
        return (lhs = lhs << underlying_cast(rhs));
      }
      
      
    ////////////////////////////////////////////////////////////////////////////////
    //                          LOGICAL OPERATORS                                                
    ////////////////////////////////////////////////////////////////////////////////
      template <typename T>
      constexpr std::enable_if_t<has_logical_operators<T>::value, bool>
      operator!(T op) noexcept
      {
        return static_cast<bool>(!underlying_cast(op));
      }
      
/* effc++ warning is triggered by casting both sides of a boolean expression
 * ie it voilates boolean short circuting
 * 
 * it is continued in the arithmetic operators because g++ does not properly
 * notices if the return type is a reference on not 
 */
ELIB_PRAGMA_DIAG_PUSH()
ELIB_PRAGMA_IGNORE_EFFCXX()
      
      template <typename T>
      constexpr std::enable_if_t<has_logical_operators<T>::value, bool>
      operator&&(T lhs, T rhs) noexcept
      {
        return static_cast<bool>(underlying_cast(lhs) && underlying_cast(rhs));
      }
      
      template <typename T>
      constexpr std::enable_if_t<has_logical_operators<T>::value, bool>
      operator||(T lhs, T rhs) noexcept
      {
        return static_cast<bool>(underlying_cast(lhs) || underlying_cast(rhs));
      }
      
      // Mixed logical operators
      // LHS = Enum & Rhs = Integral
      template <typename T, typename Int>
      constexpr std::enable_if_t<detail::is_enum_integral<T, Int>::value
          && has_mixed_logical_operators<T>::value, bool>
      operator&&(T lhs, Int rhs) noexcept
      {
        return static_cast<bool>(underlying_cast(lhs) && rhs);
      }
      
      template <typename T, typename Int>
      constexpr std::enable_if_t<detail::is_enum_integral<T, Int>::value
          && has_mixed_logical_operators<T>::value, bool>
      operator||(T lhs, Int rhs) noexcept
      {
        return static_cast<bool>(underlying_cast(lhs) || rhs);
      }
      
      // LHS = Integral & RHS = Enum
      template <typename Int, typename T>
      constexpr std::enable_if_t<detail::is_enum_integral<T, Int>::value
          && has_mixed_logical_operators<T>::value, bool>
      operator&&(Int lhs, T rhs) noexcept
      {
        return static_cast<bool>(lhs && underlying_cast(rhs));
      }
      
      template <typename Int, typename T>
      constexpr std::enable_if_t<detail::is_enum_integral<T, Int>::value
          && has_mixed_logical_operators<T>::value, bool>
      operator||(Int lhs, T rhs) noexcept
      {
        return static_cast<bool>(lhs || underlying_cast(rhs));
      }
      

      
    ////////////////////////////////////////////////////////////////////////////////
    //                       Arithmetic Operators                                                   
    ////////////////////////////////////////////////////////////////////////////////
    
    // Unary operators
      template <typename T>
      constexpr std::enable_if_t<has_arithmetic_operators<T>::value, T>
      operator+(T op) noexcept
      {
        return static_cast<T>(+ underlying_cast(op));
      }
    
      template <typename T>
      constexpr std::enable_if_t<has_arithmetic_operators<T>::value, T>
      operator-(T op) noexcept
      {
        return static_cast<T>(- underlying_cast(op));
      }
    
    //TODO fix reference return types 
    
    // Increment & Decrement
      template <typename T>
      std::enable_if_t<has_arithmetic_operators<T>::value, T&>
      operator++(T& op) noexcept
      {
        return (op = static_cast<T>(underlying_cast(op) + 1));
      }
      
      template <typename T>
      std::enable_if_t<has_arithmetic_operators<T>::value, T>
      operator++(T& op, int) noexcept
      {
        auto tmp = op;
        ++op;
        return tmp;
      }
      
      template <typename T>
      std::enable_if_t<has_arithmetic_operators<T>::value, T&>
      operator--(T& op) noexcept
      {
        return (op = static_cast<T>(underlying_cast(op) - 1));
      }

      template <typename T>
      std::enable_if_t<has_arithmetic_operators<T>::value, T>
      operator--(T& op, int) noexcept
      {
        auto tmp = op;
        --op;
        return tmp;
      }
      
ELIB_PRAGMA_DIAG_POP()
      
    // Pure Binary operators
      
      template <typename T>
      constexpr std::enable_if_t<has_arithmetic_operators<T>::value, T>
      operator+(T lhs, T rhs) noexcept
      {
        return static_cast<T>(underlying_cast(lhs) + underlying_cast(rhs));
      }
      
      template <typename T>
      constexpr std::enable_if_t<has_arithmetic_operators<T>::value, T>
      operator-(T lhs, T rhs) noexcept
      {
        return static_cast<T>(underlying_cast(lhs) - underlying_cast(rhs));
      }
      
      template <typename T>
      constexpr std::enable_if_t<has_arithmetic_operators<T>::value, T>
      operator*(T lhs, T rhs) noexcept
      {
        return static_cast<T>(underlying_cast(lhs) * underlying_cast(rhs));
      }
      
      template <typename T>
      constexpr std::enable_if_t<has_arithmetic_operators<T>::value, T>
      operator/(T lhs, T rhs) noexcept
      {
        return static_cast<T>(underlying_cast(lhs) / underlying_cast(rhs));
      }
      
      template <typename T>
      constexpr std::enable_if_t<has_arithmetic_operators<T>::value, T>
      operator%(T lhs, T rhs) noexcept
      {
        return static_cast<T>(underlying_cast(lhs) % underlying_cast(rhs));
      }
      
      // Compound Pure Binary Arithmetic operators
      
      template <typename T>
      std::enable_if_t<has_arithmetic_operators<T>::value, T>&
      operator+=(T& lhs, T rhs) noexcept
      {
        return (lhs = lhs + rhs);
      }
      
      template <typename T>
      std::enable_if_t<has_arithmetic_operators<T>::value, T>&
      operator-=(T& lhs, T rhs) noexcept
      {
        return (lhs = lhs - rhs);
      }
      
      template <typename T>
      std::enable_if_t<has_arithmetic_operators<T>::value, T>&
      operator*=(T& lhs, T rhs) noexcept
      {
        return (lhs = lhs * rhs);
      }
      
      template <typename T>
      std::enable_if_t<has_arithmetic_operators<T>::value, T>&
      operator/=(T& lhs, T rhs) noexcept
      {
        return (lhs = lhs / rhs);
      }
      
      template <typename T>
      std::enable_if_t<has_arithmetic_operators<T>::value, T>&
      operator%=(T& lhs, T rhs) noexcept
      {
        return (lhs = lhs % rhs);
      }
      
      
      // MIXED ARITHMETIC OPERATORS
      
      // LHS = Enum & RHS = Integral
      template <typename T, typename Int>
      constexpr std::enable_if_t< detail::is_enum_integral<T, Int>::value
          && has_mixed_arithmetic_operators<T>::value, T>
      operator+(T lhs, Int rhs) noexcept
      {
        return static_cast<T>(underlying_cast(lhs) + rhs);
      }
      
      template <typename T, typename Int>
      constexpr std::enable_if_t< detail::is_enum_integral<T, Int>::value
          && has_mixed_arithmetic_operators<T>::value, T>
      operator-(T lhs, Int rhs) noexcept
      {
        return static_cast<T>(underlying_cast(lhs) - rhs);
      }
      
      template <typename T, typename Int>
      constexpr std::enable_if_t< detail::is_enum_integral<T, Int>::value
          && has_mixed_arithmetic_operators<T>::value, T>
      operator*(T lhs, Int rhs) noexcept
      {
        return static_cast<T>(underlying_cast(lhs) * rhs);
      }
      
      template <typename T, typename Int>
      constexpr std::enable_if_t< detail::is_enum_integral<T, Int>::value
          && has_mixed_arithmetic_operators<T>::value, T>
      operator/(T lhs, Int rhs) noexcept
      {
        return static_cast<T>(underlying_cast(lhs) / rhs);
      }
      
      template <typename T, typename Int>
      constexpr std::enable_if_t< detail::is_enum_integral<T, Int>::value
          && has_mixed_arithmetic_operators<T>::value, T>
      operator%(T lhs, Int rhs) noexcept
      {
        return static_cast<T>(underlying_cast(lhs) % rhs);
      }
      
      // Compound mixed with LHS = Enum & RHS = Integral
      template <typename T, typename Int>
      std::enable_if_t<detail::is_enum_integral<T, Int>::value
          && has_mixed_arithmetic_operators<T>::value, T>&
      operator+=(T& lhs, Int rhs) noexcept
      {
        return (lhs = lhs + rhs);
      }
      
      template <typename T, typename Int>
      std::enable_if_t<detail::is_enum_integral<T, Int>::value
          && has_mixed_arithmetic_operators<T>::value, T>&
      operator-=(T& lhs, Int rhs) noexcept
      {
        return (lhs = lhs - rhs);
      }
      
      template <typename T, typename Int>
      std::enable_if_t<detail::is_enum_integral<T, Int>::value
          && has_mixed_arithmetic_operators<T>::value, T>&
      operator*=(T& lhs, Int rhs) noexcept
      {
        return (lhs = lhs * rhs);
      }
      
      template <typename T, typename Int>
      std::enable_if_t<detail::is_enum_integral<T, Int>::value
          && has_mixed_arithmetic_operators<T>::value, T>&
      operator/=(T& lhs, Int rhs) noexcept
      {
        return (lhs = lhs / rhs);
      }
      
      template <typename T, typename Int>
      std::enable_if_t<detail::is_enum_integral<T, Int>::value
          && has_mixed_arithmetic_operators<T>::value, T>&
      operator%=(T& lhs, Int rhs) noexcept
      {
        return (lhs = lhs % rhs);
      }
        
      
      // LHS = Integral & RHS = Enum
      
      template <typename Int, typename T>
      constexpr std::enable_if_t<detail::is_enum_integral<T, Int>::value
          && has_mixed_arithmetic_operators<T>::value, Int>
      operator+(Int rhs, T lhs) noexcept
      {
        return rhs + underlying_cast(lhs);
      }
      
      template <typename Int, typename T>
      constexpr std::enable_if_t<detail::is_enum_integral<T, Int>::value
          && has_mixed_arithmetic_operators<T>::value, Int>
      operator-(Int rhs, T lhs) noexcept
      {
        return rhs - underlying_cast(lhs);
      }
      
      template <typename Int, typename T>
      constexpr std::enable_if_t<detail::is_enum_integral<T, Int>::value
          && has_mixed_arithmetic_operators<T>::value, Int>
      operator*(Int rhs, T lhs) noexcept
      {
        return rhs * underlying_cast(lhs);
      }
      
      template <typename Int, typename T>
      constexpr std::enable_if_t<detail::is_enum_integral<T, Int>::value
          && has_mixed_arithmetic_operators<T>::value, Int>
      operator/(Int rhs, T lhs) noexcept
      {
        return rhs / underlying_cast(lhs);
      }
      
      template <typename Int, typename T>
      constexpr std::enable_if_t<detail::is_enum_integral<T, Int>::value
          && has_mixed_arithmetic_operators<T>::value, Int>
      operator%(Int rhs, T lhs) noexcept
      {
        return rhs % underlying_cast(lhs);
      }
      
      // compound mixed arithmetic where LHS = Integral & RHS = Enum
      template <typename Int, typename T>
      std::enable_if_t<detail::is_enum_integral<T, Int>::value
          && has_mixed_arithmetic_operators<T>::value, Int>&
      operator+=(Int& lhs, T rhs) noexcept
      {
        return (lhs = lhs + rhs);
      }
      
      template <typename Int, typename T>
      std::enable_if_t<detail::is_enum_integral<T, Int>::value
          && has_mixed_arithmetic_operators<T>::value, Int>&
      operator-=(Int& lhs, T rhs) noexcept
      {
        return (lhs = lhs - rhs);
      }
      
      template <typename Int, typename T>
      std::enable_if_t<detail::is_enum_integral<T, Int>::value
          && has_mixed_arithmetic_operators<T>::value, Int>&
      operator*=(Int& lhs, T rhs) noexcept
      {
        return (lhs = lhs * rhs);
      }
      
      template <typename Int, typename T>
      std::enable_if_t<detail::is_enum_integral<T, Int>::value
          && has_mixed_arithmetic_operators<T>::value, Int>&
      operator/=(Int& lhs, T rhs) noexcept
      {
        return (lhs = lhs / rhs);
      }
      
      template <typename Int, typename T>
      std::enable_if_t<detail::is_enum_integral<T, Int>::value
          && has_mixed_arithmetic_operators<T>::value, Int>&
      operator%=(Int& lhs, T rhs) noexcept
      {
        return (lhs = lhs % rhs);
      }
      
      
    ////////////////////////////////////////////////////////////////////////////////
    //                              Stream Operators                                              
    ////////////////////////////////////////////////////////////////////////////////
     
      template <typename T>
      std::enable_if_t<has_stream_insertion_operator<T>::value, std::ostream>&
      operator<< (std::ostream& out, T val)
      {
        out << enum_cast<std::string>(val);
        return out;
      }
      
      template <typename T>
      std::enable_if_t<has_stream_extraction_operator<T>::value, std::istream>&
      operator>>(std::istream& in, T& val)
      {
        std::string s;
        in >> s;
        val = enum_cast<T>(s);
        return in;
      }
      
      
    ////////////////////////////////////////////////////////////////////////////////
    //                 Bool Indirection and Underlying dereference                                                   
    ////////////////////////////////////////////////////////////////////////////////
      
      
      template <typename T>
      constexpr std::enable_if_t<has_bool_indirection_operator<T>::value, bool>
      operator*(T val) noexcept
      {
        return static_cast<bool>(val);
      }
      
      
      template <typename T>
      constexpr std::enable_if_t<has_underlying_dereference_operator<T>::value,
        detail::sfinae_underlying_type_t<T>>
      operator&(T val) noexcept
      {
        return underlying_cast(val);
      }
      
      
    }                                                    // namespace operators
  }                                                    // namespace enumeration
}                                                      // namespace elib

ELIB_PRAGMA_DIAG_PUSH()
ELIB_PRAGMA_IGNORE_HEADER_HYGIENE()

// import operators into top level namespace
using namespace elib::enumeration::operators;

ELIB_PRAGMA_DIAG_POP()

#endif /* ELIB_ENUMERATION_OPERATORS_HPP */
