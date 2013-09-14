#ifndef ELIB_TYPE_TRAITS_IS_SCALAR_H
#define ELIB_TYPE_TRAITS_IS_SCALAR_H

#include <elib/type_traits/integral_constant.h>
#include <elib/type_traits/is_arithmetic.h>
#include <elib/type_traits/is_enum.h>
#include <elib/type_traits/is_pointer.h>
#include <elib/type_traits/is_member_pointer.h>
#include <elib/type_traits/is_nullptr_t.h>

namespace elib {
namespace type_traits {

template<class T>
struct is_scalar 
    : public  integral_constant<bool,
        is_arithmetic<T>::value     ||
        is_enum<T>::value           ||
        is_pointer<T>::value        ||
        is_member_pointer<T>::value ||
        is_nullptr_t<T>::value>
{ };
    
    
} /* namespace type_traits */
} /* namespace elib */
#endif /* ELIB_TYPE_TRAITS_IS_SCALAR_H */