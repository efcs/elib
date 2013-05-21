#include <elib/lock.h>
#include <elib/log.h>

#include <iostream>
#include <thread>
#include <vector>

#include <cassert>

#define NUM_THREADS 8

#define PRINT_MAX 10
#define RACE_MAX 100000000000

void thread_print(int thread_num, elib::Mutex &lock) 
{
	lock.lock();
	for (int i=0; i < PRINT_MAX; ++i) {
		std::cout << thread_num << std::endl;
	}
	lock.unlock();
}

void consume(elib::MultiLock<elib::Mutex> count_lock) 
{
	for (unsigned long long i=0; i < RACE_MAX; ++i) {
		assert(count_lock.taken() <= 10);
	}
}

void print_test(void) 
{
	elib::MultiLock<elib::Mutex> test_lock(10);
	std::vector<std::thread*> threads(NUM_THREADS);
	elib::Mutex shared_lock;
	for (int i=0; i < NUM_THREADS; ++i) {
		threads[i] = new std::thread(thread_print, i, std::ref(shared_lock));
	}
	for (auto it=threads.begin(); it != threads.end(); ++it) {
		(*it)->join();
		delete (*it);
	}
}

int main(void)
{
	//print_test();
	elib::Log::set_level(elib::ERROR_L);
	return 0;
}
