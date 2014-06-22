config_message(STATUS "Configuring for Environment: Travis")
# On Travis, warnings should cause the build to fail.
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")

# The current TRAVIS enviroment for clang and libstdc++ emits this
# warning for std::hash since libstdc++ declares std::hash as a class
# not a struct.
if (${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-mismatched-tags")
endif()