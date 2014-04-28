#ifndef ELIB_CONFIG_COMPILER_GCC_HPP
#define ELIB_CONFIG_COMPILER_GCC_HPP

# define ELIB_COMPILER GCC
# define ELIB_COMPILER_VERSION (__GNUC__ * 10000) + (__GNUC_MINOR__ * 100) + __GNUC_PATCHLEVEL__
# define ELIB_CONFIG_GCC 1

# if ELIB_COMPILER < 40800L
#   define ELIB_CONFIG_NO_INHERITING_CONSTRUCTORS 1
# endif

# if ELIB_COMPILER_VERSION < 40801L
#   define ELIB_CONFIG_NO_ATTRIBUTES 1
# endif

/** GCC claims they support ref qualifiers in 4.8.1
 * But they are buggy and cause compile errors */
# if ELIB_COMPILER_VERSION < 40802L
#   define ELIB_CONFIG_NO_REF_QUALIFIERS 1
# endif

#endif /* ELIB_CONFIG_COMPILER_GCC_HPP */