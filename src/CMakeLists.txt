# Author: Eric Fiselier
################################################################################
##                             Library Parts
################################################################################
set(LIBRARY_SRC "")
set(LIBRARY_FLAGS "")

# Include the core elib library. 
# NOTE: this should not be turned off.
if (ELIB_SOURCE)
    include(elib/build.cmake)
    list(APPEND ELIB_LIBRARIES "ELIB_SOURCE")
    set(ELIB_LIBRARIES ${ELIB_LIBRARIES} PARENT_SCOPE)
    add_definitions( -DELIB_SOURCE )
else()
    config_message(WARN "ELIB_SOURCE should not be disabled")
endif()

# Include each library if its option is enabled.
include_library_if(ELIB_AUX_SOURCE         aux          )
include_library_if(ELIB_CONTAINER_SOURCE   container    )
include_library_if(ELIB_ENUMERATION_SOURCE enumeration  )
include_library_if(ELIB_EXCEPTION_SOURCE   exception    )
include_library_if(ELIB_FILESYSTEM_SOURCE  filesystem   )
include_library_if(ELIB_FUNCTIONAL_SOURCE  functional   )
include_library_if(ELIB_ITERATOR_SOURCE    iterator     )
include_library_if(ELIB_LOGGING_SOURCE     logging      )
include_library_if(ELIB_MEMORY_SOURCE      memory       )
include_library_if(ELIB_MP_SOURCE          mp           )
include_library_if(ELIB_PP_SOURCE          preprocessor )


# Include experimental libraries.
if (CONFIG_ENABLE_EXPERIMENTAL)
  include_library_if(ELIB_CONTRACT_ASSERT_SOURCE 
                     experimental/contract_assert)
  include_library_if(ELIB_WEB_SOURCE
                     experimental/web)
else()
    list(APPEND ELIB_EXCLUDE_DIRECTORIES "experimental")
    set(ELIB_EXCLUDE_DIRECTORIES ${ELIB_EXCLUDE_DIRECTORIES} PARENT_SCOPE)
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
target_link_libraries(elib ${CMAKE_THREAD_LIBS_INIT})
set_target_properties(elib PROPERTIES 
                           LIBRARY_OUTPUT_DIRECTORY ${ELIB_ROOT_PATH}/bin)

################################################################################
add_library(elib_static STATIC $<TARGET_OBJECTS:ObjLib>)
target_link_libraries(elib_static ${CMAKE_THREAD_LIBS_INIT})
set_target_properties(elib_static PROPERTIES
                                  ARCHIVE_OUTPUT_DIRECTORY ${ELIB_ROOT_PATH}/bin)


# Installation information
# NOTE: For some reason this will not work on CYGWIN
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

