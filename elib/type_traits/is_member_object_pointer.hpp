#ifndef ELIB_TYPE_TRAITS_IS_MEMBER_OBJECT_POINTER_H
#define ELIB_TYPE_TRAITS_IS_MEMBER_OBJECT_POINTER_H

#include <elib/type_traits/integral_constant.hpp>
#include <elib/type_traits/is_member_pointer.hpp>
#include <elib/type_traits/is_member_function_pointer.hpp>


namespace elib {
namespace type_traits {

    
template <typename T>
struct is_member_object_pointer 
    : public integral_constant<bool,
        is_member_pointer<T>::value &&
        !is_member_function_pointer<T>::value>
{ };        
        

} /* namespace type_traits */
} /* namespace elib */
#endif /* ELIB_TYPE_TRAITS_IS_MEMBER_OBJECT_POINTER_H */
