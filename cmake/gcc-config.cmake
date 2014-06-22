# check min version
config_message(STATUS "Configuring for Compiler: GCC")
    
if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS "4.8.0")
    message(WARNING "Insufficient GCC Version")
endif()

if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS "4.8.3")
    set(ELIB_WEB_SOURCE OFF CACHE BOOL "build web library" FORCE)
endif()
    
if(CMAKE_CXX_COMPILER_VERSION VERSION_EQUAL "4.9.0"
    OR CMAKE_CXX_COMPILER_VERSION VERSION_GREATER "4.9.0")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -fdiagnostics-color=auto ")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fmax-errors=5")