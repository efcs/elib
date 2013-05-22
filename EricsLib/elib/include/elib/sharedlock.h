#ifndef ELIB_SHAREDLOCK_H
#define ELIB_SHAREDLOCK_H

#include "lock.h"
#include <memory>

namespace elib {

	
namespace _elib { class SharedLockImpl; }

class SharedOnlyLock;

class SharedLock : public LockInterface
{
public:
	SharedLock();
	~SharedLock();
	
	void lock();
	bool try_lock();
	void unlock();
	
	void lock_shared();
	bool try_lock_shared();
	void unlock_shared();
	
	SharedOnlyLock &as_shared_only_lock();
private:
	void init();
	std::shared_ptr<_elib::SharedLockImpl> m_impl;
};


class SharedOnlyLock : public LockInterface
{
private:
	friend class SharedLock;
	SharedOnlyLock(SharedLock &lock);
public:
	~SharedOnlyLock();
	void lock();
	bool try_lock();
	void unlock();
private:
	SharedLock &m_lock;
};

	
} /* namespace elib */
#endif /* ELIB_SHAREDLOCK_H */