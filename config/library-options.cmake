################################################################################
##                         Library Parts                                      ##
################################################################################
# NOTE There are top level files that are not a member of any library part
# config, any, fmt, lexical_cast, scope_guard are some examples.

option(ELIB_CORE "Build top level source" ON)
option(ELIB_AUX "Build aux" ON)
option(ELIB_CONFIG "Build configuration source" ON)
option(ELIB_CONTAINER "Build containers" ON)
option(ELIB_ENUMERATION "Build enumeration" ON)
option(ELIB_EXCEPTION "Build except" ON)
option(ELIB_FILESYSTEM "Build filesystem" ON)
option(ELIB_FUNCTIONAL "Build functional" ON)
option(ELIB_ITERATOR "Build iterators" ON)
option(ELIB_LOGGING "Build logging library" ON)
option(ELIB_MEMORY "Build memory library" ON)
option(ELIB_MP "Build metaprogramming library" ON)
option(ELIB_PREPROCESSOR "Build preprocessor library" ON)


# Experimental libraries
option(ELIB_CONTRACT_ASSERT "Build contract assert source" ON)
option(ELIB_WEB "Build web library (experimental)" ON)