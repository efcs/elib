#ifndef ELIB_DECLVAL_HPP
#define ELIB_DECLVAL_HPP

namespace elib {

    
template <typename T>
typename add_rvalue_reference<T>::type declval();
    

} /* namespace elib */
#endif /* ELIB_DECLVAL_HPP */