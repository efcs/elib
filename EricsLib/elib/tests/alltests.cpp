#include "alltests.h"

int main(int argc, const char* argv[]) 
{
	UNUSED(argc); UNUSED(argv);
	
	sharedlock_test();
	semaphore_test();
	
	return 0;
}