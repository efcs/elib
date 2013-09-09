#ifndef ELIB_FS_PERMS_BITWISE_OPERATORS_H
#define ELIB_FS_PERMS_BITWISE_OPERATORS_H

namespace elib {
namespace fs {
namespace detail {
    
template <typename T, typename U>
constexpr unsigned
_perms_bitwise_and(T lhs, U rhs) noexcept
{
    return (static_cast<unsigned>(lhs) & static_cast<unsigned>(rhs));
}

template <typename T, typename U>
constexpr unsigned
_perms_bitwise_or(T lhs, U rhs) noexcept
{
    return (static_cast<unsigned>(lhs) | static_cast<unsigned>(rhs));
}

template <typename T, typename U>
constexpr unsigned
_perms_bitwise_xor(T lhs, U rhs) noexcept
{
    return (static_cast<unsigned>(lhs) ^ static_cast<unsigned>(rhs));
}

    
} /* namespace detail */

constexpr unsigned
operator&(perms lhs, perms rhs) noexcept
{
    return detail::_perms_bitwise_and(lhs, rhs);
}

constexpr unsigned
operator&(perms lhs, unsigned rhs) noexcept
{
    return detail::_perms_bitwise_and(lhs, rhs);
}

constexpr unsigned
operator&(unsigned lhs, perms rhs) noexcept
{
    return detail::_perms_bitwise_and(lhs, rhs);
}

constexpr unsigned
operator|(perms lhs, perms rhs) noexcept
{
    return detail::_perms_bitwise_or(lhs, rhs);
}

constexpr unsigned
operator|(perms lhs, unsigned rhs) noexcept
{
    return detail::_perms_bitwise_or(lhs, rhs);
}

constexpr unsigned
operator|(unsigned lhs, perms rhs) noexcept
{
    return detail::_perms_bitwise_or(lhs, rhs);
}

constexpr unsigned
operator^(perms lhs, perms rhs) noexcept
{
    return detail::_perms_bitwise_xor(lhs, rhs);
}

constexpr unsigned
operator^(perms lhs, unsigned rhs) noexcept
{
    return detail::_perms_bitwise_xor(lhs, rhs);
}

constexpr unsigned
operator^(unsigned lhs, perms rhs) noexcept
{
    return detail::_perms_bitwise_xor(lhs, rhs);
}


inline perms&
operator&=(perms& lhs, perms rhs) noexcept
{
    return (lhs = static_cast<perms>(detail::_perms_bitwise_and(lhs, rhs)));
}

inline perms&
operator&=(perms& lhs, unsigned rhs) noexcept
{
    return (lhs = static_cast<perms>(detail::_perms_bitwise_and(lhs, rhs)));
}

inline unsigned&
operator&=(unsigned& lhs, perms rhs) noexcept
{
    return lhs = detail::_perms_bitwise_and(lhs, rhs);
}

inline perms&
operator|=(perms& lhs, perms rhs) noexcept
{
    return (lhs = static_cast<perms>(detail::_perms_bitwise_or(lhs, rhs)));
}

inline perms&
operator|=(perms& lhs, unsigned rhs) noexcept
{
    return (lhs = static_cast<perms>(detail::_perms_bitwise_or(lhs, rhs)));
}

inline unsigned&
operator|=(unsigned& lhs, perms rhs) noexcept
{
    return (lhs = detail::_perms_bitwise_or(lhs, rhs));
}

inline perms&
operator^=(perms& lhs, perms rhs) noexcept
{
    return (lhs = static_cast<perms>(detail::_perms_bitwise_xor(lhs, rhs)));
}

inline perms&
operator^=(perms& lhs, unsigned rhs) noexcept
{
    return (lhs = static_cast<perms>(detail::_perms_bitwise_xor(lhs, rhs)));
}

inline unsigned&
operator^=(unsigned& lhs, perms rhs) noexcept
{
    return (lhs = detail::_perms_bitwise_xor(lhs, rhs));
}


} /* namespace fs */
} /* namespace elib */

#endif /* ELIB_FS_PERMS_BITWISE_OPERATORS_H */