# Author: Eric Fiselier
################################################################################
##                             Library Parts
################################################################################
set(LIBRARY_SRC "")
set(LIBRARY_FLAGS "")
set(ELIB_LIBRARIES "")

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
if (NOT CYGWIN)
    set(OBJECT_FLAGS "-fPIC ${WARNING_FLAGS} ${LIBRARY_FLAGS}")
else()
    set(OBJECT_FLAGS "${WARNING_FLAGS} ${LIBRARY_FLAGS}")
endif()

# Compile source files into "Object Libraries"
add_library(ObjLib OBJECT ${LIBRARY_SRC})
set_target_properties(ObjLib PROPERTIES COMPILE_FLAGS "${OBJECT_FLAGS}")

################################################################################
##                             Libraries
################################################################################

################################################################################
add_library(elib SHARED $<TARGET_OBJECTS:ObjLib>)
add_dependencies(elib depends)
target_link_libraries(elib ${CMAKE_THREAD_LIBS_INIT})
set_target_properties(elib PROPERTIES 
                           LIBRARY_OUTPUT_DIRECTORY ${ELIB_ROOT_PATH}/bin)

################################################################################
add_library(elib_static STATIC $<TARGET_OBJECTS:ObjLib>)
add_dependencies(elib_static depends)  
target_link_libraries(elib_static ${CMAKE_THREAD_LIBS_INIT})
set_target_properties(elib_static PROPERTIES
                                  ARCHIVE_OUTPUT_DIRECTORY ${ELIB_ROOT_PATH}/bin)


# Installation information
if (NOT DEFINED CYGWIN)
    install(TARGETS elib LIBRARY DESTINATION lib)
    install(TARGETS elib_static ARCHIVE DESTINATION lib)
    install(DIRECTORY "${ELIB_ROOT_PATH}/elib" DESTINATION include)
endif()

# Add a build rule to build both static and shared libraries
add_custom_target(libs)
add_dependencies(libs elib elib_static)

################################################################################
if (CONFIG_UNIT_TESTS)
    include(unit_tests.cmake)
endif()

