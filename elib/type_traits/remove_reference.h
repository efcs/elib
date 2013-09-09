#ifndef ELIB_TYPE_TRAITS_REMOVE_REFERENCE_H
#define ELIB_TYPE_TRAITS_REMOVE_REFERENCE_H


namespace elib {

    
template <typename T>
struct remove_reference {
    typedef T type;
};


template <typename T>
struct remove_reference<T&> {
    typedef T type;
};


template <typename T>
struct remove_reference<T&&> {
    typedef T type;
};


template <typename T>
using remove_reference_t = typename remove_reference<T>::type;


} /* namespace elib */
#endif /* ELIB_TYPE_TRAITS_REMOVE_REFERENCE_H */