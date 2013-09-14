#ifndef ELIB_TYPE_TRAITS_IS_CONST_H
#define ELIB_TYPE_TRAITS_IS_CONST_H

#include <elib/type_traits/integral_constant.hpp>

namespace elib {
namespace type_traits {

        
template <typename T>
struct is_const : public false_type
{ };


template <typename T>
struct is_const<const T> : public true_type
{ };
        
        
} /* namespace type_traits */
} /* namespace elib */
#endif /* ELIB_TYPE_TRAITS_IS_CONST_H */