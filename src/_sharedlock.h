#ifndef _SHAREDLOCK_H
#define _SHAREDLOCK_H

#include "elib/sharedlock.h"

#include <mutex>
#include <thread>
#include <condition_variable>
#include <atomic>
#include <vector>
#include <map>
#include <algorithm>
#include <iostream>

#include <cassert>
	
#define SHARED true
#define EXCLUSIVE false

#define TRY_TO_LOCK true
#define LOCK	 false

#define MEM_ORD_ACQ std::memory_order_acquire
#define MEM_ORD_REL std::memory_order_release


namespace elib {	
namespace _elib { 
	
	
using lock_guard = std::lock_guard<std::mutex>;
using unique_lock = std::unique_lock<std::mutex>;


typedef struct shared_lock_struct {
	std::thread::id thread_id;
	std::atomic_uint depth = ATOMIC_VAR_INIT(1);
	std::atomic_bool shared = ATOMIC_VAR_INIT(false);
	std::atomic_bool allowed = ATOMIC_VAR_INIT(false);
	std::condition_variable allowed_cv;
} shared_lock_t;
	

bool is_allowed(const shared_lock_t* item) { return item->allowed.load(MEM_ORD_ACQ); }

bool is_exclusive(const shared_lock_t* item) { return !item->shared.load(MEM_ORD_ACQ); } 

void verify_shared_lock_type(const shared_lock_t *item) 
{
		assert(item);
		assert(item->thread_id != std::thread::id());
		assert(item->depth.load(MEM_ORD_ACQ) <= 10000);
		if (item->allowed.load(MEM_ORD_ACQ)) {
			assert(item->depth.load(MEM_ORD_ACQ) > 0);
		} else {
			assert(item->depth.load(MEM_ORD_ACQ) == 1);
		}
}


class SharedLockImpl 
{
public:
	SharedLockImpl() { }
	~SharedLockImpl() { }
	
	/* mutualy exclusive locking */
	void lock() {
		unique_lock lock(m_lock);
		auto t_id = std::this_thread::get_id();
		auto lock_item = this->process_request(t_id, EXCLUSIVE, LOCK);
		
		assert(lock_item);
		assert(lock_item->thread_id == t_id);
		assert(lock_item->shared.load(MEM_ORD_ACQ) == EXCLUSIVE);
		assert(lock_item->depth.load(MEM_ORD_ACQ) > 0);
		
		lock_item->allowed_cv.wait(lock, [=]{ return lock_item->allowed.load(MEM_ORD_ACQ); });
		
		assert(lock_item->allowed.load(MEM_ORD_ACQ));
		assert(lock_item->thread_id == t_id);
		assert(lock_item->shared.load(MEM_ORD_ACQ) == EXCLUSIVE);
		assert(lock_item->depth.load(MEM_ORD_ACQ) > 0);	
	}
	
	bool try_lock() {
		lock_guard lock(m_lock);
		
		auto t_id = std::this_thread::get_id();
		auto lock_item = this->process_request(t_id, EXCLUSIVE, TRY_TO_LOCK);
		
		if (lock_item) {
			assert(lock_item->allowed.load(MEM_ORD_ACQ));
			assert(lock_item->thread_id == t_id);
			assert(lock_item->shared.load(MEM_ORD_ACQ) == EXCLUSIVE);
			assert(lock_item->depth.load(MEM_ORD_ACQ) > 0);
			
			return true;
		} else {
			assert(!m_lock_queue.empty());
			return false;
		}
	}
	
	void unlock() {
		auto t_id = std::this_thread::get_id();
		lock_guard lock(m_lock);

		this->_unlock(t_id, EXCLUSIVE);
	}
	
	/* shared locking */
	void lock_shared() {
		unique_lock lock(m_lock);
		auto t_id = std::this_thread::get_id();
		auto lock_item = this->process_request(t_id, SHARED, LOCK);
		
		assert(lock_item);
		assert(lock_item->thread_id == t_id);
		assert(lock_item->shared.load(MEM_ORD_ACQ) == SHARED);
		assert(lock_item->depth.load(MEM_ORD_ACQ) > 0);
		
		lock_item->allowed_cv.wait(lock, [=]{ return lock_item->allowed.load(MEM_ORD_ACQ); });
		
		assert(lock_item);
		assert(lock_item->thread_id == t_id);
		assert(lock_item->shared.load(MEM_ORD_ACQ) == SHARED);
		assert(lock_item->depth.load(MEM_ORD_ACQ) > 0);
	}
	
	bool try_lock_shared() {
		lock_guard lock(m_lock);
		auto t_id = std::this_thread::get_id();
		auto lock_item = this->process_request(t_id, SHARED, TRY_TO_LOCK);
		if (lock_item) {
			assert(lock_item->allowed.load(MEM_ORD_ACQ));
			assert(lock_item->thread_id == t_id);
			assert(lock_item->shared.load(MEM_ORD_ACQ) == SHARED);
			assert(lock_item->depth.load(MEM_ORD_ACQ) > 0);
			return true;
		} else {
			assert(!m_lock_queue.empty());
			return false;
		}
		
	}
	
	void unlock_shared() {
		auto t_id = std::this_thread::get_id();
		lock_guard lock(m_lock);
		this->_unlock(t_id, SHARED);
	}
	
	SharedOnlyLock &as_shared_only_lock() {
		return *m_shared_only_lock;
	}
	

private:
	
	void _unlock(std::thread::id &t_id, bool shared) {
/* without assertions shared is unused */
#if defined(NDEBUG)
		UNUSED(shared);
#endif 
		auto it = m_lock_queue.begin();
		while(it != m_lock_queue.end()) {
			auto item = (*it);
			
			assert(item->allowed.load(MEM_ORD_ACQ) == true);
			assert(item->depth.load(MEM_ORD_ACQ) > 0);
			
			if (item->thread_id == t_id) {
				assert(item->shared.load(MEM_ORD_ACQ) == shared);
				item->depth.fetch_sub(1);
				
				if (item->depth.load(MEM_ORD_ACQ) == 0) {
					m_lock_queue.erase(it++);
					delete item;
					if (! m_lock_queue.empty() && 
						! m_lock_queue.front()->allowed.load(MEM_ORD_ACQ)) {
						this->reschedule();
					}
				}
				
				return;
			} /* end if thread_id == t_id */
			++it;
		}
		
		assert(false);
	}
	
	shared_lock_t *get_recursive_lock_item(const std::thread::id &t_id, bool shared) {
		for (auto item : m_lock_queue) {
			/* if the item is not currently allowed,
			 * then it is not a req lock request */
			if (item->allowed.load(MEM_ORD_ACQ) == false)
				return nullptr;
			
			if (item->thread_id == t_id) {
				/* if they are the same lock type it is a recursive lock on item,
				 * otherwise we cannot recursively lock different lock types */
				if (item->shared.load(MEM_ORD_ACQ) == shared)
					return item;
				else
					return nullptr;
			}
		} /* end for */
		
		return nullptr;
	}
	
	/* return true if we can imm schedule it,
	 * if it is a recursive lock, then rec_ptr will be set to the
	 * lock_item for the recursive lock */
	bool can_sched_imm(const std::thread::id &t_id, bool shared, 
					   shared_lock_t* &rec_ptr) {
		rec_ptr = nullptr;
		
		if (m_lock_queue.empty())
			return true;
		
		rec_ptr = this->get_recursive_lock_item(t_id, shared);
		if (rec_ptr)
			return true;
		
		/* after this point, only SHARED locks are allowed */
		if (shared == EXCLUSIVE)
			return false;
		
		/* if the front is a write lock, 
		 * or the back is not allowed return false */
		return (m_lock_queue.front()->shared.load(MEM_ORD_ACQ) == SHARED &&
				m_lock_queue.back()->allowed.load(MEM_ORD_ACQ) == true);
	}

	
	
	shared_lock_t *process_request(std::thread::id &t_id, 
							   bool shared, bool try_to_lock) {
		
		assert(t_id != std::thread::id());
		shared_lock_t *lock_item = nullptr;
		bool imm_sched = this->can_sched_imm(t_id, shared, lock_item);
		
		/* if we cant imediatly schedule, then 
		 * try_to_lock must fail */
		if (!imm_sched && try_to_lock)
			return nullptr;
		
		if (lock_item) {
			assert(imm_sched);
		}
		
		/* if it is a recursive lock */
		if (imm_sched && lock_item) {
			assert(lock_item->depth.load(MEM_ORD_ACQ) > 0);
			lock_item->depth.fetch_add(1);
			return lock_item;
		}
		
		/* otherwise, create a new lock item */
		lock_item = new shared_lock_t;
		lock_item->thread_id = t_id;
		lock_item->shared.store(shared, MEM_ORD_REL);
		lock_item->allowed.store(imm_sched, MEM_ORD_REL);
		
		m_lock_queue.push_back(lock_item);
		return lock_item;
	}
	
	void reschedule() {
		int new_allowed = 0;
		for (auto &item : m_lock_queue) {
			assert(item->thread_id != std::thread::id());
			assert(item->allowed.load(MEM_ORD_ACQ) == false);
			assert(item->depth.load(MEM_ORD_ACQ) == 1);
			
			if (new_allowed != 0 && item->shared.load(MEM_ORD_ACQ) == EXCLUSIVE)
				break;
			
			item->allowed.store(true, MEM_ORD_REL);
			item->allowed_cv.notify_all();
			++new_allowed;
			
			if (item->shared.load(MEM_ORD_ACQ) == EXCLUSIVE)
				break;
		}
	}
	
	
private:
	std::mutex m_lock;
	std::vector<shared_lock_t*> m_lock_queue;
	SharedOnlyLock *m_shared_only_lock;
	friend class elib::SharedLock;
	DISALLOW_COPY_AND_ASSIGN(SharedLockImpl);

/* this method is only allowed when assertions are on */
#ifndef NDEBUG
	void verify() {
		lock_guard lock(m_lock);
		
		if (m_lock_queue.empty())
			return;
		
		std::for_each(m_lock_queue.begin(), m_lock_queue.end(), 
										verify_shared_lock_type);

		
		auto waiting_begin = std::find_if_not(m_lock_queue.begin(), 
											 m_lock_queue.end(), is_allowed);
	
		assert(waiting_begin != m_lock_queue.begin());
		
		std::map<std::thread::id, shared_lock_t*> allowed_seen;
		std::map<std::thread::id, shared_lock_t*> other_seen;
		
		int num_allowed = 0;
		bool last_shared, shared;
		last_shared = false;
		std::thread::id t_id;
		for (auto it=m_lock_queue.begin(); it != waiting_begin; ++it) {
			auto item = (*it);
			assert(item->allowed.load(MEM_ORD_ACQ));
			t_id = item->thread_id;
			shared = item->shared.load(MEM_ORD_ACQ);
			
			if (num_allowed == 0)
				last_shared = shared;
			
			/* verify first item was the same type of lock */
			if (num_allowed == 1)
				assert(shared == last_shared);
		
			/* num_allowed > 0 means that every lock item must be
			 * shared */
			if (num_allowed > 0)
				assert(shared == SHARED);
			
			assert(allowed_seen.count(t_id) == 0);
			allowed_seen[t_id] = item;
			last_shared = shared;
			++num_allowed;
		}
		
		int num_rest = 0;
		for (auto it=waiting_begin; it != m_lock_queue.end(); ++it) {
			auto item = (*it);
			assert(item->allowed.load(MEM_ORD_ACQ) == false);
			
			t_id = item->thread_id;
			shared = item->shared.load(MEM_ORD_ACQ);
			
			if (num_rest == 0 && last_shared == SHARED)
				assert(shared == EXCLUSIVE);
			
			assert(other_seen.count(t_id) == 0);
			assert(allowed_seen.count(t_id) <= 1);
			
			auto found = allowed_seen.find(t_id);
			if (found != allowed_seen.end()) {
				auto tmp = found->second;
				assert(tmp->shared.load(MEM_ORD_ACQ) != shared);
			}
			
			other_seen[t_id] = item;
			++num_rest;
		}
		
		unsigned int total = num_rest + num_allowed;
		assert(total == m_lock_queue.size());
	}
#endif /* NDEBUG */

};


} /* namespace _elib */
} /* namespace elib */
#endif /* _RWLOCK_H */
