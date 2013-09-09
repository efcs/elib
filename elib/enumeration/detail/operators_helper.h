#ifndef ELIB_ENUMERATION_OPERATORS_HELPER_H
#define ELIB_ENUMERATION_OPERATORS_HELPER_H


#include <elib/operators/operators_e.h>
#include <elib/operators/all_operators.h>


#include <type_traits>


namespace elib {
namespace enumeration {
namespace detail {
    
    
    
template <typename T>
using base_t = typename std::underlying_type<T>::type;
    

template <typename T>
using remove_ref_t = typename std::remove_reference<T>::type;
    
    
template <typename T>
using is_enum_type = std::is_enum<remove_ref_t<T>>;


template <typename T>
using enable_if_enum_type = std::enable_if<is_enum_type<T>::value>;


template <typename T>
using enable_if_enum_type_t = typename enable_if_enum_type<T>::type;


template <typename T, typename U>
using enable_if_either_enum = std::enable_if<


template <typename T>
using is_integral_type = std::is_integral<remove_ref_t<T>>;


template <typename T>
using enable_if_integral_type = std::enable_if<is_integral_type<T>::value>;


template <typename T>
using enable_if_integral_type_t = typename enable_if_integral_type<T>::type;

                        

template <typename T, typename U>
using enable_if_enum_enum = std::enable_if<is_enum_type<T>::value &&
                                           is_enum_type<U>::value>;
           
                                           
template <typename T, typename U>
using enable_if_enum_integral = std::enable_if<is_enum_type<T>::value &&
                                               is_integral_type<U>::value>;
                   
                                        
template <typename T, typename U>
using enable_if_integral_enum = std::enable_if<is_integral_type<T>::value &&
                                               is_enum_type<U>::value>;
                                               
                                               
template <typename F, typename... Args>
using result_of_t = typename std::result_of<F(Args...)>::type;
                                               
                                               
template <typename Func, typename = void>
struct binary_operator_helper {};

template <typename Func, typename T, typename U>
struct binary_operator_helper<Func, enable_if_enum_enum<T, U>> {
    
    typedef base_t<T> return_type;
    
    template <typename Tp, typename Up>
    static inline return_type
    op(Tp&& lhs, Up&& rhs)
    { 
        Func fn;
        return fn(enum_base_cast(lhs), enum_base_cast(rhs));
    }
};

template <typename Func, typename T, typename U>
struct binary_operator_helper<Func, enable_if_enum_integral<T, U>> {
    
    typedef base_t<T> return_type;
    
    template <typename Tp, typename Up>
    static inline return_type
    op(Tp&& lhs, Up&& rhs)
    { 
        Func fn;
        return fn(enum_base_cast(lhs), rhs);
    }
};

template <typename Func, typename T, typename U>
struct binary_operator_helper<Func, enable_if_integral_enum<T, U>> {
    
    typedef base_t<U> return_type;
    
    template <typename Tp, typename Up>
    static inline return_type
    op(Tp&& lhs, Up&& rhs)
    { 
        Func fn;
        return fn(enum_base_cast(lhs),rhs);
    }
};

} /* namespace detail */
} /* namespace enumeration */
} /* namespace elib */
#endif /* ELIB_ENUMERATION_OPERATORS_HELPER_H */