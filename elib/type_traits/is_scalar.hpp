#ifndef ELIB_TYPE_TRAITS_IS_SCALAR_H
#define ELIB_TYPE_TRAITS_IS_SCALAR_H

#include <elib/type_traits/integral_constant.hpp>
#include <elib/type_traits/is_arithmetic.hpp>
#include <elib/type_traits/is_enum.hpp>
#include <elib/type_traits/is_pointer.hpp>
#include <elib/type_traits/is_member_pointer.hpp>
#include <elib/type_traits/is_nullptr_t.hpp>

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