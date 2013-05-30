#include "alltests.h"

#include <chrono>
#include <iostream>
#include <cstdint>

#define INIT_TIMED() \
	std::chrono::time_point<std::chrono::high_resolution_clock> start, end; \
	int64_t total_sec, f_sec; \
	total_sec = 0

#define RUN_TIMED(func) start = std::chrono::high_resolution_clock::now(); \
	func(); \
	end = std::chrono::high_resolution_clock::now(); \
	f_sec = std::chrono::duration_cast<std::chrono::milliseconds> \
		(end-start).count(); \
	std::cout << "elapsed time: " << f_sec << "ms" << std::endl; \
	std::cout << std::endl; \
	total_sec += f_sec
	
#define END_TIMED() \
	std::cout << "total elapsed time: " << total_sec << "ms" << std::endl
	

int main(void) 
{
	INIT_TIMED();
	RUN_TIMED(sharedlock_test);
	RUN_TIMED(semaphore_test);
	END_TIMED();
	
	return 0;
}