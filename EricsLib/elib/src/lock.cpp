#include "elib/lock.h"
#include "_lock.h"
#include "_multilock.h"
#include "_uniquelock.h"

namespace elib {

Mutex::Mutex() : m_impl(new _elib::WaitLockImpl()) { }
Mutex::~Mutex() { }
void Mutex::lock() { m_impl->lock(); }
bool Mutex::try_lock() { return m_impl->try_lock(); }
void Mutex::unlock() { m_impl->unlock(); }

SpinLock::SpinLock() : m_impl(new _elib::SpinLockImpl()) { }
SpinLock::~SpinLock() { }
void SpinLock::lock() { m_impl->lock(); }
bool SpinLock::try_lock() { return m_impl->try_lock(); }
void SpinLock::unlock() { m_impl->unlock(); }

template<typename LockT>
inline
MultiLock<LockT>::MultiLock(unsigned int size) : 
				m_impl(new _elib::MultiLockImpl<LockT>(size)) { }
				
template<typename LockT>
inline
MultiLock<LockT>::~MultiLock() { }

template<typename LockT>
inline
unsigned int MultiLock<LockT>::up() { return m_impl->up(); }

template<typename LockT>
inline
unsigned int MultiLock<LockT>::down() { return m_impl->down(); }

template<typename LockT>
inline
void MultiLock<LockT>::lock() { m_impl->lock(); }

template<typename LockT>
inline
bool MultiLock<LockT>::try_lock() { return m_impl->try_lock(); }

template<typename LockT>
inline
void MultiLock<LockT>::unlock() { m_impl->unlock(); }

template<typename LockT>
inline
unsigned int MultiLock<LockT>::size() const { return m_impl->size(); }

template<typename LockT>
inline
unsigned int MultiLock<LockT>::available() const { return m_impl->available(); }

template<typename LockT>
inline
unsigned int MultiLock<LockT>::taken() const { return m_impl->taken(); }

template<typename LockT>
inline
UniqueLock<LockT>::UniqueLock(LockT &lock, bool try_lock) : 
					m_impl(new _elib::UniqueLockImpl<LockT>(lock, try_lock)) { }

template<typename LockT>
inline
UniqueLock<LockT>::~UniqueLock() { }

template<typename LockT>
inline
void UniqueLock<LockT>::lock() { m_impl->lock(); }

template<typename LockT>
inline
bool UniqueLock<LockT>::try_lock() { return m_impl->try_lock(); }

template<typename LockT>
inline
void UniqueLock<LockT>::unlock() { m_impl->unlock(); }

template<typename LockT>
inline
void UniqueLock<LockT>::release() { m_impl->release(); }

template<typename LockT>
inline
bool UniqueLock<LockT>::owns_lock() const { return m_impl->owns_lock(); }


/* force template classes into libraries */
template class MultiLock<Mutex>;
template class MultiLock<SpinLock>;

template class LockGuard<Mutex>;
template class LockGuard<SpinLock>;
template class LockGuard<MultiLock<Mutex>>;
template class LockGuard<MultiLock<SpinLock>>;

template class UniqueLock<Mutex>;
template class UniqueLock<SpinLock>;
template class UniqueLock<MultiLock<Mutex>>;
template class UniqueLock<MultiLock<SpinLock>>;

} /* namespace elib */