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
#endif /* ELIB_RW_LOCK_H */