#ifndef ELIB_PP_EQUAL_HPP
#define ELIB_PP_EQUAL_HPP
#
# include <elib/pp/not_equal.hpp>
# include <elib/pp/logical.hpp>
#
# define ELIB_PP_EQUAL(x, y) ELIB_PP_NOT_C( ELIB_PP_NOT_EQUAL(x, y) )
#
#
#endif ELIB_PP_EQUAL_HPP
