#ifndef ELIB_CONFIG_PLATFORM_CONFIG_HPP
#define ELIB_CONFIG_PLATFORM_CONFIG_HPP
# 
#   ifdef _WIN32
#     define ELIB_CONFIG_WINDOWS 1
#   elif defined(__APPLE__) && defined(__MACH__)
#     define ELIB_CONFIG_APPLE 1
#   elif defined(__posix__) || defined(__unix__) || defined(__linux__)
#     define ELIB_CONFIG_POSIX 1
#   else
#     error ELIB failed to deduce platform information
#   endif
# 
#endif /* ELIB_CONFIG_PLATFORM_CONFIG_HPP */