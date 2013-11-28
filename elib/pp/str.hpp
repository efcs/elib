#ifndef ELIB_PP_STR_HPP
#define ELIB_PP_STR_HPP
# 
# // Delay stringification so macros are expanded
# define ELIB_PP_STR(s) ELIB_PP_STR_(s)
# 
# define ELIB_PP_STR_(s) #s
# 
#endif /* ELIB_PP_STR_HPP */