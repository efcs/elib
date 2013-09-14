#ifndef ELIB_DECLVAL_H
#define ELIB_DECLVAL_H

namespace elib {

    
template <typename T>
typename add_rvalue_reference<T>::type declval();
    

} /* namespace elib */
#endif /* ELIB_DECLVAL_H */