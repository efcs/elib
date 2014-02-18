#ifndef ELIB_CONFIG_STANDARD_CONFIG_HPP
#define ELIB_CONFIG_STANDARD_CONFIG_HPP
# 
# define ELIB_CPLUSPLUS_11 201103L
# define ELIB_CPLUSPLUS_1Y 201303L
# /* the c++14 version is yet to be defined. So its set to a version
#    that will likely be bigger than c++14 for the time being */
# define ELIB_CPLUSPLUS_14 201600L
# 
# if __cplusplus < ELIB_CPLUSPLUS_11
#   error "C++11 or greater required"
# elif __cplusplus == ELIB_CPLUSPLUS_11
#   define ELIB_STANDARD C++11
#   define ELIB_CONFIG_CXX11 1
# elif __cplusplus < ELIB_CPLUSPLUS_14
#   define ELIB_STANDARD C++1Y
#   define ELIB_CONFIG_CXX1Y 1
# else
#   error "elib/config/standard_config.hpp needs to be updated for C++14"
#   define ELIB_STANDARD C++14
#   define ELIB_CONFIG_CXX14 1
# endif
#  
#endif /* ELIB_CONFIG_STANDARD_CONFIG_HPP */