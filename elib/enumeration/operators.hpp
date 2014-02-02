#ifndef ELIB_ENUMERATION_OPERATORS_HPP
#define ELIB_ENUMERATION_OPERATORS_HPP

# include <elib/enumeration/enum_helper.hpp>
# include <elib/enumeration/enum_traits.hpp>

# include <elib/aux.hpp>
# include <elib/CXX14/type_traits.hpp>

# define ELIB_ENUM_UNARY_OP(Op, Ret, Type0)                               \
    operator Op (Type0 lhs) noexcept                                      \
    {                                                                     \
       return static_cast<Ret>( Op static_cast<opt_cast_t<Type0>>(lhs) ); \
    }
      
# define ELIB_ENUM_BINARY_OP(Op, Ret, Type0, Type1) \
    operator Op (Type0 lhs, Type1 rhs) noexcept     \
    {                                               \
        return static_cast<Ret>(                    \
                static_cast<opt_cast_t<Type0>>(lhs) \
                Op                                  \
                static_cast<opt_cast_t<Type1>>(rhs) \
            );                                      \
    }
    
# define ELIB_ENUM_BINARY_ASSIGN_OP(Op, Type0, Type1)  \
    operator Op (Type0 & lhs, Type1 rhs) noexcept      \
    {                                                  \
        return reinterpret_cast<Type0 &>(              \
            reinterpret_cast<opt_cast_t<Type0> &>(lhs) \
            Op                                         \
            static_cast<opt_cast_t<Type1>>(rhs)        \
          );                                           \
    }

/* To defeat ADL, elib::enumeration provides highly constrained operators
 * which frequently need to be imported into another namespace
 * these macros provide that */
# define ELIB_ENUM_USING_OPERATORS() \
  using namespace ::elib::enumeration::operators;
    
namespace elib { namespace enumeration
{
    namespace detail
    {
        ////////////////////////////////////////////////////////////////////////
        //
        template <class T, bool=aux::is_enum<T>::value>
        struct is_bitmask : std::false_type {};
        
        template <class T>
        struct is_bitmask<T, true> : bool_<enum_traits<T>::is_bitmask> {};
        
        ////////////////////////////////////////////////////////////////////////
        //
        template <class T, bool=aux::is_enum<T>::value>
        struct is_arithmetic : std::false_type {};
        
        template <class T>
        struct is_arithmetic<T, true>
            : std::integral_constant<bool, enum_traits<T>::is_arithmetic>
        {};
        
        ////////////////////////////////////////////////////////////////////////
        //
        template <class T, bool=aux::is_enum<T>::value>
        struct is_logical : std::false_type {};
        
        template <class T>
        struct is_logical<T, true> : bool_<enum_traits<T>::is_logical> {};
        
        ////////////////////////////////////////////////////////////////////////
        //
        template <class T, bool=aux::is_enum<T>::value>
        struct is_mixed_comparible : std::false_type {};
        
        template <class T>
        struct is_mixed_comparible<T, true>
            : bool_<enum_traits<T>::is_mixed_comparible>
        {};
        
        template <class LHS, class RHS>
        using is_mixed_comparible_impl =
            aux::and_<
                is_mixed_comparible<LHS>
              , aux::is_integral_enum<RHS>
            >;
                
        template <class LHS, class RHS>
        using is_mixed_comparible_expr = 
            aux::or_<
                is_mixed_comparible_impl<LHS, RHS>
              , is_mixed_comparible_impl<RHS, LHS>
            >;
        
        ////////////////////////////////////////////////////////////////////////
        //
        /* logical operators work differently then arithmetic and bitwise
        * operators. First they accept the following combinations of operands
        * (assuming the enum types are logical)
        * 
        * Enum1 op Enum2 -> bool
        * Enum op Integral -> bool
        * Integral op Enum -> bool
        * 
        */
        template <class LHS, class RHS>
        using is_logical_enum_enum = 
            aux::and_<
                is_logical<LHS>
              , is_logical<RHS>
            >;
            
        template <class LHS, class RHS>
        using is_logical_enum_integral =
            aux::and_<
                is_logical<LHS>
              , aux::is_integral<RHS>
            >;
            
        template <class LHS, class RHS>
        using is_logical_expr =
            aux::or_<
                is_logical_enum_enum<LHS, RHS>
              , is_logical_enum_integral<LHS, RHS>
              , is_logical_enum_integral<RHS, LHS>
            >;
    
    }                                                       // namespace detail
    
    namespace operators
    {
////////////////////////////////////////////////////////////////////////////////
// Bitwise
# define ELIB_ENUM_BITMASK_UNARY_OP(Op)                                  \
    template <class LHS, ELIB_ENABLE_IF(detail::is_bitmask<LHS>::value)> \
    constexpr LHS ELIB_ENUM_UNARY_OP(Op, LHS, LHS)
    
# define ELIB_ENUM_BITMASK_BINARY_OP(Op)                                            \
    template <class LHS, class RHS, ELIB_ENABLE_IF(detail::is_bitmask<LHS>::value)> \
    constexpr LHS ELIB_ENUM_BINARY_OP(Op, LHS, LHS, RHS)                            \
                                                                                    \
    template <class LHS, class RHS, ELIB_ENABLE_IF(detail::is_bitmask<LHS>::value)> \
    constexpr LHS& ELIB_ENUM_BINARY_ASSIGN_OP(Op ##=, LHS, RHS)
      
        ELIB_ENUM_BITMASK_UNARY_OP(~)
        
        ELIB_ENUM_BITMASK_BINARY_OP(&)
        ELIB_ENUM_BITMASK_BINARY_OP(|)
        ELIB_ENUM_BITMASK_BINARY_OP(^)
        ELIB_ENUM_BITMASK_BINARY_OP(<<)
        ELIB_ENUM_BITMASK_BINARY_OP(>>)
        
# undef ELIB_ENUM_BITMASK_UNARY_OP
# undef ELIB_ENUM_BITMASK_BINARY_OP
      
      
////////////////////////////////////////////////////////////////////////////////
// Arithmetic
# define ELIB_ENUM_ARITH_UNARY_OP(Op)                                       \
    template <class LHS, ELIB_ENABLE_IF(detail::is_arithmetic<LHS>::value)> \
    constexpr LHS ELIB_ENUM_UNARY_OP(Op, LHS, LHS)
# 

# define ELIB_ENUM_ARITH_BINARY_OP(Op)                                                 \
    template <class LHS, class RHS, ELIB_ENABLE_IF(detail::is_arithmetic<LHS>::value)> \
    constexpr LHS ELIB_ENUM_BINARY_OP(Op, LHS, LHS, RHS)                               \
                                                                                       \
    template <class LHS, class RHS, ELIB_ENABLE_IF(detail::is_arithmetic<LHS>::value)> \
    constexpr LHS& ELIB_ENUM_BINARY_ASSIGN_OP(Op ##= , LHS, RHS)
# 

# define ELIB_ENUM_ARITH_PREFIX_POSTFIX_OP(Op)                              \
    template <class LHS, ELIB_ENABLE_IF(detail::is_arithmetic<LHS>::value)> \
    constexpr LHS & operator Op (LHS & lhs) noexcept                        \
    {                                                                       \
        return reinterpret_cast<LHS & >(                                    \
               Op reinterpret_cast<aux::underlying_type_t<LHS> &>(lhs)      \
          );                                                                \
    }                                                                       \
                                                                            \
    template <class LHS, ELIB_ENABLE_IF(detail::is_arithmetic<LHS>::value)> \
    constexpr LHS operator Op (LHS & lhs, int) noexcept                     \
    {                                                                       \
        return static_cast<LHS>(                                            \
            reinterpret_cast<aux::underlying_type_t<LHS> &>(lhs) Op         \
          );                                                                \
    }
# 
        ELIB_ENUM_ARITH_UNARY_OP(+)
        ELIB_ENUM_ARITH_UNARY_OP(-)

        // Add, Sub, Mul, Div, Mod
        ELIB_ENUM_ARITH_BINARY_OP(+)
        ELIB_ENUM_ARITH_BINARY_OP(-)
        ELIB_ENUM_ARITH_BINARY_OP(*)
        ELIB_ENUM_ARITH_BINARY_OP(/)
        ELIB_ENUM_ARITH_BINARY_OP(%)
        
        ELIB_ENUM_ARITH_PREFIX_POSTFIX_OP(++)
        ELIB_ENUM_ARITH_PREFIX_POSTFIX_OP(--)
    
# undef ELIB_ENUM_ARITH_UNARY_OP
# undef ELIB_ENUM_ARITH_BINARY_OP
# undef ELIB_ENUM_ARITH_PREFIX_POSTFIX_OP

////////////////////////////////////////////////////////////////////////////////
// Logical
# define ELIB_ENUM_LOGICAL_BINARY_OP(Op)                                                      \
    template <class LHS, class RHS, ELIB_ENABLE_IF(detail::is_logical_expr<LHS, RHS>::value)> \
    constexpr bool ELIB_ENUM_BINARY_OP(Op, bool, LHS, RHS)
    
        template <class LHS, ELIB_ENABLE_IF(detail::is_logical<LHS>::value)>
        constexpr bool ELIB_ENUM_UNARY_OP(!, bool, LHS)
        
        ELIB_ENUM_LOGICAL_BINARY_OP(&&)
        ELIB_ENUM_LOGICAL_BINARY_OP(||)
        
# undef ELIB_ENUM_LOGICAL_BINARY_OP

////////////////////////////////////////////////////////////////////////////////
// Mixed Comparible
# define ELIB_ENUM_COMPARE_BINARY_OP(Op)                                  \
    template <                                                            \
        class LHS, class RHS                                              \
      , ELIB_ENABLE_IF(detail::is_mixed_comparible_expr<LHS, RHS>::value) \
    >                                                                     \
    constexpr bool ELIB_ENUM_BINARY_OP(Op, bool, LHS, RHS)
      
        ELIB_ENUM_COMPARE_BINARY_OP(==)
        ELIB_ENUM_COMPARE_BINARY_OP(!=)
        ELIB_ENUM_COMPARE_BINARY_OP(<)
        ELIB_ENUM_COMPARE_BINARY_OP(>)
        ELIB_ENUM_COMPARE_BINARY_OP(<=)
        ELIB_ENUM_COMPARE_BINARY_OP(>=)
        
# undef ELIB_ENUM_COMPARE_BINARY_OP

# undef ELIB_ENUM_UNARY_OP
# undef ELIB_ENUM_BINARY_OP
# undef ELIB_ENUM_BINARY_ASSIGN_OP

    }                                                    // namespace operators
}}                                               // namespace elib::enumeration
#endif /* ELIB_ENUMERATION_OPERATORS_HPP */
