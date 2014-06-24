
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
macro(make_abs_path Path Out)
    string(FIND ${Path} "/" Pos)
    if (${Pos} EQUAL 0)
        set(${Out} ${Path})
    else()
        set(${Out} ${CMAKE_CURRENT_LIST_DIR}/${Path})
    endif()
endmacro(make_abs_path)

################################################################################
macro(mangle_path File Out)
    make_abs_path(${File} _AbsFile)
    get_filename_component(_Prefix ${_AbsFile} PATH)
    string(REPLACE ${ELIB_ROOT_PATH}/src/ "" _Prefix ${_Prefix})
    string(REPLACE "/" "_" _Prefix ${_Prefix})
    get_filename_component(_Suffix ${_AbsFile} NAME_WE)
    set(${Out} ${_Prefix}_${_Suffix})
endmacro(mangle_path)

################################################################################

macro(append_parent_scope List Value)
    list(APPEND ${List} ${Value})
    set(${List} ${${List}} PARENT_SCOPE)
endmacro(append_parent_scope)

macro(parent_scope Val)
    set(${Val} ${${Val}} PARENT_SCOPE)
endmacro(parent_scope)

################################################################################
# Use the library configuration option to selectivly 
# build build a library. 
macro(include_library_if Pred CFile)
    if (${Pred})
        include(${CFile}/build.cmake)
        append_parent_scope(ELIB_LIBRARIES ${Pred})
        append_parent_scope(ELIB_INCLUDE_DIRECTORIES elib/${CFile})
        append_parent_scope(ELIB_AVAILABLE_FEATURES ${Pred})
    else()
        append_parent_scope(ELIB_EXCLUDE_LIBRARIES ${Pred})
        append_parent_scope(ELIB_EXCLUDE_DIRECTORIES elib/${CFile})
    endif()
endmacro(include_library_if)

################################################################################
macro(include_build_dir BuildDir)
    include(${CMAKE_CURRENT_LIST_DIR}/${BuildDir}/build.cmake)
endmacro(include_build_dir)

################################################################################
# adds all c++ file in the CWD
macro(add_library_src)
    if (${ARGC} EQUAL 0)
        aux_source_directory(${CMAKE_CURRENT_LIST_DIR} _library_src)
    elseif(${ARGC} EQUAL 1)
        aux_source_directory(${CMAKE_CURRENT_LIST_DIR}/${ARGV0}/ _library_src)
    else()
        message(FATAL_ERROR "Cannot use macro add_library_src with args ${ARGV}")
    endif()
    list(APPEND LIBRARY_SRC ${_library_src})
endmacro(add_library_src)


################################################################################
macro(add_test_target TargetName File)
    add_executable(${TargetName} ${File})
    target_include_directories(${TargetName} PUBLIC ${RAPID_CXX_TEST_INCLUDE_DIRS})
    set_target_properties(${TargetName} PROPERTIES COMPILE_FLAGS "${WARNING_FLAGS}")
    target_link_libraries(${TargetName} elib ${CMAKE_THREAD_LIBS_INIT})
    add_test(${TargetName} ${TargetName})
    # Print the name of the target that was added
    # config_message(STATUS "Adding Target: ${TargetName}")
endmacro(add_test_target)

macro(add_test_file File)
    mangle_path(${File} _TargetName)
    add_test_target(${_TargetName} ${File})
endmacro(add_test_file)

macro(add_test_list)
    foreach(_MyFile ${ARGN})
        add_test_file(${_MyFile})
    endforeach()
endmacro(add_test_list)
    
################################################################################
macro(add_test_dir)
    if (${ARGC} EQUAL 0)
        file(GLOB _Files ${CMAKE_CURRENT_LIST_DIR}/*.pass.cpp)
    elseif(${ARGC} EQUAL 1)
        file(GLOB _Files ${CMAKE_CURRENT_LIST_DIR}/${ARGV0}/*.pass.cpp)
    else()
        message(FATAL_ERROR "Incorrect usage of add_test_dir")
    endif()
    add_test_list(${_Files})
endmacro(add_test_dir)

################################################################################
macro(add_recursive_test_dir)
    if (${ARGC} EQUAL 0)
        file(GLOB_RECURSE _Files "${CMAKE_CURRENT_LIST_DIR}/*.pass.cpp")
    elseif(${ARGC} EQUAL 1)
        file(GLOB_RECURSE _Files "${CMAKE_CURRENT_LIST_DIR}/${ARGV0}/*.pass.cpp")
    else()
        message(FATAL_ERROR "Incorrect usage of add_test_dir")
    endif()
    add_test_list(${_Files})
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

