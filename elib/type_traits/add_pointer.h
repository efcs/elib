#ifndef ELIB_TYPE_TRAITS_ADD_POINTER_H
#define ELIB_TYPE_TRAITS_ADD_POINTER_H

#include <elib/type_traits/remove_reference.h>

namespace elib {
namespace type_traits {
  
        
template <typename T>
struct add_pointer {
    typedef typename remove_reference<T>::type* type;
};
        
        
} /* namespace type_traits */
} /* namespace elib */
#endif /* ELIB_TYPE_TRAITS_ADD_POINTER_H */