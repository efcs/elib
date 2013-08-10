#ifndef ELIB_LOCK_H
#define ELIB_LOCK_H

#include "lock_fwd.h"

#include <mutex>

namespace elib {
    
 
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



class rw_lock {
public:
    rw_lock();
    ~rw_lock();
    
    void read_lock();
    void read_unlock();
    bool try_read_lock();
    
    void write_lock();
    void write_unlock();
    bool try_write_lock();
    
    rw_read_lock 
    as_read_lock();
    
    rw_write_lock 
    as_write_lock();
private:
    detail::rw_lock_impl* m_impl;
private:
    rw_lock(const rw_lock&);
    rw_lock& operator=(const rw_lock&);
};


class rw_read_lock {
private:
    friend rw_lock;
    rw_read_lock(rw_lock &lock);
public:
    void lock();
    void unlock();
    bool try_lock();
private:
    rw_lock & m_lock;
};


class rw_write_lock {
private:
    friend rw_lock;
    rw_write_lock(rw_lock & lock);
public:
    void lock();
    void unlock();
    bool try_lock();
private:
    rw_lock & m_lock;
};


} /* namespace elib */
#endif /* ELIB_LOCK_H */