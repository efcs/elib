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
	/* this just maps to the shared versions of the function */
	void lock();
	bool try_lock();
	void unlock();
private:
	SharedLock &m_lock;
};


} /* namespace elib */
#endif /* ELIB_SHAREDLOCK_H */