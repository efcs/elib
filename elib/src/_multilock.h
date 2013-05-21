#ifndef _MULTILOCK_H
#define _MULTILOCK_H


namespace elib {
namespace _elib {
	
template <typename LockT>
class MultiLockImpl
{
public:
	explicit MultiLockImpl(unsigned int size) : m_size(size), m_count(size) { }
	
	~MultiLockImpl() { }
	
	inline unsigned int down() {
		register unsigned int val;
		m_next_lock.lock();
		/* by using an "empty lock", we can switch between a spining and yeilding
		 * version of the multilock between spining/yielding */ 
		m_empty_lock.lock();
		m_lock.lock();
		val = m_count;
		--m_count;
		if (m_count != 0)
			m_empty_lock.unlock();
		m_lock.unlock();
		m_next_lock.unlock();
		return val;
	}
	
	inline unsigned int up() {
		unsigned int val;
		m_lock.lock();
		val = m_count;
		m_empty_lock.unlock();
		m_lock.unlock();
		return val;
	}
	
	inline void lock() {
		this->down();
	}
	
	inline bool try_lock() {
		if (!m_next_lock.try_lock())
			return false;
		if (! m_empty_lock.try_lock()) {
			m_next_lock.unlock();
			return false;
		}
		if (! m_lock.try_lock()) {
			m_empty_lock.unlock();
			m_next_lock.unlock();
			return false;
		}
		/* we hold proper locks */
		--m_count;
		if (m_count != 0)
			m_empty_lock.unlock();
		m_lock.unlock();
		m_next_lock.unlock();
		return true;
	}
	
	inline void unlock() {
		up();
	}
	
	unsigned int size() const { return m_size; }
	unsigned int available() const { return m_count; }
	unsigned int taken() const { return m_size - m_count; }
private:
	LockT m_lock, m_next_lock, m_empty_lock;
	unsigned int m_size, m_count;
	DISALLOW_COPY_AND_ASSIGN(MultiLockImpl);
};

	
} /* namespace _elib */
} /* namespace elib */
#endif /* _MULTILOCK_H */