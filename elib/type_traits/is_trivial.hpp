#ifndef ELIB_TYPE_TRAITS_IS_TRIVIAL_H
#define ELIB_TYPE_TRAITS_IS_TRIVIAL_H

#include <elib/type_traits/integral_constant.hpp>
#include <elib/type_traits/is_trivially_copyable.hpp>
#include <elib/type_traits/is_trivially_default_constructable.hpp>

namespace elib {
namespace type_traits {
   
        
template <typename T>
struct is_trivial 
    : public integral_constant<bool,
        is_trivially_copyable<T>::value &&
        is_trivially_default_constructable<T>::value>
{ };
        
        
} /* namespace type_traits */
} /* namespace elib */
#endif /* ELIB_TYPE_TRAITS_IS_TRIVIAL_H */