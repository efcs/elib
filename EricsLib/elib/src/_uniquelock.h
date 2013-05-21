#ifndef _UNIQUELOCK_H
#define _UNIQUELOCK_H

namespace elib {
namespace _elib {
	
template <typename LockT>
class UniqueLockImpl 
{
public:
	UniqueLockImpl(LockT &lock, bool try_lock) : m_lock(lock) {
		m_owns_lock = false;
		m_lock_released = false;
		if (try_lock)
			this->try_lock();
		else
			this->lock();
	}
	
	~UniqueLockImpl() {
		if (m_owns_lock)
			m_lock.unlock();
	}
	
	void lock() {
		if (m_lock_released) 
			return;
		m_lock.lock();
		m_owns_lock = true;
	}
	
	bool try_lock() {
		if (m_lock_released)
			return false;
		m_owns_lock = m_lock.try_lock();
		return m_owns_lock;
	}
	
	void unlock() { 
		if (m_lock_released)
			return;
		m_lock.unlock();
		m_owns_lock = false;
	}
	
	void release() {
		m_lock_released = true;
		m_owns_lock = false;
	}
	
	bool owns_lock() const {
		return m_owns_lock;
	}
	
	explicit operator bool() const {
		return m_owns_lock;
	}
	
private:
	bool m_owns_lock, m_lock_released;
	LockT &m_lock;
};
	

} /* namespace _elib */	
} /* namespace elib */
#endif /* _UNIQUELOCK_H */