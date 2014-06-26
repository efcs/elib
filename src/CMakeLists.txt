# Author: Eric Fiselier
################################################################################
##                             Library Parts
################################################################################
set(LIBRARY_SRC "")
set(LIBRARY_FLAGS "")

# Include the core elib library. 
# NOTE: this should not be turned off.
if (ELIB_CORE)
    include(elib/build.cmake)
    append_parent_scope(ELIB_LIBRARIES ELIB_CORE)
    append_parent_scope(ELIB_AVAILABLE_FEATURES ELIB_CORE)
    append_parent_scope(ELIB_INCLUDE_DIRECTORIES ELIB_CORE)
else()
    append_parent_scope(ELIB_EXCLUDE_LIBRARIES ELIB_CORE)
    config_message(WARNING "ELIB_CORE should not be disabled")
endif()

# Include each library if its option is enabled.
include_library_if(ELIB_AUX          aux          )
include_library_if(ELIB_CONFIG       config       )
include_library_if(ELIB_CONTAINER    container    )
include_library_if(ELIB_ENUMERATION  enumeration  )
include_library_if(ELIB_EXCEPTION    exception    )
include_library_if(ELIB_FILESYSTEM   filesystem   )
include_library_if(ELIB_FUNCTIONAL   functional   )
include_library_if(ELIB_ITERATOR     iterator     )
include_library_if(ELIB_LOGGING      logging      )
include_library_if(ELIB_MEMORY       memory       )
include_library_if(ELIB_MP           mp           )
include_library_if(ELIB_PREPROCESSOR preprocessor )

# Include experimental libraries.
include_experimental_library_if(ELIB_CONTRACT_ASSERT experimental/contract_assert)
include_experimental_library_if(ELIB_WEB experimental/web)


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

