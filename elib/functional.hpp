#ifndef ELIB_FUNCTIONAL_CXX_HPP
#define ELIB_FUNCTIONAL_CXX_HPP

# include <elib/aux.hpp>
# include <type_traits>
# include <utility>
# include <cstddef>
        
namespace elib 
{ 
    namespace functional 
    {
        ////////////////////////////////////////////////////////////////////////
        // unary_plus
        template <class T = void>
        struct unary_plus
        {
            using result_type = T;
            using argument_type = T;
            
            constexpr T operator()(const T& t) const
            ELIB_RETURN_NOEXCEPT(
                +t
            )
        };
        
        template <>
        struct unary_plus<void>
        {
            using is_transparent = aux::true_;
            
            template <class T>
            constexpr auto operator()(T && t) const
            ELIB_AUTO_RETURN_NOEXCEPT(
                + static_cast<T &&>(t)
            )
        };
        
        ////////////////////////////////////////////////////////////////////////
        // negate
        template <class T = void>
        struct negate
        {
            using result_type = T;
            using argument_type = T;
            
            constexpr T operator()(const T& t) const
            ELIB_RETURN_NOEXCEPT(
                -t
            )
        };
        
        template <>
        struct negate<void>
        {
            using is_transparent = aux::true_;
            
            template <class T>
            constexpr auto operator()(T && t) const
            ELIB_AUTO_RETURN_NOEXCEPT(
                - static_cast<T &&>(t)
            )
        };

        ////////////////////////////////////////////////////////////////////////
        // pre_increment
        template <class T = void>
        struct pre_increment
        {
            using result_type = T &;
            using argument_type = T &;
            
            constexpr T& operator()(T& t) const noexcept(noexcept(++t))
            {
                return (++t);
                
                static_assert(
                    aux::is_lvalue_reference<decltype(++t)>::value
                  , "Return type must be lvalue reference"
                );
            }
        };
        
        template <>
        struct pre_increment<void>
        {
            using is_transparent = aux::true_;
            
            template <class T>
            constexpr auto operator()(T && t) const
            ELIB_AUTO_RETURN_NOEXCEPT(
                ++ static_cast<T &&>(t)
            )
        };
        
        ////////////////////////////////////////////////////////////////////////
        // post_increment
        template <class T = void>
        struct post_increment
        {
            using result_type = T;
            using argument_type = T &;
            
            constexpr T operator()(T & t) const 
            ELIB_RETURN_NOEXCEPT(
                t++
            )
        };
        
        template <>
        struct post_increment<void>
        {
            using is_transparent = aux::true_;
            
            template <class T>
            constexpr auto operator()(T && t) const
            ELIB_AUTO_RETURN_NOEXCEPT(
                static_cast<T &&>(t) ++
            )
        };
        
        ////////////////////////////////////////////////////////////////////////
        // pre_decrement
        template <class T = void>
        struct pre_decrement
        {
            using result_type = T &;
            using argument_type = T &;
            
            constexpr T& operator()(T & t) const noexcept(noexcept(--t))
            {
                return (--t);
                
                static_assert(
                    aux::is_lvalue_reference<decltype(--t)>::value
                  , "Must be lvalue reference"
                );
            }
        };
        
        template <>
        struct pre_decrement<void>
        {
            using is_transparent = aux::true_;
            
            template <class T>
            constexpr auto operator()(T && t) const 
            ELIB_AUTO_RETURN_NOEXCEPT(
                -- static_cast<T &&>(t)
            )
        };
        
        ////////////////////////////////////////////////////////////////////////
        // post_decrement
        template <class T = void>
        struct post_decrement
        {
            using result_type = T;
            using argument_type = T &;
            
            constexpr T operator()(T& t) const
            ELIB_RETURN_NOEXCEPT(
                t--
            )
        };
        
        template <>
        struct post_decrement<void>
        {
            using is_transparent = aux::true_;
            
            template <class T>
            constexpr auto operator()(T && t) const
            ELIB_AUTO_RETURN_NOEXCEPT(
                static_cast<T &&>(t) --
            )
        };
        
        ////////////////////////////////////////////////////////////////////////
        // plus
        template <class T = void>
        struct plus
        {
            using result_type = T;
            using first_argument_type = T;
            using second_argument_type = T;
            
            constexpr T operator()(const T& lhs, const T& rhs) const
            ELIB_RETURN_NOEXCEPT(
                lhs + rhs
            )
        };
        
        template <>
        struct plus<void>
        {
            using is_transparent = aux::true_;
            
            template <class T, class U>
            constexpr auto operator()(T && lhs, U && rhs) const
            ELIB_AUTO_RETURN_NOEXCEPT(
                static_cast<T &&>(lhs) + static_cast<U &&>(rhs)
            )
        };
        
        ////////////////////////////////////////////////////////////////////////
        // plus_assign
        template <class T = void>
        struct plus_assign
        {
            using result_type = T &;
            using first_argument_type = T &;
            using second_argument_type = T;
            
            constexpr T& operator()(T & lhs, const T & rhs) const noexcept(noexcept(lhs += rhs))
            {
                return (lhs += rhs);
                
                static_assert(
                    aux::is_lvalue_reference<decltype(lhs += rhs)>::value
                  , "Must be lvalue reference"
                );
            }
        };
        
        template <>
        struct plus_assign<void>
        {
            using is_transparent = aux::true_;
            
            template <class T, class U>
            constexpr auto operator()(T && lhs, U && rhs) const
            ELIB_AUTO_RETURN_NOEXCEPT(
                static_cast<T &&>(lhs) += static_cast<U &&>(rhs)
            )
        };
        
        ////////////////////////////////////////////////////////////////////////
        // minus
        template <class T = void>
        struct minus
        {
            using result_type = T;
            using first_argument_type = T;
            using second_argument_type = T;
            
            constexpr T operator()(const T & lhs, const T & rhs) const
            ELIB_RETURN_NOEXCEPT(
                lhs - rhs
            )
        };
        
        template <>
        struct minus<void>
        {
            using is_transparent = aux::true_;
            
            template <class T, class U>
            constexpr auto operator()(T && lhs, U && rhs) const
            ELIB_AUTO_RETURN_NOEXCEPT(
                static_cast<T &&>(lhs) - static_cast<U &&>(rhs)
            )
        };
        
        ////////////////////////////////////////////////////////////////////////
        // minus_assign
        template <class T = void>
        struct minus_assign
        {
            using result_type = T &;
            using first_argument_type = T &;
            using second_argument_type = T;
            
            constexpr T& operator()(T & lhs, const T & rhs) const noexcept(noexcept(lhs -= rhs))
            {
                return (lhs -= rhs);
                
                static_assert(
                    aux::is_lvalue_reference<decltype(lhs -= rhs)>::value
                  , "Must be lvalue reference"
                );
            }
        };
        
        template <>
        struct minus_assign<void>
        {
            using is_transparent = aux::true_;
            
            template <class T, class U>
            constexpr auto operator()(T && lhs, U && rhs) const
            ELIB_AUTO_RETURN_NOEXCEPT(
                static_cast<T &&>(lhs) -= static_cast<U &&>(rhs)
            )
        };
        
        ////////////////////////////////////////////////////////////////////////
        // multiplies
        template <class T = void>
        struct multiplies
        {
            using result_type = T;
            using first_argument_type = T;
            using second_argument_type = T;
            
            constexpr T operator()(const T& lhs, const T& rhs) const
            ELIB_RETURN_NOEXCEPT(
                lhs * rhs
            )
        };
        
        template <>
        struct multiplies<void>
        {
            using is_transparent = aux::true_;
            
            template <class T, class U>
            constexpr auto operator()(T && lhs, U && rhs) const
            ELIB_AUTO_RETURN_NOEXCEPT(
                static_cast<T &&>(lhs) * static_cast<U &&>(rhs)
            )
        };
        
        ////////////////////////////////////////////////////////////////////////
        // multiplies_assign
        template <class T = void>
        struct multiplies_assign
        {
            using result_type = T &;
            using first_argument_type = T &;
            using second_argument_type = T;
            
            constexpr T& operator()(T & lhs, const T& rhs) const noexcept(noexcept(lhs *= rhs))
            {
                return (lhs *= rhs);
                
                static_assert(
                    aux::is_lvalue_reference<decltype(lhs *= rhs)>::value
                  , "Must be lvalue reference"
                );
            }
        };
        
        template <>
        struct multiplies_assign<void>
        {
            using is_transparent = aux::true_;
            
            template <class T, class U>
            constexpr auto operator()(T && lhs, U && rhs) const
            ELIB_AUTO_RETURN_NOEXCEPT(
                static_cast<T &&>(lhs) *= static_cast<U &&>(rhs)
            )
        };
        
        ////////////////////////////////////////////////////////////////////////
        // divides
        template <class T = void>
        struct divides
        {
            using result_type = T;
            using first_argument_type = T;
            using second_argument_type = T;
            
            constexpr T operator()(const T& lhs, const T& rhs) const
            ELIB_RETURN_NOEXCEPT(
                lhs / rhs
            )
        };
        
        template <>
        struct divides<void>
        {
            using is_transparent = aux::true_;
            
            template <class T, class U>
            constexpr auto operator()(T && lhs, U && rhs) const
            ELIB_AUTO_RETURN_NOEXCEPT(
                static_cast<T &&>(lhs) / static_cast<U &&>(rhs)
            )
        };
        
        ////////////////////////////////////////////////////////////////////////
        // divides_assign
        template <class T = void>
        struct divides_assign
        {
            using result_type = T &;
            using first_argument_type = T &;
            using second_argument_type = T;
            
            constexpr T& operator()(T& lhs, const T& rhs) const noexcept(noexcept(lhs /= rhs))
            {
                return (lhs /= rhs);
                
                static_assert(
                    aux::is_lvalue_reference<decltype(lhs /= rhs)>::value
                  , "Must be lvalue reference"
                );
            }
        };
        
        template <>
        struct divides_assign<void>
        {
            using is_transparent = aux::true_;
            
            template <class T, class U>
            constexpr auto operator()(T && lhs, U && rhs) const
            ELIB_AUTO_RETURN_NOEXCEPT(
                static_cast<T &&>(lhs) /= static_cast<U &&>(rhs)
            )
        };
        
        ////////////////////////////////////////////////////////////////////////
        // modulus
        template <class T = void>
        struct modulus
        {
            using result_type = T;
            using first_argument_type = T;
            using second_argument_type = T;
            
            constexpr T operator()(const T& lhs, const T& rhs) const
            ELIB_RETURN_NOEXCEPT(
                lhs % rhs
            )
        };
        
        template <>
        struct modulus<void>
        {
            using is_transparent = aux::true_;
            
            template <class T, class U>
            constexpr auto operator()(T && lhs, U && rhs) const
            ELIB_AUTO_RETURN_NOEXCEPT(
                static_cast<T &&>(lhs) % static_cast<U &&>(rhs)
            )
        };
        
        ////////////////////////////////////////////////////////////////////////
        // modulus_assign
        template <class T = void>
        struct modulus_assign
        {
            using result_type = T &;
            using first_argument_type = T &;
            using second_argument_type = T;
            
            constexpr T& operator()(T& lhs, const T& rhs) const noexcept(noexcept(lhs %= rhs))
            {
                return (lhs %= rhs);
                
                static_assert(
                    aux::is_lvalue_reference<decltype(lhs %= rhs)>::value
                  , "Must be lvalue reference"
                );
            }
        };
        
        template <>
        struct modulus_assign<void>
        {
            using is_transparent = aux::true_;
            
            template <class T, class U>
            constexpr auto operator()(T && lhs, U && rhs) const
            ELIB_AUTO_RETURN_NOEXCEPT(
                static_cast<T &&>(lhs) %= static_cast<U &&>(rhs)
            )
        };
        
        ////////////////////////////////////////////////////////////////////////
        // equal_to
        template <class T = void>
        struct equal_to
        {
            using result_type = bool;
            using first_argument_type = T;
            using second_argument_type = T;
            
            constexpr bool operator()(const T& lhs, const T& rhs) const noexcept(noexcept(lhs == rhs))
            {
                return (lhs == rhs);
                
                static_assert(
                    aux::is_same<decltype(lhs == rhs), bool>::value
                  , "Must be boolean expression"
                );
            }
        };
        
        template <>
        struct equal_to<void>
        {
            using is_transparent = aux::true_;
            
            template <class T, class U>
            constexpr auto operator()(T && lhs, U && rhs) const
            ELIB_AUTO_RETURN_NOEXCEPT(
                static_cast<T &&>(lhs) == static_cast<U &&>(rhs)
            )
        };
        
        ////////////////////////////////////////////////////////////////////////
        // not_equal_to
        template <class T = void>
        struct not_equal_to
        {
            using result_type = bool;
            using first_argument_type = T;
            using second_argument_type = T;
            
            constexpr bool operator()(const T& lhs, const T& rhs) const noexcept(noexcept(lhs != rhs))
            {
                return (lhs != rhs);
                
                static_assert(
                    aux::is_same<decltype(lhs != rhs), bool>::value
                  , "Must be boolean expression"
                );
            }
        };
        
        template <>
        struct not_equal_to<void>
        {
            using is_transparent = aux::true_;
            
            template <class T, class U>
            constexpr auto operator()(T && lhs, U && rhs) const
            ELIB_AUTO_RETURN_NOEXCEPT(
                static_cast<T &&>(lhs) != static_cast<U &&>(rhs)
            )
        };
        
        ////////////////////////////////////////////////////////////////////////
        // greater
        template <class T = void>
        struct greater
        {
            using result_type = bool;
            using first_argument_type = T;
            using second_argument_type = T;
            
            constexpr bool operator()(const T& lhs, const T& rhs) const noexcept(noexcept(lhs > rhs))
            {
                return (lhs > rhs);
                
                static_assert(
                    aux::is_same<decltype(lhs>rhs), bool>::value
                  , "Must be boolean expression"
                );
            }
        };
        
        template <>
        struct greater<void>
        {
            using is_transparent = aux::true_;
            
            template <class T, class U>
            constexpr auto operator()(T && lhs, U && rhs) const
            ELIB_AUTO_RETURN_NOEXCEPT(
                static_cast<T &&>(lhs) > static_cast<U &&>(rhs)
            )
        };
        
        ////////////////////////////////////////////////////////////////////////
        // less
        template <class T = void>
        struct less
        {
            using result_type = bool;
            using first_argument_type = T;
            using second_argument_type = T;
            
            constexpr bool operator()(const T& lhs, const T& rhs) const
            ELIB_RETURN_NOEXCEPT(
                lhs < rhs
            )
        };
        
        template <>
        struct less<void>
        {
            using is_transparent = aux::true_;
            
            template <class T, class U>
            constexpr auto operator()(T && lhs, U && rhs) const
            ELIB_AUTO_RETURN_NOEXCEPT(
                static_cast<T &&>(lhs) < static_cast<U &&>(rhs)
            )
        };
        
        ////////////////////////////////////////////////////////////////////////
        // greater_equal
        template <class T = void>
        struct greater_equal
        {
            using result_type = bool;
            using first_argument_type = T;
            using second_argument_type = T;
            
            constexpr bool operator()(const T& lhs, const T& rhs) const
            ELIB_RETURN_NOEXCEPT(
                lhs >= rhs
            )
        };
        
        template <>
        struct greater_equal<void>
        {
            using is_transparent = aux::true_;
            
            template <class T, class U>
            constexpr auto operator()(T && lhs, U && rhs) const
            ELIB_AUTO_RETURN_NOEXCEPT(
                static_cast<T &&>(lhs) >= static_cast<U &&>(rhs)
            )
        };
        
        ////////////////////////////////////////////////////////////////////////
        // less_equal
        template <class T = void>
        struct less_equal
        {
            using result_type = bool;
            using first_argument_type = T;
            using second_argument_type = T;
            
            constexpr bool operator()(const T& lhs, const T& rhs) const
            ELIB_RETURN_NOEXCEPT(
                lhs <= rhs
            )
        };
        
        template <>
        struct less_equal<void>
        {
            using is_transparent = aux::true_;
            
            template <class T, class U>
            constexpr auto operator()(T && lhs, U && rhs) const
            ELIB_AUTO_RETURN_NOEXCEPT(
                static_cast<T &&>(lhs) <= static_cast<U &&>(rhs)
            )
        };
        
        
        ////////////////////////////////////////////////////////////////////////
        // logical_not
        template <class T = void>
        struct logical_not
        {
            using result_type = bool;
            using argument_type = T;
            
            constexpr bool operator()(const T& arg) const
            ELIB_RETURN_NOEXCEPT(
                ! arg
            )
        };
        
        template <>
        struct logical_not<void>
        {
            using is_transparent = aux::true_;
            
            template <class T>
            constexpr auto operator()(T && t) const
            ELIB_AUTO_RETURN_NOEXCEPT(
                ! static_cast<T &&>(t)
            )
        };
        
        ////////////////////////////////////////////////////////////////////////
        // logical_and
        template <class T = void>
        struct logical_and
        {
            using result_type = bool;
            using first_argument_type = T;
            using second_argument_type = T;
            
            constexpr bool operator()(const T& lhs, const T& rhs) const
            ELIB_RETURN_NOEXCEPT(
                lhs && rhs
            )
        };
        
        template <>
        struct logical_and<void>
        {
            using is_transparent = aux::true_;
            
            template <class T, class U>
            constexpr auto operator()(T && lhs, U && rhs) const
            ELIB_AUTO_RETURN_NOEXCEPT(
                static_cast<T &&>(lhs) && static_cast<U &&>(rhs)
            )
        };
        
        ////////////////////////////////////////////////////////////////////////
        // logical_or
        template <class T = void>
        struct logical_or
        {
            using result_type = bool;
            using first_argument_type = T;
            using second_argument_type = T;
            
            constexpr bool operator()(const T& lhs, const T& rhs) const
            ELIB_RETURN_NOEXCEPT(
                lhs || rhs
            )
        };
        
        template <>
        struct logical_or<void>
        {
            using is_transparent = aux::true_;
            
            template <class T, class U>
            constexpr auto operator()(T && lhs, U && rhs) const
            ELIB_AUTO_RETURN_NOEXCEPT(
                static_cast<T &&>(lhs) || static_cast<U &&>(rhs)
            )
        };
        
        ////////////////////////////////////////////////////////////////////////
        // bit_and
        template <class T = void>
        struct bit_and
        {
            using result_type = T;
            using first_argument_type = T;
            using second_argument_type = T;
            
            constexpr T operator()(const T& lhs, const T& rhs) const
            ELIB_RETURN_NOEXCEPT(
                lhs & rhs
            )
        };
        
        template <>
        struct bit_and<void>
        {
            using is_transparent = aux::true_;
            
            template <class T, class U>
            constexpr auto operator()(T && lhs, U && rhs) const
            ELIB_AUTO_RETURN_NOEXCEPT(
                static_cast<T &&>(lhs) & static_cast<U &&>(rhs)
            )
        };
        
        ////////////////////////////////////////////////////////////////////////
        // bit_and_assign
        template <class T = void>
        struct bit_and_assign
        {
            using result_type = T &;
            using first_argument_type = T &;
            using second_argument_type = T;
            
            constexpr T& operator()(T& lhs, const T& rhs) const
            ELIB_RETURN_NOEXCEPT(
                lhs &= rhs
            )
        };
        
        template <>
        struct bit_and_assign<void>
        {
            using is_transparent = aux::true_;
            
            template <class T, class U>
            constexpr auto operator()(T && lhs, U && rhs) const
            ELIB_AUTO_RETURN_NOEXCEPT(
                static_cast<T &&>(lhs) &= static_cast<U &&>(rhs)
            )
        };
        
        ////////////////////////////////////////////////////////////////////////
        // bit_or
        template <class T = void>
        struct bit_or
        {
            using result_type = T;
            using first_argument_type = T;
            using second_argument_type = T;
            
            constexpr T operator()(const T& lhs, const T& rhs) const
            ELIB_RETURN_NOEXCEPT(
                lhs | rhs
            )
        };
        
        template <>
        struct bit_or<void>
        {
            using is_transparent = aux::true_;
            
            template <class T, class U>
            constexpr auto operator()(T && lhs, U && rhs) const
            ELIB_AUTO_RETURN_NOEXCEPT(
                static_cast<T &&>(lhs) | static_cast<U &&>(rhs)
            )
        };
        
        ////////////////////////////////////////////////////////////////////////
        // bit_or_assign
        template <class T = void>
        struct bit_or_assign
        {
            using result_type = T &;
            using first_argument_type = T &;
            using second_argument_type = T;
            
            constexpr T& operator()(T& lhs, const T& rhs) const
            ELIB_RETURN_NOEXCEPT(
                lhs |= rhs
            )
        };
        
        template <>
        struct bit_or_assign<void>
        {
            using is_transparent = aux::true_;
            
            template <class T, class U>
            constexpr auto operator()(T && lhs, U && rhs) const
            ELIB_AUTO_RETURN_NOEXCEPT(
                static_cast<T &&>(lhs) |= static_cast<U &&>(rhs)
            )
        };
        
        ////////////////////////////////////////////////////////////////////////
        // bit_xor
        template <class T = void>
        struct bit_xor
        {
            using result_type = T;
            using first_argument_type = T;
            using second_argument_type = T;
            
            constexpr T operator()(const T& lhs, const T& rhs) const
            ELIB_RETURN_NOEXCEPT(
                lhs ^ rhs
            )
        };
        
        template <>
        struct bit_xor<void>
        {
            using is_transparent = aux::true_;
            
            template <class T, class U>
            constexpr auto operator()(T && lhs, U && rhs) const
            ELIB_AUTO_RETURN_NOEXCEPT(
                static_cast<T &&>(lhs) ^ static_cast<U &&>(rhs)
            )
        };
        
        ////////////////////////////////////////////////////////////////////////
        // bit_xor_assign
        template <class T = void>
        struct bit_xor_assign
        {
            using result_type = T &;
            using first_argument_type = T &;
            using second_argument_type = T;
            
            constexpr T& operator()(T& lhs, const T& rhs) const
            ELIB_RETURN_NOEXCEPT(
                lhs ^= rhs
            )
        };
        
        template <>
        struct bit_xor_assign<void>
        {
            using is_transparent = aux::true_;
            
            template <class T, class U>
            constexpr auto operator()(T && lhs, U && rhs) const
            ELIB_AUTO_RETURN_NOEXCEPT(
                static_cast<T &&>(lhs) ^= static_cast<U &&>(rhs)
            )
        };
        
        ////////////////////////////////////////////////////////////////////////
        // complement
        template <class T = void>
        struct complement
        {
            using result_type = T;
            using argument_type = T;
            
            constexpr T operator()(const T& t) const
            ELIB_RETURN_NOEXCEPT(
                ~ t
            )
        };
        
        template <>
        struct complement<void>
        {
            using is_transparent = aux::true_;
            
            template <class T>
            constexpr auto operator()(const T& t) const
            ELIB_AUTO_RETURN_NOEXCEPT(
                ~ static_cast<T &&>(t)
            )
        };
        
        ////////////////////////////////////////////////////////////////////////
        // shift_left
        template <class T = void>
        struct shift_left
        {
            using result_type = T;
            using first_argument_type = T;
            using second_argument_type = T;
            
            constexpr T operator()(const T& lhs, const T& rhs) const
            ELIB_RETURN_NOEXCEPT(
                lhs << rhs
            )
        };
        
        template <>
        struct shift_left<void>
        {
            using is_transparent = aux::true_;
            
            template <class T, class U>
            constexpr auto operator()(T && lhs, U && rhs) const
            ELIB_AUTO_RETURN_NOEXCEPT(
                static_cast<T &&>(lhs) << static_cast<U &&>(rhs)
            )
        };
        
        ////////////////////////////////////////////////////////////////////////
        // shift_left_assign
        template <class T = void>
        struct shift_left_assign
        {
            using result_type = T &;
            using first_argument_type = T &;
            using second_argument_type = T;
            
            constexpr T& operator()(T& lhs, const T& rhs) const
            ELIB_RETURN_NOEXCEPT(
                lhs <<= rhs
            )
        };
        
        template <>
        struct shift_left_assign<void>
        {
            using is_transparent = aux::true_;
            
            template <class T, class U>
            constexpr auto operator()(T && lhs, U && rhs) const
            ELIB_AUTO_RETURN_NOEXCEPT(
                static_cast<T &&>(lhs) <<= static_cast<U &&>(rhs)
            )
        };
        
        ////////////////////////////////////////////////////////////////////////
        // shift_right
        template <class T = void>
        struct shift_right
        {
            using result_type = T;
            using first_argument_type = T;
            using second_argument_type = T;
            
            constexpr T operator()(const T& lhs, const T& rhs) const
            ELIB_RETURN_NOEXCEPT(
                lhs >> rhs
            )
        };
        
        template <>
        struct shift_right<void>
        {
            using is_transparent = aux::true_;
            
            template <class T, class U>
            constexpr auto operator()(T && lhs, U && rhs) const
            ELIB_AUTO_RETURN_NOEXCEPT(
                static_cast<T &&>(lhs) >> static_cast<U &&>(rhs)
            )
        };
        
        ////////////////////////////////////////////////////////////////////////
        // shift_right_assign
        template <class T = void>
        struct shift_right_assign
        {
            using result_type = T &;
            using first_argument_type = T &;
            using second_argument_type = T;
            
            constexpr T& operator()(T& lhs, const T& rhs) const
            ELIB_RETURN_NOEXCEPT(
                lhs >>= rhs
            )
        };
        
        template <>
        struct shift_right_assign<void>
        {
            using is_transparent = aux::true_;
            
            template <class T, class U>
            constexpr auto operator()(T && lhs, U && rhs) const
            ELIB_AUTO_RETURN_NOEXCEPT(
                static_cast<T &&>(lhs) >>= static_cast<U &&>(rhs)
            )
        };
        
        ////////////////////////////////////////////////////////////////////////
        // address_of
        template <class T = void>
        struct address_of
        {
            using result_type = T*;
            using argument_type = T;
            
            constexpr const T* operator()(const T& arg) const noexcept(noexcept(&arg))
            {
                return (&arg);
                
                static_assert(
                    aux::is_same<decltype(&arg), T*>::value
                  , "Must be lvalue reference expression"
                );
            }
            
            constexpr T* operator()(T& arg) const noexcept(noexcept(&arg))
            {
                return (&arg);
                
                static_assert(
                    aux::is_same<decltype(&arg), T*>::value
                  , "Must be lvalue reference expression"
                );
            }
        };
        
        template <>
        struct address_of<void>
        {
            using is_transparent = aux::true_;
            
            template <class T>
            constexpr auto operator()(T && t) const
            ELIB_AUTO_RETURN_NOEXCEPT(
                & static_cast<T &&>(t)
            )
        };
        
        ////////////////////////////////////////////////////////////////////////
        // assign
        template <class T = void>
        struct assign
        {
            using result_type = T &;
            using first_argument_type = T &;
            using second_argument_type = T;
            
            constexpr T& operator()(T& lhs, const T& rhs) const noexcept(noexcept(lhs = rhs))
             {
                return (lhs = rhs);
                
                static_assert(
                    aux::is_same<decltype(lhs = rhs), T&>::value
                  , "Must be lvalue reference expression"
                );
            }
            
        };
        
        template <>
        struct assign<void>
        {
            using is_transparent = aux::true_;
            
            template <class T, class U>
            constexpr auto operator()(T && lhs, U && rhs) const
            ELIB_AUTO_RETURN_NOEXCEPT(
                static_cast<T &&>(lhs) = static_cast<U &&>(rhs)
            )
        };
        
        ////////////////////////////////////////////////////////////////////////
        // comma
        template <class T = void>
        struct comma
        {
            using result_type = T;
            using first_argument_type = T;
            using second_argument_type = T;
            
            constexpr T operator()(const T& lhs, const T& rhs) const
            ELIB_RETURN_NOEXCEPT(
                lhs , rhs
            )
        };
        
        template <>
        struct comma<void>
        {
            using is_transparent = aux::true_;
            
            template <class T, class U>
            constexpr auto operator()(T && lhs, U && rhs) const
            ELIB_AUTO_RETURN_NOEXCEPT(
                static_cast<T &&>(lhs) , static_cast<U &&>(rhs)
            )
        };
        
        ////////////////////////////////////////////////////////////////////////
        // dereference
        template <class T = void>
        struct dereference
        {
            using result_type = T&;
            using argument_type = T*;
            
            constexpr const T& operator()(const T* t) const noexcept(noexcept(*t))
            {
                return (*t);
                
                static_assert(
                    aux::is_same<decltype(*t), T&>::value
                  , "Must be lvalue reference expression"
                );
            }
            
            constexpr T& operator()(T* t) const noexcept(noexcept(*t))
            {
                return (*t);
                
                static_assert(
                    aux::is_same<decltype(*t), T&>::value
                  , "Must be lvalue reference expression"
                );
            }
        };
        
        template <>
        struct dereference<void>
        {
            using is_transparent = aux::true_;
            
            template <class T>
            constexpr auto operator()(T && t) const
            ELIB_AUTO_RETURN_NOEXCEPT(
                * static_cast<T &&>(t)
            )
        };
        
        ////////////////////////////////////////////////////////////////////////
        // function
        template <class T = void>
        struct function;
        
        //TODO
        template <class Ret, class ...Args>
        struct function<Ret(Args...)>;
        
        //TODO
        template <class Ret, class ...Args>
        struct function<Ret(Args..., ...)>;
        
        //TODO
        template <class Ret, class ...Args>
        struct function<Ret(*)(Args...)>;
        
        //TODO
        template <class Ret, class ...Args>
        struct function<Ret(*)(Args..., ...)>;
        
        //TODO
        
        template <>
        struct function<void>
        {
            using is_transparent = aux::true_;
            
            template <class Fn, class ...Args>
            constexpr auto operator()(Fn && fn, Args &&... args) const
            ELIB_AUTO_RETURN_NOEXCEPT(
                static_cast<Fn &&>(fn)(static_cast<Args &&>(args)...)
            )
            
            //TODO
            template <class Ret, class Class, class Obj>
            constexpr auto operator()(Ret Class::*, Obj &&) const
            ELIB_AUTO_RETURN_NOEXCEPT(
                aux::any{}
            )
            
            //TODO
            template <
                class Ret, class Class, class ...Args
              , class Obj, class ...T
            >
            constexpr auto operator()(Ret (Class::*)(Args...), Obj&&, T&&...) const
            ELIB_AUTO_RETURN_NOEXCEPT(
                aux::any{}
            )
        };
        
        ////////////////////////////////////////////////////////////////////////
        // if_else
        template <class T = void>
        struct if_else
        {
            using result_type = T;
            using first_argument_type = bool;
            using second_argument_type = T;
            using third_argument_type = T;
            
            constexpr T operator()(bool Pred, const T& lhs, const T& rhs) const
            ELIB_RETURN_NOEXCEPT(
                Pred ? lhs : rhs
            )
        };
        
        template <>
        struct if_else<void>
        {
            using is_transparent = aux::true_;
            
            template <class T, class U, class V>
            constexpr auto operator()(T && pred, U && lhs, V && rhs) const
            ELIB_AUTO_RETURN_NOEXCEPT(
                static_cast<T &&>(pred) ? 
                    static_cast<U &&>(lhs) : static_cast<V &&>(rhs)
            )
        };
        
        ////////////////////////////////////////////////////////////////////////
        // mem_pointer
        //TODO
        template <class T = void>
        struct mem_pointer;
        
        ////////////////////////////////////////////////////////////////////////
        // subscript
        template <class T = void>
        struct subscript
        {
            using result_type = decltype( 
                std::declval<T>()[ std::declval<std::size_t>() ]
            );
            
            using first_argument_type = T;
            using second_argument_type = std::size_t;
            
            constexpr const result_type operator()(const T& t, std::size_t i) const
            ELIB_RETURN_NOEXCEPT(
                t[i]
            )
            
            constexpr result_type operator()(T& t, std::size_t i) const
            ELIB_RETURN_NOEXCEPT(
                t[i]
            )
            
            static_assert(
                aux::is_lvalue_reference<result_type>::value
              , "Return type of subscript must be lvalue reference"
            );
        };
        
        template <>
        struct subscript<void>
        {
            using is_transparent = aux::true_;
            
            template <class T, class U>
            constexpr auto operator()(T && lhs, U && rhs) const
            ELIB_AUTO_RETURN_NOEXCEPT(
                static_cast<T &&>(lhs)[ static_cast<U &&>(rhs) ]
            )
        };
        
        
        ////////////////////////////////////////////////////////////////////////
        // static_cast_
        template <class T>
        struct static_cast_
        {
            using result_type = T;
            
            template <class U>
            constexpr auto operator()(U && u) const
            ELIB_AUTO_RETURN_NOEXCEPT(
                static_cast<T>( static_cast<U &&>(u) )
            )
        };
        
        ////////////////////////////////////////////////////////////////////////
        // const_cast_
        template <class T>
        struct const_cast_
        {
            using result_type = T;
            
            template <class U>
            constexpr auto operator()(U && u) const
            ELIB_AUTO_RETURN_NOEXCEPT(
                const_cast<T>( static_cast<U &&>(u) )
            )
        };
        
        ////////////////////////////////////////////////////////////////////////
        // dynamic_cast_
        template <class T>
        struct dynamic_cast_
        {
            using result_type = T;
            
            template <class U>
            constexpr auto operator()(U && u) const
            ELIB_AUTO_RETURN_NOEXCEPT(
                dynamic_cast<T>( static_cast<U &&>(u) )
            )
        };
        
        ////////////////////////////////////////////////////////////////////////
        // reinterpret_cast_
        template <class T>
        struct reinterpret_cast_
        {
            using result_type = T;
            
            template <class U>
            constexpr auto operator()(U && u) const
            ELIB_AUTO_RETURN_NOEXCEPT(
                reinterpret_cast<T>( static_cast<U &&>(u) )
            )
        };
        
        ////////////////////////////////////////////////////////////////////////
        // construct
        template <class T>
        struct construct
        {
            using result_type = T;
            
            template <class ...Args>
            constexpr T operator()(Args &&... args) const
            ELIB_RETURN_NOEXCEPT(
                T{ static_cast<Args &&>(args)... }
            )
        };
        
        ////////////////////////////////////////////////////////////////////////
        // throw_
        template <class T = void>
        struct throw_
        {
            using result_type = T;
            
            [[noreturn]] void operator()(const T& t) const noexcept(false)
            {
                throw t;
            }
            
            [[noreturn]] void operator()(T& t) const noexcept(false)
            {
                throw t;
            }
            
            template <class U>
            [[noreturn]] void operator()(U && u) const noexcept(false)
            {
                throw static_cast<T>(u);
            }
        };
        
        template <>
        struct throw_<void>
        {
            using is_transparent = aux::true_;
            
            template <class T>
            [[noreturn]] void operator()(T && t) const noexcept(false)
            {
                throw static_cast<T &&>(t);
            }
        };
    }                                                      // namespace functional
}                                                          // namespace elib
#endif /* ELIB_FUNCTIONAL_CXX_HPP */