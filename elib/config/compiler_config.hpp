#ifndef ELIB_COMPILER_CONFIG_HPP
#define ELIB_COMPILER_CONFIG_HPP


#   undef ELIB_GNU
#   undef ELIB_CLANG
#   undef ELIB_MSVC
#   undef ELIB_MINGW
#   undef ELIB_COMPILER_NAME

#   if defined(__GNUC__) && !defined(__clang__)
#     define ELIB_GNU   1
#     define ELIB_COMPILER_NAME GCC
#   elif defined(__clang__)
#     define ELIB_CLANG 1
#     define ELIB_COMPILER_NAME clang
#   elif defined(__MINGW32__)
#     define ELIB_MINGW 1
#     define ELIB_COMPILER_NAME mingw
#   elif _MSC_VER
#     define ELIB_MSVC  1
#     define ELIB_COMPILER_NAME MSVC
#   else
#     error ELIB cannot find compiler information
#   endif

# define __ELIB_DEF_COUNT defined(ELIB_GNU) + defined(ELIB_CLANG) + \
                          defined(ELIB_MSVC) + defined(ELIB_MINGW)


# if __ELIB_DEF_COUNT == 0
#   error ELIB compiler info not set
# endif

# if __ELIB_DEF_COUNT > 1
#   error ELIB compiler info has multiple definitions
# endif


# undef __ELIB_DEF_COUNT


#endif /* ELIB_COMPILER_CONFIG_HPP */