#include "alltests.h"

int main(int argc, const char* argv[]) 
{
	UNUSED(argc); UNUSED(argv);
	
	rwlock_test();
	log_test();
	
	return 0;
}