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
#include "_semaphore.h"
#include "_lock.h"

#include <climits>

namespace elib {
	
semaphore::semaphore() : m_impl(new _elib::semaphore_impl(UINT_MAX))
{
}

semaphore::semaphore(unsigned int size) : m_impl(new _elib::semaphore_impl(size))
{
}

semaphore::~semaphore() { }

void semaphore::lock() 
{ 
	m_impl->down();
}

bool semaphore::try_lock()
{
	unsigned int tmp;
	return m_impl->try_down(tmp);
}

void semaphore::unlock()
{
	m_impl->up();
}

unsigned int semaphore::down()
{
	return m_impl->down();
}

bool semaphore::try_down(unsigned int &resource)
{
	return m_impl->try_down(resource);
}

void semaphore::up()
{
	m_impl->up();
}

unsigned int semaphore::size() const
{
	return m_impl->size();
}

unsigned int semaphore::available() const
{
	return m_impl->available();
}

unsigned int semaphore::taken() const 
{
	return m_impl->taken();
}


/* forced instantiation */
template class unique_lock<semaphore>;

	
} /* namespace elib */