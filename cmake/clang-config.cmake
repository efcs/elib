config_message(STATUS "Configuring for Compiler: Clang")

if (CONFIG_CXX1Y AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS "3.4")
    message(FATAL_ERROR "Insufficient Clang Version for C++1y")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ferror-limit=3")

string(REPLACE " " ";" CXX_FLAGS_LIST ${CMAKE_CXX_FLAGS})
list(FIND CXX_FLAGS_LIST "-stdlib=libc++" LIBCXX_FLAG_POS)
if (LIBCXX_FLAG_POS EQUAL -1)
    set(ELIB_WEB_SOURCE OFF CACHE BOOL "Build web library" FORCE)
endif()