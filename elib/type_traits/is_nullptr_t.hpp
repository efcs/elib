#ifndef ELIB_TYPE_TRAITS_IS_NULLPTR_T_H
#define ELIB_TYPE_TRAITS_IS_NULLPTR_T_H

#include <elib/type_traits/integral_constant.hpp>
#include <elib/type_traits/remove_cv.hpp>

#include <cstddef>

namespace elib {
namespace type_traits {
namespace detail {

    
template <typename T>
struct is_nullptr_t : public false_type
{ };

template <>
struct is_nullptr_t<std::nullptr_t> : public true_type
{ };


} /* namespace detail */


template <typename T>
struct is_nullptr_t : public detail::is_nullptr_t<typename remove_cv<T>::type>
{ };


} /* namespace type_traits */
} /* namespace elib */
#endif /* ELIB_TYPE_TRAITS_IS_NULLPTR_T_H */