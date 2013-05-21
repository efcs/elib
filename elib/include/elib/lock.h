#ifndef ELIB_LOCK_H
#define ELIB_LOCK_H

#include "elib/commondef.h"

#include <cstdint>
#include <memory>
#include <atomic>

namespace elib {

/* forward declare private implementations */
namespace _elib {
template <bool v> class _LockImpl;
template <typename LockT> class MultiLockImpl;
template <typename LockT> class UniqueLockImpl;

using SpinLockImpl = _LockImpl<false>;
using WaitLockImpl = _LockImpl<true>;
} /* namespace _elib */


class LockInterface
{
public:
	virtual ~LockInterface() { }
	virtual void lock() = 0;
	virtual bool try_lock() = 0;
	virtual void unlock() = 0;
};


class MultiLockInterface : public LockInterface
{
public:
	virtual ~MultiLockInterface() { }
	/* lock interface for use with LockGuard() */
	virtual void lock() = 0;
	virtual bool try_lock() = 0;
	virtual void unlock() = 0;
	/* a more common interface */
	virtual unsigned int down() = 0;
	virtual unsigned int up() = 0;
	/* total size, # remaining from size, # taken from size */
	virtual unsigned int size() const = 0;
	virtual unsigned int available() const = 0;
	virtual unsigned int taken() const = 0;
};


class Mutex : public LockInterface 
{
public:
	Mutex();
	~Mutex();
	void lock();
	bool try_lock();
	void unlock();
private:
	std::shared_ptr<_elib::WaitLockImpl> m_impl;
};


class SpinLock : public LockInterface
{
public:
	SpinLock();
	~SpinLock();
	void lock();
	bool try_lock();
	void unlock();
private:
	std::shared_ptr<_elib::SpinLockImpl> m_impl;
};


/* LockT must implement LockInterface */
template <typename LockT=SpinLock>
class MultiLock : public MultiLockInterface
{
public:
	explicit MultiLock(unsigned int size);
	~MultiLock();
	
	void lock();
	bool try_lock();
	void unlock();
	
	unsigned int down();
	unsigned int up();
	
	unsigned int size() const;
	unsigned int available() const;
	unsigned int taken() const;
private:
	std::shared_ptr<_elib::MultiLockImpl<LockT>> m_impl;
};

/* LockT must implement LockInterface */
template<typename LockT>
class LockGuard
{
public:
	LockGuard(LockT &lock) : m_lock(lock) { }
	~LockGuard() { m_lock.unlock(); }
private:
	LockT &m_lock;
	DISALLOW_COPY_AND_ASSIGN(LockGuard);
};


template<typename LockT>
class UniqueLock : LockInterface
{
public:
	UniqueLock(LockT &lock, bool try_lock=false);
	~UniqueLock();
	
	void lock();
	bool try_lock();
	void unlock();
	
	void release();
	
	bool owns_lock() const;
private:
	std::unique_ptr<_elib::UniqueLockImpl<LockT> > m_impl;
	DISALLOW_COPY_AND_ASSIGN(UniqueLock);
};
	

} /* namespace elib */
#endif /* ELIB_LOCK_H */