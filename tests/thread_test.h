#ifndef TESTING_THREAD_TEST_H
#define TESTING_THREAD_TEST_H

#include <vector>
#include <thread>

class RunInterface
{
public:
	virtual ~RunInterface() { }
	virtual void run(void) = 0;
};

/* empty version of template */
void run_thread_tests();

template <typename FirstT, typename ...RestT>
void run_thread_tests(std::vector<FirstT> first, 
			   std::vector<RestT>... rest)
{
	std::vector<std::thread*> threads;
	
	for (auto &item : first) 
		threads.push_back( new std::thread(&RunInterface::run, item) );
	
	run_thread_tests(rest...);
	
	for (auto &item : threads) 
		item->join();
	
}

#endif /* TESTING_THREAD_TEST_H */