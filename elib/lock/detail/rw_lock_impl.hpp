#ifndef ELIB_LOCK_RW_LOCK_IMPL_HPP
#define ELIB_LOCK_RW_LOCK_IMPL_HPP

#include <mutex>
#include <condition_variable>
#include <list>

static_assert(ATOMIC_INT_LOCK_FREE == 2, "rw_lock is not lock free");

namespace elib {
namespace lock {
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
    
    class request_group {
    public:
        inline
        request_group()
        { }
        
        inline explicit 
        request_group(lock_type_e ltype)
            : lock_type(ltype)
        { }
        
        /* read, write lock request */
        lock_type_e lock_type;
        /* currently held/requested locks */
        unsigned lock_count{0};
        /* is this group allowed to have the lock ? */
        bool allowed = false;
        /* this condition variable is used to notify the group members,
         * when the group is allowed to run */
        std::condition_variable allowed_cv{ };
    private:
        request_group(const request_group&);
        request_group& operator=(const request_group&);
    };
    
    typedef std::unique_lock<std::mutex> unique_lock;
    typedef std::list<request_group> list_type;

public:
    /* these functions lock */
    void lock(lock_type_e ltype);
    void unlock();
    bool try_lock(lock_type_e ltype);
    
    /* _func requires that the lock already be held */
    request_group &
    _process_request(lock_type_e ltype);
    
    bool _can_imm_schedule(lock_type_e ltype);
    
    void _advance_group();
private:
    std::mutex m_lock;
    list_type m_groups;
private:
    rw_lock_impl(const rw_lock_impl&);
    rw_lock_impl& operator=(const rw_lock_impl&);
    friend class test_rw_lock_impl;
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
    req_group.lock_count++;
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
    
    /* fail if we don't get the lock, or can't 
     * schedule right away */
    if (! ulock || ! _can_imm_schedule(ltype))
        return false;
    
    request_group & req_group = _process_request(ltype);

    req_group.lock_count++;
    
    /* since we already checked if we could schedule right away,
     * we can just return true */
    return true;
}

inline void
rw_lock_impl::unlock()
{
    unique_lock ulock(m_lock);
    
    request_group & req_group = m_groups.front();
    
    --req_group.lock_count;
    
    /* All members of a group have unlocked,
     * advance to next group */
    if (req_group.lock_count == 0) {
        m_groups.erase(m_groups.begin());
        _advance_group();
    }
}

inline rw_lock_impl::request_group &
rw_lock_impl::_process_request(lock_type_e ltype)
{
    /* special case: if the last group a read_lock group, 
     * and this is a read_lock request, 
     * then stick it in the current group, and return the lock */
    if (ltype == lock_type_e::read && m_groups.size() > 0 &&
        m_groups.back().lock_type == lock_type_e::read) {
        return m_groups.back();
    }
    
    /* Otherwise, we we must have one of
     *  a) m_groups is empty 
     *  b) back() is write lock, req is read lock
     *  c) the request is a write lock 
     * 
     * so construct a new group at the back */
    m_groups.emplace_back(ltype);
    
    /* if we have 1 group, then we were just empty
     * so allow this new group to run */
    if (m_groups.size() == 1)
        _advance_group();
    
    /* finally, return the group data */
    return m_groups.back();
}

inline bool
rw_lock_impl::_can_imm_schedule(lock_type_e ltype)
{
    /* if the lock is currently held by nobody,
     * then we can schedule */
    bool good = m_groups.size() == 0;
    
    /* otherwise, we can schedule, when we get a read request,
     * and there is a reader group running with no groups waiting,
     * then we can schedule it in the current group */
    good |= (m_groups.size() == 1 && 
             ltype == lock_type_e::read &&
             m_groups.front().lock_type == ltype);
    
    return good;
}


inline void
rw_lock_impl::_advance_group()
{
    /* can't advance on no groups,
     * don't need to advance if already allowed */
    if (m_groups.size() == 0 || m_groups.front().allowed)
        return;
    
    request_group & req_g = m_groups.front();
    
    /* set the group allowed flag, and notify waiting threads */
    req_g.allowed = true;
    req_g.allowed_cv.notify_all();
}

} /* namespace detail */
} /* namespace lock */
} /* namespace elib */
#endif /* ELIB_LOCK_RW_LOCK_IMPL_HPP */