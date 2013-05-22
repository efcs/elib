#ifndef ELIB_LOCK_H
#define ELIB_LOCK_H

#include "commondef.h"
#include <mutex>
#include <memory>

namespace elib {

/* forward declarations */
namespace _elib {
template <typename T> class UniqueLockImpl;
}


/* for UniqueLock */
struct try_lock_t { };
struct defer_lock_t { };
constexpr try_lock_t try_to_lock = try_lock_t();
constexpr defer_lock_t defer_lock = defer_lock_t();


class LockInterface 
{
public:
	virtual ~LockInterface() { }
	virtual void lock() = 0;
	virtual bool try_lock() = 0;
	virtual void unlock() = 0;
};


/* why not have my own mutex class that is really just a wrapper */
class SharedMutex : public LockInterface
{
public:
	SharedMutex() : m_lock(new std::mutex()) { }
	
	~SharedMutex() { }
	
	void lock() { m_lock->lock(); }
	
	bool try_lock() { return m_lock->try_lock();}
	
	void unlock() { m_lock->unlock(); }
private:
	std::shared_ptr<std::mutex> m_lock;
};


template <typename LockT>
class LockGuard
{
public:
	explicit LockGuard(LockT &lock) : m_lock(lock) { m_lock.lock(); }
	~LockGuard() { m_lock.unlock(); }
private:
	LockT &m_lock;
	DISALLOW_COPY_AND_ASSIGN(LockGuard);
};


template <typename LockT>
class UniqueLock
{
public:
	explicit UniqueLock(LockT &lock);
	UniqueLock(LockT &lock, try_lock_t &t);
	UniqueLock(LockT &lock, defer_lock_t &t);
	
	~UniqueLock();
	
	void lock();
	bool try_lock();
	void unlock();
	
	void release();
	bool owns_lock() const;
	LockT *get_lock() const;
private:
	std::unique_ptr<_elib::UniqueLockImpl<LockT>> m_impl;
	DISALLOW_COPY_AND_ASSIGN(UniqueLock);
};
	

} /* namespace elib */
#endif /* ELIB_LOCK_H */