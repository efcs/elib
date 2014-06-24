set(ELIB_WEB_SOURCE OFF CACHE BOOL "Build web library" FORCE)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-missing-include-dirs -U__STRICT_ANSI__")