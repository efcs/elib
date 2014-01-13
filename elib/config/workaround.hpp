#ifndef ELIB_WORKAROUND_HPP
#define ELIB_WORKAROUND_HPP
# 
# include <elib/config/compiler_config.hpp>
# include <elib/config/platform_config.hpp>
# 
# define ELIB_WORKAROUND(compiler, test) \
  ( ( compiler ) && ( ELIB_WORKAROUND_ ## test ) )
# 
# /* A clang bug */
# if ELIB_CLANG
#   if __clang_major__ <= 3 && __clang_minor__ < 4
#     define ELIB_WORKAROUND_CLANG_ENUMERATION_COMPARE_BUG 1
#   endif
# endif                                                      // clang bugs
# 
# if  ELIB_GNU
#   define ELIB_WORKAROUND_GCC_NOEXCEPT_THIS_BUG 1
# endif
# 
#endif /* ELIB_WORKAROUND_HPP */