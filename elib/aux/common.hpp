#ifndef ELIB_AUX_COMMON_HPP
#define ELIB_AUX_COMMON_HPP
# 
# include <elib/config.hpp>
# include <elib/aux/declval.hpp>
# 
# 

# 


# if __cplusplus <= 201303L
#   define ELIB_CXX14_CONSTEXPR inline
# else
#   define ELIB_CXX14_CONSTEXPR constexpr
# endif
# 
#endif /* ELIB_AUX_COMMON_HPP */