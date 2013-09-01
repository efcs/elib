#ifndef ELIB_ENABLE_IF_H
#define ELIB_ENABLE_IF_H

namespace elib {
    

template <bool B, typename T = void>
struct enable_if {};


template <typename T>
struct enable_if<true, T> {
    typedef T type;
};
    
    
} /* namespace elib */
#endif /* ELIB_ENABLE_IF_H */
