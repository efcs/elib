#ifndef ELIB_LOCK_H
#define ELIB_LOCK_H

#include "commondef.h"

#include <memory>

namespace elib {

/* forward declarations */
namespace _elib {
template <typename T> class UniqueLockImpl;
}


/* for UniqueLock */
struct lock_op_t  { };
struct try_lock_t : lock_op_t { };
struct defer_lock_t : lock_op_t { };
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


template <typename LockT>
class LockGuard
{
public:
	explicit LockGuard(LockT lock) : m_lock(lock) { }
	~LockGuard() { m_lock.unlock(); }
private:
	LockT &m_lock;
	DISALLOW_COPY_AND_ASSIGN(LockGuard);
};


template <typename LockT>
class UniqueLock
{
public:
	explicit UniqueLock(LockT lock);
	UniqueLock(LockT lock, lock_op_t lock_op);
	
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