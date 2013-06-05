# Author: Eric Fiselier
# Compiler: GCC/Clang
# 
# I apologize to windows users, I have built it this project on windows,
# but the project configurations in this make file DO NOT WORK and they 
# must be commented out.

add_definitions(-fPIC)

#turn assertions on/off
add_definitions(-D NDEBUG)

find_package( Threads REQUIRED )

set(dotSrc lock.cpp log.cpp semaphore.cpp sharedlock.cpp)

# compile into objects
add_library(ObjLib OBJECT ${dotSrc})

#create static & shared libraries
add_library(elib STATIC $<TARGET_OBJECTS:ObjLib>)
add_library(elib_s SHARED $<TARGET_OBJECTS:ObjLib>)

target_link_libraries(elib ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(elib_s ${CMAKE_THREAD_LIBS_INIT})

file(GLOB lib_headers "${CMAKE_CURRENT_LIST_DIR}/include/elib/*.h" )
install(TARGETS elib ARCHIVE DESTINATION lib)
install(TARGETS elib_s LIBRARY DESTINATION lib)
install(FILES ${lib_headers} DESTINATION include/elib)
				

