#ifndef ELIB_CONFIG_PLATFORM_CONFIG_HPP
#define ELIB_CONFIG_PLATFORM_CONFIG_HPP
# 
# if defined(linux) || defined(__linux) || defined(__linux__)
#   include <elib/config/platform/linux.ipp>
# elif defined(macintosh) || defined(Macintosh) \
        || (defined(__APPLE__) && defined(__MACH__))
#   include <elib/config/platform/apple.ipp>
# elif defined(_WIN32) || defined(__WIN32__) || defined(__WINDOWS__)
#   include <elib/config/platform/windows.ipp>
# elif defined(__CYGWIN__)
#   include <elib/config/platform/cygwin.ipp>
# elif defined(ELIB_ASSERT_CONFIG)
#   error "Platform config failed to deduce platform"
# endif
# 
# if defined(unix) || defined(__unix) || defined(__unix__) \
    || defined(_XOPEN_SOURCE) || defined(_POSIX_SOURCE) \
    || defined(ELIB_CONFIG_APPLE)
#   include <elib/config/platform/posix_config.ipp>
# endif
# 
#endif /* ELIB_CONFIG_PLATFORM_CONFIG_HPP */
