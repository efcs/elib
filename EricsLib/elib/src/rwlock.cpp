#include "elib/rwlock.h"
#include "_rwlock.h"
#include "elib/lock.h"

namespace elib {
	
	
RWLock::RWLock() : m_impl(new _elib::RWLockImpl())
{
}

RWLock::~RWLock()
{
}

void RWLock::read_lock()
{
	m_impl->read_lock();
}

bool RWLock::try_read_lock()
{
	return m_impl->try_read_lock();
}

void RWLock::read_unlock()
{
	m_impl->read_unlock();
}

void RWLock::write_lock()
{
	m_impl->write_lock();
}

bool RWLock::try_write_lock()
{
	return m_impl->try_write_lock();
}

void RWLock::write_unlock()
{
	m_impl->write_unlock();
}

ReadLock RWLock::as_read_lock() 
{
	return ReadLock(*this);
}

WriteLock RWLock::as_write_lock() 
{
	return WriteLock(*this);
}


/* force instantiation of UniqueLock for ReadLock && WriteLock */
template class UniqueLock<ReadLock>;
template class UniqueLock<WriteLock>;
	

} /* namespace elib */