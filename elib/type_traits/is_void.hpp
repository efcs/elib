#ifndef ELIB_IS_VOID_H
#define ELIB_TYPE_TRAITS_IS_VOID_H

#include <elib/type_traits/integral_constant.hpp>

namespace elib {
namespace type_traits {
    
    
template <typename T>
struct is_void : public false_type
{ };


template <>
struct is_void<void> : public true_type
{ };


} /* namespace type_traits */
} /* namespace elib */
#endif /* ELIB_IS_VOID_H */