#ifndef ELIB_COMPILER_CONFIG_HPP
#define ELIB_COMPILER_CONFIG_HPP
# 
# if defined(__clang__)
#   define ELIB_CLANG 1
#   define ELIB_COMPILER_NAME clang
#   /* __GNUC__ must come after clang since clang also defines it */
# elif defined(__GNUC__) 
#   define ELIB_GNU   1
#   define ELIB_COMPILER_NAME GCC
# elif defined(__MINGW32__)
#   define ELIB_MINGW 1
#   define ELIB_COMPILER_NAME mingw
# elif _MSC_VER
#   define ELIB_MSVC  1
#   define ELIB_COMPILER_NAME MSVC
# else
#   error ELIB cannot find compiler information
# endif
# 
# 
#endif /* ELIB_COMPILER_CONFIG_HPP */