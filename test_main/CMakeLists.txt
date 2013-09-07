# Author: Eric Fiselier
# Compiler: GCC/Clang
# 
# I apologize to windows users, I have built it this project on windows,
# but the project configurations in this make file DO NOT WORK and they 
# must be commented out.

set(dotDir ${CMAKE_CURRENT_LIST_DIR})
aux_source_directory(${dotDir} dotSrc)

include_directories(${dotDir}/../src)
include_directories(${dotDir})

aux_source_directory(${dotDir} dotSrc)
set(testSources ${dotSrc})

add_executable(elib_test_main ${testSources})


target_link_libraries(elib_test_main elib_static ${LD_FLAGS})




