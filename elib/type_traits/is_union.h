#ifndef ELIB_TYPE_TRAITS_IS_UNION_H
#define ELIB_TYPE_TRAITS_IS_UNION_H

#include <elib/type_traits/integral_constant.h>

namespace elib {
namespace type_traits {
                        
 
template <typename T>
struct is_union : public integral_constant<bool, __is_union(T)>
{ };
        
        
} /* namespace type_traits */
} /* namespace elib */
#endif /* ELIB_TYPE_TRAITS_IS_UNION_H */