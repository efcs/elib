#ifndef ELIB__STATIC_STRING_H
#define ELIB__STATIC_STRING_H


#ifndef ELIB_STATIC_STRING_H
#   error do not include this file directly
#endif


#include <cstring>


namespace elib {
    

template <unsigned N>
inline unsigned
basic_static_string<N>::size() const
{
    return strlen(string_value);
}

template <unsigned N>
inline constexpr
basic_static_string<N>::operator bool() const
{
    return (string_value[0] != 0);
}

template <unsigned N>
inline constexpr const char*
basic_static_string<N>::c_str() const
{
    return string_value;
}

template <unsigned N>
inline constexpr
basic_static_string<N>::operator const char*() const
{
    return string_value;
}

template <unsigned N>
inline constexpr char
basic_static_string<N>::operator[](unsigned i) const
{ 
    return string_value[i];
}

template <unsigned N>
inline char &
basic_static_string<N>::operator[](unsigned i)
{
    return string_value[i];
}

template <unsigned N>
inline 
basic_static_string<N>::operator std::string() const
{
    return std::string(string_value);
}

template <unsigned N>
inline std::string 
basic_static_string<N>::str() const
{
    return std::string(string_value);
}


} /* namespace elib */
#endif /* ELIB__STATIC_STRING_H */
