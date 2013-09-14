#ifndef ELIB_TYPE_TRAITS_IS_MEMBER_POINTER_H
#define ELIB_TYPE_TRAITS_IS_MEMBER_POINTER_H

#include <elib/type_traits/integral_constant.hpp>
#include <elib/type_traits/remove_cv.hpp>

namespace elib {
namespace type_traits {
namespace detail {
     
    
template <typename T>
struct is_member_pointer : public false_type
{ };

template <typename T, typename U>
struct is_member_pointer<T U::*> : public true_type
{ };
    
    
} /* namespace detail */
        
        
template <typename T>
struct is_member_pointer 
    : public detail::is_member_pointer<typename remove_cv<T>::type>
{ };
        
        
} /* namespace type_traits */
} /* namespace elib */
#endif /* ELIB_TYPE_TRAITS_IS_MEMBER_POINTER_H */