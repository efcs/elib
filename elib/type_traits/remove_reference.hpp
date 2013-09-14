#ifndef ELIB_TYPE_TRAITS_REMOVE_REFERENCE_H
#define ELIB_TYPE_TRAITS_REMOVE_REFERENCE_H

namespace elib {
namespace type_traits {
    

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
       

} /* namespace type_traits */
} /* namespace elib */
#endif /* ELIB_TYPE_TRAITS_REMOVE_REFERENCE_H */