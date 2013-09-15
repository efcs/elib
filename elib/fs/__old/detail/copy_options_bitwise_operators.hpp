#ifndef ELIB_FS_COPY_OPTIONS_BITWISE_OPERATORS_HPP
#define ELIB_FS_COPY_OPTIONS_BITWISE_OPERATORS_HPP

namespace elib {
namespace fs {
namespace detail {
    
    
template <typename T, typename U>
constexpr unsigned
_copy_options_bitwise_and(T lhs, U rhs) noexcept
{
    return (static_cast<unsigned>(lhs) & static_cast<unsigned>(rhs));
}

template <typename T, typename U>
constexpr unsigned
_copy_options_bitwise_or(T lhs, U rhs) noexcept
{
    return (static_cast<unsigned>(lhs) | static_cast<unsigned>(rhs));
}

template <typename T, typename U>
constexpr unsigned
_copy_options_bitwise_xor(T lhs, U rhs) noexcept
{
    return (static_cast<unsigned>(lhs) ^ static_cast<unsigned>(rhs));
}

    
} /* namespace detail */

constexpr unsigned
operator&(copy_options lhs, copy_options rhs) noexcept
{
    return detail::_copy_options_bitwise_and(lhs, rhs);
}

constexpr unsigned
operator&(copy_options lhs, unsigned rhs) noexcept
{
    return detail::_copy_options_bitwise_and(lhs, rhs);
}

constexpr unsigned
operator&(unsigned lhs, copy_options rhs) noexcept
{
    return detail::_copy_options_bitwise_and(lhs, rhs);
}

constexpr unsigned
operator|(copy_options lhs, copy_options rhs) noexcept
{
    return detail::_copy_options_bitwise_or(lhs, rhs);
}

constexpr unsigned
operator|(copy_options lhs, unsigned rhs) noexcept
{
    return detail::_copy_options_bitwise_or(lhs, rhs);
}

constexpr unsigned
operator|(unsigned lhs, copy_options rhs) noexcept
{
    return detail::_copy_options_bitwise_or(lhs, rhs);
}

constexpr unsigned
operator^(copy_options lhs, copy_options rhs) noexcept
{
    return detail::_copy_options_bitwise_xor(lhs, rhs);
}

constexpr unsigned
operator^(copy_options lhs, unsigned rhs) noexcept
{
    return detail::_copy_options_bitwise_xor(lhs, rhs);
}

constexpr unsigned
operator^(unsigned lhs, copy_options rhs) noexcept
{
    return detail::_copy_options_bitwise_xor(lhs, rhs);
}


inline copy_options&
operator&=(copy_options& lhs, copy_options rhs) noexcept
{
    return (lhs = static_cast<copy_options>(detail::_copy_options_bitwise_and(lhs, rhs)));
}

inline copy_options&
operator&=(copy_options& lhs, unsigned rhs) noexcept
{
    return (lhs = static_cast<copy_options>(detail::_copy_options_bitwise_and(lhs, rhs)));
}

inline unsigned&
operator&=(unsigned& lhs, copy_options rhs) noexcept
{
    return lhs = detail::_copy_options_bitwise_and(lhs, rhs);
}

inline copy_options&
operator|=(copy_options& lhs, copy_options rhs) noexcept
{
    return (lhs = static_cast<copy_options>(detail::_copy_options_bitwise_or(lhs, rhs)));
}

inline copy_options&
operator|=(copy_options& lhs, unsigned rhs) noexcept
{
    return (lhs = static_cast<copy_options>(detail::_copy_options_bitwise_or(lhs, rhs)));
}

inline unsigned&
operator|=(unsigned& lhs, copy_options rhs) noexcept
{
    return (lhs = detail::_copy_options_bitwise_or(lhs, rhs));
}

inline copy_options&
operator^=(copy_options& lhs, copy_options rhs) noexcept
{
    return (lhs = static_cast<copy_options>(detail::_copy_options_bitwise_xor(lhs, rhs)));
}

inline copy_options&
operator^=(copy_options& lhs, unsigned rhs) noexcept
{
    return (lhs = static_cast<copy_options>(detail::_copy_options_bitwise_xor(lhs, rhs)));
}

inline unsigned&
operator^=(unsigned& lhs, copy_options rhs) noexcept
{
    return (lhs = detail::_copy_options_bitwise_xor(lhs, rhs));
}


} /* namespace fs */
} /* namespace elib */
#endif /* ELIB_FS_COPY_OPTIONS_BITWISE_OPERATORS_HPP */