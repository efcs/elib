# Author: Eric Fiselier
# Compiler: GCC/Clang
# 
# I apologize to windows users, I have built it this project on windows,
# but the project configurations in this make file DO NOT WORK and they 
# must be commented out.

#turn assertions on/off
add_definitions(-D NDEBUG)

find_package( Threads REQUIRED )

set(dotSrc alltests.cpp semaphore_test.cpp sharedlock_test.cpp thread_test.cpp)
add_executable(elib_tests ${dotSrc})

#create static & shared libraries
target_link_libraries(elib_tests ${CMAKE_THREAD_LIBS_INIT} -lelib)



