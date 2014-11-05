#ifndef ELIB_CONFIG_COMPILER_CLANG_IPP
#define ELIB_CONFIG_COMPILER_CLANG_IPP

# define ELIB_COMPILER clang
# define ELIB_CONFIG_CLANG 1

# define ELIB_COMPILER_VERSION (__clang_major__ * 10000) + (__clang_minor__ * 100) + (__clang_patchlevel__)

# if __cplusplus > 201103L && __has_feature(cxx_variable_templates)
#   define ELIB_CONFIG_HAS_VARIABLE_TEMPLATES
# endif

#endif /* ELIB_CONFIG_COMPILER_CLANG_IPP */