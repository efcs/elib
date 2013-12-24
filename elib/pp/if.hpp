#ifndef ELIB_PP_IF_HPP
#define ELIB_PP_IF_HPP
# 
# include <elib/pp/cat.hpp>
# include <elib/pp/bool.hpp>
# 
# define ELIB_PP_IF(val, then, else) \
  ELIB_PP_IF_C( ELIB_PP_BOOL(val), then, else)
# 
# define ELIB_PP_IF_C(b, then, else) \
  ELIB_PP_CAT(ELIB_PP_IF_C_, b)(then, else)
# 
# define ELIB_PP_IF_C_0(then, else) else
# 
# define ELIB_PP_IF_C_1(then, else) then
# 
#endif /* ELIB_PP_IF_HPP */