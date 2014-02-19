#ifndef ELIB_CONFIG_LIBRARY_CONFIG_HPP
#define ELIB_CONFIG_LIBRARY_CONFIG_HPP
# 
# /* include a file to get library version macros */
# include <cstddef>
# 
# if defined(__GLIBCXX__)
#   include <elib/config/library/libstdcxx.hpp>
# elif defined(_LIBCPP_VERSION)
#   include <elib/config/library/libcxx.hpp>
# elif defined(_CPPLIB_VER)
#   include <elib/config/library/dinkumware.hpp>
# elif defined(ELIB_ASSERT_CONFIG)
#   error "Unknown standard library"
# endif
# 
#endif /* ELIB_CONFIG_LIBRARY_CONFIG_HPP */