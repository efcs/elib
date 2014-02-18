#ifndef ELIB_CONFIG_LIBRARY_LIBSTDCXX_HPP
#define ELIB_CONFIG_LIBRARY_LIBSTDCXX_HPP
# 
# define ELIB_LIBRARY libstdcxx
# define ELIB_CONFIG_LIBSTDCXX 1
# 
# if !defined(__GLIBCXX__)
#   error "unsupported version of libstdc++"
# endif
# 
# if __GLIBCXX__ > 20131017L
#   define ELIB_CONFIG_HAS_REGEX 1
# endif
# 
#endif /* ELIB_CONFIG_LIBRARY_LIBSTDCXX_HPP */