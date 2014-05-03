#ifndef ELIB_PREPROCESSOR_CAT_HPP
#define ELIB_PREPROCESSOR_CAT_HPP
#
# define ELIB_PP_CAT(x, y) ELIB_PP_CAT_(x, y)
#
# define ELIB_PP_CAT_(x, y) x##y
#
#endif /* ELIB_PREPROCESSOR_CAT_HPP */
