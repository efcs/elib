#include "alltests.h"

#include <chrono>
#include <iostream>
#include <cstdint>


#define RUN_TIMED(func)  {\
	std::chrono::time_point<std::chrono::high_resolution_clock> start, end;\
	int64_t f_sec; \
	start = std::chrono::high_resolution_clock::now(); \
	func; \
	end = std::chrono::high_resolution_clock::now(); \
	f_sec = std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count(); \
	std::cout << " -- PASSED: " << f_sec << "ms" << std::endl; \
	}
	
	
int main(void) 
{
	
	RUN_TIMED(sharedlock_test());
	RUN_TIMED(semaphore_test());
	
	return 0;
}
