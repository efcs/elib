#ifndef ELIB_TYPE_TRAITS_IS_REFERENCE_H
#define ELIB_TYPE_TRAITS_IS_REFERENCE_H

#include <elib/type_traits/integral_constant.h>

namespace elib {
namespace type_traits {
    
    
template <typename T>
struct is_reference : public false_type
{ };

template <typename T>
struct is_reference<T&> : public true_type
{ };

template <typename T>
struct is_reference<T&&> : public true_type
{ };
        

} /* namespace type_traits */
} /* namespace elib */
#endif /* ELIB_TYPE_TRAITS_IS_REFERENCE_H */