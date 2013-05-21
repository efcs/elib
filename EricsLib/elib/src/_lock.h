#ifndef _LOCK_H
#define _LOCK_H

#include <atomic>
#include <thread>

namespace elib {
namespace _elib {

template <bool sleep>
class _LockImpl
{
public:
	_LockImpl() : m_atomic(ATOMIC_FLAG_INIT) { }
	
	~_LockImpl() { }
	
	void lock() {
		while (m_atomic.test_and_set()) {
			if (sleep) std::this_thread::yield();
		}
	}
	
	bool try_lock() {
		return (! m_atomic.test_and_set());
	}
	
	void unlock() {
		m_atomic.clear();
	}
	
private:
	std::atomic_flag m_atomic;
	DISALLOW_COPY_AND_ASSIGN(_LockImpl);
};

/* force compilation */
template class _LockImpl<true>;
template class _LockImpl<false>;


} /* namespace _elib */
} /* namespace elib */
#endif /* _LOCK_H */