#ifndef ELIB_MP_CONFIG_HPP
#define ELIB_MP_CONFIG_HPP
#
# include <elib/config.hpp>
# 
# ////////////////////////////////////////////////////////////////////////////////
# //                            CONFIGURATION                                          
# ////////////////////////////////////////////////////////////////////////////////
# 
# // allow the use of boost compatible names
# define ELIB_MP_BOOST_COMPATIBLE_NAMES 1
# 
# // test against boost in unit tests
# // TODO find a better place to put this
# define ELIB_MP_BOOST_MPL_TESTS 1
# 
# // Allow use of integral constants as sequences
# define ELIB_MP_SEQUENTIAL_INTEGRAL_CONSTANT 1
# 
# //-------------------------------- limits config ------------------------// 
# 
# // as defined in the c++11 standard 
# define ELIB_MP_MAX_PARAM_LIMIT 1024
# define ELIB_MP_MAX_REC_LIMIT 1024
#
# define ELIB_MP_DEFAULT_PARAM_LIMIT 256
# define ELIB_MP_DEFAULT_REC_LIMIT 256
#
# ifdef ELIB_MP_USE_MAX_LIMITS
#   define ELIB_MP_PARAM_LIMIT ELIB_MP_MAX_PARAM_LIMIT
#   define ELIB_MP_REC_LIMIT ELIB_MP_MAX_REC_LIMIT
# endif
#
# ifndef ELIB_MP_PARAM_LIMIT
#   define ELIB_MP_PARAM_LIMIT ELIB_MP_DEFAULT_PARAM_LIMIT
# endif
#
# ifndef ELIB_MP_REC_LIMIT
#   define ELIB_MP_REC_LIMIT ELIB_MP_DEFAULT_REC_LIMIT
# endif
#
# define ELIB_MP_ASSERT_PARAM_LIMIT(pack)                                      \
  static_assert(sizeof...(pack) <= ELIB_MP_PARAM_LIMIT,                        \
    "the number of parameters is limited to " ELIB_PP_STR(ELIB_MP_PARAM_LIMIT) \
  )
#   
# define ELIB_MP_ASSERT_REC_LIMIT(pack)                             \
  static_assert(sizeof...(pack) <= ELIB_MP_REC_LIMIT,               \
    "the number of parameters in the pack will cause the recursion" \
    " limit to be violated: " ELIB_PP_STR(ELIB_MP_REC_LIMIT)        \
  )
#
#endif /* ELIB_MP_CONFIG_HPP */
