# Author: Eric Fiselier

set(LIBRARY_FLAGS "")
set(WARNING_FLAGS "")
set(UNIT_TEST_FLAGS "")

set(LIBRARY_SRC "")
set(HEADER_TEST_SRC "")
set(UNIT_TEST_SRC "")

find_package( Threads REQUIRED )

################################################################################
##                            Unit Tests
################################################################################
if(CONFIG_UNIT_TESTS) 
    ################################### BOOST ######################################
    set(Boost_USE_STATIC_LIBS OFF)
    set(Boost_USE_MULTITHREADED ON)
    set(Boost_USE_STATIC_RUNTIME OFF)
    find_package(Boost COMPONENTS unit_test_framework REQUIRED)
    set(Boost_FIND_QUIETLY ON CACHE BOOL "Find Boost Quietly" FORCE)
    include_directories(${Boost_INCLUDE_DIRS})

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

         
if (NOT CYGWIN)
    add_flags(LIBRARY_FLAGS -fPIC)
endif()
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
if (NOT CYGWIN)
    install(TARGETS elib LIBRARY DESTINATION lib)
    install(TARGETS elib_static ARCHIVE DESTINATION lib)
    install(DIRECTORY "${ELIB_ROOT_PATH}/elib" DESTINATION include)
endif()
  
################################################################################
#                            Header Tests
################################################################################
if (CONFIG_HEADER_TESTS)
    add_library(HeaderTestLib OBJECT ${HEADER_TEST_SRC})
    set_target_properties(HeaderTestLib PROPERTIES COMPILE_FLAGS "-fsyntax-only")
endif()

endif()
################################################################################

# SAMPLEOBJ is used by lit.cfg to create a template build rule. 
# When we LIT builds a negative compilation test it uses the flags for SAMPLEOBJ
add_executable(SAMPLEOBJ sample_test.pass.cpp)
target_link_libraries(SAMPLEOBJ elib ${CMAKE_THREAD_LIBS_INIT} ${Boost_LIBRARIES})
set_target_properties(SAMPLEOBJ PROPERTIES EXCLUDE_FROM_ALL ON EXCLUDE_FROM_DEFAULT_BUILD ON)

# We actually need to give sample_test a target that matches the naming convention
# for tests. 
add_executable(sample_test sample_test.pass.cpp)
target_link_libraries(sample_test elib ${CMAKE_THREAD_LIBS_INIT} ${Boost_LIBRARIES})


include (FindPythonInterp)
if (PYTHONINTERP_FOUND)

  get_directory_property(ELIB_AVAILABLE_FEATURES DIRECTORY . COMPILE_DEFINITIONS)
  list(APPEND ELIB_AVAILABLE_FEATURES "ELIB_BOOST_TEST")

  set(LIT_EXECUTABLE "${ELIB_ROOT_PATH}/packages/lit/lit.py" CACHE FILEPATH "Path to LLVM's lit.py.")
  set(LIT_ARGS_DEFAULT "-sv" CACHE STRING "Default lit args")
  set(LIT_ARGS "${LIT_ARGS_DEFAULT}")
  separate_arguments(LIT_ARGS)

  set(SAMPLE_OBJECT "SAMPLEOBJ")

  set(AUTO_GEN_COMMENT "## Autogenerated by elib configuration.\n# Do not edit!")
  
  configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/lit.site.cfg.in
    ${CMAKE_CURRENT_BINARY_DIR}/lit.site.cfg
    @ONLY)

  add_custom_target(check-lit
    COMMAND ${PYTHON_EXECUTABLE}
            ${LIT_EXECUTABLE}
            ${LIT_ARGS}
            ${CMAKE_CURRENT_BINARY_DIR}
    DEPENDS elib
    COMMENT "Running elib tests")

else()
  message(WARNING "Could not find Python, no check target will be available!")
endif()
