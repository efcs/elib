# Author: Eric Fiselier
# Compiler: GCC/Clang
# 
# I apologize to windows users, I have built it this project on windows,
# but the project configurations in this make file DO NOT WORK and they 
# must be commented out.

set(CONFIG_MY_BUILD ON)
set(CONFIG_ALL_WARNINGS ON)
if (CONFIG_MY_BUILD)

  if (CONFIG_ALL_WARNINGS)
  
     add_definitions( -g -O -Wall -Weffc++ -pedantic  
      -pedantic-errors -Wextra  -Wall -Waggregate-return -Wcast-align 
      -Wcast-qual  -Wchar-subscripts  -Wcomment -Wconversion 
      -Wdisabled-optimization 
      -Wfloat-equal  -Wformat  -Wformat=2 
      -Wformat-nonliteral -Wformat-security  
      -Wformat-y2k 
      -Wimport  -Winit-self  -Winline 
      -Winvalid-pch   
      -Wlong-long -Wmissing-braces 
      -Wmissing-field-initializers -Wmissing-format-attribute   
      -Wmissing-include-dirs -Wmissing-noreturn 
      -Wpacked  -Wpadded -Wparentheses  -Wpointer-arith 
      -Wredundant-decls -Wreturn-type 
      -Wsequence-point  -Wshadow -Wsign-compare  -Wstack-protector 
      -Wstrict-aliasing -Wstrict-aliasing=2 -Wswitch  -Wswitch-default 
      -Wswitch-enum -Wtrigraphs  -Wuninitialized 
      -Wunknown-pragmas  -Wunreachable-code -Wunused 
      -Wunused-function  -Wunused-label  -Wunused-parameter 
      -Wunused-value  -Wunused-variable  -Wvariadic-macros 
      -Wvolatile-register-var  -Wwrite-strings
    )
  
    if (CONFIG_USE_CLANG)
    
      add_definitions( -Weverything -Wno-c++98-compat 
                       -Wno-c++98-compat-pedantic)
    else()
    
      add_definitions( -Wunsafe-loop-optimizations )
      
    endif()
  
    add_definitions( -Wno-padded -Wno-aggregate-return 
                      -Wno-inline 
                   )
  
  endif()

endif()

if ( NOT CONFIG_NO_LIBRARIES )
  add_definitions(-fPIC)
endif()

set(dotDir ${CMAKE_CURRENT_LIST_DIR})
aux_source_directory(${dotDir} dotSrc)
aux_source_directory(${dotDir}/argp argpSrc)
aux_source_directory(${dotDir}/fs fsSrc)
aux_source_directory(${dotDir}/enumeration enumSrc)
aux_source_directory(${dotDir}/log logSrc)
aux_source_directory(${dotDir}/lock lockSrc)
aux_source_directory(${dotDir}/utility utilSrc)


# compile into objects
add_library(ObjLib OBJECT ${dotSrc} 
                          ${utilSrc}
                          ${argpSrc} 
                          ${fsSrc}
                          ${enumSrc} 
                          ${logSrc}
                          ${lockSrc}
           )
           

    
if ( NOT CONFIG_NO_LIBRARIES )
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



  install(TARGETS elib LIBRARY DESTINATION lib)
  install(TARGETS elib_static ARCHIVE DESTINATION lib)
  install(DIRECTORY ${headerDir} DESTINATION include)
  
endif() # NOT CONFIG_NO_LIBRARIES 


				

