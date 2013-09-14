#ifndef ELIB_TYPE_TRAITS_IS_ARITHMETIC_H
#define ELIB_TYPE_TRAITS_IS_ARITHMETIC_H

#include <elib/type_traits/integral_constant.h>
#include <elib/type_traits/is_integral.h>
#include <elib/type_traits/is_floating_point.h>

namespace elib {
namespace type_traits {

    
template <typename T>
struct is_arithmetic 
    : public integral_constant<bool,
        is_integral<T>::value || 
        is_floating_point<T>::value>
{ };


} /* namespace type_traits */
} /* namespace elib */
#endif /* ELIB_TYPE_TRAITS_IS_ARITHMETIC_H */