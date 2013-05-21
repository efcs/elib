#include "elib/lock.h"
#include "_lock.h"

namespace elib {
	
template <typename LockT>
UniqueLock<LockT>::UniqueLock(LockT &lock) 
					: m_impl(new _elib::UniqueLockImpl<LockT>(lock))
{ }
					
template <typename LockT>
UniqueLock<LockT>::UniqueLock(LockT &lock, try_lock_t& t)
					: m_impl(new _elib::UniqueLockImpl<LockT>(lock, t)) 
{ }

template <typename LockT>
UniqueLock<LockT>::UniqueLock(LockT &lock, defer_lock_t& t)
					: m_impl(new _elib::UniqueLockImpl<LockT>(lock, t)) 
{ }

template <typename LockT>
UniqueLock<LockT>::~UniqueLock() { }

template <typename LockT>
void UniqueLock<LockT>::lock()
{
	m_impl->lock();
}

template <typename LockT>
bool UniqueLock<LockT>::try_lock()
{
	return m_impl->try_lock();
}

template <typename LockT>
void UniqueLock<LockT>::unlock()
{
	m_impl->unlock();
}

template <typename LockT>
void UniqueLock<LockT>::release()
{
	m_impl->release();
}

template <typename LockT>
bool UniqueLock<LockT>::owns_lock() const
{
	return m_impl->owns_lock();
}

template <typename LockT>
LockT *UniqueLock<LockT>::get_lock() const 
{
	return m_impl->get_lock();
}


/* force templates instant's into the library */
template class LockGuard<std::mutex>;
template class UniqueLock<std::mutex>;
	

} /* namespace elib */