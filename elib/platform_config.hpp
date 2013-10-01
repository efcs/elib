#ifndef ELIB_PLATFORM_CONFIG_HPP
#define ELIB_PLATFORM_CONFIG_HPP


# include <elib/version_config.hpp>


# ifdef ELIB_PLATFORM_DEFAULT_CONFIG

#   undef ELIB_WINDOWS
#   undef ELIB_APPLE
#   undef ELIB_POSIX

#   ifdef _WIN32
#     define ELIB_WINDOWS 1
#   elif __APPLE__ && __MACH__
#     define ELIB_APPLE 1
#   elif __posix__ || __unix__ || __linux__
#     define ELIB_POSIX 1
#   else
#     error ELIB failed to deduce platform information
#   endif


# endif                                        // ELIB_PLATFORM_DEFAULT_CONFIG


# define __ELIB_DEF_COUNT defined(ELIB_WINDOWS) + defined(ELIB_APPLE) + \
                          defined(ELIB_POSIX)


# if __ELIB_DEF_COUNT == 0
#   error ELIB platform information is not defined
# endif

# if __ELIB_DEF_COUNT > 1
#   error ELIB platform information has multiple definitions
# endif


# undef __ELIB_DEF_COUNT

#endif /* ELIB_PLATFORM_CONFIG_HPP */