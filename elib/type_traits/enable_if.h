#ifndef ELIB_TYPE_TRAITS_ENABLE_IF_H
#define ELIB_TYPE_TRAITS_ENABLE_IF_H

namespace elib {
namespace type_traits {

    
template <bool pred, typename T=void>
struct enable_if { };

template <typename T>
struct enable_if<true, T> {
    typedef T type;
};
   

} /* namespace type_traits */
} /* namespace elib */
#endif /* ELIB_TYPE_TRAITS_ENABLE_IF_H */