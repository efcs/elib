#ifndef ELIB_PP_CAT_HPP
#define ELIB_PP_CAT_HPP
#
#
# define ELIB_PP_CAT(x, y) ELIB_PP_CAT_(x, y)
#
# define ELIB_PP_CAT_(x, y) x##y
#
#endif /* ELIB_PP_CAT_HPP */
