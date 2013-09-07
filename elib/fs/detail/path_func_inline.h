#ifndef ELIB_FS_PATH_FUNC_INLINE_H
#define ELIB_FS_PATH_FUNC_INLINE_H

namespace elib {
namespace fs {
    
inline void
swap(path & lhs, path & rhs)
{
    lhs.swap(rhs);
}

inline bool
operator<(const path & lhs, const path & rhs)
{
    return (lhs.compare(rhs) < 0);
}

inline bool
operator<=(const path & lhs, const path & rhs)
{
    return (lhs.compare(rhs) <= 0);
}

inline bool
operator>(const path & lhs, const path & rhs)
{
    return (lhs.compare(rhs) > 0);
}

inline bool
operator>=(const path & lhs, const path & rhs)
{
    return (lhs.compare(rhs) >= 0);
}

inline bool
operator==(const path & lhs, const path & rhs)
{
    return (lhs.compare(rhs) == 0);
}

inline bool
operator!=(const path & lhs, const path & rhs)
{
    return (lhs.compare(rhs) != 0);
}

inline path
operator/(const path & lhs, const path & rhs)
{
    return (path(lhs) /= rhs);
}

template <class charT, class traits>
inline std::basic_ostream<charT, traits>&
operator<<(std::basic_ostream<charT, traits>& os, const path& p)
{
    os << p.str();
    return os;
}

template <class charT, class traits>
inline std::basic_istream<charT, traits>&
operator>>(std::basic_istream<charT, traits>& is, path& p)
{
    std::string tmp;
    is >> tmp;
    p.clear();
    p += tmp;
    return is;
}


    
} /* namespace fs */
} /* namespace elib */
#endif /* ELIB_FS_PATH_FUNC_INLINE_H */
