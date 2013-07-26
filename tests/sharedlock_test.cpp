#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "elib/sharedlock.h"

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


using lock_guard_shared = elib::lock_guard<elib::shared_only_lock>;
using lock_guard = elib::lock_guard<elib::shared_lock>;

class ReaderThread : public RunInterface
{
public:
	ReaderThread(int id, std::mutex &io_lock, elib::shared_lock &shared_lock, 
				 const char *shared_str) : m_id(id), m_io_lock(io_lock), 
				 m_shared_lock(shared_lock),  m_shared_str(shared_str)
	{ }
	
	~ReaderThread() { }
	
	void run() {
		elib::shared_only_lock &s_lock(m_shared_lock.as_shared_only_lock());
		for (int i=0; i < NUM_READS; ++i) {
			{
				lock_guard_shared lock(s_lock);
				this->verify();
			}
		}
	}
	
private:
	inline void verify() {
		int i=0;
		char last = m_shared_str[0];
		/* last is unused when assertions are off */
		UNUSED(last);
		while (m_shared_str[i] != '\0') {
			assert(m_shared_str[i] == last);
			++i;
		}
	}
	
	
	int m_id;
	std::mutex &m_io_lock;
	elib::shared_lock &m_shared_lock;
	const char *m_shared_str;
};


class WriterThread : public RunInterface
{
public:
	WriterThread(int id, std::mutex &io_lock, elib::shared_lock &shared_lock, 
				char* shared_str, char value) : m_id(id), m_io_lock(io_lock), 
				m_shared_lock(shared_lock), m_shared_str(shared_str), m_val(value)
	{ }
	
	~WriterThread() { } 
	
	void run() {
		for (int i=0; i < NUM_WRITES; ++i) {
			{
				lock_guard lock(m_shared_lock);
				this->write();
				this->verify();
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
	
	int m_id;
	std::mutex &m_io_lock;
	elib::shared_lock &m_shared_lock;
	char *m_shared_str;
	char m_val;
};

BOOST_AUTO_TEST_SUITE(sharedlock_test_suite)

BOOST_AUTO_TEST_CASE(test_sharedlock)
{	
	elib::shared_lock shared_lock;
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
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_SUITE_END()
