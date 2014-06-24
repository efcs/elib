
################################################################################
##                         Library Parts                                      ##
################################################################################
# NOTE There are top level files that are not a member of any library part
# config, any, fmt, lexical_cast, scope_guard are some examples.

option(ELIB_SOURCE "Build top level source" ON)
option(ELIB_AUX_SOURCE "Build aux" ON)
option(ELIB_CONTAINER_SOURCE "Build containers" ON)
option(ELIB_ENUMERATION_SOURCE "Build enumeration" ON)
option(ELIB_EXCEPTION_SOURCE "Build except" ON)
option(ELIB_FILESYSTEM_SOURCE "Build filesystem" ON)
option(ELIB_FUNCTIONAL_SOURCE "Build functional" ON)
option(ELIB_ITERATOR_SOURCE "Build iterators" ON)
option(ELIB_LOGGING_SOURCE "Build logging library" ON)
option(ELIB_MEMORY_SOURCE "Build memory library" ON)
option(ELIB_MP_SOURCE "Build metaprogramming library" ON)
option(ELIB_PP_SOURCE "Build preprocessor library" ON)


# Experimental libraries
option(ELIB_CONTRACT_ASSERT_SOURCE "Build contract assert source" ON)
option(ELIB_WEB_SOURCE "Build web library (experimental)" ON)