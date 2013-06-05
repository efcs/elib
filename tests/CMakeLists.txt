# Author: Eric Fiselier
# Compiler: GCC/Clang
# 
# I apologize to windows users, I have built it this project on windows,
# but the project configurations in this make file DO NOT WORK and they 
# must be commented out.


set(dotSrc alltests.cpp  thread_test.cpp sharedlock_test.cpp semaphore_test.cpp)

add_library(TestObjLib OBJECT ${dotSrc})

add_executable(elib_test_static $<TARGET_OBJECTS:TestObjLib>)
add_executable(elib_test_shared $<TARGET_OBJECTS:TestObjLib>)


target_link_libraries(elib_test_static elib_static ${LD_FLAGS} ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(elib_test_shared elib ${LD_FLAGS})



