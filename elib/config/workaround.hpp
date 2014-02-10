#ifndef ELIB_CONFIG_WORKAROUND_HPP
#define ELIB_CONFIG_WORKAROUND_HPP
# 
# include <elib/config/compiler_config.hpp>
# include <elib/config/platform_config.hpp>
# include <elib/config/library_config.hpp>
# 
# define ELIB_WORKAROUND(compiler_or_lib, test) \
  ( ( compiler_or_lib ) && ( ELIB_WORKAROUND_ ## test ) )
# 
# //////////////////////////////////////////////////////////////////////////////
# //                        Specific Workarounds
# //////////////////////////////////////////////////////////////////////////////
# 
# if ELIB_CONFIG_CLANG
#   if __clang_major__ <= 3 && __clang_minor__ < 4
#     define ELIB_WORKAROUND_CLANG_ENUMERATION_COMPARE_BUG 1
#   endif
#   if __clang_major__ <= 3 && __clang_minor__ <= 4
#     define ELIB_WORKAROUND_CLANG_IS_FINAL_BUG 1
#   endif
# endif                                                      // clang bugs
# 
# 
# if ELIB_CONFIG_GNU
#   define ELIB_WORKAROUND_GCC_NOEXCEPT_THIS_BUG 1
# endif
# 
# 
# if ELIB_CONFIG_LIBSTDCXX
#   define ELIB_WORKAROUND_LIBSTDCXX_LIMITED_TYPE_TRAITS 1
# endif
# 
#endif /* ELIB_CONFIG_WORKAROUND_HPP */