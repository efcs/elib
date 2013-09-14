#ifndef ELIB_TYPE_TRAITS_REMOVE_EXTENT_H
#define ELIB_TYPE_TRAITS_REMOVE_EXTENT_H

#include <cstddef>

namespace elib {
namespace type_traits {
    
    
template<class T>
struct remove_extent { 
    typedef T type; 
};
 
template<class T>
struct remove_extent<T[]> { 
    typedef T type; 
};
 
template<class T, std::size_t Size>
struct remove_extent<T[Size]> { 
    typedef T type;
};
     
        
} /* namespace type_traits */
} /* namespace elib */
#endif /* ELIB_TYPE_TRAITS_REMOVE_EXTENT_H */