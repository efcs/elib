#ifndef ELIB_CONFIG_STANDARD_CONFIG_HPP
#define ELIB_CONFIG_STANDARD_CONFIG_HPP
# 
# if __cplusplus < 201103L
#   error C++11 or greater required
# elif __cplusplus == 201103L
#   define ELIB_CONFIG_CXX11 1
#   define ELIB_CONFIG_CXX1Y 0
#   define ELIB_CONFIG_CXX14 0
# else
#   define ELIB_CONFIG_CXX11 0
#   define ELIB_CONFIG_CXX1Y 1
#   define ELIB_CONFIG_CXX14 0
# endif

#endif /* ELIB_CONFIG_STANDARD_CONFIG_HPP */