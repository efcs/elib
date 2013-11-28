#ifndef ELIB_PP_ARITY_HPP
#define ELIB_PP_ARITY_HPP
# 
# /* allow for macro overloading by counting # args */
# define ELIB_PP_ARITY(...) \
    ELIB_PP_ARITY_(__VA_ARGS__, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)
#
# 
# define ELIB_PP_ARITY_(_9, _8, _7, _6, _5, _4, _3, _2, _1, _, ...) _
# 
# 
#endif /* ELIB_PP_ARITY_HPP */