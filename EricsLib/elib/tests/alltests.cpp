#include "alltests.h"

int main(int argc, const char* argv[]) 
{
	UNUSED(argc); UNUSED(argv);
	
	lock_test();
	rwlock_test();
	log_test();
	
	return 0;
}