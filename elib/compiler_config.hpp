#ifndef ELIB_COMPILER_CONFIG_HPP
#define ELIB_COMPILER_CONFIG_HPP


# include <elib/version_config.hpp>


# ifdef ELIB_COMPILER_DEFAULT_CONFIG

#   undef ELIB_GNU
#   undef ELIB_CLANG
#   undef ELIB_MSVC
#   undef ELIB_MINGW


#   if __GNUC__
#     define ELIB_GNU   1
#   elif __clang__
#     define ELIB_CLANG 1
#   elif __MINGW32__
#     define ELIB_MINGW 1
#   elif _MSC_VER
#     define ELIB_MSVC  1
#   else
#     error ELIB cannot find compiler information
#   endif


# endif                                        // ELIB_COMPILER_DEFAULT_CONFIG


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