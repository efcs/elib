#ifndef ELIB_TYPE_TRAITS_REMOVE_VOLATILE_H
#define ELIB_TYPE_TRAITS_REMOVE_VOLATILE_H

namespace elib {
namespace type_traits {

        
template <typename T>
struct remove_volatile {
    typedef T type;
};

template <typename T>
struct remove_volatile<volatile T> {
    typedef T type;
};
        
        
} /* namespace type_traits */
} /* namespace elib */
#endif /* ELIB_TYPE_TRAITS_REMOVE_VOLATILE_H */