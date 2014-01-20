#ifndef ELIB_CONFIG_STANDARD_CONFIG_HPP
#define ELIB_CONFIG_STANDARD_CONFIG_HPP
# 
# if __cplusplus < 201100
#   error C++11 or greater required
# elseif __cplusplus < 201300
#   define ELIB_CONFIG_CXX11 1
#   define ELIB_CONFIG_CXX1Y 0
# else
#   define ELIB_CONFIG_CXX11 0
#   define ELIB_CONFIG_CXX1Y 1
# endif

#endif /* ELIB_CONFIG_STANDARD_CONFIG_HPP */