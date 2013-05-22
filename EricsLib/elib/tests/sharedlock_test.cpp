#include <elib/sharedlock.h>

#include "thread_test.h"

#include <cassert>
#include <mutex>
#include <thread>
#include <vector>
#include <iostream>

#define NUM_READERS 5
#define NUM_WRITERS 5

#define NUM_READS 100
#define NUM_WRITES 50

#define BUFF_LEN 1000000

//#define PRINT_DEBUG

using lock_guard_shared = elib::LockGuard<elib::SharedOnlyLock>;
using lock_guard = elib::LockGuard<elib::SharedLock>;

class ReaderThread : public RunInterface
{
public:
	ReaderThread(int id, std::mutex &io_lock, elib::SharedLock &shared_lock, 
				 const char *shared_str) : m_id(id), m_io_lock(io_lock), 
				 m_shared_lock(shared_lock),  m_shared_str(shared_str)
	{ }
	
	~ReaderThread() { }
	
	void run() {
		elib::SharedOnlyLock &s_lock(m_shared_lock.as_shared_only_lock());
		for (int i=0; i < NUM_READS; ++i) {
			{
				lock_guard_shared lock(s_lock);
				this->print(std::string("start " + std::to_string(i)).c_str());
				this->verify();
				this->print("end");
			}
		}
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
	
	inline void print(const char *msg) {
#if		defined(PRINT_DEBUG)
		std::lock_guard<std::mutex> lock(m_io_lock);
		std::cout << "Reader:" << m_id;
		std::cout << " " << msg << std::endl;
		std::cout.flush();
#else
		UNUSED(msg);
#endif
	}
	
	int m_id;
	std::mutex &m_io_lock;
	elib::SharedLock &m_shared_lock;
	const char *m_shared_str;
};


class WriterThread : public RunInterface
{
public:
	WriterThread(int id, std::mutex &io_lock, elib::SharedLock &shared_lock, 
				char* shared_str, char value) : m_id(id), m_io_lock(io_lock), 
				m_shared_lock(shared_lock), m_shared_str(shared_str), m_val(value)
	{ }
	
	~WriterThread() { } 
	
	void run() {
		for (int i=0; i < NUM_WRITES; ++i) {
			{
				lock_guard lock(m_shared_lock);
				this->print(std::string("start " + std::to_string(i)).c_str());
				this->write();
				this->verify();
				this->print(std::string("end " + std::to_string(i)).c_str());
			}
		}
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
	
	inline void print(const char *msg) {
#if		defined(PRINT_DEBUG)
		std::lock_guard<std::mutex> lock(m_io_lock);
		std::cout << "Writer:" << m_id;
		std::cout << " " << msg << std::endl;
		std::cout.flush();
#else
		UNUSED(msg);
#endif 
	}
	
	int m_id;
	std::mutex &m_io_lock;
	elib::SharedLock &m_shared_lock;
	char *m_shared_str;
	char m_val;
};



void sharedlock_test()
{
	std::cout << "Running sharedlock_tests" << std::endl;
	
	elib::SharedLock shared_lock;
	std::mutex io_lock;
	
	char *str = new char[BUFF_LEN];
	char curr_val = 'a';
	for (int i=0; i < BUFF_LEN; ++i) {
		str[i] = '0';
	}
	str[BUFF_LEN-1] = '\0';
	
	std::vector<ReaderThread*> readers(NUM_READERS);
	std::vector<WriterThread*> writers(NUM_WRITERS);
	
	int uid = 1;
	for (ReaderThread* &r : readers)
		r = new ReaderThread(uid++, std::ref(io_lock), std::ref(shared_lock), str);
	
	uid = 1;
	for (WriterThread* &w : writers)
		w = new WriterThread(uid++, std::ref(io_lock), std::ref(shared_lock), str, curr_val++);
	
	run_thread_tests(readers, writers);
}