#ifndef ELIB_TYPE_TRAITS_REMOVE_CONST_H
#define ELIB_TYPE_TRAITS_REMOVE_CONST_H

namespace elib {
namespace type_traits {

        
template <typename T>
struct remove_const {
    typedef T type;
};

template <typename T>
struct remove_const<const T> {
    typedef T type;
};
        
        
} /* namespace type_traits */
} /* namespace elib */
#endif /* ELIB_TYPE_TRAITS_REMOVE_CONST_H */