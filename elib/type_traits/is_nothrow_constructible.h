#ifndef ELIB_TYPE_TRAITS_IS_NOTHROW_CONSTRUCTIBLE_H
#define ELIB_TYPE_TRAITS_IS_NOTHROW_CONSTRUCTIBLE_H

#include <elib/type_traits/integral_constant.h>
#include <elib/type_traits/remove_cv.h>

namespace elib {
namespace type_traits {
        
        
template <typename T>
struct is_nothrow_constructible 
    : public integral_constant<bool, __has_nothrow_constructor(T)>
{ };
        
        
} /* namespace type_traits */
} /* namespace elib */
#endif /* ELIB_TYPE_TRAITS_IS_NOTHROW_CONSTRUCTIBLE_H */