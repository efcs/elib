#ifndef ELIB_CONFIG_LIBRARY_CONFIG_HPP
#define ELIB_CONFIG_LIBRARY_CONFIG_HPP
# 
# /* include a file to get library version macros */
# include <utility>
# 
# define ELIB_CONFIG_LIBSTDCXX 0
# define ELIB_CONFIG_LIBCXX 0
# 
# if defined(__GLIBCXX__)
#   undef ELIB_CONFIG_LIBSTDCXX
#   define ELIB_CONFIG_LIBSTDCXX __GLIBCXX__
# elif defined(_LIBCPP_VERSION)
#   undef ELIB_CONFIG_LIBCXX
#   define ELIB_CONFIG_LIBCXX _LIBCPP_VERSION
# else
#   error Unknown standard library
# endif
# 
#endif /* ELIB_CONFIG_LIBRARY_CONFIG_HPP */