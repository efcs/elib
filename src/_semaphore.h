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
#ifndef _SEMAPHORE_H
#define _SEMAPHORE_H

#include "elib/semaphore.h"

#include <mutex>
#include <atomic>
#include <condition_variable>
#include <cassert>

#define MEM_ORD_ACQ std::memory_order_seq_cst
#define MEM_ORD_REL std::memory_order_seq_cst
#define MEM_ORD_ACQ_REL std::memory_order_seq_cst

namespace elib {
namespace _elib {
	
using unique_lock = std::unique_lock<std::mutex>;

class semaphore_impl 
{
public:
	semaphore_impl(unsigned int size) : m_size(size), m_count(ATOMIC_VAR_INIT(size))
	{ }
	
	inline unsigned int down() {
		unique_lock lock(m_lock);
		m_nempty_cv.wait(lock, [this]{ return this->m_count.load() > 0; });
		unsigned int val = m_count.fetch_sub(1, MEM_ORD_ACQ_REL);
		assert(val > 0 && val <= m_size);
		return val;
	}
	
	inline bool try_down(unsigned int &resource) {
		unique_lock lock(m_lock, std::try_to_lock);
		if (lock.owns_lock() && m_count.load(MEM_ORD_ACQ) > 0) {
			resource = m_count.fetch_sub(1, MEM_ORD_ACQ_REL);
			return true;
		} else {
			return false;
		}
	}
	
	inline void up() {
		m_count.fetch_add(1, MEM_ORD_ACQ_REL);
		assert(m_count.load(MEM_ORD_ACQ) <= m_size);
		m_nempty_cv.notify_one();
	}
	
	inline unsigned int size() const { 
		return m_size; 
	}
	
	inline unsigned int available() const {
		return m_count.load(MEM_ORD_ACQ);
	}
	
	inline unsigned int taken() const { 
		return m_size - m_count.load(MEM_ORD_ACQ);
	}

private:
	unsigned int m_size;
	std::atomic_uint m_count;
	std::mutex m_lock;
	std::condition_variable m_nempty_cv;
	DISALLOW_COPY_AND_ASSIGN(semaphore_impl);
};


} /* namespace _elib */
} /* namespace elib */
#endif /* _SEMAPHORE_H */
