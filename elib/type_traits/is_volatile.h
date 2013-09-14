#ifndef ELIB_TYPE_TRAITS_IS_VOLATILE_H
#define ELIB_TYPE_TRAITS_IS_VOLATILE_H

#include <elib/type_traits/integral_constant.h>

namespace elib {
namespace type_traits {

        
template <typename T>
struct is_volatile : public false_type
{ };

      
template <typename T>
struct is_volatile<volatile T> : public true_type
{ };
        
        
} /* namespace type_traits */
} /* namespace elib */
#endif /* ELIB_TYPE_TRAITS_IS_VOLATILE_H */