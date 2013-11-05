#ifndef ELIB_ENUMERATION_OPERATORS_HPP
# define ELIB_ENUMERATION_OPERATORS_HPP

# include <elib/config.hpp>
# include <elib/enumeration/v3/enum_helper.hpp>
# include <elib/enumeration/v3/enum_traits.hpp>

# include <elib/CXX14/type_traits.hpp>

namespace elib 
{
  namespace enumeration
  {
    
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
      template <class LHS>
      constexpr std::enable_if_t<detail::is_arithmetic<LHS>::value, LHS>
      operator++(LHS lhs, int) noexcept
      {
        return static_cast<LHS>(underlying_cast(lhs) + 1);
      }
      
      template <class LHS>
      std::enable_if_t<detail::is_arithmetic<LHS>::value, LHS&>
      operator++(LHS& lhs) noexcept
      {
        return lhs = lhs++;
      }
      
      template <class LHS>
      constexpr std::enable_if_t<detail::is_arithmetic<LHS>::value, LHS>
      operator--(LHS lhs, int) noexcept
      {
        return static_cast<LHS>(underlying_cast(lhs) - 1);
      }
      
      template <class LHS>
      std::enable_if_t<detail::is_arithmetic<LHS>::value, LHS&>
      operator--(LHS& lhs) noexcept
      {
        return lhs = lhs--;
      }
      
    // Add, Sub, Mul, Div, Mod
      template <class LHS, class RHS>
      constexpr detail::enable_if_arithmetic_t<LHS, RHS>
      operator+(LHS lhs, RHS rhs) noexcept
      {
        return static_cast<LHS>(opt_cast(lhs) + opt_cast(rhs));
      }
      
      template <class LHS, class RHS>
      constexpr detail::enable_if_arithmetic_t<LHS, RHS>
      operator-(LHS lhs, RHS rhs) noexcept
      {
        return static_cast<LHS>(opt_cast(lhs) - opt_cast(rhs));
      }
      
      template <class LHS, class RHS>
      constexpr detail::enable_if_arithmetic_t<LHS, RHS>
      operator*(LHS lhs, RHS rhs) noexcept
      {
        return static_cast<LHS>(opt_cast(lhs) * opt_cast(rhs));
      }
      
      template <class LHS, class RHS>
      constexpr detail::enable_if_arithmetic_t<LHS, RHS>
      operator/(LHS lhs, RHS rhs)
      {
        return static_cast<LHS>(opt_cast(lhs) / opt_cast(rhs));
      }
      
      template <class LHS, class RHS>
      constexpr detail::enable_if_arithmetic_t<LHS, RHS>
      operator%(LHS lhs, RHS rhs)
      {
        return static_cast<LHS>(opt_cast(lhs) % opt_cast(rhs));
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
      
      
      
      
      
    }                                                    // namespace operators
  }                                                    // namespace enumeration
}                                                            // namespace elib
#endif /* ELIB_ENUMERATION_OPERATORS_HPP */
