#include <elib/rwlock.h>
#include <elib/log.h>

#include <cassert>
#include <vector>
#include <iostream>

#include "thread_test.h"


#define NUM_READERS 15
#define NUM_WRITERS 5

#define NUM_READS 5
#define NUM_WRITES 5

using namespace elib;

class ReaderThread : public RunInterface
{
public:
	ReaderThread(RWLock &rw_lock, const char *shared_str) 
				: m_rw_lock(rw_lock), m_shared_str(shared_str)
	{ }
	
	~ReaderThread() { }
	
	void run() {
		for (int i=0; i < NUM_READS; ++i) {
			m_rw_lock.read_lock();
			this->verify();
			Log::raw_out("%s", m_shared_str);
			m_rw_lock.read_unlock();
		}
		return;
	}
	
private:
	inline void verify() {
		int i=0;
		char last = m_shared_str[0];
		while (m_shared_str[i] != '\0') {
			assert(m_shared_str[i] == last);
			++i;
		}
	}
	
	RWLock &m_rw_lock;
	const char *m_shared_str;
};


class WriterThread : public RunInterface
{
public:
	WriterThread(RWLock &rw_lock, char* shared_str, char value)
					: m_rw_lock(rw_lock), m_shared_str(shared_str), m_val(value)
	{ }
	
	~WriterThread() { } 
	
	void run(void) {
		for (int i=0; i < NUM_WRITES; ++i) {
			m_rw_lock.write_lock();
			this->write();
			m_rw_lock.write_unlock();
		}
		return;
	}
private:
	inline void write() {
		int i=0;
		while(m_shared_str[i] != '\0') {
			m_shared_str[i] = m_val;
			++i;
		}
	}
	
	inline void verify() {
		int i=0;
		while (m_shared_str[i] != '\0') {
			assert(m_shared_str[i] == m_val);
			++i;
		}
	}
	RWLock &m_rw_lock;
	char *m_shared_str;
	char m_val;
};



void rwlock_test()
{
	std::cout << "Running rwlock_tests" << std::endl;
	RWLock rw_lock;
	char *str = new char[11];
	char curr_val = 'a';
	for (int i=0; i < 10; ++i) {
		str[i] = '0';
	}
	str[10] = '\0';
	
	std::vector<ReaderThread*> readers(NUM_READERS);
	std::vector<WriterThread*> writers(NUM_WRITERS);
	
	for (ReaderThread* &r : readers)
		r = new ReaderThread(rw_lock, str);
	
	for (WriterThread* &w : writers)
		w = new WriterThread(rw_lock, str, curr_val++);
	
	run_thread_tests(readers, writers);
	
	return;
}