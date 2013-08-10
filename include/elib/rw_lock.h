#ifndef ELIB_RW_LOCK_H
#define ELIB_RW_LOCK_H

namespace elib {
    

namespace detail { class rw_lock_impl; }


class rw_read_lock;
class rw_write_lock;


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
    
    /* get read lock adapter */
    rw_read_lock 
    as_read_lock();
    /* get write lock adapter */
    rw_write_lock 
    as_write_lock();
private:
    /* PIMPL */
    detail::rw_lock_impl* m_impl;
private:
    /* NO COPY & ASSIGN */
    rw_lock(const rw_lock&);
    rw_lock& operator=(const rw_lock&);
};


/* this can be used as a adapter to gain the
 * lock interface for the read_lock commands.
 * ie rw_read_lock -> rw_lock
 *    lock()       -> read_lock()
 *    unlock()     -> read_unlock()
 *    try_lock()   -> try_read_lock() 
 * 
 * This is meant for use with std::lock_guard && std::unique_lock */
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

/* Same as rw_read_lock, but obviously for writing */
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
#endif /* ELIB_RW_LOCK_H */