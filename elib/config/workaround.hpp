#ifndef ELIB_WORKAROUND_HPP
#define ELIB_WORKAROUND_HPP
# 
# define ELIB_WORKAROUND(compiler, test) \
  ( ( compiler ) && ( ELIB_WORKAROUND_ ## test ) )
# 
# /* A clang bug */
# if defined(__clang__)
#   if __clang_major__ <= 3 && __clang_minor__ < 4
#     define ELIB_WORKAROUND_CLANG_ENUMERATION_COMPARE_BUG 1
#   endif
# endif                                                      // clang bugs
# 
#endif /* ELIB_WORKAROUND_HPP */