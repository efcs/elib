#ifndef ELIB_AUX_ATTRIBUTES_HPP
# define ELIB_AUX_ATTRIBUTES_HPP

# include <elib/config.hpp>

# if ! defined(ELIB_CONFIG_NO_ATTRIBUTES)
#   define ELIB_NORETURN [[noreturn]]
# else
#   define ELIB_NORETURN
# endif

#endif /* ELIB_AUX_ATTRIBUTES_HPP */