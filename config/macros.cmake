
################################################################################
#                           Macros & Functions
################################################################################

################################################################################
macro(config_message level msg)
    if (NOT CONFIGURATION_DONE)
        message(${level} ${msg})
    endif()
endmacro()

################################################################################
macro(set_dot_dir)
    set(dotDir ${CMAKE_CURRENT_LIST_DIR})
endmacro(set_dot_dir)


macro(parent_scope Val)
    set(${Val} ${${Val}} PARENT_SCOPE)
endmacro(parent_scope)

################################################################################
# Use the library configuration option to selectivly 
# build build a library. 
macro(include_library_if Pred CFile)
    if (${Pred})
        include(${CFile}/build.cmake)
        list(APPEND ELIB_LIBRARIES ${Pred})
        parent_scope(ELIB_LIBRARIES)
        list(APPEND ELIB_INCLUDE_DIRECTORIES elib/${CFile})
        parent_scope(ELIB_INCLUDE_DIRECTORIES)
        add_definitions( -D${Pred} )
    else()
        list(APPEND ELIB_EXCLUDE_LIBRARIES ${Pred})
        parent_scope(ELIB_EXCLUDE_LIBRARIES)
        list(APPEND ELIB_EXCLUDE_DIRECTORIES ${CFile})
        parent_scope(ELIB_EXCLUDE_DIRECTORIES)
    endif()
endmacro(include_library_if)

################################################################################
macro(include_build_dir BuildDir)
    set_dot_dir()
    include(${dotDir}/${BuildDir}/build.cmake)
endmacro(include_build_dir)

################################################################################
# adds all c++ file in the CWD
macro(add_library_src)
    set_dot_dir()
    if (${ARGC} EQUAL 0)
        aux_source_directory(${dotDir} _library_src)
    elseif(${ARGC} EQUAL 1)
        aux_source_directory(${dotDir}/${ARGV0}/ _library_src)
    else()
        message(FATAL_ERROR "Cannot use macro add_library_src with args ${ARGV}")
    endif()
    list(APPEND LIBRARY_SRC ${_library_src})
endmacro(add_library_src)


################################################################################
macro(add_test_target TargetName File)
    add_executable(${TargetName} ${File})
    target_include_directories(${TargetName} PUBLIC ${RAPID_CXX_TEST_INCLUDE_DIRS})
    # Currently way too noisy because of Boost.Test. 
    set_target_properties(${TargetName} PROPERTIES COMPILE_FLAGS "${WARNING_FLAGS}")
    target_link_libraries(${TargetName} elib ${CMAKE_THREAD_LIBS_INIT})
    add_test(${TargetName} ${TargetName})
    # Print the name of the target that was added
    # config_message(STATUS "Adding Target: ${TargetName}")
endmacro(add_test_target)
    
################################################################################
macro(add_test_dir)
    set_dot_dir()
    if (${ARGC} EQUAL 0)
        string(REPLACE ${ELIB_ROOT_PATH}/src/ "" temp_prefix ${CMAKE_CURRENT_LIST_DIR})
        string(REPLACE "/" "_" prefix ${temp_prefix})
        file(GLOB MyOut ${dotDir}/*.pass.cpp)
    elseif(${ARGC} EQUAL 1)
        string(REPLACE ${ELIB_ROOT_PATH}/src/ "" temp_prefix ${CMAKE_CURRENT_LIST_DIR}/${ARGV0})
        string(REPLACE "/" "_" prefix ${temp_prefix})
        file(GLOB MyOut ${dotDir}/${ARGV0}/*.pass.cpp)
    else()
        message(FATAL_ERROR "Incorrect usage of add_test_dir")
    endif()
    foreach(MyFile ${MyOut})
        get_filename_component(MyExeName ${MyFile} NAME_WE)
        set(TargetName ${prefix}_${MyExeName})
        add_test_target(${TargetName} ${MyFile})
    endforeach()
endmacro(add_test_dir)

################################################################################
macro(add_recursive_test_dir)
    set_dot_dir()
    if (${ARGC} EQUAL 0)
        string(REPLACE ${ELIB_ROOT_PATH}/src/ "" temp_prefix ${CMAKE_CURRENT_LIST_DIR})
        string(REPLACE "/" "_" prefix ${temp_prefix})
        file(GLOB_RECURSE MyOut "${CMAKE_CURRENT_LIST_DIR}/*.pass.cpp")
    elseif(${ARGC} EQUAL 1)
        string(REPLACE ${ELIB_ROOT_PATH}/src/ "" temp_prefix ${CMAKE_CURRENT_LIST_DIR}/${ARGV0})
        string(REPLACE "/" "_" prefix ${temp_prefix})
        file(GLOB_RECURSE MyOut "${CMAKE_CURRENT_LIST_DIR}/${ARGV0}/*.pass.cpp")
    else()
        message(FATAL_ERROR "Incorrect usage of add_test_dir")
    endif()
    foreach(MyFile ${MyOut})
        get_filename_component(MyExeName ${MyFile} NAME_WE)
        set(TargetName ${prefix}_${MyExeName})
        add_test_target(${TargetName} ${MyFile})
    endforeach()
endmacro(add_recursive_test_dir)

################################################################################
macro(stringify_list m_list dest)
    string(REPLACE ";" " " ${dest} "${m_list}")
endmacro(stringify_list)

################################################################################
macro(add_flags to)
    stringify_list("${ARGN}" _TMP)
    set(${to} "${${to}} ${_TMP}")
endmacro(add_flags)

