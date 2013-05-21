#ifndef _RWLOCK_H
#define _RWLOCK_H

#include <mutex>
#include <thread>
#include <queue>
#include <map>
#include <cassert>


namespace elib {
namespace _elib { 

using lock_guard = std::unique_lock<std::mutex>;

typedef struct rw_lock {
	std::thread::id thread_id;
	unsigned int lock_depth;
	bool allowed, write_lock;
} rw_lock_t;
	
class RWLockImpl 
{
public:
	RWLockImpl() { }
	~RWLockImpl() { }
	
	inline void read_lock() {
		lock_guard lock(m_lock);
		rw_lock_t *lock_item =  this->_process(false);
		lock_item->lock_depth++;
		lock.unlock();
		/* spin while the group is not allowed */
		while (! (lock_item->allowed))
			;
		/* we now own the lock */
	}
	
	inline bool try_read_lock() {
		lock_guard lock(m_lock);
		rw_lock_t *lock_item = this->_process(false);
		if (lock_item->allowed) {
			lock_item->lock_depth++;
			return true;
		} else {
			return false;
		}
	}
	
	inline void read_unlock() {
		lock_guard lock(m_lock);
		this->_unlock();
	}
	
	inline void write_lock() {
		lock_guard lock(m_lock);
		rw_lock_t *lock_item = this->_process(true);
		lock_item->lock_depth++;
		lock.unlock();
		while( ! lock_item->allowed)
			;
	}
	
	inline bool try_write_lock() {
		lock_guard lock(m_lock);
		auto lock_item = this->_process(true);
		if (lock_item->allowed) {
			lock_item->lock_depth++;
			return true;
		} else {
			return false;
		}
	}
	
	inline void write_unlock() {
		lock_guard lock(m_lock);
		this->_unlock();
	}
	
private:
	inline bool _curr_read() const {
		return (m_curr_locks.empty() 
				|| !(m_curr_locks.begin()->second)->write_lock);
	}
	
	inline void _schedule() {
		rw_lock_t *ptr;
		while (! m_requests.empty()) {
			ptr = m_requests.front();
			
			/* if we already have inserted readers, and 
			 * we have a write lock */
			if (! m_curr_locks.empty() && ptr->write_lock)
				return;
			
			/* otherwise consume the head */
			m_requests.pop();
			/* lock_depth of 0 means that nobody intends to
			 * hold this lock, so delete it and move on */
			if (ptr->lock_depth == 0) {
				delete ptr;
			} else {
				assert(m_curr_locks.count(ptr->thread_id) == 0);
				m_curr_locks[ptr->thread_id] = ptr;
				/* if we chose a writer, break */
				if (ptr->write_lock)
					return;
			}
		} /* while ! m_requests.empty() */
	}
	
	rw_lock_t *_process(bool write_lock) {
		auto thread_id = std::this_thread::get_id();
		/* try to recursivly lock */
		auto found = m_curr_locks.find(thread_id);
		if (found != m_curr_locks.end()) {
			rw_lock_t *item = found->second;
			if (item->write_lock == write_lock)
				return item;
		}
		
		/* otherwise create new lock item and queue it */
		rw_lock_t *lock_item = new rw_lock_t;
		lock_item->thread_id = thread_id;
		lock_item->lock_depth = 0;
		lock_item->write_lock = write_lock;
		/* if we can schedule it right away */
		if (m_curr_locks.empty() || 
			(m_requests.empty() && this->_curr_read())) {
			lock_item->allowed = true;
			m_curr_locks[thread_id] = lock_item;
		} else { // otherwise, add to queue 
			lock_item->allowed = false;
			m_requests.push(lock_item);
		}
				 
		return lock_item;
	}
	
	
	
	void _unlock() { 
		auto thread_id = std::this_thread::get_id();
		auto found = m_curr_locks.find(thread_id);
		assert(found != m_curr_locks.end());
		assert(m_curr_locks.count(thread_id) == 1);
		
		rw_lock_t *item = found->second;
		assert(item->lock_depth > 0);
		item->lock_depth--;
		
		if (item->lock_depth == 0) {
			m_curr_locks.erase(found);
			delete item;
		}
		
		/* if nobody is holding lock */
		if (m_curr_locks.empty())
			this->_schedule();
		
	}

	
	std::mutex m_lock;
	std::queue<rw_lock_t*> m_requests;
	std::map<std::thread::id, rw_lock_t*> m_curr_locks;
};


} /* namespace _elib */
} /* namespace elib */
#endif /* _RWLOCK_H */