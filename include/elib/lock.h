/* 
 * Copyright (C) 2013  Eric Fiselier
 * 
 * This file is part of elib.
 *
 * elib is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * elib is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with elib.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef ELIB_LOCK_H
#define ELIB_LOCK_H

#include <mutex>
#include <memory>

namespace elib {

/* forward declarations */
namespace _elib {
    template <typename T> 
    class unique_lock_impl;
}


/* for unique_lock */
struct try_lock_t { };
struct defer_lock_t { };
constexpr try_lock_t try_to_lock = try_lock_t();
constexpr defer_lock_t defer_lock = defer_lock_t();


class lock_interface 
{
public:
	virtual ~lock_interface() { }
	virtual void lock() = 0;
	virtual bool try_lock() = 0;
	virtual void unlock() = 0;
};


/* why not have my own mutex class that is really just a wrapper 
 * at least it is copyable */
class mutex : public lock_interface
{
public:
	mutex() : m_lock(new std::mutex()) { }
	
	~mutex() { }
	
	void lock() { m_lock->lock(); }
	
	bool try_lock() { return m_lock->try_lock();}
	
	void unlock() { m_lock->unlock(); }
private:
	std::shared_ptr<std::mutex> m_lock;
};


template <typename LockT>
class lock_guard
{
public:
	explicit lock_guard(LockT &lock) : m_lock(lock) { m_lock.lock(); }
	~lock_guard() { m_lock.unlock(); }
private:
	LockT &m_lock;
	lock_guard(const lock_guard &);
    lock_guard & operator=(const lock_guard &);
};


template <typename LockT>
class unique_lock
{
public:
	explicit unique_lock(LockT &lock);
	unique_lock(LockT &lock, try_lock_t &t);
	unique_lock(LockT &lock, defer_lock_t &t);
	
	~unique_lock();
	
	void lock();
	bool try_lock();
	void unlock();
	
	void release();
	
	bool owns_lock() const;
	operator bool() const; //same as owns_lock 
	
	LockT *get_lock() const;
private:
	std::unique_ptr<_elib::unique_lock_impl<LockT>> m_impl;
	unique_lock(const unique_lock &);
    unique_lock & operator=(const unique_lock &);
};
	

} /* namespace elib */
#endif /* ELIB_LOCK_H */