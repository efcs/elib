#ifndef ELIB_PP_OVERLOAD_HPP
#define ELIB_PP_OVERLOAD_HPP
# 
# include <elib/pp/cat.hpp>
# include <elib/pp/arity.hpp>
# 
# // Determine a macro overload via arity
# define ELIB_PP_OVERLOAD(name, ...) \
  ELIB_PP_CAT(name, ELIB_PP_ARITY(__VA_ARGS__))
# 
# 
# endif /* ELIB_PP_OVERLOAD_HPP */