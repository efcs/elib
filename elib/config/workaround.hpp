#ifndef ELIB_CONFIG_WORKAROUND_HPP
#define ELIB_CONFIG_WORKAROUND_HPP
# 
# include <elib/config/compiler_config.hpp>
# include <elib/config/platform_config.hpp>
# include <elib/config/library_config.hpp>
# include <elib/config/standard_config.hpp>
# 
# /* C++ standard workaround guards */
# if defined(ELIB_CONFIG_CXX11)
#   define ELIB_WORKAROUND_GUARD_ELIB_CONFIG_CXX11 1
# else
#   define ELIB_WORKAROUND_GUARD_ELIB_CONFIG_CXX11 0
# endif
# if defined(ELIB_CONFIX_CXX1Y)
#   define ELIB_WORKAROUND_GUARD_ELIB_CONFIG_CXX1Y 1
# else
#   define ELIB_WORKAROUND_GUARD_ELIB_CONFIG_CXX1Y 0
# endif
# if defined(ELIB_CONFIG_CXX14)
#   define ELIB_WORKAROUND_GUARD_ELIB_CONFIG_CXX14 1
# else
#   define ELIB_WORKAROUND_GUARD_ELIB_CONFIG_CXX14 0
# endif
# 
# /* compiler workaround guards */
# if defined(ELIB_CONFIG_GCC)
#   define ELIB_WORKAROUND_GUARD_ELIB_CONFIG_GCC 1
# else
#   define ELIB_WORKAROUND_GUARD_ELIB_CONFIG_GCC 0
# endif
# if defined(ELIB_CONFIG_CLANG)
#   define ELIB_WORKAROUND_GUARD_ELIB_CONFIG_CLANG 1
# else
#   define ELIB_WORKAROUND_GUARD_ELIB_CONFIG_CLANG 0
# endif
# if defined(ELIB_CONFIG_MSVC)
#   define ELIB_WORKAROUND_GUARD_ELIB_CONFIG_MSVC 1
# else
#   define ELIB_WORKAROUND_GUARD_ELIB_CONFIG_MSVC 0
# endif
# if defined(ELIB_CONFIG_EDG)
#   define ELIB_WORKAROUND_GUARD_ELIB_CONFIG_EDG 1
# else
#   define ELIB_WORKAROUND_GUARD_ELIB_CONFIG_EDG 0
# endif
#  
# /* library workaround guards */
# if defined(ELIB_CONFIG_LIBSTDCXX)
#   define ELIB_WORKAROUND_GUARD_ELIB_CONFIG_LIBSTDCXX 1
# else
#   define ELIB_WORKAROUND_GUARD_ELIB_CONFIG_LIBSTDCXX 0
# endif
# if defined(ELIB_CONFIG_LIBCXX)
#   define ELIB_WORKAROUND_GUARD_ELIB_CONFIG_LIBCXX 1
# else
#   define ELIB_WORKAROUND_GUARD_ELIB_CONFIG_LIBCXX 0
# endif
# if defined(ELIB_CONFIG_DINKUMWARE)
#   define ELIB_WORKAROUND_GUARD_ELIB_CONFIG_DINKUMWARE 1
# else 
#   define ELIB_WORKAROUND_GUARD_ELIB_CONFIG_DINKUMWARE 0
# endif
# 
# /* platform workaround guards */
# if defined(ELIB_CONFIG_LINUX)
#   define ELIB_WORKAROUND_GUARD_ELIB_CONFIG_LINUX 1
# else
#   define ELIB_WORKAROUND_GUARD_ELIB_CONFIG_LINUX 0
# endif
# if defined(ELIB_CONFIG_APPLE)
#   define ELIB_WORKAROUND_GUARD_ELIB_CONFIG_APPLE 1
# else
#   define ELIB_WORKAROUND_GUARD_ELIB_CONFIG_APPLE 0
# endif
# if defined(ELIB_CONFIG_WINDOWS)
#   define ELIB_WORKAROUND_GUARD_ELIB_CONFIG_WINDOWS 1
# else
#   define ELIB_WORKAROUND_GUARD_ELIB_CONFIG_WINDOWS 0
# endif
# if defined(ELIB_CONFIG_CYGWIN)
#   define ELIB_WORKAROUND_GUARD_ELIB_CONFIG_CYGWIN 1
# else
#   define ELIB_WORKAROUND_GUARD_ELIB_CONFIG_CYGWIN 0
# endif
# 
# if defined(ELIB_CONFIG_POSIX)
#   define ELIB_WORKAROUND_GUARD_ELIB_CONFIG_POSIX 1
# else
#   define ELIB_WORKAROUND_GUARD_ELIB_CONFIG_POSIX 0
# endif
# 
# 
# define ELIB_WORKAROUND(compiler_or_lib, test)   \
  ( ( ELIB_WORKAROUND_GUARD_ ## compiler_or_lib ) \
  && ( ELIB_WORKAROUND_GUARD_ ## test ) )
# 
# //////////////////////////////////////////////////////////////////////////////
# //                        Specific Workarounds
# //////////////////////////////////////////////////////////////////////////////
# 
# if defined(ELIB_CONFIG_CLANG)
#   if __clang_major__ < 5 || (__clang_major__ == 5 && __clang_minor__ <= 0)
#     /* Clang compares all enumerations as if they were unsigned */
#     define ELIB_WORKAROUND_GUARD_CLANG_ENUMERATION_COMPARE_BUG 1
#   else
#     define ELIB_WORKAROUND_GUARD_CLANG_ENUMERATION_COMPARE_BUG 0
#   endif
#   
#   if __clang_major__ < 5 || (__clang_major__ == 5 && __clang_minor__ <= 0)
#     /* absolutely bizzare bug from clang where using 
#      * __is_final in some contexts will cause clang to spit out:
#      *     error: cannot yet mangle expression type UnaryTypeTraitExpr
#      */
#     define ELIB_WORKAROUND_GUARD_CLANG_IS_FINAL_BUG 1
#   else
#     define ELIB_WORKAROUND_GUARD_CLANG_IS_FINAL_BUG 0
#   endif
# endif                                                      // clang bugs
# 
# 
# if defined(ELIB_CONFIG_GCC)
#   /* GCC does not accept "this" in noexcept clauses */
#   define ELIB_WORKAROUND_GUARD_GCC_NOEXCEPT_THIS_BUG 1
# endif
# 
# 
# if defined(ELIB_CONFIG_LIBSTDCXX)
#   /* libstdc++ lacks support for some parts of <type_traits> */
#   define ELIB_WORKAROUND_GUARD_LIBSTDCXX_LIMITED_TYPE_TRAITS 1
# endif
# 
#endif /* ELIB_CONFIG_WORKAROUND_HPP */