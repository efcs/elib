#include "elib/lock.h"
#include "impl/rw_lock_impl.h"

namespace elib {
    
rw_lock::rw_lock()
    : m_impl(new detail::rw_lock_impl())
{
}

rw_lock::~rw_lock()
{
    delete m_impl;
}

void 
rw_lock::read_lock()
{
    m_impl->read_lock();
}

void 
rw_lock::read_unlock()
{
    m_impl->read_unlock();
}

bool 
rw_lock::try_read_lock()
{
    return m_impl->try_read_lock();
}
    
void 
rw_lock::write_lock()
{
    m_impl->write_lock();
}

void 
rw_lock::write_unlock()
{
    m_impl->write_unlock();
}

bool 
rw_lock::try_write_lock()
{
    return m_impl->try_write_lock();
}
    
rw_read_lock
rw_lock::as_read_lock()
{
    return rw_read_lock(*this);
}
    
rw_write_lock
rw_lock::as_write_lock()
{
    return rw_write_lock(*this);
}


////////////////////////////////////////////////////////////////////////////////
//                            read_lock                                             
////////////////////////////////////////////////////////////////////////////////


rw_read_lock::rw_read_lock(rw_lock &lock)
    : m_lock(lock)
{ 
}
 
void
rw_read_lock::lock()
{
    m_lock.read_lock();
}

void
rw_read_lock::unlock()
{
    m_lock.read_unlock();
}

bool
rw_read_lock::try_lock()
{
    return m_lock.try_read_lock();
}


////////////////////////////////////////////////////////////////////////////////
//                            write_lock                                             
////////////////////////////////////////////////////////////////////////////////


rw_write_lock::rw_write_lock(rw_lock &lock)
    : m_lock(lock)
{ 
}
 
void
rw_write_lock::lock()
{
    m_lock.write_lock();
}

void
rw_write_lock::unlock()
{
    m_lock.write_unlock();
}

bool
rw_write_lock::try_lock()
{
    return m_lock.try_write_lock();
}

} /* namespace elib */