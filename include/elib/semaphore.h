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
#ifndef ELIB_SEMAPHORE_H
#define ELIB_SEMAPHORE_H

#include "lock.h"
#include <memory>

namespace elib {
	

namespace _elib {
class semaphore_impl;	
}

class semaphore_interface 
{
public:
	virtual ~semaphore_interface() { }
	virtual unsigned int down() = 0;
	virtual bool try_down(unsigned int &resource) = 0;
	virtual void up() = 0;
	
	virtual unsigned int size() const = 0;
	virtual unsigned int available() const = 0;
	virtual unsigned int taken() const = 0;
};


class semaphore : public semaphore_interface, public lock_interface
{
public:
	semaphore();
	explicit semaphore(unsigned int size);
	~semaphore();
	
	/* semaphore interface */
	unsigned int down();
	bool try_down(unsigned int &resource);
	void up();
	
	unsigned int size() const;
	unsigned int available() const;
	unsigned int taken() const;
	
	/* lock interface */
	void lock();
	bool try_lock();
	void unlock();
private:
	std::shared_ptr<_elib::semaphore_impl> m_impl;
};


} /* namespace elib */
#endif /* ELIB_SEMAPHORE_H */