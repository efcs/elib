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
#include "_sharedlock.h"
#include "_lock.h"

#include <iostream>

namespace elib {
	
	
shared_lock::shared_lock() : m_impl(new _elib::shared_lock_impl())
{
	this->init();
}

shared_lock::~shared_lock()
{
}

void shared_lock::lock()
{
	m_impl->lock();
#ifndef NDEBUG
	m_impl->verify();
#endif
}

bool shared_lock::try_lock()
{
	return m_impl->try_lock();
#ifndef NDEBUG
	m_impl->verify();
#endif
}

void shared_lock::unlock()
{
	m_impl->unlock();
#ifndef NDEBUG
	m_impl->verify();
#endif
}

void shared_lock::lock_shared()
{
	m_impl->lock_shared();
#ifndef NDEBUG
	m_impl->verify();
#endif
}

bool shared_lock::try_lock_shared()
{
	return m_impl->try_lock_shared();
#ifndef NDEBUG
	m_impl->verify();
#endif
}

void shared_lock::unlock_shared()
{
	m_impl->unlock_shared();
#ifndef NDEBUG
	m_impl->verify();
#endif
}

shared_only_lock &shared_lock::as_shared_only_lock() 
{
	return m_impl->as_shared_only_lock();
}


void shared_lock::init()
{
	m_impl->m_shared_only_lock = new shared_only_lock(*this);
}

shared_only_lock::shared_only_lock(shared_lock &s_lock) : m_lock(s_lock) 
{ 
}

shared_only_lock::~shared_only_lock() 
{ 
}

void shared_only_lock::lock() 
{
	m_lock.lock_shared();
}

bool shared_only_lock::try_lock() 
{
	return m_lock.try_lock_shared();
}

void shared_only_lock::unlock() 
{
	m_lock.unlock_shared();
}

/* force template creation */
template class unique_lock<shared_lock>;
template class unique_lock<shared_only_lock>;

} /* namespace elib */