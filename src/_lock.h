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
#ifndef _LOCK_H
#define _LOCK_H

#include "elib/lock.h"
#include <system_error>

#define OP_NOT_PERMIT std::errc::operation_not_permitted

#define VERIFY_LOCK() do { \
	if (m_released) \
		throw new std::system_error(std::make_error_code(OP_NOT_PERMIT)); \
	} while(false) 

namespace elib {
namespace _elib {


template <typename LockT>
class UniqueLockImpl 
{
public:
	explicit UniqueLockImpl(LockT &lock) : m_lock(lock), m_released(false) {
		m_lock.lock();
		m_owns_lock = true;
	}
	
	UniqueLockImpl(LockT &lock, defer_lock_t &t) : m_lock(lock), 
					m_released(false), m_owns_lock(false) {
		UNUSED(t);				
	} 
					
	UniqueLockImpl(LockT &lock, try_lock_t &t) : m_lock(lock), m_released(false) {
		UNUSED(t);
		m_owns_lock = m_lock.try_lock();
	}
	
	~UniqueLockImpl() {
		if (m_owns_lock)
			m_lock.unlock();
	}
	
	inline void lock() {
		VERIFY_LOCK();
		m_lock.lock();
		m_owns_lock = true;
	}
	
	inline bool try_lock() {
		VERIFY_LOCK();
		m_owns_lock = m_lock.try_lock();
		return m_owns_lock;
	}
	
	inline void unlock() {
		VERIFY_LOCK();
		if (!m_owns_lock) {
			throw new std::system_error(std::make_error_code(OP_NOT_PERMIT));			
		} else {
			m_owns_lock = false;
			m_lock.unlock();
		}
	}
	
	inline void release() {
		m_released = true;
		m_owns_lock = false;
	}
	
	inline bool owns_lock() const { 
		return m_owns_lock;
	}
	
	inline LockT *get_lock() const {
		VERIFY_LOCK();
		return &m_lock;
	}
private:
	LockT &m_lock;
	bool m_released, m_owns_lock;
	DISALLOW_COPY_AND_ASSIGN(UniqueLockImpl);
};


} /* namespace _elib */


template <typename LockT>
UniqueLock<LockT>::UniqueLock(LockT &lock) 
					: m_impl(new _elib::UniqueLockImpl<LockT>(lock))
{ }
					
template <typename LockT>
UniqueLock<LockT>::UniqueLock(LockT &lock, try_lock_t& t)
					: m_impl(new _elib::UniqueLockImpl<LockT>(lock, t)) 
{ }

template <typename LockT>
UniqueLock<LockT>::UniqueLock(LockT &lock, defer_lock_t& t)
					: m_impl(new _elib::UniqueLockImpl<LockT>(lock, t)) 
{ }

template <typename LockT>
UniqueLock<LockT>::~UniqueLock() { }

template <typename LockT>
void UniqueLock<LockT>::lock()
{
	m_impl->lock();
}

template <typename LockT>
bool UniqueLock<LockT>::try_lock()
{
	return m_impl->try_lock();
}

template <typename LockT>
void UniqueLock<LockT>::unlock()
{
	m_impl->unlock();
}

template <typename LockT>
void UniqueLock<LockT>::release()
{
	m_impl->release();
}

template <typename LockT>
bool UniqueLock<LockT>::owns_lock() const
{
	return m_impl->owns_lock();
}

template <typename LockT>
UniqueLock<LockT>::operator bool() const
{
	return m_impl->owns_lock();
}

template <typename LockT>
LockT *UniqueLock<LockT>::get_lock() const 
{
	return m_impl->get_lock();
}


} /* namespace elib */
#endif /* _LOCK_H */