#ifndef ELIB_TYPE_TRAITS_IS_ARRAY_H
#define ELIB_TYPE_TRAITS_IS_ARRAY_H

#include <elib/type_traits/integral_constant.h>
#include <elib/type_traits/remove_cv.h>

#include <cstddef>


namespace elib {
namespace type_traits {
namespace detail {
    
    
template <typename T>
struct is_array : public false_type
{ };

template <typename T, std::size_t Size>
struct is_array<T[Size]> : public true_type
{ };

template <typename T>
struct is_array<T[]> : public true_type
{ };
    

} /* namespace detail */


template <typename T>
struct is_array : public detail::is_array<typename remove_cv<T>::type>
{ };

} /* namespace type_traits */
} /* namespace elib */
#endif /* ELIB_TYPE_TRAITS_IS_ARRAY_H */