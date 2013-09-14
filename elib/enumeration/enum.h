#ifndef ELIB_ENUMERATION_ENUM_H
#define ELIB_ENUMERATION_ENUM_H


#include <elib/enumeration/basic_enum_traits.h>
#include <elib/template_conditional.h>

#include <type_traits>

namespace elib {
namespace enumeration {
    

template <typename EnumT>
using enum_type = std::remove_reference<EnumT>;

template <typename EnumT>
using enum_t = typename enum_type<EnumT>::type;

/* return the underlying type of the enum */
template <typename EnumT>
using base_type = std::underlying_type<enum_t<EnumT>>;

template <typename EnumT>
using base_t = typename base_type<EnumT>::type;

/* same as base_type & base_t but with standard name */
template <typename EnumT>
using underlying_type = base_type<EnumT>;

template <typename EnumT>
using underlying_t = base_t<EnumT>;


/* checks if an enum has traits defined for it */
template <typename EnumT>
using has_enum_traits = std::is_enum<decltype(basic_enum_traits<EnumT>::default_value)>;

/* enable if a type is an enum */
template <typename EnumT, typename Ret=EnumT>
using enable_if_enum = std::enable_if<std::is_enum<EnumT>::value, Ret>;

template <typename EnumT, typename Ret=EnumT>
using enable_if_enum_t = typename enable_if_enum<EnumT, Ret>::type;

/* enable if a type has defined basic_enum_traits<EnumT> */
template <typename EnumT, typename Ret=EnumT>
using enable_if_has_traits = std::enable_if<has_enum_traits<EnumT>::value, Ret>;

template <typename EnumT, typename Ret=EnumT>
using enable_if_has_traits_t = typename enable_if_has_traits<EnumT, Ret>::type;
  

/* npos_enum is a value that:
 *   a) is the numeric max for Enum's underlying type
 *   b) should not be a member of Enum (if it is used) */
template <typename EnumT>
constexpr EnumT 
npos_enum() noexcept
{
    return static_cast<EnumT>(-1);
}

/* return e == npos_enum() 
 * is_npos_enum can only be used when basic_traits::last_value < NPOS_ENUM */
template <typename EnumT>
constexpr bool
is_npos_enum(EnumT e) noexcept
{
    return (e == npos_enum<EnumT>());
}

/* cast to base type,
 * may be used without defining basic_enum_traits */
template <typename EnumT>
constexpr enable_if_enum_t<EnumT, base_t<EnumT>>
base_enum_cast(EnumT e) noexcept
{
    return static_cast<base_t<EnumT>>(e);
}

/* cast an enum to a boolean,
 * equiv to (e != 0) */
template <typename EnumT>
constexpr enable_if_enum_t<EnumT, bool>
bool_enum_cast(EnumT e) noexcept
{
    return (base_enum_cast(e) != 0);
}

template <typename EnumT>
constexpr enable_if_enum_t<EnumT, bool>
is_true(EnumT e) noexcept
{
    return (base_enum_cast(e) != 0);
}

template <typename EnumT>
constexpr enable_if_enum_t<EnumT, bool>
is_false(EnumT e) noexcept
{
    return (base_enum_cast(e) == 0);
}

    
} /* namespace enumeration */
} /* namespace elib */
#endif /* ELIB_ENUMERATION_ENUM_H */