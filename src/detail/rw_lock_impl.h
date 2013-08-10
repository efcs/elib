#ifndef ELIB_RW_LOCK_IMPL_H
#define ELIB_RW_LOCK_IMPL_H

#include <mutex>
#include <condition_variable>
#include <list>

class test_rw_lock_impl;

namespace elib {
namespace detail { 


class rw_lock_impl {
public:
    rw_lock_impl() = default;
    ~rw_lock_impl() = default;
    
    void read_lock();
    void read_unlock();
    bool try_read_lock();
    
    void write_lock();
    void write_unlock();
    bool try_write_lock();
    
public:
    enum class lock_type_e {
        read,
        write
    };
    
    enum class request_e {
        lock,
        unlock,
        try_lock
    };
    
    class request_group {
    public:
        inline
        request_group()
        { }
        
        inline explicit 
        request_group(lock_type_e ltype)
            : lock_type(ltype)
        { }
        
        lock_type_e lock_type;
        unsigned group_size{0};
        bool allowed = false;
        std::condition_variable allowed_cv{ };
    private:
        request_group(const request_group&);
        request_group& operator=(const request_group&);
    };
    
    typedef std::unique_lock<std::mutex> unique_lock;
    typedef std::list<request_group> list_type;

    friend list_type;
private:
    void lock(lock_type_e ltype);
    void unlock();
    bool try_lock(lock_type_e ltype);
    
    request_group &
    _process_request(lock_type_e ltype);
    
    bool _can_imm_scedule(lock_type_e ltype);
    
    void _advance_group();
private:
    std::mutex m_lock;
    list_type m_groups;
private:
    rw_lock_impl(const rw_lock_impl&);
    rw_lock_impl& operator=(const rw_lock_impl&);
    friend class ::test_rw_lock_impl;
};


////////////////////////////////////////////////////////////////////////////////
//                             definition                                       
////////////////////////////////////////////////////////////////////////////////


inline void 
rw_lock_impl::read_lock()
{
    lock(lock_type_e::read);
}

inline void 
rw_lock_impl::read_unlock()
{
    unlock();
}

inline bool 
rw_lock_impl::try_read_lock()
{
    return try_lock(lock_type_e::read);
}
    
inline void 
rw_lock_impl::write_lock()
{
    lock(lock_type_e::write);
}

inline void 
rw_lock_impl::write_unlock()
{
    unlock();
}

inline bool 
rw_lock_impl::try_write_lock()
{
    return try_lock(lock_type_e::write);
}

inline void
rw_lock_impl::lock(lock_type_e ltype)
{
    unique_lock ulock(m_lock);
    request_group & req_group = _process_request(ltype);
    /* add a group member */
    req_group.group_size++;
    /* try and skip waiting */
    if (req_group.allowed)
        return;
    /* wait to be notified */
    req_group.allowed_cv.wait(ulock, [&](){ return req_group.allowed; });
}

inline bool
rw_lock_impl::try_lock(lock_type_e ltype)
{
    unique_lock ulock(m_lock, std::try_to_lock);
    
    if (! ulock || ! _can_imm_scedule(ltype))
        return false;
    
    request_group & req_group = _process_request(ltype);

    req_group.group_size++;
    
    return true;
}

inline void
rw_lock_impl::unlock()
{
    unique_lock ulock(m_lock);
    
    request_group & req_group = m_groups.front();
    --req_group.group_size;
    
    if (req_group.group_size == 0) {
        m_groups.erase(m_groups.begin());
        _advance_group();
    }
}

inline rw_lock_impl::request_group &
rw_lock_impl::_process_request(lock_type_e ltype)
{
    if (ltype == lock_type_e::read && m_groups.size() > 0 &&
        m_groups.back().lock_type == lock_type_e::read) {
        return m_groups.back();
    }
    
    m_groups.emplace_back(ltype);
    
    if (m_groups.size() == 1)
        _advance_group();
    
    return m_groups.back();
}

inline bool
rw_lock_impl::_can_imm_scedule(lock_type_e ltype)
{
    bool good = m_groups.size() == 0;
    good |= (m_groups.size() == 1 && 
             ltype == lock_type_e::read &&
             m_groups.front().lock_type == ltype);
    
    return good;
}


inline void
rw_lock_impl::_advance_group()
{
    if (m_groups.size() == 0 || m_groups.front().allowed)
        return;
    
    request_group & req_g = m_groups.front();
    req_g.allowed = true;
    req_g.allowed_cv.notify_all();
}

} /* namespace detail */    
} /* namespace elib */
#endif /* ELIB_RW_LOCK_IMPL_H */