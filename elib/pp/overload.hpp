#ifndef ELIB_PP_OVERLOAD_HPP
#define ELIB_PP_OVERLOAD_HPP
#
# include <elib/pp/arity.hpp>
# include <elib/pp/cat.hpp>
#
#
# define ELIB_PP_OVERLOAD(name, ...) \
    ELIB_PP_CAT(name, ELIB_PP_ARITY(__VA_ARGS__))
#
#
#endif /* ELIB_PP_OVERLOAD_HPP */
