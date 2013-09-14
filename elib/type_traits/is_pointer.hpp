#ifndef ELIB_TYPE_TRAITS_IS_POINTER_H
#define ELIB_TYPE_TRAITS_IS_POINTER_H

#include <elib/type_traits/integral_constant.hpp>
#include <elib/type_traits/remove_cv.hpp>

namespace elib {
namespace type_traits {
namespace detail {
     
template <typename T>
struct is_pointer : public false_type
{ };

template <typename T>
struct is_pointer<T*> : public true_type
{ };


} /* namespace detail */
        

template <typename T>
struct is_pointer : public detail::is_pointer<typename remove_cv<T>::type>
{ };
        
        
} /* namespace type_traits */
} /* namespace elib */
#endif /* ELIB_TYPE_TRAITS_IS_POINTER_H */
