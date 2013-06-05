# Author: Eric Fiselier
# Compiler: GCC/Clang
# 
# I apologize to windows users, I have built it this project on windows,
# but the project configurations in this make file DO NOT WORK and they 
# must be commented out.

add_definitions(-fPIC)

set(dotSrc lock.cpp log.cpp semaphore.cpp sharedlock.cpp)

# compile into objects
add_library(ObjLib OBJECT ${dotSrc})

#create static & shared libraries
add_library(elib SHARED $<TARGET_OBJECTS:ObjLib>)
add_library(elib_static STATIC $<TARGET_OBJECTS:ObjLib>)

target_link_libraries(elib ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(elib_static)


if(CMAKE_BUILD_TYPE MATCHES RELEASE)
	file(GLOB lib_headers "${CMAKE_CURRENT_LIST_DIR}/include/elib/*.h" )
	install(TARGETS elib LIBRARY DESTINATION lib)
	install(TARGETS elib_static ARCHIVE DESTINATION lib)
	install(FILES ${lib_headers} DESTINATION include/elib)
endif()

				

