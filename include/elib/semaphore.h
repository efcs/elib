#ifndef ELIB_SEMAPHORE_H
#define ELIB_SEMAPHORE_H

namespace elib {
    

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

    
} /* namespace elib */
#endif /* ELIB_SEMAPHORE_H */