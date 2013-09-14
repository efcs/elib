#ifndef ELIB_TYPE_TRAITS_IS_ENUM_H
#define ELIB_TYPE_TRAITS_IS_ENUM_H

#include <elib/type_traits/integral_constant.hpp>

namespace elib {
namespace type_traits {


template <typename T>
struct is_enum : public integral_constant<bool,  __is_enum(T)>
{ };


} /* namespace type_traits */
} /* namespace elib */
#endif /* ELIB_TYPE_TRAITS_IS_ENUM_H */