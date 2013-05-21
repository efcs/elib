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

void run_thread_tests()
{
	return;
}

template <typename FirstT, typename ...RestT>
void run_thread_tests(std::vector<FirstT> first, 
			   std::vector<RestT>... rest)
{
	std::vector<std::thread*> threads;
	for (auto it=first.begin(); it != first.end(); ++it) {
		threads.push_back( new std::thread(&RunInterface::run, (*it)) );
	}
	
	run_thread_tests(rest...);
	
	for (auto it=threads.begin(); it != threads.end(); ++it) {
		(*it)->join();
	}
	
	return;
}

#endif /* TESTING_THREAD_TEST_H */