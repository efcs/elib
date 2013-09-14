#ifndef ELIB_TYPE_TRAITS_IS_FLOATING_POINT_H
#define ELIB_TYPE_TRAITS_IS_FLOATING_POINT_H


#include <elib/type_traits/integral_constant.hpp>

namespace elib {
namespace type_traits {
namespace detail {
    
template <typename T>
struct is_floating_point : public false_type
{ };

template <>
struct is_floating_point<float> : public true_type
{ };

template <>
struct is_floating_point<double> : public true_type
{ };

template <>
struct is_floating_point<long double> : public true_type
{ };
    

} /* namespace detail */


template <typename T>
struct is_floating_point 
    : public detail::is_floating_point<typename remove_cv<T>::type>
{ };


} /* namespace type_traits */    
} /* namespace elib */
#endif /* ELIB_TYPE_TRAITS_IS_FLOATING_POINT_H */