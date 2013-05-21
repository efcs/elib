#ifndef _SEMAPHORE_H
#define _SEMAPHORE_H

#include <mutex>

namespace elib {
namespace _elib {
	
using lock_guard = std::unique_lock<std::mutex>;

class SemaphoreImpl 
{
public:
	SemaphoreImpl(unsigned int size) : m_size(size), m_count(size)
	{ }
	
	unsigned int down() {
		lock_guard nlock(m_next_lock);
		/* spin */
		while (m_count == 0)
			;
		lock_guard obj_lock(m_lock);
		--m_count;
		return (m_count + 1);
	}
	
	bool try_down(unsigned int &resource) {
		lock_guard nlock(m_next_lock, std::try_to_lock);
		if (nlock && m_count > 0) {
			lock_guard obj_lock(m_lock);
			resource = m_count;
			--m_count;
			return true;
		}
		return false;
	}
	
	void up() {
		lock_guard lock(m_lock);
		++m_count;
	}
	
	unsigned int size() const { 
		return m_size; 
	}
	
	unsigned int available() const {
		return m_count;
	}
	
	unsigned int taken() const { 
		return m_size - m_count;
	}

private:
	std::mutex m_lock, m_next_lock;
	unsigned int m_size, m_count;
};


} /* namespace _elib */
} /* namespace elib */
#endif /* _SEMAPHORE_H */