#ifndef ELIB_PREPROCESSOR_ARITY_HPP
#define ELIB_PREPROCESSOR_ARITY_HPP
#
# define ELIB_PP_ARITY(...) \
    ELIB_PP_ARITY_(__VA_ARGS__, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)
#
#
# define ELIB_PP_ARITY_(_15, _14, _13, _12, _11, _10, _9, _8, _7, _6, _5, _4, _3, _2, _1, _0, ...) _0
#
#endif /* ELIB_PREPROCESSOR_ARITY_HPP */
