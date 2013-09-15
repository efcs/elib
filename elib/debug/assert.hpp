#ifndef ELIB_ASSERT_HPP
#define ELIB_ASSERT_HPP


#ifndef NDEBUG

#   include <cassert>
#   define ELIB_ASSERT(x) assert(x)

#else

#   define ELIB_ASSERT(x) ((void)0)

#endif


#endif /* ELIB_ASSERT_HPP */