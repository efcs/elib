#ifndef ELIB_TYPE_TRAITS_IS_UNSIGNED_H
#define ELIB_TYPE_TRAITS_IS_UNSIGNED_H

#include <elib/type_traits/integral_constant.hpp>
#include <elib/type_traits/is_arithmetic.hpp>
#include <elib/type_traits/is_signed.hpp>

namespace elib {
namespace type_traits {
namespace detail {
    
    
template <typename T, bool = is_arithmetic<T>::value &&
                             !is_signed<T>::value>
struct is_unsigned : public false_type
{ };

template <typename T>
struct is_unsigned<T, true> : public true_type
{ };
    

} /* namespace detail */
        
        
template <typename T>
struct is_unsigned : public detail::is_unsigned<T>
{ };


} /* namespace type_traits */
} /* namespace elib */
#endif /* ELIB_TYPE_TRAITS_IS_UNSIGNED_H */