#ifndef ELIB_TYPE_TRAITS_DECAY_H
#define ELIB_TYPE_TRAITS_DECAY_H

#include <elib/type_traits/integral_constant.hpp>
#include <elib/type_traits/remove_reference.hpp>
#include <elib/type_traits/remove_extent.hpp>
#include <elib/type_traits/remove_extent.hpp>
#include <elib/type_traits/conditional.hpp>
#include <elib/type_traits/is_array.hpp>
#include <elib/type_traits/add_pointer.hpp>
#include <elib/type_traits/is_function.hpp>
#include <elib/type_traits/remove_cv.hpp>

namespace elib {
namespace type_traits {
    
    
template <typename T>
struct decay {
    typedef typename remove_reference<T>::type U;
    typedef typename conditional< 
        is_array<U>::value,
        typename remove_extent<U>::type*,
        typename conditional< 
            is_function<U>::value,
            typename add_pointer<U>::type,
            typename remove_cv<U>::type
        >::type
    >::type type;
};
       
        
} /* namespace type_traits */
} /* namespace elib */
#endif /* ELIB_TYPE_TRAITS_DECAY_H */