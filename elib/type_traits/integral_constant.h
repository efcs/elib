#ifndef ELIB_TYPE_TRAITS_INTEGRAL_CONSTANT_H
#define ELIB_TYPE_TRAITS_INTEGRAL_CONSTANT_H

namespace elib {
    
    
template <typename T, T v>
struct integral_constant {
    typedef T value_type;
    typedef integral_constant type;
    
    static constexpr T value = v;
    
    constexpr 
    operator value_type() const
    { return value; }
    
    constexpr value_type
    operator()() const
    { return value; }
};


typedef integral_constant<bool, true> true_type;
typedef integral_constant<bool, false> false_type;

    
} /* namespace elib */
#endif /* ELIB_TYPE_TRAITS_INTEGRAL_CONSTANT_H */