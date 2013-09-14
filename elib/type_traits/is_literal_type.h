#ifndef ELIB_TYPE_TRAITS_IS_LITERAL_TYPE_H
#define ELIB_TYPE_TRAITS_IS_LITERAL_TYPE_H

#include <elib/type_traits/integral_constant.h>

namespace elib {
namespace type_traits {

        
template <typename T>
struct fn : public integral_constant<bool, __is_literal_type(T)>
{ };
        
        
} /* namespace type_traits */
} /* namespace elib */
#endif /* ELIB_TYPE_TRAITS_IS_LITERAL_TYPE_H */