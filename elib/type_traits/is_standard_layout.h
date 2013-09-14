#ifndef ELIB_TYPE_TRAITS_IS_STANDARD_LAYOUT_H
#define ELIB_TYPE_TRAITS_IS_STANDARD_LAYOUT_H

#include <elib/type_traits/integral_constant.h>

namespace elib {
namespace type_traits {  
        
        
template <typename T>
struct is_standard_layout 
    : public integral_constant<bool, __is_standard_layout(T)>
{ };
        
        
} /* namespace type_traits */
} /* namespace elib */
#endif /* ELIB_TYPE_TRAITS_IS_STANDARD_LAYOUT_H */