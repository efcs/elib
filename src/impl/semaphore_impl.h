#ifndef ELIB_SEMAPHORE_IMPL_H
#define ELIB_SEMAPHORE_IMPL_H


#include <atomic>


class test_semaphore_impl;


namespace elib {
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
    unsigned m_max;
    std::atomic_uint m_count;
private:
    semaphore_impl(const semaphore_impl&);
    semaphore_impl& operator=(const semaphore_impl&);
    friend class ::test_semaphore_impl;
}; 


////////////////////////////////////////////////////////////////////////////////
//                            definition                                                 
////////////////////////////////////////////////////////////////////////////////


inline
semaphore_impl::semaphore_impl(unsigned count)
    : m_max(count), m_count(count)
{
}

inline void
semaphore_impl::lock()
{
    unsigned old_val;
    
    old_val = m_count;
    while (true) {
        if (old_val == 0)
            continue;
        if (m_count.compare_exchange_weak(old_val, old_val-1))
            return;
    }
    /* shouldn't be here */
    throw 1;
}

inline void
semaphore_impl::unlock()
{
    ++m_count;
}

inline bool
semaphore_impl::try_lock()
{
    unsigned old_val;
    
    old_val = m_count;
    while (true) {
        if (old_val == 0)
            return false;
        
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
} /* namespace elib */
#endif /* ELIB_SEMAPHORE_IMPL_H */