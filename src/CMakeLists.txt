# Author: Eric Fiselier
# Compiler: GCC/Clang
# 
# I apologize to windows users, I have built it this project on windows,
# but the project configurations in this make file DO NOT WORK and they 
# must be commented out.

add_definitions(-fPIC)

set(dotDir ${CMAKE_CURRENT_LIST_DIR})
aux_source_directory(${dotDir} dotSrc)
aux_source_directory(${dotDir}/argp argpSrc)
aux_source_directory(${dotDir}/fs fsSrc)
aux_source_directory(${dotDir}/enumeration enumSrc)
aux_source_directory(${dotDir}/log logSrc)
aux_source_directory(${dotDir}/lock lockSrc)

# compile into objects
add_library(ObjLib OBJECT ${dotSrc} ${argpSrc} ${fsSrc} ${enumSrc} ${logSrc}
                          ${lockSrc}
           )

#create static & shared libraries
add_library(elib SHARED $<TARGET_OBJECTS:ObjLib>)
add_library(elib_static STATIC $<TARGET_OBJECTS:ObjLib>)

################################################################################
##                      BOOST library configuration                           ##
################################################################################

find_package(Boost ${CONFIG_BOOST_VERSION}
             COMPONENTS system filesystem REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})



target_link_libraries(elib ${CMAKE_THREAD_LIBS_INIT} ${Boost_LIBRARIES})
target_link_libraries(elib_static ${CMAKE_THREAD_LIBS_INIT} ${Boost_LIBRARIES})


if(CMAKE_BUILD_TYPE MATCHES RELEASE)
	install(TARGETS elib LIBRARY DESTINATION lib)
	install(TARGETS elib_static ARCHIVE DESTINATION lib)
	install(DIRECTORY ${headerDir} DESTINATION include)
endif()

				

