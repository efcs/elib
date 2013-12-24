#ifndef ELIB_PP_LOGICAL_HPP
#define ELIB_PP_LOGICAL_HPP
# 
# include <elib/pp/bool.hpp>
#
# /* not */
# define ELIB_PP_NOT(x) ELIB_PP_NOT_C(ELIB_PP_BOOL(x))
# 
# define ELIB_PP_NOT_C(x) ELIB_PP_NOT_C_##x
# 
# define ELIB_PP_NOT_C_0 1
# define ELIB_PP_NOT_C_1 0
# 
# /* and */
# define ELIB_PP_AND(x, y) ELIB_PP_AND_C(ELIB_PP_BOOL(x), ELIB_PP_BOOL(y))
# 
# define ELIB_PP_AND_C(x, y) ELIB_PP_AND_C_##x(y)
# 
# define ELIB_PP_AND_C_0(x) 0
# define ELIB_PP_AND_C_1(x) x
# 
# /* or */
# define ELIB_PP_OR(x, y) ELIB_PP_OR_C(ELIB_PP_BOOL(x), ELIB_PP_BOOL(y))
# 
# define ELIB_PP_OR_C(x, y) ELIB_PP_OR_C_##x(y)
# 
# define ELIB_PP_OR_C_0(x) x
# define ELIB_PP_OR_C_1(x) 1
# 
#endif /* ELIB_PP_LOGICAL_HPP */