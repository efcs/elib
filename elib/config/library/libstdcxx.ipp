#ifndef ELIB_CONFIG_LIBRARY_LIBSTDCXX_IPP
#define ELIB_CONFIG_LIBRARY_LIBSTDCXX_IPP
# 
# include <elib/config/compiler_config.hpp>
# include <cstddef>
# 
# define ELIB_LIBRARY libstdcxx
# define ELIB_LIBRARY_VERSION __GLIBCXX__
# define ELIB_CONFIG_LIBSTDCXX 1
# 
# if !defined(__GLIBCXX__)
#   error "unsupported version of libstdc++"
# endif
# 
# if defined(ELIB_CONFIG_GCC) && ELIB_COMPILER_VERSION < 40800L
#   define ELIB_CONFIG_LIBSTDCXX_HAS_TRIVIAL_DESTRUCTOR_WORKAROUND
#   define ELIB_CONFIG_NO_IS_NOTHROW_DESTRUCTIBLE
# endif
# 
# if defined(ELIB_CONFIG_GCC) && ELIB_COMPILER_VERSION >= 40900L
#   define ELIB_CONFIG_HAS_REGEX 1
# endif
# 
# /** GCC claims they support ref qualifiers in 4.8.1
 * But they are buggy and cause compile errors */
# if (__GNUC__ < 4 || (__GNUC__ == 4 && __GNUC_MINOR__ <= 8))  \
    && !defined(ELIB_CONFIG_NO_REF_QUALIFIERS)
#   define ELIB_CONFIG_NO_REF_QUALIFIERS 1
# endif
# 
#endif /* ELIB_CONFIG_LIBRARY_LIBSTDCXX_IPP */