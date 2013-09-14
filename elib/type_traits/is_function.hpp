#ifndef ELIB_TYPE_TRAITS_IS_FUNCTION_H
#define ELIB_TYPE_TRAITS_IS_FUNCTION_H

#include <elib/type_traits/integral_constant.hpp>


namespace elib {
namespace type_traits {
    
    
template <typename>
struct  is_function : public false_type
{ };

template <typename R, typename... Args>
struct  is_function<R(Args...)> : public true_type
{ };

template <typename R, typename... Args>
struct  is_function<R(Args......)> : public true_type
{ };

            
} /* namespace type_traits */
} /* namespace elib */
#endif /* ELIB_TYPE_TRAITS_IS_FUNCTION_H */