#ifndef ELIB_CONFIG_COMPILER_CONFIG_HPP
#define ELIB_CONFIG_COMPILER_CONFIG_HPP
# 
# define ELIB_CONFIG_CLANG 0
# define ELIB_CONFIG_GNU 0
# 
# if defined(__clang__)
#   undef ELIB_CONFIG_CLANG
#   define ELIB_CONFIG_CLANG 1
#   define ELIB_CONFIG_COMPILER_NAME clang
#   /* __GNUC__ must come after clang since clang also defines it */
# elif (defined(__GNUG__) && !defined(__clang__))
#   undef ELIB_CONFIG_GNU
#   define ELIB_CONFIG_GNU 1
#   define ELIB_CONFIG_COMPILER_NAME GNU
# else
#   error ELIB cannot find compiler information
# endif
# 
# 
#endif /* ELIB_CONFIG_COMPILER_CONFIG_HPP */