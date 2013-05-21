#ifndef ELIB_RWLOCK_H
#define ELIB_RWLOCK_H

#include <memory>

namespace elib {


namespace _elib { 
class RWLockImpl;
}


class RWLock 
{
public:
	RWLock();
	RWLock(unsigned int reader_size);
	~RWLock();
	
	void read_lock();
	bool try_read_lock();
	void read_unlock();
	
	void write_lock();
	bool try_write_lock();
	void write_unlock();
private:
	std::shared_ptr<_elib::RWLockImpl> m_impl;
}
	
} /* namespace elib */
#endif /* ELIB_RWLOCK_H */