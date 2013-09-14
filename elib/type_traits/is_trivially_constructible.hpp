#ifndef ELIB_TYPE_TRAITS_IS_TRIVIALLY_CONSTRUCTIBLE_H
#define ELIB_TYPE_TRAITS_IS_TRIVIALLY_CONSTRUCTIBLE_H

#include <elib/type_traits/integral_constant.hpp>

namespace elib {
namespace type_traits {

        
template <typename T>
struct is_trivially_constructible 
    : public integral_constant<bool, __has_trivially_constructor(T)>
{ };
        
        
} /* namespace type_traits */
} /* namespace elib */
#endif /* ELIB_TYPE_TRAITS_IS_TRIVIALLY_CONSTRUCTIBLE_H */