#ifndef _LOCK_H
#define _LOCK_H

#include "elib/lock.h"
#include <system_error>

#define OP_NOT_PERMIT std::errc::operation_not_permitted

#define VERIFY_LOCK() do { \
	if (m_released) \
		throw new std::system_error(std::make_error_code(OP_NOT_PERMIT)); \
	} while(false) 

namespace elib {
namespace _elib {

	
template <typename LockT>
class UniqueLockImpl 
{
public:
	explicit UniqueLockImpl(LockT &lock) : m_lock(lock), m_released(false) {
		m_lock.lock();
		m_owns_lock = true;
	}
	
	UniqueLockImpl(LockT &lock, defer_lock_t t) : m_lock(lock), 
					m_released(false), m_owns_lock(false) { } 
					
	UniqueLockImpl(LockT &lock, try_lock_t t) : m_lock(lock), m_released(false) {
		m_owns_lock = m_lock.try_lock();
	}
	
	~UniqueLockImpl() {
		if (m_owns_lock)
			m_lock.unlock();
	}
	
	void lock() {
		VERIFY_LOCK();
		m_lock.lock();
		m_owns_lock = true;
	}
	
	bool try_lock() {
		VERIFY_LOCK();
		m_owns_lock = m_lock.try_lock();
		return m_owns_lock;
	}
	
	void unlock() {
		VERIFY_LOCK();
		if (!m_owns_lock) {
			throw new std::system_error(std::make_error_code(OP_NOT_PERMIT));			
		} else {
			m_owns_lock = false;
			m_lock.unlock();
		}
	}
	
	void release() {
		m_released = true;
		m_owns_lock = false;
	}
	
	bool owns_lock() const { 
		return m_owns_lock;
	}
	
	LockT *get_lock() const {
		VERIFY_LOCK();
		return &m_lock;
	}
private:
	bool m_owns_lock, m_released;
	LockT m_lock;
	DISALLOW_COPY_AND_ASSIGN(UniqueLockImpl);
};


} /* namespace _elib */
} /* namespace elib */
#endif /* _LOCK_H */