#ifndef ELIB_LOCK_SEMAPHORE_IMPL_H
#define ELIB_LOCK_SEMAPHORE_IMPL_H


#include <atomic>
#include <cassert>


namespace elib {
namespace lock {
namespace detail {
    
    
class semaphore_impl {
public:
    semaphore_impl(unsigned count);
    ~semaphore_impl() = default;
    
    void lock();
    void unlock();
    bool try_lock();
    
    unsigned count() const;
    unsigned max() const;

private:
    /* the max number of resources
     * m_count is initalized to this */
    unsigned m_max;
    /* the number of resources currently left */
    std::atomic_uint m_count;
private:
    semaphore_impl(const semaphore_impl&);
    semaphore_impl& operator=(const semaphore_impl&);
}; 


////////////////////////////////////////////////////////////////////////////////
//                            definition                                                 
////////////////////////////////////////////////////////////////////////////////


inline
semaphore_impl::semaphore_impl(unsigned count)
    : m_max(count), m_count(count)
{
    /* just make sure that std::atomic_uint is lock free */
    if (m_count.is_lock_free() == false)
        throw 1;
}

inline void
semaphore_impl::lock()
{
    unsigned old_val;
    
    old_val = m_count;
    while (true) {
        /* if semaphore empty, then spin */
        if (old_val == 0)
            continue;
        /* otherwise, old_value is still the same, then take the lock
         * note: on failure old_val is set to the current value of m_count */
        if (m_count.compare_exchange_weak(old_val, old_val-1))
            return;
    }
    /* shouldn't be here */
    throw 1;
}

inline void
semaphore_impl::unlock()
{
    m_count.fetch_add(1);
}

inline bool
semaphore_impl::try_lock()
{
    unsigned old_val;
    
    old_val = m_count.load();
    while (true) {
        /* fail if semaphore is empty */
        if (old_val == 0)
            return false;
        /* if old_val is still the same, then take the lock */
        if (m_count.compare_exchange_strong(old_val, old_val-1))
            return true;
    }
    throw 1;
}

inline unsigned 
semaphore_impl::count() const
{
    return m_count;
}

inline unsigned 
semaphore_impl::max() const
{
    return m_max;
}


} /* namespace detail */  
} /* namespace lock */
} /* namespace elib */
#endif /* ELIB_LOCK_SEMAPHORE_IMPL_H */