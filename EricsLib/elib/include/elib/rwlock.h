#ifndef ELIB_RWLOCK_H
#define ELIB_RWLOCK_H

#include "lock.h"
#include <memory>

namespace elib {

namespace _elib { 
class RWLockImpl;
}

class ReadLock;
class WriteLock;

class RWLock
{
public:
	RWLock();
	~RWLock();
	
	void read_lock();
	bool try_read_lock();
	void read_unlock();
	
	void write_lock();
	bool try_write_lock();
	void write_unlock();
	
	ReadLock as_read_lock();
	WriteLock as_write_lock();
private:
	std::shared_ptr<_elib::RWLockImpl> m_impl;
};


class ReadLock : public LockInterface
{
private:
	friend class RWLock;
public:
	~ReadLock() { }
	
	inline void lock() { 
		m_lock.read_lock(); 
	}
	
	inline bool try_lock() { 
		return m_lock.try_read_lock(); 
	}
	
	inline void unlock() {
		m_lock.read_unlock();
	}
	
private:
	ReadLock(RWLock rw_lock) : m_lock(rw_lock) { }
	RWLock m_lock;
};


class WriteLock : public LockInterface
{
private:
	friend class RWLock;
public:
	~WriteLock() { }
	
	inline void lock() { 
		m_lock.write_lock();
	}
	
	inline bool try_lock() { 
		return m_lock.try_write_lock(); 
	}
	
	inline void unlock() {
		m_lock.write_unlock();
	}
private:
	WriteLock(RWLock rw_lock) : m_lock(rw_lock) { }
	RWLock m_lock;
};

	
} /* namespace elib */
#endif /* ELIB_RWLOCK_H */