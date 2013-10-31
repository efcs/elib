#include <elib/config.hpp>

#if defined(ELIB_GNU)
#   pragma GCC diagnostic ignored "-Wnon-virtual-dtor"
#elif defined(ELIB_CLANG)
#   pragma clang diagnostic ignored "-Wnon-virtual-dtor"
#endif
