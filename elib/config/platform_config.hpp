#ifndef ELIB_CONFIG_PLATFORM_CONFIG_HPP
#define ELIB_CONFIG_PLATFORM_CONFIG_HPP
# 
# if defined(linux) || defined(__linux) || defined(__linux__)
#   include <elib/config/platform/linux.hpp>
# elif defined(macintosh) || defined(Macintosh) \
        || (defined(__APPLE__) && defined(__MACH__))
#   include <elib/config/platform/apple.hpp>
# elif defined(_WIN32) || defined(__WIN32__) || defined(__WINDOWS__)
#   include <elib/config/platform/windows.hpp>
# elif defined(__CYGWIN__)
#   include <elib/config/platform/cygwin.hpp>
# elif defined(ELIB_ASSERT_CONFIG)
#   error "Platform config failed to deduce platform"
# endif
# 
# if defined(unix) || defined(__unix) || defined(__unix__) \
    || defined(_XOPEN_SOURCE) || defined(_POSIX_SOURCE)
#   include <elib/config/posix_config.hpp>
# endif
# 
#endif /* ELIB_CONFIG_PLATFORM_CONFIG_HPP */