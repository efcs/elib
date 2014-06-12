# Author: Eric Fiselier

set(LIBRARY_FLAGS "")
set(WARNING_FLAGS "")
set(UNIT_TEST_FLAGS "")

set(LIBRARY_SRC "")
set(HEADER_TEST_SRC "")
set(UNIT_TEST_SRC "")

find_package( Threads REQUIRED )

################################### BOOST ######################################
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost COMPONENTS unit_test_framework REQUIRED)
set(Boost_FIND_QUIETLY ON CACHE BOOL "Find Boost Quietly" FORCE)
include_directories(${Boost_INCLUDE_DIRS})

add_flags(LIBRARY_FLAGS -fPIC)

################################################################################
##                               Warnings
################################################################################
if (CONFIG_ALL_WARNINGS)

    add_flags( WARNING_FLAGS
    -pedantic-errors  -Waggregate-return -Wcast-align 
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
            -Wno-c++98-compat-pedantic -Wno-newline-eof)
        add_flags(UNIT_TEST_FLAGS -Wno-global-constructors -Wno-exit-time-destructors)
  endif()
  
  add_flags( WARNING_FLAGS 
        -Wno-padded -Wno-aggregate-return -Wno-inline -Wno-long-long)


endif()

set(LIBRARY_FLAGS "${WARNING_FLAGS} ${LIBRARY_FLAGS}")

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
  include_library_if(ELIB_CONTRACT_ASSERT_SOURCE 
                     experimental/contract_assert/build.cmake)
  include_library_if(ELIB_WEB_SOURCE
                     experimental/web/build.cmake)
endif()

################################################################################
##                               Objects
################################################################################
# Compile source files into "Object Libraries"
add_library(ObjLib OBJECT ${LIBRARY_SRC})
set_target_properties(ObjLib PROPERTIES COMPILE_FLAGS "${WARNING_FLAGS} ${LIBRARY_FLAGS}")


################################################################################
##                             Libraries
################################################################################
add_library(elib SHARED $<TARGET_OBJECTS:ObjLib>)
add_library(elib_static STATIC $<TARGET_OBJECTS:ObjLib>)  
target_link_libraries(elib ${CMAKE_THREAD_LIBS_INIT} ${STDLIB_LINK})
target_link_libraries(elib_static ${CMAKE_THREAD_LIBS_INIT} ${STDLIB_LINK})

# Installation information
install(TARGETS elib LIBRARY DESTINATION lib)
install(TARGETS elib_static ARCHIVE DESTINATION lib)
install(DIRECTORY ${ELIB_ROOT_PATH}/elib DESTINATION include)
  
################################################################################
#                            Header Tests
################################################################################
if (CONFIG_HEADER_TESTS)
    add_library(HeaderTestLib OBJECT ${HEADER_TEST_SRC})
    set_target_properties(HeaderTestLib PROPERTIES COMPILE_FLAGS "-fsyntax-only")
endif()


################################################################################
##                            Unit Tests
################################################################################
if(CONFIG_UNIT_TESTS) 

################################### PYTHON #####################################
# Check for a python interpreter the first time we run configuration.
if (NOT DEFINED CONFIGURATION_DONE)
    include (FindPythonInterp)
    if (NOT PYTHONINTERP_FOUND)
        message(FATAL_ERROR
            "Cannot find python interpreter. 
             Python is required to run the test suite.
             Please configure using make UNIT_TESTS=OFF configure."
           )
    endif()
endif() 



############################# Test Executables #################################
set(ELIB_TEST_LINK_FLAGS ${STDLIB_LINK} ${CMAKE_THREAD_LIBS_INIT} ${Boost_LIBRARIES})
add_library(TestObj OBJECT ${UNIT_TEST_SRC} unit_test_main.cpp)
set_target_properties(TestObj PROPERTIES COMPILE_FLAGS "${UNIT_TEST_FLAGS}")
add_executable(elib_test_static $<TARGET_OBJECTS:TestObj> )
add_executable(elib_test_shared $<TARGET_OBJECTS:TestObj> )
target_link_libraries(elib_test_static elib_static ${ELIB_TEST_LINK_FLAGS})
target_link_libraries(elib_test_shared elib ${ELIB_TEST_LINK_FLAGS})
set_target_properties(elib_test_static PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${ELIB_ROOT_PATH}/bin)
set_target_properties(elib_test_shared PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${ELIB_ROOT_PATH}/bin)

         
endif()
################################################################################
