#ifndef ELIB_TYPE_TRAITS_IS_COMPOUND_H
#define ELIB_TYPE_TRAITS_IS_COMPOUND_H

#include <elib/type_traits/integral_constant.h>
#include <elib/type_traits/is_fundamental.h>

namespace elib {
namespace type_traits {
    
    
template<class T>
struct is_compound 
    : public integral_constant<bool, !is_fundamental<T>::value> 
{ };


} /* namespace type_traits */
} /* namespace elib */
#endif /* ELIB_TYPE_TRAITS_IS_COMPOUND_H */