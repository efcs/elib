#ifndef ELIB_SINGLETON_H
#define ELIB_SINGLETON_H


#include <memory>
#include <functional> 


namespace elib {
    
    
template <typename T>
class singleton {
public:
    template <typename... Args>
    static void
    create_singleton(Args&&... args);
    
    static void 
    create_singleton();
    
    static T & 
    get();
private:
    static std::unique_ptr<T> m_ptr;
private:
    singleton() = delete;
};

    
    
} /* namespace elib */


#include "detail/_singleton.h"


#endif /* ELIB_SINGLETON_H */
