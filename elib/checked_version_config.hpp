
#ifdef ELIB_VERSION

# define __ELIB_OLD_VERSION ELIB_VERSION
# define __ELIB_OLD_VERSION_STR ELIB_VERSION_STR

# undef ELIB_VERSION_CONFIG_HPP
# undef ELIB_VERSION

#include <elib/version_config.hpp>

# if ELIB_VERSION != __ELIB_OLD_VERSION
#   error ELIB versions do not match: \
    ( ELIB_VERSION_STR != __ELIB_OLD_VERSION_STR )
# endif

# undef __ELIB_OLD_VERSION
# undef __ELIB_OLD_VERSION_STR
