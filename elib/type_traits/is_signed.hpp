#ifndef ELIB_TYPE_TRAITS_IS_SIGNED_H
#define ELIB_TYPE_TRAITS_IS_SIGNED_H

#include <elib/type_traits/integral_constant.hpp>
#include <elib/type_traits/is_arithmetic.hpp>

namespace elib {
namespace type_traits {
namespace detail {
    
    
template <typename T, bool b = is_arithmetic<T>::value>
struct is_signed : public false_type
{ };
            
template <typename T>
struct is_signed<T, true> : public integral_constant<T, T(0) < T(-1)>
    
    
} /* namespace detail */
        
        
template <typename T>
struct is_signed : public detail::is_signed<T>
{ };
        
        
} /* namespace type_traits */
} /* namespace elib */
#endif /* ELIB_TYPE_TRAITS_IS_SIGNED_H */