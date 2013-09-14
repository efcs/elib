#ifndef ELIB__DEFAULT_CONSTRUCTOR_HPP
#define ELIB__DEFAULT_CONSTRUCTOR_HPP


namespace elib {
namespace detail {
    
    
template <typename T, bool default_constructable>
struct ctor_helper {
public:
    static T* 
    construct(void);
};


template <typename T>
struct ctor_helper<T, true> {
public:
    static inline T*
    construct(void) 
    { return new T; }
};


template <typename T>
struct ctor_helper<T, false> {
    static inline T*
    construct(void)
    { return nullptr; }
};
   
    
} /* namespace detail */
} /* namespace elib */
#endif /* ELIB__DEFAULT_CONSTRUCTOR_HPP */