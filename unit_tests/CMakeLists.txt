# Author: Eric Fiselier
# Compiler: GCC/Clang
# 
# I apologize to windows users, I have built it this project on windows,
# but the project configurations in this make file DO NOT WORK and they 
# must be commented out.

set(dotDir ${CMAKE_CURRENT_LIST_DIR})
set(mainSrc ${dotDir}/main.cpp)

aux_source_directory(${dotDir}/fs fsSrc)
aux_source_directory(${dotDir}/log logSrc)
aux_source_directory(${dotDir}/lock lockSrc)
aux_source_directory(${dotDir}/chrono chronoSrc)
aux_source_directory(${dotDir}/utility utilitySrc)
aux_source_directory(${dotDir}/argp argpSrc)
aux_source_directory(${dotDir}/enumeration enumSrc)

set(testSources ${mainSrc} ${logSrc} ${lockSrc} 
                ${utilitySrc} ${argpSrc} ${enumSrc}
                ${fsSrc} ${chronoSrc}
  )

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED OFF)
set(Boost_USE_STATIC_RUNTIME OFF)

# boost filesystem (and system) is used to test
# elib::fs
find_package(Boost ${CONFIG_BOOST_VERSION}
  COMPONENTS unit_test_framework
             system
             filesystem
  REQUIRED)

include_directories(${Boost_INCLUDE_DIRS} ${dotDir}/../ )

add_library(TestObjLib OBJECT ${testSources})

add_executable(elib_test_static $<TARGET_OBJECTS:TestObjLib>)
add_executable(elib_test_shared $<TARGET_OBJECTS:TestObjLib>)


target_link_libraries(elib_test_static elib_static ${LD_FLAGS} 
                      ${CMAKE_THREAD_LIBS_INIT} ${Boost_LIBRARIES})
                      
target_link_libraries(elib_test_shared elib ${LD_FLAGS} ${CMAKE_THREAD_LIBS_INIT}
                            ${Boost_LIBRARIES})



