#ifndef _RWLOCK_H
#define _RWLOCK_H

#include <mutex>
#include <thread>

namespace elib {
namespace _elib { 

	
class RWLockImpl 
{
public:
	RWLockImpl() : m_curr_group(0), m_next_group(0)
	~RWLockImpl();
	
	void read_lock();
	bool try_read_lock();
	void read_unlock();
	
	void write_lock();
	bool try_write_lock();
	void write_unlock();
private:
	using pair_t = std::pair<std::thread::id, unsigned int>;
	std::mutex m_lock;
	std::map<> m_have_lock;
	std::map<
	unsigned int m_curr_group, m_next_group;
};


} /* namespace _elib */
} /* namespace elib */
#endif /* _RWLOCK_H */