#ifndef ELIB_TYPE_TRAITS_IS_INTEGRAL_H
#define ELIB_TYPE_TRAITS_IS_INTEGRAL_H

#include <elib/type_traits/integral_constant.hpp>
#include <elib/type_traits/remove_cv.hpp>


namespace elib {
namespace type_traits {
namespace detail {
    
    
template <typename T>
struct is_integral : public false_type
{ };

template <>
struct is_integral<bool> : public true_type
{ };

template <>
struct is_integral<char> : public true_type
{ };

template <>
struct is_integral<signed char> : public true_type
{ };

template <>
struct is_integral<unsigned char> : public true_type
{ };

template <>
struct is_integral<char16_t> : public true_type
{ };

template <>
struct is_integral<char32_t> : public true_type
{ };

template <>
struct is_integral<wchar_t> : public true_type
{ };

template <>
struct is_integral<short> : public true_type
{ };

template <>
struct is_integral<unsigned short> : public true_type
{ };

template <>
struct is_integral<int> : public true_type
{ };

template <>
struct is_integral<unsigned int> : public true_type
{ };

template <>
struct is_integral<long> : public true_type
{ };

template <>
struct is_integral<unsigned long> : public true_type
{ };

template <>
struct is_integral<long long> : public true_type
{ };

template <>
struct is_integral<unsigned long long> : public true_type
{ };

template <>
struct is_integral<> : public true_type
{ };

template <>
struct is_integral<> : public true_type
{ };

template <>
struct is_integral<> : public true_type
{ };

template <>
struct is_integral<> : public true_type
{ };


} /* namespace detail */


template <typename T>
struct is_integral 
    : public detail::is_integral<typename remove_cv<T>::type>::type
{ };


} /* namespace type_traits */
} /* namespace elib */
#endif /* ELIB_TYPE_TRAITS_IS_INTEGRAL_H */
