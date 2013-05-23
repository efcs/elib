# Author: Eric Fiselier
# Compiler: GCC/Clang
# 
# I apologize to windows users, I have built it this project on windows,
# but the project configurations in this make file DO NOT WORK and they 
# must be commented out.

set( CMAKE_BUILD_TYPE debug )
set( CMAKE_CXX_FLAGS_DISTRIBUTION "-O3" )
set( CMAKE_C_FLAGS_DISTRIBUTION "-O3" )
set( CMAKE_C_FLAGS_DEBUG "-g -O0" )
set( CMAKE_CXX_FLAGS_DEBUG "-g -O0" )
add_definitions(-std=c++11 -Wall -Wextra -pedantic)

# commondef.h always needs to be included 
add_definitions(-imacros include/elib/commondef.h)

#turn assertions on/off
#add_definitions(-D NDEBUG)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY $ENV{HOME}/lib/)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY $ENV{HOME}/lib/)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ..) 

find_package( Threads REQUIRED )

include_directories(. ${CMAKE_CURRENT_BINARY_DIR})
include_directories(include) 

aux_source_directory(src Sources)
aux_source_directory(tests Tests)

#create static library 
add_library(elib STATIC ${Sources})
target_link_libraries(elib ${CMAKE_THREAD_LIBS_INIT})

#create shared library 
add_library(elib_s SHARED ${Sources})
target_link_libraries(elib_s ${CMAKE_THREAD_LIBS_INIT})

# create test executable 
add_executable(test_elib ${Tests})
add_dependencies(test_elib elib)
#add_dependencies(test_elib elib_s)
target_link_libraries(test_elib ${CMAKE_THREAD_LIBS_INIT} elib)



