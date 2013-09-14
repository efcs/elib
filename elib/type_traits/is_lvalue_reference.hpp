#ifndef ELIB_TYPE_TRAITS_IS_LVALUE_REFERENCE_H
#define ELIB_TYPE_TRAITS_IS_LVALUE_REFERENCE_H

#include <elib/type_traits/integral_constant.hpp>

namespace elib {
namespace type_traits {

    
template <typename T>
struct is_lvalue_reference : public false_type
{ };

template <typename T>
struct is_lvalue_reference<T&> : public true_type
{ };
   

} /* namespace type_traits */
} /* namespace elib */
#endif /* ELIB_TYPE_TRAITS_IS_LVALUE_REFERENCE_H */