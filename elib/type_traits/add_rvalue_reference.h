#ifndef ELIB_TYPE_TRAITS_ADD_RVALUE_REFERENCE_H
#define ELIB_TYPE_TRAITS_ADD_RVALUE_REFERENCE_H

#include <elib/type_traits/integral_constant.h>
#include <elib/type_traits/conditional.h>
#include <elib/type_traits/is_reference.h>
#include <elib/type_traits/is_void.h>


namespace elib {
namespace type_traits {
namespace detail {
    

template <typename T,
    bool b = AND<NOT<is_reference<T>>,
                NOT<is_void<T>>>::value>
struct add_rvalue_reference {
    typedef T type;
};

template <typename T>
struct add_rvalue_reference<T, true> {
    typedef T&& type;
};
    

} // namespace detail 


template <typename T>
struct add_rvalue_reference : public detail::add_rvalue_reference<T>
{ };
        
        
} /* namespace type_traits */
} /* namespace elib */
#endif /* ELIB_TYPE_TRAITS_ADD_RVALUE_REFERENCE_H */