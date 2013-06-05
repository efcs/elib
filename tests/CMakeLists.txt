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

add_library(TestObjLib OBJECT ${dotSrc})

add_executable(elib_test_static $<TARGET_OBJECTS:TestObjLib>)
add_executable(elib_test_shared $<TARGET_OBJECTS:TestObjLib>)

#create static & shared libraries
target_link_libraries(elib_test_static ${CMAKE_THREAD_LIBS_INIT} elib)
target_link_libraries(elib_test_shared ${CMAKE_THREAD_LIBS_INIT} elib_s)



