#ifndef ELIB_LOCK_LOCKING_PROXY_HPP
#define ELIB_LOCK_LOCKING_PROXY_HPP


#include <mutex>
#include <memory>
#include <type_traits>


namespace elib {
namespace lock {
    
    
template <typename T, typename Lock>
class access_guard {    
public:
    typedef T type;
    typedef Lock lock_type;
    
    access_guard() = default;
    access_guard(access_guard&&) = default;
    
    ~access_guard() = default;
    
    access_guard &
    operator=(access_guard&&) = default;
    
    type * 
    operator->();
    
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
    friend class locking_proxy;
    
    access_guard(type & val, lock_type & lock);

    type *m_val{nullptr};
    
    std::unique_lock<lock_type> m_lock{};
};
    
    

template <typename T, typename Lock=std::mutex>
class locking_proxy {
public:
    typedef T type;
    typedef Lock lock_type;
    typedef access_guard<type, lock_type> access_guard_type;
    
    locking_proxy(type & v);
    ~locking_proxy() = default;

    access_guard_type
    operator->() const;
    
    access_guard_type
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
class typed_locking_proxy : public locking_proxy<T, Lock> {
public:
    typedef locking_proxy<T, Lock> locking_proxy_type;
    typedef typename locking_proxy_type::type type;
    
    template <typename... Args>
    typed_locking_proxy(Args&&... args);
    
    ~typed_locking_proxy() = default;
private:
    type m_value;
};


template <typename T, typename Lock>
class typed_locking_proxy<T, Lock, if_default_ctor<T>>
    : public locking_proxy<T, Lock> {
public:
    typedef locking_proxy<T, Lock> locking_proxy_type;
    typedef typename locking_proxy_type::type type;
    
    typed_locking_proxy();
    
    template <typename... Args>
    typed_locking_proxy(Args&&... args);
    
    ~typed_locking_proxy() = default;
private:
    type m_value{};
};


} /* namespace lock */
} /* namespace elib */


#include <elib/lock/detail/_locking_proxy.hpp>


#endif /* ELIB_LOCK_LOCKING_PROXY_HPP */
