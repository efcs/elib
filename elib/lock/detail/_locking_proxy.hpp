#ifndef ELIB_LOCK__LOCKING_PROXY_HPP
#define ELIB_LOCK__LOCKING_PROXY_HPP


#ifndef ELIB_LOCK_LOCKING_PROXY_HPP
#   error only include this file through locking_proxy.h
#endif


namespace elib {
namespace lock {
    

template <typename T, typename Lock>
inline
locking_proxy<T, Lock>::locking_proxy(type & v)
    : m_value(v), m_lock{new lock_type{}}
{ }

template <typename T, typename Lock>
inline auto
locking_proxy<T, Lock>::operator->() const -> access_guard_type
{
    return access_guard_type(m_value, *m_lock);
}

template <typename T, typename Lock>
inline auto 
locking_proxy<T, Lock>::get_guard() const -> access_guard_type
{
    return access_guard_type(m_value, *m_lock);
}

template <typename T, typename Lock>
inline T &
locking_proxy<T, Lock>::operator*() const
{
    return m_value;
}


////////////////////////////////////////////////////////////////////////////////
//                            access_guard                                              
////////////////////////////////////////////////////////////////////////////////

    
template <typename T, typename Lock>
inline
access_guard<T, Lock>::access_guard(T & val, Lock & lock)
    : m_val(&val), m_lock(lock, std::defer_lock)
{ }

template <typename T, typename Lock>
inline T *
access_guard<T, Lock>::operator->() 
{
    if (! m_lock)
        m_lock.lock();
    
    return m_val;
}

template <typename T, typename Lock>
inline T &
access_guard<T, Lock>::operator*() const
{
    return *m_val;
}

template <typename T, typename Lock>
inline void
access_guard<T, Lock>::lock()
{
    m_lock.lock();
}

template <typename T, typename Lock>
inline bool
access_guard<T, Lock>::try_lock()
{
    return m_lock.try_lock();
}

template <typename T, typename Lock>
inline void
access_guard<T, Lock>::unlock()
{
    m_lock.unlock();
}

template <typename T, typename Lock>
inline Lock*
access_guard<T, Lock>::release()
{
    return m_lock.release();
}

template <typename T, typename Lock>
inline bool
access_guard<T, Lock>::owns_lock() const
{
    return m_lock.owns_lock();
}

template <typename T, typename Lock>
inline
access_guard<T, Lock>::operator bool() const
{
    return ((bool)m_lock);
} 
    
    
    
////////////////////////////////////////////////////////////////////////////////
//                              typed_locking_proxy                                                
////////////////////////////////////////////////////////////////////////////////
    
    

template <typename T, typename Lock, typename Enable>
template <typename... Args>
inline
typed_locking_proxy<T, Lock, Enable>::typed_locking_proxy(Args&&... args)
    : locking_proxy_type{m_value}, m_value{std::forward<Args>(args)...}
{ }


template <typename T, typename Lock>
inline
typed_locking_proxy<T, Lock, if_default_ctor<T>>::
typed_locking_proxy()
    : locking_proxy_type{m_value}
{ }

template <typename T, typename Lock>
template <typename... Args>
inline
typed_locking_proxy<T, Lock, if_default_ctor<T>>::
typed_locking_proxy(Args&&... args)
    : locking_proxy_type{m_value}, m_value{std::forward<Args>(args)...}
{ }
    
    
} /* namespace lock */
} /* namespace elib */
#endif /* ELIB_LOCK__LOCKING_PROXY_HPP */
