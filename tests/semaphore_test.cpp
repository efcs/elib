#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "elib/semaphore.h"
#include "thread_test.h"

#include <iostream>
#include <mutex>
#include <atomic>
#include <condition_variable>
#include <set>
#include <cassert>

#define NUM_THREADS 4
#define SEM_MAX 5
#define NUM_ITERS 100
#define SLEEP_MILI 20


using unique_lock = std::unique_lock<std::mutex>;


struct shared_t {
	elib::semaphore sem;
	std::mutex lock;
	std::condition_variable full_cv;
	std::set<unsigned int> taken;
};


class SemThread : public RunInterface {
public:
	SemThread(int id, shared_t & shared) : m_id(id), m_shared(shared) { }
	
	~SemThread() { }
	
	void run() {
		for (int i=0; i < NUM_ITERS; ++i) {
			unsigned int val = m_shared.sem.down();
			UNUSED(val);
			assert(val > 0 && val <= SEM_MAX);
			std::chrono::milliseconds dur(SLEEP_MILI);
			std::this_thread::sleep_for(dur);
			m_shared.sem.up();
		}
	}
	
private:
	int m_id;
	shared_t & m_shared;
};


BOOST_AUTO_TEST_SUITE(semaphore_test_suite)

BOOST_AUTO_TEST_CASE(semaphore_test)
{
	shared_t shared;
	elib::semaphore sem(SEM_MAX);
	shared.sem = sem;
	
	std::vector<SemThread*> threads(NUM_THREADS);
	int id = 1;
	for (auto &t : threads)
		t = new SemThread(id++, std::ref(shared));
	
	run_thread_tests(threads);
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_SUITE_END()