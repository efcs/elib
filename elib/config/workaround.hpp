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
#   if __clang_major__ <= 3 && __clang_minor__ <= 4
#     /* Clang compares all enumerations as if they were unsigned */
#     define ELIB_WORKAROUND_CLANG_ENUMERATION_COMPARE_BUG 1
#   endif
#   
#   if __clang_major__ <= 3 && __clang_minor__ <= 4
#     /* absolutely bizzare bug from clang where using 
#      * __is_final in some contexts will cause clang to spit out:
#      *     error: cannot yet mangle expression type UnaryTypeTraitExpr
#      */
#     define ELIB_WORKAROUND_CLANG_IS_FINAL_BUG 1
#   endif
# endif                                                      // clang bugs
# 
# 
# if ELIB_CONFIG_GNU
#   /* GCC does not accept "this" in noexcept clauses */
#   define ELIB_WORKAROUND_GCC_NOEXCEPT_THIS_BUG 1
# endif
# 
# 
# if ELIB_CONFIG_LIBSTDCXX
#   /* libstdc++ lacks support for some parts of <type_traits> */
#   define ELIB_WORKAROUND_LIBSTDCXX_LIMITED_TYPE_TRAITS 1
# endif
# 
#endif /* ELIB_CONFIG_WORKAROUND_HPP */