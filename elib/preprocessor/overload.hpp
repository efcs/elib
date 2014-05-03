#ifndef ELIB_PREPROCESSOR_OVERLOAD_HPP
#define ELIB_PREPROCESSOR_OVERLOAD_HPP
#
# include <elib/preprocessor/arity.hpp>
# include <elib/preprocessor/cat.hpp>
#
# define ELIB_PP_OVERLOAD(name, ...) \
    ELIB_PP_CAT(name, ELIB_PP_ARITY(__VA_ARGS__))
#
# define ELIB_PP_OVERLOAD_CALL(name, ...) \
    ELIB_PP_CAT(name, ELIB_PP_ARITY(__VA_ARGS__))(__VA_ARGS__)
#
#endif /* ELIB_PREPROCESSOR_OVERLOAD_HPP */
