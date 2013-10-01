#ifndef ELIB_CONFIG_HPP
# define ELIB_CONFIG_HPP

// include common macros

# include <elib/version_config.hpp>

# ifdef ELIB_DEFAULT_CONFIG
#   define ELIB_PLATFORM_DEFAULT_CONFIG
#   define ELIB_COMPILER_DEFAULT_CONFIG
# endif


# include <elib/platform_config.hpp>
# include <elib/compiler_config.hpp>

// include common macros
# include <elib/common_def.hpp>

#endif /* ELIB_CONFIG_HPP */