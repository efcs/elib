#ifndef ELIB_TYPE_TRAITS_ADD_LVALUE_REFERENCE_H
#define ELIB_TYPE_TRAITS_ADD_LVALUE_REFERENCE_H

#include <elib/type_traits/integral_constant.h>
#include <elib/type_traits/conditional.h>
#include <elib/type_traits/is_reference.h>
#include <elib/type_traits/is_void.h>
#include <elib/type_traits/remove_reference.h>

namespace elib {
namespace type_traits {
namespace detail {
    
    
template <typename T,
    bool b1 = AND<NOT<is_reference<T>>, NOT<is_void<T>> >::value,
    bool b2 = is_rvalue_reference<T>::value> 
struct add_lvalue_reference {
    typedef T type;
};

template <typename T>
struct add_lvalue_reference<T, true, false> {
    typedef T& type;
};

template <typename T>
struct add_lvalue_reference<T, false, true> {
    typedef typename remove_reference<T>::type& type;
};


} /* namespace detail */


template <typename T>
struct add_lvalue_reference : public detail::add_lvalue_reference<T>
{ };


} /* namespace type_traits */
} /* namespace elib */
#endif /* ELIB_TYPE_TRAITS_ADD_LVALUE_REFERENCE_H */
