#ifndef ELIB_ENUMERATION_OPERATORS_H
#define ELIB_ENUMERATION_OPERATORS_H


#include <elib/enumeration/enum_traits.h>
#include <elib/enumeration/enum_cast.h>
#include <elib/template_conditional.h>

#include <type_traits>


namespace elib {
namespace enumeration {

    
template <typename EnumT>
struct allow_arithmetic_operators : public std::false_type
{ };

template <typename EnumT>
struct allow_mixed_arithmetic_operators : public std::false_type
{ };

template <typename EnumT>
struct allow_logical_operators : public std::false_type
{ };

template <typename EnumT>
struct allow_mixed_logical_operators : public std::false_type
{ };
    
template <typename EnumT>
struct allow_bitwise_operators : public std::false_type
{ };

template <typename EnumT>
struct allow_mixed_bitwise_operators : public std::false_type
{ };



namespace detail {

    
template <typename EnumT, template <typename T> class allow_fn>
using is_allowed = AND<std::is_enum<EnumT>::value, allow_fn<EnumT>::value>;


template <typename EnumT>
using is_arithmetic_allowed = 
    OR<is_allowed<EnumT, allow_arithmetic_operators>::value,
       is_allowed<EnumT, allow_mixed_arithmetic_operators>::value>;

template <typename EnumT>
using is_mixed_arithmetic_allowed = 
    is_allowed<EnumT, allow_mixed_arithmetic_operators>;

    
template <typename EnumT>
using is_logical_allowed = 
    OR<is_allowed<EnumT, allow_logical_operators>::value,
       is_allowed<EnumT, allow_mixed_logical_operators>::value>;

template <typename EnumT>
using is_mixed_logical_allowed = 
    is_allowed<EnumT, allow_mixed_logical_operators>;

    
template <typename EnumT>
using is_bitwise_allowed = 
    OR<is_allowed<EnumT, allow_bitwise_operators>::value,
       is_allowed<EnumT, allow_mixed_bitwise_operators>::value>;

template <typename EnumT>
using is_mixed_bitwise_allowed = 
    is_allowed<EnumT, allow_mixed_bitwise_operators>;


template <typename EnumT, template <typename T> class allow_fn, typename Ret>
using enable_if_allowed = std::enable_if<allow_fn<EnumT>::value, Ret>;

template <typename EnumT, template <typename T> class allow_fn, typename Ret>
using enable_if_allowed_t = 
    typename enable_if_allowed<EnumT, allow_fn, Ret>::type;
    
    
template <typename EnumT, typename Ret=EnumT>
using enable_if_arithmetic_allowed = 
    enable_if_allowed<EnumT, is_arithmetic_allowed, Ret>;
    
template <typename EnumT, typename Ret=EnumT>
using enable_if_mixed_arithmetic_allowed = 
    enable_if_allowed<EnumT, is_mixed_arithmetic_allowed, Ret>;
    
    
template <typename EnumT, typename Ret=EnumT>
using enable_if_logical_allowed =
    enable_if_allowed<EnumT, is_logical_allowed, Ret>;
    
template <typename EnumT, typename Ret=EnumT>
using enable_if_mixed_logical_allowed =
    enable_if_allowed<EnumT, is_mixed_logical_allowed, Ret>;
    
    
template <typename EnumT, typename Ret=EnumT>
using enable_if_bitwise_allowed =
    enable_if_allowed<EnumT, is_bitwise_allowed, Ret>;
    
template <typename EnumT, typename Ret=EnumT>
using enable_if_mixed_bitwise_allowed =
    enable_if_allowed<EnumT, is_mixed_bitwise_allowed, Ret>;
    
    
template <typename EnumT, typename Ret=EnumT>
using enable_if_arithmetic_allowed_t = 
    enable_if_allowed_t<EnumT, is_arithmetic_allowed, Ret>;
    
template <typename EnumT, typename Ret=EnumT>
using enable_if_mixed_arithmetic_allowed_t = 
    enable_if_allowed_t<EnumT, is_mixed_arithmetic_allowed, Ret>;
    
template <typename EnumT, typename Ret=EnumT>
using enable_if_logical_allowed_t =
    enable_if_allowed_t<EnumT, is_logical_allowed, Ret>;
    
template <typename EnumT, typename Ret=EnumT>
using enable_if_mixed_logical_allowed_t =
    enable_if_allowed_t<EnumT, is_mixed_logical_allowed, Ret>;
    
template <typename EnumT, typename Ret=EnumT>
using enable_if_bitwise_allowed_t =
    enable_if_allowed_t<EnumT, is_bitwise_allowed, Ret>;
    
template <typename EnumT, typename Ret=EnumT>
using enable_if_mixed_bitwise_allowed_t =
    enable_if_allowed_t<EnumT, is_mixed_bitwise_allowed, Ret>;


// elib::enumeration::detail::operators
// this namespace will be put into the top-level namespace
// so the compiler can find it
namespace operators {

////////////////////////////////////////////////////////////////////////////////
//                        arithmetic operators                                                  
////////////////////////////////////////////////////////////////////////////////
    

template <typename EnumT>
constexpr enable_if_arithmetic_allowed_t<EnumT>
operator+(EnumT lhs) noexcept
{
    return static_cast<EnumT>(+base_enum_cast(lhs));
}

template <typename EnumT>
constexpr enable_if_arithmetic_allowed_t<EnumT>
operator-(EnumT lhs) noexcept
{
    return static_cast<EnumT>(-base_enum_cast(lhs));
}

template <typename EnumT>
constexpr enable_if_arithmetic_allowed_t<EnumT>
operator+(EnumT lhs, EnumT rhs) noexcept
{
    return static_cast<EnumT>(base_enum_cast(lhs) + base_enum_cast(rhs));
}

template <typename EnumT>
constexpr enable_if_arithmetic_allowed_t<EnumT>
operator-(EnumT lhs, EnumT rhs) noexcept
{
    return static_cast<EnumT>(base_enum_cast(lhs) - base_enum_cast(rhs));
}

template <typename EnumT>
constexpr enable_if_arithmetic_allowed_t<EnumT>
operator*(EnumT lhs, EnumT rhs) noexcept
{
    return static_cast<EnumT>(base_enum_cast(lhs) * base_enum_cast(rhs));
}

template <typename EnumT>
constexpr enable_if_arithmetic_allowed_t<EnumT>
operator/(EnumT lhs, EnumT rhs) noexcept
{
    return static_cast<EnumT>(base_enum_cast(lhs) / base_enum_cast(rhs));
}

template <typename EnumT>
constexpr enable_if_arithmetic_allowed_t<EnumT>
operator%(EnumT lhs, EnumT rhs) noexcept
{
    return static_cast<EnumT>(base_enum_cast(lhs) % base_enum_cast(rhs));
}

//
// compound operators
//

template <typename EnumT>
inline enable_if_arithmetic_allowed_t<EnumT>&
operator+=(EnumT& lhs, EnumT rhs) noexcept
{
    return (lhs = lhs + rhs);
}

template <typename EnumT>
inline enable_if_arithmetic_allowed_t<EnumT>&
operator-=(EnumT& lhs, EnumT rhs) noexcept
{
    return (lhs = lhs - rhs);
}

template <typename EnumT>
inline enable_if_arithmetic_allowed_t<EnumT>&
operator*=(EnumT& lhs, EnumT rhs) noexcept
{
    return (lhs = lhs * rhs);
}

template <typename EnumT>
inline enable_if_arithmetic_allowed_t<EnumT>&
operator/=(EnumT& lhs, EnumT rhs) noexcept
{
    return (lhs = lhs / rhs);
}

template <typename EnumT>
inline enable_if_arithmetic_allowed_t<EnumT>&
operator%=(EnumT& lhs, EnumT rhs) noexcept
{
    return (lhs = lhs % rhs);
}

//
//  inc & dec
//

template <typename EnumT>
inline enable_if_arithmetic_allowed_t<EnumT>&
operator++(EnumT& lhs) noexcept
{
    return (lhs = static_cast<EnumT>(base_enum_cast(lhs) + 1));
}

template <typename EnumT>
inline enable_if_arithmetic_allowed_t<EnumT>
operator++(EnumT& lhs, int) noexcept
{
    EnumT old = lhs;
    ++lhs;
    return old;
}

template <typename EnumT>
inline enable_if_arithmetic_allowed_t<EnumT>&
operator--(EnumT& lhs) noexcept
{
    return (lhs = static_cast<EnumT>(base_enum_cast(lhs) - 1));
}

template <typename EnumT>
inline enable_if_arithmetic_allowed_t<EnumT>
operator--(EnumT& lhs, int) noexcept
{
    EnumT old = lhs;
    --lhs;
    return old;
}

//
// mixed type expressions
//


template <typename EnumT>
constexpr enable_if_mixed_arithmetic_allowed_t<EnumT>
operator+(base_t<EnumT> lhs, EnumT rhs) noexcept
{
    return static_cast<EnumT>(lhs + base_enum_cast(rhs));
}

template <typename EnumT>
constexpr enable_if_mixed_arithmetic_allowed_t<EnumT>
operator-(base_t<EnumT> lhs, EnumT rhs) noexcept
{
    return static_cast<EnumT>(lhs - base_enum_cast(rhs));
}

template <typename EnumT>
constexpr enable_if_mixed_arithmetic_allowed_t<EnumT>
operator*(base_t<EnumT> lhs, EnumT rhs) noexcept
{
    return static_cast<EnumT>(lhs * base_enum_cast(rhs));
}

template <typename EnumT>
constexpr enable_if_mixed_arithmetic_allowed_t<EnumT>
operator/(base_t<EnumT> lhs, EnumT rhs) noexcept
{
    return static_cast<EnumT>(lhs / base_enum_cast(rhs));
}

template <typename EnumT>
constexpr enable_if_mixed_arithmetic_allowed_t<EnumT>
operator%(base_t<EnumT> lhs, EnumT rhs) noexcept
{
    return static_cast<EnumT>(lhs % base_enum_cast(rhs));
}

template <typename EnumT>
constexpr enable_if_mixed_arithmetic_allowed_t<EnumT>
operator+(EnumT lhs, base_t<EnumT> rhs) noexcept
{
    return static_cast<EnumT>(base_enum_cast(lhs) + rhs);
}

template <typename EnumT>
constexpr enable_if_mixed_arithmetic_allowed_t<EnumT>
operator-(EnumT lhs, base_t<EnumT> rhs) noexcept
{
    return static_cast<EnumT>(base_enum_cast(lhs) - rhs);
}

template <typename EnumT>
constexpr enable_if_mixed_arithmetic_allowed_t<EnumT>
operator*(EnumT lhs, base_t<EnumT> rhs) noexcept
{
    return static_cast<EnumT>(base_enum_cast(lhs) * rhs);
}

template <typename EnumT>
constexpr enable_if_mixed_arithmetic_allowed_t<EnumT>
operator/(EnumT lhs, base_t<EnumT> rhs) noexcept
{
    return static_cast<EnumT>(base_enum_cast(lhs) / rhs);
}

template <typename EnumT>
constexpr enable_if_mixed_arithmetic_allowed_t<EnumT>
operator%(EnumT lhs, base_t<EnumT> rhs) noexcept
{
    return static_cast<EnumT>(base_enum_cast(lhs) % rhs);
}


//
// mixed type compoud
//

template <typename EnumT>
inline enable_if_mixed_arithmetic_allowed_t<EnumT>&
operator+=(EnumT& lhs, base_t<EnumT> rhs) noexcept
{
    return (lhs = lhs + rhs);
}

template <typename EnumT>
inline enable_if_mixed_arithmetic_allowed_t<EnumT>&
operator-=(EnumT& lhs, base_t<EnumT> rhs) noexcept
{
    return (lhs = lhs - rhs);
}

template <typename EnumT>
inline enable_if_mixed_arithmetic_allowed_t<EnumT>&
operator*=(EnumT& lhs, base_t<EnumT> rhs) noexcept
{
    return (lhs = lhs * rhs);
}

template <typename EnumT>
inline enable_if_mixed_arithmetic_allowed_t<EnumT>&
operator/=(EnumT& lhs, base_t<EnumT> rhs) noexcept
{
    return (lhs = lhs / rhs);
}

template <typename EnumT>
inline enable_if_mixed_arithmetic_allowed_t<EnumT>&
operator%=(EnumT& lhs, base_t<EnumT> rhs) noexcept
{
    return (lhs = lhs % rhs);
}


////////////////////////////////////////////////////////////////////////////////
//                          logical operators                                               
////////////////////////////////////////////////////////////////////////////////


template <typename EnumT>
constexpr enable_if_logical_allowed_t<EnumT, bool>
operator!(EnumT lhs) noexcept
{
    return static_cast<bool>(! base_enum_cast(lhs));
}

template <typename EnumT>
constexpr enable_if_logical_allowed_t<EnumT, bool>
operator&&(EnumT lhs, EnumT rhs) noexcept
{
    return static_cast<bool>(base_enum_cast(lhs) && base_enum_cast(rhs));
}

template <typename EnumT>
constexpr enable_if_logical_allowed_t<EnumT, bool>
operator||(EnumT lhs, EnumT rhs) noexcept
{
    return static_cast<bool>(base_enum_cast(lhs) || base_enum_cast(rhs));
}

//
// mixed type expressions
//

template <typename EnumT>
constexpr enable_if_mixed_logical_allowed_t<EnumT, bool>
operator&&(EnumT lhs, bool rhs) noexcept
{
    return static_cast<bool>(base_enum_cast(lhs) && rhs);
}

template <typename EnumT>
constexpr enable_if_mixed_logical_allowed_t<EnumT, bool>
operator&&(bool lhs, EnumT rhs) noexcept
{
    return static_cast<bool>(lhs && base_enum_cast(rhs));
}

template <typename EnumT>
constexpr enable_if_mixed_logical_allowed_t<EnumT, bool>
operator||(EnumT lhs, bool rhs) noexcept
{
    return static_cast<bool>(base_enum_cast(lhs) || rhs);
}

template <typename EnumT>
constexpr enable_if_logical_allowed_t<EnumT, bool>
operator||(bool lhs, EnumT rhs) noexcept
{
    return static_cast<bool>(lhs || base_enum_cast(rhs));
}

////////////////////////////////////////////////////////////////////////////////
//                      bitwise operators                                                     
////////////////////////////////////////////////////////////////////////////////
    
template <typename EnumT>
constexpr enable_if_bitwise_allowed_t<EnumT>
operator~(EnumT lhs) noexcept
{
    return static_cast<EnumT>(~ base_enum_cast(lhs));
}

template <typename EnumT>
constexpr enable_if_bitwise_allowed_t<EnumT>
operator&(EnumT lhs, EnumT rhs) noexcept
{
    return static_cast<EnumT>(base_enum_cast(lhs) & base_enum_cast(rhs));
}

template <typename EnumT>
constexpr enable_if_bitwise_allowed_t<EnumT>
operator|(EnumT lhs, EnumT rhs) noexcept
{
    return static_cast<EnumT>(base_enum_cast(lhs) | base_enum_cast(rhs));
}


template <typename EnumT>
constexpr enable_if_bitwise_allowed_t<EnumT>
operator^(EnumT lhs, EnumT rhs) noexcept
{
    return static_cast<EnumT>(base_enum_cast(lhs) ^ base_enum_cast(rhs));
}

template <typename EnumT>
constexpr enable_if_bitwise_allowed_t<EnumT>
operator>>(EnumT lhs, base_t<EnumT> rhs) noexcept
{
    return static_cast<EnumT>(base_enum_cast(lhs) >> rhs);
}

template <typename EnumT>
constexpr enable_if_bitwise_allowed_t<EnumT>
operator<<(EnumT lhs, base_t<EnumT> rhs) noexcept
{
    return static_cast<EnumT>(base_enum_cast(lhs) << rhs);
}

//
// compound operators
//

template <typename EnumT>
inline enable_if_bitwise_allowed_t<EnumT>&
operator&=(EnumT& lhs, EnumT rhs) noexcept
{
    return (lhs = lhs & rhs);
}

template <typename EnumT>
inline enable_if_bitwise_allowed_t<EnumT>&
operator|=(EnumT& lhs, EnumT rhs) noexcept
{
    return (lhs = lhs | rhs);
}

template <typename EnumT>
inline enable_if_bitwise_allowed_t<EnumT>&
operator^=(EnumT& lhs, EnumT rhs) noexcept
{
    return (lhs = lhs ^ rhs);
}

template <typename EnumT>
inline enable_if_bitwise_allowed_t<EnumT>&
operator<<=(EnumT& lhs, base_t<EnumT> rhs) noexcept
{
    return (lhs = lhs << rhs);
}

template <typename EnumT>
inline enable_if_bitwise_allowed_t<EnumT>&
operator>>=(EnumT& lhs, base_t<EnumT> rhs) noexcept
{
    return (lhs = lhs >> rhs);
}


//
//  mixed type operators
//

template <typename EnumT>
constexpr enable_if_mixed_bitwise_allowed_t<EnumT>
operator&(EnumT lhs, base_t<EnumT> rhs) noexcept
{
    return static_cast<EnumT>(base_enum_cast(lhs) & rhs);
}

template <typename EnumT>
constexpr enable_if_mixed_bitwise_allowed_t<EnumT>
operator|(EnumT lhs, base_t<EnumT> rhs) noexcept
{
    return static_cast<EnumT>(base_enum_cast(lhs) | rhs);
}


template <typename EnumT>
constexpr enable_if_mixed_bitwise_allowed_t<EnumT>
operator^(EnumT lhs, base_t<EnumT> rhs) noexcept
{
    return static_cast<EnumT>(base_enum_cast(lhs) ^ rhs);
}


template <typename EnumT>
constexpr enable_if_mixed_bitwise_allowed_t<EnumT>
operator&(base_t<EnumT> lhs, EnumT rhs) noexcept
{
    return static_cast<EnumT>(lhs & base_enum_cast(rhs));
}

template <typename EnumT>
constexpr enable_if_mixed_bitwise_allowed_t<EnumT>
operator|(base_t<EnumT> lhs, EnumT rhs) noexcept
{
    return static_cast<EnumT>(lhs | base_enum_cast(rhs));
}


template <typename EnumT>
constexpr enable_if_mixed_bitwise_allowed_t<EnumT>
operator^(base_t<EnumT> lhs, EnumT rhs) noexcept
{
    return static_cast<EnumT>(lhs ^ base_enum_cast(rhs));
}
   
   
} // namespace operators 
} // namespace detail 
} // namespace enumeration 
} // namespace elib 


// put operators into top level namespace
using namespace elib::enumeration::detail::operators;


#endif // ELIB_ENUMERATION_OPERATORS_H