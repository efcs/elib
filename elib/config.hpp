#ifndef ELIB_CONFIG_HPP
# define ELIB_CONFIG_HPP

// include common macros

# include <elib/config/version_config.hpp>

# ifdef ELIB_DEFAULT_CONFIG
#   define ELIB_PLATFORM_DEFAULT_CONFIG
#   define ELIB_COMPILER_DEFAULT_CONFIG
# endif


# include <elib/config/platform_config.hpp>
# include <elib/config/compiler_config.hpp>

// include common macros
# include <elib/common_def.hpp>

#endif /* ELIB_CONFIG_HPP */
