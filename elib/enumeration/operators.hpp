#ifndef ELIB_ENUMERATION_OPERATORS_HPP
#define ELIB_ENUMERATION_OPERATORS_HPP

# include <elib/enumeration/enum_helper.hpp>
# include <elib/enumeration/enum_traits.hpp>

# include <elib/utility.hpp>
# include <elib/CXX14/type_traits.hpp>

namespace elib 
{
  namespace enumeration
  {
    
    /* To defeat ADL, elib::enumeration provides highly constrained operators
     * which frequently need to be imported into another namespace
     * these macros provide that
     */
# define ELIB_ENUM_USING_OPERATORS() \
  using namespace ::elib::enumeration::operators;
    
    namespace detail
    {
      
      template <class T, bool=std::is_enum<T>::value>
      struct is_bitmask : std::false_type
      {};
      
      template <class T>
      struct is_bitmask<T, true>
        : std::integral_constant<bool, enum_traits<T>::is_bitmask>
      {};
      
      
      template <class T, bool=std::is_enum<T>::value>
      struct is_arithmetic : std::false_type
      {};
      
      template <class T>
      struct is_arithmetic<T, true>
        : std::integral_constant<bool, enum_traits<T>::is_arithmetic>
      {};
      
      
      template <class T, bool=std::is_enum<T>::value>
      struct is_logical : std::false_type
      {};
      
      template <class T>
      struct is_logical<T, true>
        : std::integral_constant<bool, enum_traits<T>::is_logical>
      {};
      
      
      template <class T, bool=std::is_enum<T>::value>
      struct is_mixed_comparible : std::false_type
      {};
      
      template <class T>
      struct is_mixed_comparible<T, true>
        : std::integral_constant<bool, enum_traits<T>::is_mixed_comparible>
      {};
      
      
      template <class LHS, class RHS, class Ret=LHS>
      using enable_if_bitmask_t =
        std::enable_if_t<
          is_bitmask<LHS>::value
            && (std::is_integral<RHS>::value
              || std::is_same<LHS, RHS>::value)
          , Ret 
        >;
        
        
      template <class LHS, class RHS, class Ret=LHS>
      using enable_if_arithmetic_t =
        std::enable_if_t<
          is_arithmetic<LHS>::value
            && (std::is_integral<RHS>::value
              || std::is_same<LHS, RHS>::value)
          , Ret
        >;
        
      /* logical operators work differently then arithmetic and bitwise
       * operators. First they accept the following combinations of operands
       * (assuming the enum types are logical)
       * 
       * Enum1 op Enum2 -> bool
       * Enum op Integral -> bool
       * Integral op Enum -> bool
       * 
       */
      
      template <class Enum1, class Enum2>
      using is_logical_enum_enum = 
        std::integral_constant<bool,
          is_logical<Enum1>::value
            && is_logical<Enum2>::value
        >;
        
      template <class Enum, class Int>
      using is_logical_enum_integral =
        std::integral_constant<bool, 
          is_logical<Enum>::value
            && std::is_integral<Int>::value
        >;
        
      template <class LHS, class RHS, class Ret=bool>
      using enable_if_logical_t =
        std::enable_if_t<
          is_logical_enum_enum<LHS, RHS>::value
            || is_logical_enum_integral<LHS, RHS>::value
            || is_logical_enum_integral<RHS, LHS>::value
          , Ret
        >;
        
      template <class LHS, class RHS, class Ret=bool>
      using enable_if_mixed_comparible_t =
        std::enable_if_t<
          is_mixed_comparible<LHS>::value
            && (std::is_integral<RHS>::value
              || std::is_enum<RHS>::value)
          , Ret
        >;
        
      /* Since we frequently want to cast enum operands, 
       * but we don't know if a type is an enum (in a lot of cases)
       * we create an optional cast that downcasts enums, and
       * forwards integral types
       */
      template <class T>
      constexpr enable_if_enum_t<T, sfinae_underlying_type_t<T>>
      opt_cast(T v) noexcept
      {
        return underlying_cast(v);
      }
      
      template <class T>
      constexpr std::enable_if_t<std::is_integral<T>::value, T>
      opt_cast(T v) noexcept
      {
        return v;
      }

    }                                                       // namespace detail
    
    namespace operators
    {
      ////////////////////////////////////////////////////////////////////////////////
      //                         bitwise
      ////////////////////////////////////////////////////////////////////////////////
      
      template <class LHS>
      constexpr std::enable_if_t<detail::is_bitmask<LHS>::value, LHS>
      operator~(LHS v) noexcept
      {
        return static_cast<LHS>(~ underlying_cast(v));
      }
      
      template <class LHS, class RHS>
      constexpr detail::enable_if_bitmask_t<LHS, RHS>
      operator&(LHS lhs, RHS rhs) noexcept
      {
        return static_cast<LHS>(detail::opt_cast(lhs) & detail::opt_cast(rhs));
      }
      
      template <class LHS, class RHS>
      constexpr detail::enable_if_bitmask_t<LHS, RHS>
      operator|(LHS lhs, RHS rhs) noexcept
      {
        return static_cast<LHS>(detail::opt_cast(lhs) | detail::opt_cast(rhs));
      }
      
      template <class LHS, class RHS>
      constexpr detail::enable_if_bitmask_t<LHS, RHS>
      operator^(LHS lhs, RHS rhs) noexcept
      {
        return static_cast<LHS>(detail::opt_cast(lhs) ^ detail::opt_cast(rhs));
      }
      
      template <class LHS, class RHS>
      constexpr detail::enable_if_bitmask_t<LHS, RHS>
      operator<<(LHS lhs, RHS rhs) noexcept
      {
        return static_cast<LHS>(detail::opt_cast(lhs) << detail::opt_cast(rhs));
      }
      
      template <class LHS, class RHS>
      constexpr detail::enable_if_bitmask_t<LHS, RHS>
      operator>>(LHS lhs, RHS rhs) noexcept
      {
        return static_cast<LHS>(detail::opt_cast(lhs) >> detail::opt_cast(rhs));
      }
      
    // Compound operators
      template <class LHS, class RHS>
      detail::enable_if_bitmask_t<LHS, RHS>&
      operator&=(LHS& lhs, RHS rhs) noexcept
      {
        return lhs = lhs & rhs;
      }
      
      template <class LHS, class RHS>
      detail::enable_if_bitmask_t<LHS, RHS>&
      operator|=(LHS& lhs, RHS rhs) noexcept
      {
        return lhs = lhs | rhs;
      }
      
      template <class LHS, class RHS>
      detail::enable_if_bitmask_t<LHS, RHS>&
      operator^=(LHS& lhs, RHS rhs) noexcept
      {
        return lhs = lhs ^ rhs;
      }
      
      template <class LHS, class RHS>
      detail::enable_if_bitmask_t<LHS, RHS>&
      operator<<=(LHS& lhs, RHS rhs) noexcept
      {
        return lhs = lhs << rhs;
      }
      
      template <class LHS, class RHS>
      detail::enable_if_bitmask_t<LHS, RHS>&
      operator>>=(LHS& lhs, RHS rhs) noexcept
      {
        return lhs = lhs >> rhs;
      }
      
      
      ////////////////////////////////////////////////////////////////////////////////
      //                           arithmetic                                              
      ////////////////////////////////////////////////////////////////////////////////
      
    // Unary "+" and "-"
      template <class LHS>
      constexpr std::enable_if_t<detail::is_arithmetic<LHS>::value, LHS>
      operator+(LHS lhs) noexcept
      {
        return static_cast<LHS>(+ underlying_cast(lhs));
      }
      
      template <class LHS>
      constexpr std::enable_if_t<detail::is_arithmetic<LHS>::value, LHS>
      operator-(LHS lhs) noexcept
      {
        return static_cast<LHS>(- underlying_cast(lhs));
      }
      
    // Increment & Decrement
      template <class LHS, ELIB_ENABLE_IF(detail::is_arithmetic<LHS>::value)>
      constexpr LHS operator++(LHS lhs, int) noexcept
      {
        return static_cast<LHS>(underlying_cast(lhs) + 1);
      }
      
      template <class LHS, ELIB_ENABLE_IF(detail::is_arithmetic<LHS>::value)>
      LHS& operator++(LHS& lhs) noexcept
      {
        return lhs = lhs++;
      }
      
      template <class LHS, ELIB_ENABLE_IF(detail::is_arithmetic<LHS>::value)>
      constexpr LHS operator--(LHS lhs, int) noexcept
      {
        return static_cast<LHS>(underlying_cast(lhs) - 1);
      }
      
      template <class LHS, ELIB_ENABLE_IF(detail::is_arithmetic<LHS>::value)>
      LHS& operator--(LHS& lhs) noexcept
      {
        return lhs = lhs--;
      }

    // Add, Sub, Mul, Div, Mod
      template <class LHS, class RHS>
      constexpr detail::enable_if_arithmetic_t<LHS, RHS>
      operator+(LHS lhs, RHS rhs) noexcept
      {
        return static_cast<LHS>(detail::opt_cast(lhs) + detail::opt_cast(rhs));
      }
      
      template <class LHS, class RHS>
      constexpr detail::enable_if_arithmetic_t<LHS, RHS>
      operator-(LHS lhs, RHS rhs) noexcept
      {
        return static_cast<LHS>(detail::opt_cast(lhs) - detail::opt_cast(rhs));
      }
      
      template <class LHS, class RHS>
      constexpr detail::enable_if_arithmetic_t<LHS, RHS>
      operator*(LHS lhs, RHS rhs) noexcept
      {
        return static_cast<LHS>(detail::opt_cast(lhs) * detail::opt_cast(rhs));
      }
      
      template <class LHS, class RHS>
      constexpr detail::enable_if_arithmetic_t<LHS, RHS>
      operator/(LHS lhs, RHS rhs)
      {
        return static_cast<LHS>(detail::opt_cast(lhs) / detail::opt_cast(rhs));
      }
      
      template <class LHS, class RHS>
      constexpr detail::enable_if_arithmetic_t<LHS, RHS>
      operator%(LHS lhs, RHS rhs)
      {
        return static_cast<LHS>(detail::opt_cast(lhs) % detail::opt_cast(rhs));
      }
      
    // Compound operators
      template <class LHS, class RHS>
      detail::enable_if_arithmetic_t<LHS, RHS>&
      operator+=(LHS& lhs, RHS rhs) noexcept
      {
        return lhs = lhs + rhs;
      }
      
      template <class LHS, class RHS>
      detail::enable_if_arithmetic_t<LHS, RHS>&
      operator-=(LHS& lhs, RHS rhs) noexcept
      {
        return lhs = lhs - rhs;
      }
      
      template <class LHS, class RHS>
      detail::enable_if_arithmetic_t<LHS, RHS>&
      operator*=(LHS& lhs, RHS rhs) noexcept
      {
        return lhs = lhs * rhs;
      }
      
      template <class LHS, class RHS>
      detail::enable_if_arithmetic_t<LHS, RHS>&
      operator/=(LHS& lhs, RHS rhs)
      {
        return lhs = lhs / rhs;
      }
      
      template <class LHS, class RHS>
      detail::enable_if_arithmetic_t<LHS, RHS>&
      operator%=(LHS& lhs, RHS rhs)
      {
        return lhs = lhs % rhs;
      }
      
    ////////////////////////////////////////////////////////////////////////////////
    //                        Logical                                                  
    ////////////////////////////////////////////////////////////////////////////////

      template <class LHS>
      constexpr std::enable_if_t<detail::is_arithmetic<LHS>::value, bool>
      operator!(LHS lhs) noexcept
      {
        return (! underlying_cast(lhs));
      }
      
      template <class LHS, class RHS>
      constexpr detail::enable_if_logical_t<LHS, RHS, bool>
      operator&&(LHS lhs, RHS rhs) noexcept
      {
        return (detail::opt_cast(lhs) && detail::opt_cast(rhs));
      }
      
      template <class LHS, class RHS>
      constexpr detail::enable_if_logical_t<LHS, RHS, bool>
      operator||(LHS lhs, RHS rhs) noexcept
      {
        return (detail::opt_cast(lhs) || detail::opt_cast(rhs));
      }

    ////////////////////////////////////////////////////////////////////////////////
    //                     Mixed Comparible                                                     
    ////////////////////////////////////////////////////////////////////////////////
      
      template <class LHS, class RHS>
      constexpr detail::enable_if_mixed_comparible_t<LHS, RHS>
      operator==(LHS lhs, RHS rhs) noexcept
      {
        return static_cast<bool>(detail::opt_cast(lhs) == detail::opt_cast(rhs));
      }
      
      template <class LHS, class RHS>
      constexpr detail::enable_if_mixed_comparible_t<LHS, RHS>
      operator!=(LHS lhs, RHS rhs) noexcept
      {
        return ! (lhs == rhs);
      }
      
      template <class LHS, class RHS>
      constexpr detail::enable_if_mixed_comparible_t<LHS, RHS>
      operator<(LHS lhs, RHS rhs) noexcept
      {
        return static_cast<bool>(detail::opt_cast(lhs) < detail::opt_cast(rhs));
      }
      
      template <class LHS, class RHS>
      constexpr detail::enable_if_mixed_comparible_t<LHS, RHS>
      operator<=(LHS lhs, RHS rhs) noexcept
      {
        return (lhs < rhs || lhs == rhs);
      }
      
      template <class LHS, class RHS>
      constexpr detail::enable_if_mixed_comparible_t<LHS, RHS>
      operator>(LHS lhs, RHS rhs) noexcept
      {
        return !(lhs <= rhs);
      }
      
      template <class LHS, class RHS>
      constexpr detail::enable_if_mixed_comparible_t<LHS, RHS>
      operator>=(LHS lhs, RHS rhs) noexcept
      {
        return (lhs > rhs || lhs == rhs);
      }
 
    }                                                    // namespace operators
  }                                                    // namespace enumeration
}                                                            // namespace elib
#endif /* ELIB_ENUMERATION_OPERATORS_HPP */
