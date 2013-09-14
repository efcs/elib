#ifndef ELIB_TYPE_TRAITS_IS_OBJECT_H
#define ELIB_TYPE_TRAITS_IS_OBJECT_H

#include <elib/type_traits/integral_constant.h>
#include <elib/type_traits/is_scalar.h>
#include <elib/type_traits/is_array.h>
#include <elib/type_traits/is_union.h>
#include <elib/type_traits/is_class.h>

namespace elib {
namespace type_traits {
    
    
template< class T>
struct is_object 
    : public integral_constant<bool,
        is_scalar<T>::value ||
        is_array<T>::value  ||
        is_union<T>::value  ||
        is_class<T>::value> 
{ };
        

} /* namespace type_traits */
} /* namespace elib */
#endif /* ELIB_TYPE_TRAITS_IS_OBJECT_H */