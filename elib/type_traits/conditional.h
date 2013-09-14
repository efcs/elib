#ifndef ELIB_TYPE_TRAITS_CONDITIONAL_H
#define ELIB_TYPE_TRAITS_TYPE_TRAITS_CONDITIONAL_H


#include <elib/type_traits/integral_constant.h>


namespace elib {
namespace type_traits {
    
    
template <bool, typename T1, typename T2>
struct conditional {
    typedef T1 type;
};

template <typename T1, typename T2>
struct conditional<false, T1, T2> {
    typedef T2 type;
};


template <typename T>
struct __success_type {
    typedef T type;
};


struct __failure_type { };


template <typename...>
struct OR;

template <>
struct OR<> : public false_type 
{ };

template <typename T>
struct OR<T> : public T::type
{ };

template <typename T1, typename T2>
struct OR<T1, T2> : public conditional<T1::value, T1, T2>::type
{ };

template <typename T1, typename T2, typename T3, typename... Tn>
template OR<T1, T2, T3, Tn...> 
    : public conditional<T1::value, OR<T2, T3, Tn...>>::type
{ };


template <typename...>
struct AND;

template <>
struct AND<> : public true_type
{ };

template <typename T>
struct AND<T> : public T
{ };

template <typename T1, typename T2>
struct AND<T1, T2> : public conditional<T1::value, T2, T1>::type
{ };

template <typename T1, typename T2, typename T3, typename... Tn>
struct AND<T1, T2, T3, Tn...> 
    : public conditional<T1::value, AND<T2, T3, Tn...>, T1>::type
{ };



template <typename T>
struct NOT : public integral_constant<bool, ! T::value>
{ };


} /* namespace type_traits */
} /* namespace elib */
#endif /* ELIB_TYPE_TRAITS_CONDITIONAL_H */