#ifndef ELIB_PP_CAT_HPP
#define ELIB_PP_CAT_HPP
# 
# // Delay concatination so that the parameters are expanded
# // by the preprocessor
# define ELIB_PP_CAT(tk1, tk2) \
  ELIB_PP_CAT_(tk1, tk2)
#
# 
# define ELIB_PP_CAT_(tk1, tk2) tk1##tk2
# 
# 
#endif /* ELIB_PP_CAT_HPP */