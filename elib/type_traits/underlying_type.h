#ifndef ELIB_TYPE_TRAITS_UNDERLYING_TYPE_H
#define ELIB_TYPE_TRAITS_UNDERLYING_TYPE_H

#include <elib/type_traits/integral_constant.h>
#include <elib/type_traits/is_enum.h>
#include <elib/type_traits/enable_if.h>

namespace elib {
namespace type_traits {
namespace detail {
    
template <typename T, typename=void>
struct underlying_type
{ };

template <typename T>
struct underlying_type<T, typename enable_if<is_enum<T>::value>::type> {
    typedef __underlying_type(T) type;
};

            
} /* namespace detail */
        
        
template <typename T>
struct underlying_type : public detail::underlying_type<T>
{ };
        
        
} /* namespace type_traits */
} /* namespace elib */
#endif /* ELIB_TYPE_TRAITS_UNDERLYING_TYPE_H */