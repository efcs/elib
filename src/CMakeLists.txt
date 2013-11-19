# Author: Eric Fiselier
# Compiler: GCC/Clang
# 
# I apologize to windows users, I have built it this project on windows,
# but the project configurations in this make file DO NOT WORK and they 
# must be commented out.

set(LIBRARY_FLAGS "")
set(UNIT_TEST_FLAGS "")

if (CONFIG_MY_BUILD)

  if (CONFIG_ALL_WARNINGS)
  
     add_flags( LIBRARY_FLAGS 
      -Wall -Weffc++ -pedantic  
      -pedantic-errors -Wextra  -Wall -Waggregate-return -Wcast-align 
      -Wcast-qual  -Wchar-subscripts  -Wcomment -Wconversion 
      -Wdisabled-optimization -Wfloat-equal  -Wformat  -Wformat=2 
      -Wformat-nonliteral -Wformat-security  -Wformat-y2k -Wimport  -Winit-self  
      -Winline -Winvalid-pch -Wlong-long -Wmissing-braces 
      -Wmissing-field-initializers -Wmissing-format-attribute 
      -Wmissing-include-dirs -Wmissing-noreturn -Wpacked  -Wpadded -Wparentheses
      -Wpointer-arith -Wredundant-decls -Wreturn-type -Wsequence-point  -Wshadow 
      -Wsign-compare  -Wstack-protector -Wstrict-aliasing -Wstrict-aliasing=2 
      -Wswitch  -Wswitch-default -Wswitch-enum -Wtrigraphs  -Wuninitialized 
      -Wunknown-pragmas  -Wunreachable-code -Wunused -Wunused-function  
      -Wunused-label  -Wunused-parameter -Wunused-value  -Wunused-variable  
      -Wvariadic-macros -Wvolatile-register-var  -Wwrite-strings
    )
  
    if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
      
      add_flags( LIBRARY_FLAGS
        -Weverything -Wno-c++98-compat 
        -Wno-c++98-compat-pedantic -Wno-newline-eof 
      )
      
    else()
                       
      add_flags( LIBRARY_FLAGS -Wunsafe-loop-optimizations )

    endif()
  
    add_flags( LIBRARY_FLAGS 
      -Wno-padded -Wno-aggregate-return -Wno-inline -Wno-long-long
    )
  
  endif()
endif()


add_flags(LIBRARY_FLAGS -fPIC)


set(LIBRARY_SRC "")
set(UNIT_TEST_SRC "")

#include(enumeration/build.cmake)
include(enumeration/build.cmake)
include(log/build.cmake)
include(fs/build.cmake)
include(mp/build.cmake)
include(utility/build.cmake)

# compile into objects

add_library(ObjLib OBJECT ${LIBRARY_SRC})
set_target_properties(ObjLib PROPERTIES COMPILE_FLAGS "${LIBRARY_FLAGS}")


    
################################################################################
  #create static & shared libraries
  add_library(elib SHARED $<TARGET_OBJECTS:ObjLib>)
  add_library(elib_static STATIC $<TARGET_OBJECTS:ObjLib>)  

  target_link_libraries(elib ${CMAKE_THREAD_LIBS_INIT} ${Boost_LIBRARIES} 
                        ${STDLIB_LINK} )
                        
  target_link_libraries(elib_static ${CMAKE_THREAD_LIBS_INIT} ${Boost_LIBRARIES}
                        ${STDLIB_LINK})

  install(TARGETS elib LIBRARY DESTINATION lib)
  install(TARGETS elib_static ARCHIVE DESTINATION lib)
  install(DIRECTORY ${headerDir} DESTINATION include)
  

  



################################################################################

if(NOT CONFIG_NO_UNIT_TESTS) 

	set(Boost_USE_STATIC_LIBS OFF)
	set(Boost_USE_MULTITHREADED OFF)
	set(Boost_USE_STATIC_RUNTIME OFF)
	find_package(Boost COMPONENTS system filesystem unit_test_framework REQUIRED)
	
	include_directories(${Boost_INCLUDE_DIRS})
	add_library(TestObj OBJECT ${UNIT_TEST_SRC} unit_test_main.cpp)
	
  	add_executable(elib_test_static $<TARGET_OBJECTS:TestObj>)
  	add_executable(elib_test_shared $<TARGET_OBJECTS:TestObj>)


  	target_link_libraries(elib_test_static elib_static ${STDLIB_LINK}
                      ${CMAKE_THREAD_LIBS_INIT} ${Boost_LIBRARIES})
                      
  	target_link_libraries(elib_test_shared elib ${STDLIB_LINK} ${CMAKE_THREAD_LIBS_INIT}
                            ${Boost_LIBRARIES})
                            
endif()



