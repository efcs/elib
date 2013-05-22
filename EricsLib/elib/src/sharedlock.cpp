#include "elib/sharedlock.h"
#include "_sharedlock.h"
#include "elib/lock.h"

#include <iostream>

namespace elib {
	
	
SharedLock::SharedLock() : m_impl(new _elib::SharedLockImpl())
{
	this->init();
}

SharedLock::~SharedLock()
{
}

void SharedLock::lock()
{
	m_impl->lock();
#ifndef NDEBUG
	m_impl->verify();
#endif
}

bool SharedLock::try_lock()
{
	return m_impl->try_lock();
#ifndef NDEBUG
	m_impl->verify();
#endif
}

void SharedLock::unlock()
{
	m_impl->unlock();
#ifndef NDEBUG
	m_impl->verify();
#endif
}

void SharedLock::lock_shared()
{
	m_impl->lock_shared();
#ifndef NDEBUG
	m_impl->verify();
#endif
}

bool SharedLock::try_lock_shared()
{
	return m_impl->try_lock_shared();
#ifndef NDEBUG
	m_impl->verify();
#endif
}

void SharedLock::unlock_shared()
{
	m_impl->unlock_shared();
#ifndef NDEBUG
	m_impl->verify();
#endif
}

SharedOnlyLock &SharedLock::as_shared_only_lock() 
{
	return m_impl->as_shared_only_lock();
}


void SharedLock::init()
{
	m_impl->m_shared_only_lock = new SharedOnlyLock(*this);
}

SharedOnlyLock::SharedOnlyLock(SharedLock &s_lock) : m_lock(s_lock) 
{ 
}

SharedOnlyLock::~SharedOnlyLock() 
{ 
}

void SharedOnlyLock::lock() 
{
	m_lock.lock_shared();
}

bool SharedOnlyLock::try_lock() 
{
	return m_lock.try_lock_shared();
}

void SharedOnlyLock::unlock() 
{
	m_lock.unlock_shared();
}


/* force template creation */
template class LockGuard<SharedLock>;
template class LockGuard<SharedOnlyLock>;
template class UniqueLock<SharedLock>;
template class UniqueLock<SharedOnlyLock>;


} /* namespace elib */