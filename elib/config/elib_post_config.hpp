#ifndef ELIB_CONFIG_ELIB_POST_CONFIG_HPP
#define ELIB_CONFIG_ELIB_POST_CONFIG_HPP
# 
# if ! defined(ELIB_CONFIG_NO_ATTRIBUTES)
#   define ELIB_NORETURN [[noreturn]]
# else
#   define ELIB_NORETURN
# endif
# 
# if __cplusplus > 201103L
#   define ELIB_CXX1Y_CONSTEXPR constexpr
# else 
#   define ELIB_CXX1Y_CONSTEXPR inline
# endif
#
#endif /* ELIB_CONFIG_ELIB_POST_CONFIG_HPP */