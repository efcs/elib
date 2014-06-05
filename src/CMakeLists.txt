# Author: Eric Fiselier
# Compiler: GCC/Clang
# 
# I apologize to windows users, I have built it this project on windows,
# but the project configurations in this make file DO NOT WORK and they 
# must be commented out.

set(LIBRARY_FLAGS "")
set(WARNING_FLAGS "")
set(UNIT_TEST_FLAGS "")

set(LIBRARY_SRC "")
set(HEADER_TEST_SRC "")
set(UNIT_TEST_SRC "")

find_package( Threads REQUIRED )

add_flags(LIBRARY_FLAGS -fPIC)

################################################################################
##                               Warnings
################################################################################
if (CONFIG_ALL_WARNINGS)

    add_flags( WARNING_FLAGS
    -Wall  -pedantic  
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
  
  if (CXX_COMPILER_GCC)
        add_flags( WARNING_FLAGS -Wunsafe-loop-optimizations )
        #add_flags( WARNING_FLAGS -Weffc++)
  elseif (CXX_COMPILER_CLANG)
        add_flags( WARNING_FLAGS
            -Weverything -Wno-c++98-compat 
            -Wno-c++98-compat-pedantic -Wno-newline-eof
            -Wno-mismatched-tags)
        add_flags(UNIT_TEST_FLAGS -Wno-global-constructors -Wno-exit-time-destructors)
  endif()
  
  add_flags( WARNING_FLAGS 
        -Wno-padded -Wno-aggregate-return -Wno-inline -Wno-long-long)

  if (CONFIG_ELIB_COVERITY_SCAN)
    add_flags( WARNING_FLAGS -Wno-unknown-pragmas )
  endif()
  
endif()

set(LIBRARY_FLAGS "${LIBRARY_FLAGS} ${WARNING_FLAGS}")

################################################################################
##                             Library Parts
################################################################################
include_library_if(ELIB_SOURCE             elib/build.cmake         )
include_library_if(ELIB_AUX_SOURCE         aux/build.cmake          )
include_library_if(ELIB_CONTAINER_SOURCE   container/build.cmake    )
include_library_if(ELIB_ENUMERATION_SOURCE enumeration/build.cmake  )
include_library_if(ELIB_EXCEPTION_SOURCE   exception/build.cmake    )
include_library_if(ELIB_FILESYSTEM_SOURCE  filesystem/build.cmake   )
include_library_if(ELIB_FUNCTIONAL_SOURCE  functional/build.cmake   )
include_library_if(ELIB_ITERATOR_SOURCE    iterator/build.cmake     )
include_library_if(ELIB_LOGGING_SOURCE     logging/build.cmake      )
include_library_if(ELIB_MEMORY_SOURCE      memory/build.cmake       )
include_library_if(ELIB_MP_SOURCE          mp/build.cmake           )
include_library_if(ELIB_PP_SOURCE          preprocessor/build.cmake )


if (CONFIG_ENABLE_EXPERIMENTAL)
  include_library_if(ELIB_CONTRACT_ASSERT_SOURCE  experimental/contract_assert/build.cmake)
  include_library_if(ELIB_RANGES_SOURCE    experimental/ranges/build.cmake   )
  include_library_if(ELIB_WEB_SOURCE       experimental/web/build.cmake      )
endif()


################################################################################
##                             Libraries
################################################################################
add_library(elib SHARED ${LIBRARY_SRC})
set_target_properties(elib PROPERTIES COMPILE_FLAGS "${LIBRARY_FLAGS}")
target_link_libraries(elib ${CMAKE_THREAD_LIBS_INIT} ${STDLIB_LINK})

# Installation information
install(TARGETS elib LIBRARY DESTINATION lib)
install(DIRECTORY ${ELIB_ROOT_PATH}/elib DESTINATION include)
  

################################################################################
##                            Unit Tests
################################################################################
if(CONFIG_UNIT_TESTS) 

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost COMPONENTS unit_test_framework REQUIRED)
set(Boost_FIND_QUIETLY ON CACHE BOOL "Find Boost Quietly" FORCE)
	
include_directories(${Boost_INCLUDE_DIRS})
set(ELIB_TEST_LINK_FLAGS ${STDLIB_LINK} ${CMAKE_THREAD_LIBS_INIT} ${Boost_LIBRARIES})

add_executable(elib_test_shared ${UNIT_TEST_SRC} unit_test_main.cpp )
target_link_libraries(elib_test_shared elib ${ELIB_TEST_LINK_FLAGS})
         
endif()
################################################################################
