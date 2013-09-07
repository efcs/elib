#ifndef ELIB_SINGLETON_H
#define ELIB_SINGLETON_H


#include <elib/detail/_ctor_helper.h>

#include <memory>
#include <functional>
#include <type_traits>
#include <stdexcept>


namespace elib {
    
    
template <typename T>
class singleton {
public:
    typedef T type;
    
    singleton();
    
    template <typename... Args>
    singleton(Args&&... args);
    
    ~singleton() = default;
    
    type &
    construct();
    
    template <typename... Args>
    type &
    construct(Args&&... args);
    
    void 
    destruct();
    
    type & 
    get() const;

    bool
    good() const;
private:
    typedef detail::ctor_helper<type, 
                std::is_default_constructible<type>::value> ctor_helper;
                
    std::unique_ptr<T> m_ptr;
private:
    singleton(const singleton &);
    singleton & operator=(const singleton &);
};
    
    
template <typename T>
class static_singleton {
public:
    typedef T type;
    
    static T & 
    construct();
    
    template <typename... Args>
    static T &
    construct(Args&&... args);
    
    static void
    destruct();
    
    static T & 
    get();
    
    static bool
    good();
private:
    typedef detail::ctor_helper<type, 
                std::is_default_constructible<type>::value> ctor_helper;
    
    typedef std::unique_ptr<T> ptr_type;
                
    static ptr_type m_ptr;
private:
    static_singleton();
};


} /* namespace elib */


#include "detail/_singleton.h"


#endif /* ELIB_SINGLETON_H */