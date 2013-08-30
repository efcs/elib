#ifndef ELIB_LOCK_WRAPPER_H
#define ELIB_LOCK_WRAPPER_H


#include <mutex>
#include <memory>
#include <type_traits>


namespace elib {
    
    
template <typename T, typename Lock>
class scoped_lock_wrapper {    
public:
    typedef T type;
    typedef Lock lock_type;
    
    scoped_lock_wrapper() = default;
    scoped_lock_wrapper(scoped_lock_wrapper&&) = default;
    
    ~scoped_lock_wrapper() = default;
    
    scoped_lock_wrapper &
    operator=(scoped_lock_wrapper&&) = default;
    
    type * 
    operator->() const;
    
    type &
    operator*() const;
    
    void 
    lock();
    
    bool 
    try_lock();
    
    void 
    unlock();
    
    lock_type*
    release();
    
    bool 
    owns_lock() const;
    
    operator bool() const;
    
private:    
    template <typename T2, typename Lock2>
    friend class lock_wrapper;
    
    scoped_lock_wrapper(type & val, lock_type & lock);

    type *m_val{nullptr};
    
    mutable std::unique_lock<lock_type> m_lock{};
};
    
    

template <typename T, typename Lock=std::mutex>
class lock_wrapper {
public:
    typedef T type;
    typedef Lock lock_type;
    typedef scoped_lock_wrapper<type, lock_type> scoped_wrapper;
    
    lock_wrapper(type & v);
    ~lock_wrapper() = default;

    scoped_wrapper
    operator->() const;
    
    scoped_wrapper
    get_guard() const;
    
    type &
    operator*() const;
private:
    type & m_value;
    mutable std::shared_ptr<lock_type> m_lock;
};


template <typename T>
using if_default_ctor = 
typename std::enable_if<std::is_default_constructible<T>::value>::type;
    

template <typename T, typename Lock=std::mutex, typename = void>
class type_lock_wrapper : public lock_wrapper<T, Lock> {
public:
    typedef lock_wrapper<T, Lock> lock_wrapper_type;
    typedef typename lock_wrapper_type::type type;
    
    template <typename... Args>
    type_lock_wrapper(Args&&... args);
    
    ~type_lock_wrapper() = default;
private:
    type m_value;
};


template <typename T, typename Lock>
class type_lock_wrapper<T, Lock, if_default_ctor<T>>
    : public lock_wrapper<T, Lock> {
public:
    typedef lock_wrapper<T, Lock> lock_wrapper_type;
    typedef typename lock_wrapper_type::type type;
    
    type_lock_wrapper();
    
    template <typename... Args>
    type_lock_wrapper(Args&&... args);
    
    ~type_lock_wrapper() = default;
private:
    type m_value{};
};

    
} /* namespace elib */


#include "detail/_lock_wrapper.h"


#endif /* ELIB_LOCK_WRAPPER_H */
