#ifndef ELIB_TYPE_TRAITS_INTEGRAL_CONSTANT_H
#define ELIB_TYPE_TRAITS_INTEGRAL_CONSTANT_H

namespace elib {
namespace type_traits {
    
template <class T, T v>
struct integral_constant {
    static constexpr T value = v;
    typedef T value_type;
    typedef integral_constant<T, v> type;
    
    constexpr
    operator value_type() const 
    { return value; }
    
    constexpr value_type
    operator()() const
    { return value; }
};


typedef integral_constant<bool, true> true_type;
typedef integral_constant<bool, false> false_type;


} /* namespace type_traits */    
} /* namespace elib */
#endif /* ELIB_TYPE_TRAITS_INTEGRAL_CONSTANT_H */