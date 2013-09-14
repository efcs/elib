#ifndef ELIB_TYPE_TRAITS_IS_MEMBER_FUNCTION_POINTER_H
#define ELIB_TYPE_TRAITS_IS_MEMBER_FUNCTION_POINTER_H

#include <elib/type_traits/integral_constant.h>
#include <elib/type_traits/remove_cv.h>
#include <elib/type_traits/is_function.h>

namespace elib {
namespace type_traits {
namespace detail {
    

template <typename T>
struct is_member_function_pointer : public false_type
{ };

template <typename T, typename U>
struct is_member_function_pointer<T U::*> : public is_function<T>
{ };

    
} /* namespace detail */

    
template <typename T>
struct is_member_function_pointer 
    : public detail::is_member_function_pointer<typename remove_cv<T>::type>
{ };
        

} /* namespace type_traits */
} /* namespace elib */
#endif /* ELIB_TYPE_TRAITS_IS_MEMBER_FUNCTION_POINTER_H */