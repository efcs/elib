#ifndef ELIB_CONFIG_COMPILER_CLANG_HPP
#define ELIB_CONFIG_COMPILER_CLANG_HPP

# define ELIB_COMPILER clang
# define ELIB_CONFIG_CLANG 1

# if __cplusplus > 201103L && __has_feature(cxx_variable_templates)
#   define ELIB_CONFIG_HAS_VARIABLE_TEMPLATES
# endif

#endif /* ELIB_CONFIG_COMPILER_CLANG_HPP */