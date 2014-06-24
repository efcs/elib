
################################################################################
##                         Library Parts                                      ##
################################################################################
# NOTE There are top level files that are not a member of any library part
# config, any, fmt, lexical_cast, scope_guard are some examples.

option(ELIB_CORE "Build top level source" ON)
option(ELIB_AUX "Build aux" OFF)
option(ELIB_CONFIG "Build configuration source" OFF)
option(ELIB_CONTAINER "Build containers" OFF)
option(ELIB_ENUMERATION "Build enumeration" OFF)
option(ELIB_EXCEPTION "Build except" OFF)
option(ELIB_FILESYSTEM "Build filesystem" ON)
option(ELIB_FUNCTIONAL "Build functional" OFF)
option(ELIB_ITERATOR "Build iterators" OFF)
option(ELIB_LOGGING "Build logging library" OFF)
option(ELIB_MEMORY "Build memory library" OFF)
option(ELIB_MP "Build metaprogramming library" OFF)
option(ELIB_PREPROCESSOR "Build preprocessor library" OFF)


# Experimental libraries
option(ELIB_CONTRACT_ASSERT "Build contract assert source" OFF)
option(ELIB_WEB "Build web library (experimental)" OFF)