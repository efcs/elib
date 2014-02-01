// ELIB_AUX_TODO_HPP
// header guard omitted on purpose

#if defined(ELIB_TODO)
#   undef ELIB_TODO
#endif

////////////////////////////////////////////////////////////////////////////////
//
# define ELIB_AUX_TODO_SUM \
    defined(ELIB_TODO_STATIC_ASSERT) + defined(ELIB_TODO_ASSERT) \
      + defined(ELIB_TODO_WARN) + defined(ELIB_TODO_THROW)

#if ELIB_AUX_TODO_SUM > 1
# error More than one ELIB_TODO mode selected
#endif
     
# undef ELIB_AUX_TODO_SUM

////////////////////////////////////////////////////////////////////////////////
// 
# if defined( ELIB_TODO_STATIC_ASSERT )
#   define ELIB_TODO(str) static_assert(! "ELIB TODO FOUND: ", str)
# elif defined( ELIB_TODO_ASSERT )
#   include <elib/aux/assert.hpp>
#   define ELIB_TODO(msg) ELIB_ASSERT(! "ELIB TODO", msg)
# elif defined( ELIB_TODO_WARN )
#   include <elib/aux/assert.hpp>
#   define ELIB_TODO(msg) ELIB_WARN(! "ELIB TODO", msg)
# elif defined( ELIB_TODO_THROW )
#   define ELIB_TODO(msg) throw "ELIB TODO " msg
# else
#   define ELIB_TODO(msg) ((void)0)
# endif