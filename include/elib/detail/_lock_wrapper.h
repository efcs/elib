#ifndef ELIB__LOCK_WRAPPER_H
#define ELIB__LOCK_WRAPPER_H


#ifndef ELIB_LOCK_WRAPPER_H
#   error only include this file through lock_wrapper.h
#endif


namespace elib {
    

template <typename T, typename Lock>
inline
lock_wrapper<T, Lock>::lock_wrapper(type & v)
    : m_value(v), m_lock{new lock_type{}}
{ }

template <typename T, typename Lock>
inline typename lock_wrapper<T, Lock>::scoped_wrapper
lock_wrapper<T, Lock>::operator->() const
{
    return scoped_wrapper(m_value, *m_lock);
}

template <typename T, typename Lock>
inline typename lock_wrapper<T, Lock>::scoped_wrapper
lock_wrapper<T, Lock>::get_guard() const
{
    return scoped_wrapper(m_value, *m_lock);
}

template <typename T, typename Lock>
inline typename lock_wrapper<T, Lock>::type &
lock_wrapper<T, Lock>::operator*() const
{
    return m_value;
}


////////////////////////////////////////////////////////////////////////////////
//                            scoped_lock_wrapper                                              
////////////////////////////////////////////////////////////////////////////////

    
template <typename T, typename Lock>
inline
scoped_lock_wrapper<T, Lock>::scoped_lock_wrapper(T & val, lock_type & lock)
    : m_val(&val), m_lock(lock, std::defer_lock)
{ }

template <typename T, typename Lock>
inline T *
scoped_lock_wrapper<T, Lock>::operator->() const
{
    if (! m_lock)
        m_lock.lock();
    
    return m_val;
}

template <typename T, typename Lock>
inline T &
scoped_lock_wrapper<T, Lock>::operator*() const
{
    return *m_val;
}

template <typename T, typename Lock>
inline void
scoped_lock_wrapper<T, Lock>::lock()
{
    m_lock.lock();
}

template <typename T, typename Lock>
inline bool
scoped_lock_wrapper<T, Lock>::try_lock()
{
    return m_lock.try_lock();
}

template <typename T, typename Lock>
inline void
scoped_lock_wrapper<T, Lock>::unlock()
{
    m_lock.unlock();
}

template <typename T, typename Lock>
inline typename scoped_lock_wrapper<T, Lock>::lock_type*
scoped_lock_wrapper<T, Lock>::release()
{
    return m_lock.release();
}

template <typename T, typename Lock>
inline bool
scoped_lock_wrapper<T, Lock>::owns_lock() const
{
    return m_lock.owns_lock();
}

template <typename T, typename Lock>
inline
scoped_lock_wrapper<T, Lock>::operator bool() const
{
    return ((bool)m_lock);
} 
    
    
    
////////////////////////////////////////////////////////////////////////////////
//                              type_lock_wrapper                                                
////////////////////////////////////////////////////////////////////////////////
    
    

template <typename T, typename Lock, typename Enable>
template <typename... Args>
inline
type_lock_wrapper<T, Lock, Enable>::type_lock_wrapper(Args&&... args)
    : lock_wrapper_type{m_value}, m_value{std::forward<Args>(args)...}
{ }


template <typename T, typename Lock>
inline
type_lock_wrapper<T, Lock, if_default_ctor<T>>::
type_lock_wrapper()
    : lock_wrapper_type{m_value}
{ }

template <typename T, typename Lock>
template <typename... Args>
inline
type_lock_wrapper<T, Lock, if_default_ctor<T>>::
type_lock_wrapper(Args&&... args)
    : lock_wrapper_type{m_value}, m_value{std::forward<Args>(args)...}
{ }
    
    
} /* namespace elib */
#endif /* ELIB__LOCK_WRAPPER_H */
