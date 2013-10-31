#ifndef ELIB_FS_CONVERSION_HPP
#define ELIB_FS_CONVERSION_HPP

# include <elib/pragma.hpp>

#include <locale>
#include <string>
#include <cwchar>
#include <vector>
#include <list>
#include <type_traits>


namespace elib {
namespace fs {
    

class directory_entry;    

    
namespace detail {

ELIB_PRAGMA_DIAG_PUSH()
ELIB_PRAGMA_IGNORE_EFFCXX()
    
template <typename T>
struct is_convertible : public std::false_type { };

template <>
struct is_convertible<char*> : public std::true_type { };

template <>
struct is_convertible<const char*> : public std::true_type { };

template <>
struct is_convertible<std::string> : public std::true_type { };

template <>
struct is_convertible<std::vector<char>> : public std::true_type { };

template <>
struct is_convertible<std::list<char>> : public std::true_type { };

template <>
struct is_convertible<directory_entry> : public std::true_type { };


template <typename T, typename Ret=void>
struct enable_if_convertible 
    : public std::enable_if<is_convertible<typename std::decay<T>::type>::value,
                            Ret>
{ };

ELIB_PRAGMA_DIAG_POP()

template <typename T, typename Ret=void>
using enable_if_convertible_t = typename enable_if_convertible<T, Ret>::type;




template <typename Ret>
Ret
convert(const std::string& s);

template <>
inline std::string
convert(const std::string& s)
{ return s; }

template <typename Ret>
inline Ret
dispatch(const char* from)
{
    return convert<Ret>(std::string{from});
}

template <typename Ret>
inline Ret
dispatch(const std::string& from)
{
    return convert<Ret>(from);
}

template <typename Ret>
inline Ret
dispatch(const std::vector<char>& from)
{
    return convert<Ret>(std::string{from.begin(), from.end()});
}

template <typename Ret>
inline Ret
dispatch(const std::list<char>& from)
{
    return convert<Ret>(std::string{from.begin(), from.end()});
}

template <typename Ret>
Ret
dispatch(const directory_entry& from);

template <>
std::string
dispatch(const directory_entry& from);


    
} /* namespace detail */
} /* namespace fs */
} /* namespace elib */
#endif /* ELIB_FS_CONVERSION_HPP */