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

	
namespace _elib { class shared_lock_impl; }


class shared_only_lock;

class shared_lock : public lock_interface
{
public:
	shared_lock();
	~shared_lock();
	
	void lock();
	bool try_lock();
	void unlock();
	
	void lock_shared();
	bool try_lock_shared();
	void unlock_shared();
	
	shared_only_lock &as_shared_only_lock();
private:
	void init();
	std::shared_ptr<_elib::shared_lock_impl> m_impl;
};


class shared_only_lock : public lock_interface
{
private:
	friend class shared_lock;
	shared_only_lock(shared_lock &lock);
public:
	~shared_only_lock();
	/* this just maps to the shared versions of the function */
	void lock();
	bool try_lock();
	void unlock();
private:
	shared_lock &m_lock;
};


} /* namespace elib */
#endif /* ELIB_SHAREDLOCK_H */