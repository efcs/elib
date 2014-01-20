#ifndef ELIB_AUX_TODO_HPP
#define ELIB_AUX_TODO_HPP
# 
# include <elib/assert.hpp>
# 
# /* ELIB_TODO can be used to locate TODO 's in code */
# if defined( ELIB_STATIC_ASSERT_TODO )
#   define ELIB_TODO(str) static_assert(! "ELIB TODO FOUND: ", str)
# elif defined( ELIB_ASSERT_TODO )
#   define ELIB_TODO(msg) ELIB_ASSERT(! "ELIB TODO", msg)
# elif defined( ELIB_WARN_TODO )
#   define ELIB_TODO(msg) ELIB_WARN(! "ELIB TODO", msg)
# elif defined( ELIB_THROW_TODO )
#   define ELIB_TODO(msg) throw "ELIB TODO " msg
# else
#   define ELIB_TODO(msg) ((void)0)
# endif
# 
#endif /* ELIB_AUX_TODO_HPP */