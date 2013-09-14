#ifndef ELIB_TYPE_TRAITS_IS_TRIVIALLY_COPYABLE_H
#define ELIB_TYPE_TRAITS_IS_TRIVIALLY_COPYABLE_H

#include <elib/type_traits/integral_constant.hpp>
#include <elib/type_traits/remove_cv.hpp>

namespace elib {
namespace type_traits {

        
        
template <typename T>
struct is_trivially_copyable 
    : public integral_constant<bool, __has_trivial_copy(T)>
{ };

template <typename T>
struct is_trivially_copyable 
    : public integral_constant<bool, __has_trivial_copy(T)>
{ };
        
        
} /* namespace type_traits */
} /* namespace elib */
#endif /* ELIB_TYPE_TRAITS_IS_TRIVIALLY_COPYABLE_H */