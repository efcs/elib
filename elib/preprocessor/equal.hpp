#ifndef ELIB_PREPROCESSOR_EQUAL_HPP
#define ELIB_PREPROCESSOR_EQUAL_HPP
#
# include <elib/preprocessor/not_equal.hpp>
# include <elib/preprocessor/logical.hpp>
#
# define ELIB_PP_EQUAL(x, y) ELIB_PP_NOT_C( ELIB_PP_NOT_EQUAL(x, y) )
#
#
#endif /* ELIB_PREPROCESSOR_EQUAL_HPP */
