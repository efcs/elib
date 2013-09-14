#ifndef ELIB_TYPE_TRAITS_REMOVE_POINTER_H
#define ELIB_TYPE_TRAITS_REMOVE_POINTER_H

namespace elib {
namespace type_traits {
     
    
template <typename T>
struct remove_pointer {
    typedef T type;
};

template <typename T>
struct remove_pointer<T*> {
    typedef T type;
};

template <typename T>
struct remove_pointer<const T*> {
    typedef T type;
};

template <typename T>
struct remove_pointer<volatile T*> {
    typedef T type;
};

template <typename T>
struct remove_pointer<const volatile T*> {
    typedef T type;
};
        
} /* namespace type_traits */
} /* namespace elib */
#endif /* ELIB_TYPE_TRAITS_REMOVE_POINTER_H */