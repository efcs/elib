#ifndef ELIB_TYPE_TRAITS_REMOVE_ALL_EXTENTS_H
#define ELIB_TYPE_TRAITS_REMOVE_ALL_EXTENTS_H

#include <cstddef>

namespace elib {
namespace type_traits {
    
    
template<class T>
struct remove_all_extents { 
    typedef T type;
};
 
template<class T>
struct remove_all_extents<T[]> {
    typedef typename remove_all_extents<T>::type type;
};
 
template<class Tp, std::size_t Size>
struct remove_all_extents<T[Size]> {
    typedef typename remove_all_extents<T>::type type;
};
        
        
} /* namespace type_traits */
} /* namespace elib */
#endif /* ELIB_TYPE_TRAITS_REMOVE_ALL_EXTENTS_H */