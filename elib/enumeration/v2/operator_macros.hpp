#ifndef ELIB_ELIB_ENUMERATION_OPERATOR_MACROS_HPP
# define ELIB_ELIB_ENUMERATION_OPERATOR_MACROS_HPP

# include <elib/config.hpp>
# include <elib/enumeration/v2/operators.hpp>
# include <elib/enumeration/v2/enum_traist.hpp>
# include <elib/enumeration/v2/enum_cast.hpp>

# include <elib/CXX14/type_traits.hpp>


namespace elib
{
  namespace enumeration
  {
    namespace detail
    {
      template <typename T>
      constexpr std::enable_if_t<std::is_integral<T>::value, T>
      generic_cast(T val) noexcept
      { return val; }
      
      template <typename T>
      constexpr std::enable_if_t<std::is_enum<T>::value, 
          sfinae_underlying_type_t<T>>
      generic_cast(T val) noexcept
      { return underlying_cast(val); }
    
    }                                                       // namespace detail
  }                                                    // namespace enumeration
}                                                           // namespace elib


# define _ELIB_GCAST(v) ::elib::enumeration::detail::generic_cast(v)


////////////////////////////////////////////////////////////////////////////////
//                         binary bitwise operators                                              
////////////////////////////////////////////////////////////////////////////////

# define ELIB_ENUMERATION_DEFINE_UNARY_BITWISE_OPERATORS(EnumT) \
                                                                \
  constexpr EnumT operator~(EnumT op) noexcept                  \
  { return static_cast<EnumT>(~ _ELIB_GCAST(op)); }             
  
  
# define ELIB_ENUMERATION_DEFINE_BINARY_BITWISE_OPERATORS_2(LHS, RHS)       \
                                                                            \
  constexpr LHS operator&(LHS lhs, RHS rhs) noexcept                        \
  { return static_cast<LHS>(_ELIB_GCAST(lhs) & _ELIB_GCAST(rhs)); }         \
                                                                            \
  constexpr LHS operator|(LHS lhs, RHS rhs) noexcept                        \
  { return static_cast<LHS>(_ELIB_GCAST(lhs) | _ELIB_GCAST(rhs)); }         \
                                                                            \
  constexpr LHS operator^(LHS lhs, RHS rhs) noexcept                        \
  { return static_cast<LHS>(_ELIB_GCAST(lhs) ^ _ELIB_GCAST(rhs)); }         \
                                                                            \
  inline LHS& operator&=(LHS& lhs, RHS rhs) noexcept                        \
  { return (lhs = static_cast<LHS>(_ELIB_GCAST(lhs) & _ELIB_GCAST(rhs))); } \
                                                                            \
  inline LHS& operator|=(LHS& lhs, RHS rhs) noexcept                        \
  { return (lhs = static_cast<LHS>(_ELIB_GCAST(lhs) | _ELIB_GCAST(rhs))); } \
                                                                            \
  inline LHS& operator^=(LHS& lhs, RHS rhs) noexcept                        \
  { return (lhs = static_cast<LHS>(_ELIB_GCAST(lhs) ^ _ELIB_GCAST(rhs))); }
  
  
# define ELIB_ENUMERATION_DEFINE_BINARY_BITWISE_OPERATORS(EnumT)   \
  ELIB_ENUMERATION_DEFINE_BINARY_BITWISE_OPERATORS_2(EnumT, EnumT) 
  
  
# define ELIB_ENUMERATION_DEFINE_BITWISE_OPERATORS(EnumT) \
  ELIB_ENUMERATION_DEFINE_UNARY_BITWISE_OPERATORS(EnumT)  \
  ELIB_ENUMERATION_DEFINE_BINARY_BITWISE_OPERATORS(EnumT)
  

////////////////////////////////////////////////////////////////////////////////
//                      LOGICAL OPERATORS                                                        
////////////////////////////////////////////////////////////////////////////////
  
# define ELIB_ENUMERATION_DEFINE_UNARY_LOGICAL_OPERATORS(EnumT) \
                                                                \
  constexpr bool operator!(EnumT op) noexcept                   \
  { return static_cast<bool>(op); }                             
  
  
# define ELIB_ENUMERATION_DEFINE_BINARY_LOGICAL_OPERATORS_2(LHS, RHS)   \
                                                                      \
  constexpr bool operator&&(LHS lhs, RHS rhs) noexcept                \
  { return static_cast<bool>(_ELIB_GCAST(lhs) && _ELIB_GCAST(rhs)); } \
                                                                      \
  constexpr bool operator||(LHS lhs, RHS rhs) noexcept                \
  { return static_cast<bool>(_ELIB_GCAST(lhs) || _ELIB_GCAST(rhs)); } 
  
  
# define ELIB_ENUMERATION_DEFINE_BINARY_LOGICAL_OPERATORS(EnumT)   \
  ELIB_ENUMERATION_DEFINE_BINARY_LOGICAL_OPERATORS_2(EnumT, EnumT) 
  
  
# define ELIB_ENUMERATION_DEFINE_LOGICAL_OPERATORS(EnumT) \
  ELIB_ENUMERATION_DEFINE_UNARY_LOGICAL_OPERATORS(EnumT)  \
  ELIB_ENUMERATION_DEFINE_BINARY_LOGICAL_OPERATORS(EnumT)
  
  
////////////////////////////////////////////////////////////////////////////////
//                           Arithmetic Operators                                               
////////////////////////////////////////////////////////////////////////////////

# define ELIB_ENUMERATION_DEFINE_INCREMENT_OPERATORS(EnumT)   \
                                                              \
  inline EnumT& operator++(EnumT& op) noexcept                \
  { return (op = static_cast<EnumT>(_ELIB_GCAST(op) + 1)); } \
                                                              \
  inline EnumT operator++(EnumT& op, int) noexcept            \
  {                                                           \
    auto ret = op;                                            \
    ++op;                                                     \
    return ret;                                               \
  }                                                           
                                                              
                                                              
# define ELIB_ENUMERATION_DEFINE_DECREMENT_OPERATORS(EnumT)  \
                                                             \
  inline EnumT& operator--(EnumT& op) noexcept               \
  { return (op = static_cast<EnumT>(_ELIB_GCAST(op) - 1)); } \
                                                             \
  inline EnumT operator--(EnumT& op, int) noexcept           \
  {                                                          \
    auto ret = op;                                           \
    --op;                                                    \
    return ret;                                              \
  }
  
  
# define ELIB_ENUMERATION_DEFINE_UNARY_ARITHMETIC_OPERATORS(EnumT) \
                                                                   \
  constexpr EnumT operator+(EnumT op) noexcept                     \
  { return static_cast<EnumT>(+ _ELIB_GCAST(op)); }                \
                                                                   \
  constexpr EnumT operator-(EnumT op) noexcept                     \
  { return static_cast<EnumT>(- _ELIB_GCAST(op)); }
  
  
# define ELIB_ENUMERATION_DEFINE_BINARY_ADD_2(LHS, RHS)               \
                                                                      \
  constexpr EnumT operator+(LHS lhs, RHS rhs) noexcept                \
  { return static_cast<EnumT>(_ELIB_GCAST(lhs) + _ELIB_GCAST(rhs)); } \
                                                                      \
  inline EnumT& operator+=(LHS& lhs, RHS rhs) noexcept                \
  { return (lhs = static_cast<EnumT>(_ELIB_GCAST(lhs) + _ELIB_GCAST(rhs))); } 
  
  
# define ELIB_ENUMERATION_DEFINE_BINARY_ADD(EnumT)   \
  ELIB_ENUMERATION_DEFINE_BINARY_ADD_2(EnumT, EnumT)
  
  
# define ELIB_ENUMERATION_DEFINE_BINARY_SUBTRACT_2(LHS, RHS)          \
                                                                      \
  constexpr EnumT operator-(LHS lhs, RHS rhs) noexcept                \
  { return static_cast<EnumT>(_ELIB_GCAST(lhs) - _ELIB_GCAST(rhs)); } \
                                                                      \
  inline EnumT& operator-=(LHS& lhs, RHS rhs) noexcept                \
  { return (lhs = static_cast<EnumT>(_ELIB_GCAST(lhs) - _ELIB_GCAST(rhs))); } 


# define ELIB_ENUMERATION_DEFINE_BINARY_SUBTRACT(EnumT)   \
  ELIB_ENUMERATION_DEFINE_BINARY_SUBTRACT_2(EnumT, EnumT)
  
  
# define ELIB_ENUMERATION_DEFINE_BINARY_MULTIPLY_2(LHS, RHS)        \
                                                                    \
  constexpr EnumT operator*(LHS lhs, RHS rhs) noexcept              \
{ return static_cast<EnumT>(_ELIB_GCAST(lhs) * _ELIB_GCAST(rhs)); } \
                                                                    \
  inline EnumT& operator*=(LHS& lhs, RHS rhs) noexcept              \
  { return (lhs = static_cast<EnumT>(_ELIB_GCAST(lhs) * _ELIB_GCAST(rhs))); } 


# define ELIB_ENUMERATION_DEFINE_BINARY_MULTIPLY(EnumT)   \
  ELIB_ENUMERATION_DEFINE_BINARY_MULTIPLY_2(EnumT, EnumT)
  
  
# define ELIB_ENUMERATION_DEFINE_BINARY_DIVIDE_2(LHS, RHS)            \
                                                                      \
  constexpr EnumT operator/(LHS lhs, RHS rhs) noexcept                \
  { return static_cast<EnumT>(_ELIB_GCAST(lhs) / _ELIB_GCAST(rhs)); } \
                                                                      \
  inline EnumT& operator/=(LHS& lhs, RHS rhs) noexcept                \
  { return (lhs = static_cast<EnumT>(_ELIB_GCAST(lhs) / _ELIB_GCAST(rhs))); } 


# define ELIB_ENUMERATION_DEFINE_BINARY_DIVIDE(EnumT)   \
ELIB_ENUMERATION_DEFINE_BINARY_DIVIDE_2(EnumT, EnumT)


# define ELIB_ENUMERATION_DEFINE_BINARY_MODULO_2(LHS, RHS)            \
                                                                      \
  constexpr EnumT operator%(LHS lhs, RHS rhs) noexcept                \
  { return static_cast<EnumT>(_ELIB_GCAST(lhs) % _ELIB_GCAST(rhs)); } \
                                                                      \
  inline EnumT& operator%=(LHS& lhs, RHS rhs) noexcept                \
  { return (lhs = static_cast<EnumT>(_ELIB_GCAST(lhs) % _ELIB_GCAST(rhs))); } 


# define ELIB_ENUMERATION_DEFINE_BINARY_MODULO(EnumT)   \
  ELIB_ENUMERATION_DEFINE_BINARY_MODULO_2(EnumT, EnumT)
  
  
# define ELIB_ENUMERATION_DEFINE_BINARY_ARITHMETIC_OPERATORS_2(LHS, RHS) \
  ELIB_ENUMERATION_DEFINE_BINARY_ADD_2(LHS, RHS)                         \
  ELIB_ENUMERATION_DEFINE_BINARY_SUBTRACT_2(LHS, RHS)                    \
  ELIB_ENUMERATION_DEFINE_BINARY_MULTIPLY_2(LHS, RHS)                    \
  ELIB_ENUMERATION_DEFINE_BINARY_DIVIDE_2(LHS, RHS)                      \
  ELIB_ENUMERATION_DEFINE_BINARY_MODULO_2(LHS, RHS)
  
  
# define ELIB_ENUMERATION_DEFINE_BINARY_ARITHMETIC_OPERATORS(EnumT) \
  ELIB_ENUMERATION_DEFINE_BINARY_ARITHMETIC_OPERATORS_2(EnumT, EnumT)
  
# define ELIB_ENUMERATION_DEFINE_ARITHMETIC_OPERATORS(EnumT) \
  ELIB_ENUMERATION_DEFINE_INCREMENT_OPERATORS(EnumT)         \
  ELIB_ENUMERATION_DEFINE_DECREMENT_OPERATORS(EnumT)         \
  ELIB_ENUMERATION_DEFINE_UNARY_ARITHMETIC_OPERATORS(EnumT)  \
  ELIB_ENUMERATION_DEFINE_BINARY_ARITHMETIC_OPERATORS(EnumT)
  

////////////////////////////////////////////////////////////////////////////////
//                             MISC OPERATORS                                            
////////////////////////////////////////////////////////////////////////////////
  
  
# define ELIB_ENUMERATION_DEFINE_BOOL_INDIRECTION_OPERATOR(EnumT) \
                                                                  \
  constexpr bool operator*(EnumT op) noexcept                     \
  { return static_cast<bool>(op); }                               
  
  
# define ELIB_ENUMERATION_DEFINE_UNDERLYING_DEREFERENCE_OPERATOR(EnumT) \
                                                                        \
  constexpr std::underlying_type_t<EnumT> operator&(EnumT op) noexcept  \
  { return _ELIB_GCAST(op); }
  
  


# undef _ELIB_GCAST


#endif /* ELIB_ELIB_ENUMERATION_OPERATOR_MACROS_HPP */