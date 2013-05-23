#include "elib/lock.h"
#include "_lock.h"


namespace elib {
	
/* force templates instant's into the library */
template class UniqueLock<std::mutex>;

} /* namespace elib */