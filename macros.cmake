
################################################################################
#                           Macros & Functions
################################################################################

macro(set_dot_dir)
    set(dotDir ${CMAKE_CURRENT_LIST_DIR})
endmacro(set_dot_dir)

# Use the library configuration option to selectivly 
# build build a library. 
macro(include_library_if Pred CFile)
    if (${Pred})
        include(${CFile})
        add_definitions( -D${Pred} )
    endif()
endmacro(include_library_if)

macro(include_build_dir BuildDir)
    set_dot_dir()
    include(${dotDir}/${BuildDir}/build.cmake)
endmacro(include_build_dir)

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


macro(add_header_test_src)
    set_dot_dir()
    if (${ARGC} EQUAL 0)
        aux_source_directory(${dotDir} _header_test_src)
    elseif(${ARGC} EQUAL 1)
        aux_source_directory(${dotDir}/${ARGV0} _header_test_src)
    else()
        message(FATAL_ERROR "Cannot use macro add_header_test_src with args ${ARGV}")
    endif()
    list(APPEND HEADER_TEST_SRC ${_header_test_src})
endmacro(add_header_test_src)
    
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
        add_executable(${TargetName} ${MyFile})
        # Currently way too noisy because of Boost.Test. 
        #set_target_properties(${TargetName} PROPERTIES COMPILE_FLAGS "${WARNING_FLAGS}")
        target_link_libraries(${TargetName} elib ${CMAKE_THREAD_LIBS_INIT} ${Boost_LIBRARIES})
        add_test(${TargetName} ${TargetName})
    endforeach()
endmacro(add_test_dir)

macro(stringify_list m_list dest)
    string(REPLACE ";" " " ${dest} "${m_list}")
endmacro(stringify_list)

macro(add_flags to)
    stringify_list("${ARGN}" _TMP)
    set(${to} "${${to}} ${_TMP}")
endmacro(add_flags)

macro(config_message level msg)
    if (NOT CONFIGURATION_DONE)
        message(${level} ${msg})
    endif()
endmacro()