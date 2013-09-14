#ifndef ELIB_LOCK_SEMAPHORE_HPP
#define ELIB_LOCK_SEMAPHORE_HPP

namespace elib {
namespace lock {
    

namespace detail { class semaphore_impl; }
    
    
class semaphore {
public:
    semaphore(unsigned count);
    ~semaphore();
    
    /* lock interface */
    void lock();
    void unlock();
    bool try_lock();
    
    unsigned count() const;
    unsigned max() const;
private:
    detail::semaphore_impl* m_impl;
private:
    semaphore(const semaphore&);
    semaphore& operator=(const semaphore&);
};


} /* namespace lock */
} /* namespace elib */
#endif /* ELIB_LOCK_SEMAPHORE_HPP */