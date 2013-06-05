#include "elib/semaphore.h"
#include "thread_test.h"

#include <iostream>
#include <mutex>
#include <atomic>
#include <condition_variable>
#include <set>
#include <cassert>

#define NUM_THREADS 15
#define SEM_MAX 5
#define NUM_ITERS 100
#define SLEEP_MILI 20

using unique_lock = std::unique_lock<std::mutex>;

typedef struct shared_state_struct {
	elib::Semaphore sem;
	std::mutex lock;
	std::condition_variable full_cv;
	std::set<unsigned int> taken;
} shared_t;

class SemThread : public RunInterface
{
public:
	SemThread(int id, shared_t & shared) : m_id(id), m_shared(shared) { }
	
	~SemThread() { }
	
	void run() {
		
		for (int i=0; i < NUM_ITERS; ++i) {
/* when assertions are off, val is unused, so dont define it */
			unsigned int val = m_shared.sem.down();
#ifdef NDEBUG
			UNUSED(val);
#endif 
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

void semaphore_test(void) 
{
	std::cout << "Running semaphore_test";
	
	shared_t shared;
	elib::Semaphore sem(SEM_MAX);
	shared.sem = sem;
	
	std::vector<SemThread*> threads(NUM_THREADS);
	int id = 1;
	for (auto &t : threads)
		t = new SemThread(id++, std::ref(shared));
	
	run_thread_tests(threads);
	
}
