#ifndef ELIB_COMMON_DEF_HPP
#define ELIB_COMMON_DEF_HPP
# 
# /* used to suppress unused warnings */
# define ELIB_UNUSED(x) ((void)x)
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
# /* used to clearly have exposition for code we don't want to compile */
# define ELIB_EXPO(...) 
# 
# define ELIB_DEFAULT_CLASS(Name)           \
  Class() = default;                        \
                                            \
  Class(const Class&) = default;            \
  Class(Class&&) = default;                 \
                                            \
  Class& operator=(const Class&) = default; \
  Class& operator(Class&&) = default
# 
#
#endif /* ELIB_COMMON_DEF_HPP */