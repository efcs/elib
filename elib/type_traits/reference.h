#ifndef ELIB_TYPE_TRAITS_REFERENCE_H
#define ELIB_TYPE_TRAITS_REFERENCE_H

namespace elib {
namespace type_traits {

template <typename T>
struct is_reference<T> : public false_type
{ };

template <typename T>
struct is_reference<T&> : public true_type
{ };

template <typename T>
struct is_reference<T&&> : public true_type
{ };
    
template <typename T>
struct remove_reference {
    typedef T type;
};

template <typename T>
struct remove_reference<T&> {
    typedef T type;
};

template <typename T>
struct remove_reference<T&&> {
    typedef T type;
};


namespace detail {
    
    
template <typename T,
    bool b1 = AND<NOT<is_reference<T>>, NOT<is_void<T>> >::value,
    bool b2 = is_rvalue_reference<T>::value> 
struct add_lvalue_reference {
    typedef T type;
};

template <typename T>
struct add_lvalue_reference<T, true, false> {
    typedef T& type;
};

template <typename T>
struct add_lvalue_reference<T, false, true> {
    typedef typename remove_reference<T>::type& type;
};


template <typename T,
    bool b = AND<NOT<is_reference<T>>,
                NOT<is_void<T>>>::value>
struct add_rvalue_reference {
    typedef T type;
};

template <typename T>
struct add_rvalue_reference<T, true> {
    typedef T&& type;
};
    

} // namespace detail 


template <typename T>
struct add_lvalue_reference : public detail::add_lvalue_reference<T>
{ };

template <typename T>
struct add_rvalue_reference : public detail::add_rvalue_reference<T>
{ };
    
    
} /* namespace type_traits */
} /* namespace elib */
#endif /* ELIB_TYPE_TRAITS_REFERENCE_H */