#ifndef ELIB_TYPE_TRAITS_IS_ABSTRACT_H
#define ELIB_TYPE_TRAITS_IS_ABSTRACT_H

#include <elib/type_traits/integral_constant.h>

namespace elib {
namespace type_traits {

        
template <typename T>
struct is_abstract : public integral_constant<bool, __is_abstract(T)>
{ };
        
        
} /* namespace type_traits */
} /* namespace elib */
#endif /* ELIB_TYPE_TRAITS_IS_ABSTRACT_H */