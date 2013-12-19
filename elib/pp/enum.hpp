#ifndef ELIB_PP_ENUM_HPP
#define ELIB_PP_ENUM_HPP
# 
# include <elib/pp/concat.hpp>
# include <elib/mp/overload.hpp>
# 
# 
# define ELIB_PP_ENUM(n, name) ELIB_PP_CONCAT(ELIB_PP_ENUM_I, n)(name)
# 
# define ELIB_PP_ENUM_I1(name) name##1
# define ELIB_PP_ENUM_I2(name) name##1 , name##2
# define ELIB_PP_ENUM_I3(name) name##1 , name##2 , name##3
# define ELIB_PP_ENUM_I4(name) name##1 , name##2 , name##3 , name##4
# define ELIB_PP_ENUM_I5(name) name##1 , name##2 , name##3 , name##4 , name##5
# define 


#endif /* ELIB_PP_ENUM_HPP */
