#ifndef ELIB_CONFIG_COMPILER_CLANG_HPP
#define ELIB_CONFIG_COMPILER_CLANG_HPP

# define ELIB_COMPILER clang
# define ELIB_CONFIG_CLANG 1

// Attempt to map Apples Clang version to the LLVM version it was taken from
# if !defined(ELIB_CONFIG_APPLE)
#   define ELIB_COMPILER_VERSION (__clang_major__ * 10000) + (__clang_minor__ * 100) + (__clang_patchlevel__)
# else /* ELIB_CONFIG_APPLE */
#   if __clang_major__ == 5
#     if   __clang_minor__ == 0
#       define ELIB_COMPILER_VERSION 30300
#     elif __clang_minor__ == 1
#       define ELIB_COMPILER_VERSION 30400
#     endif
#   endif
# endif

# if !defined(ELIB_COMPILER_VERSION)
#   error Unknown version of Apple LLVM found when probing Clang.
# endif

# if __cplusplus > 201103L && __has_feature(cxx_variable_templates)
#   define ELIB_CONFIG_HAS_VARIABLE_TEMPLATES
# endif

#endif /* ELIB_CONFIG_COMPILER_CLANG_HPP */