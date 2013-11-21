cmake_minimum_required (VERSION 2.7)

option(CONFIG_MY_BUILD "turn on personal configurations" ON)

option(CONFIG_USE_CLANG "use clang instead of gcc" OFF)
option(CONFIG_USE_CLANG_TRUNK " use /opt/llvm/bin/clang" OFF)
option(CONFIG_USE_LIBCXX "if clang is selected,  it will use libc++" OFF)

option(CONFIG_USE_GCC_49 "use gcc 4.9" OFF)
option(CONFIG_USE_OPT_LIBSTDCXX "use newer libstdc++" OFF)

option(CONFIG_ALL_WARNINGS "turn on all warnings for either GCC on clang" ON)

option(CONFIG_ASAN "address sanitizer" OFF)
option(CONFIG_TSAN "thread sanitizer" OFF)
option(CONFIG_MSAN "memory sanitizer" OFF)

option(CONFIG_UNIT_TESTS "build unit tests" ON)

# Options to select what parts to build
option(CONFIG_LIB_FILESYSTEM "Build filesystem" ON)
option(CONFIG_LIB_MPL "Build MPL" ON)
option(CONFIG_LIB_LOG "Build Log" ON)
option(CONFIG_LIB_UTILITY "Build Utility" ON)
option(CONFIG_LIB_ENUMERATION "Build Enumeration" ON)
              

if (CONFIG_USE_GCC_49)
  set(CMAKE_C_COMPILER /opt/gcc4.9/bin/gcc)
  set(CMAKE_CXX_COMPILER /opt/gcc4.9/bin/g++)
endif()

if (CONFIG_USE_CLANG_TRUNK)
  set(CMAKE_C_COMPILER /opt/llvm/bin/clang)
  set(CMAKE_CXX_COMPILER /opt/llvm/bin/clang++)
endif()
      
if(CONFIG_USE_CLANG)
    set(CMAKE_C_COMPILER /usr/bin/clang)
    set(CMAKE_CXX_COMPILER /usr/bin/clang++)
endif()


################################################################################
#                         PROJECT ELIB
################################################################################

# we need C to get the pthreads library 
project(EricsLibrary CXX C)

# Turn off filesystem on Win32
if ( WIN32 )

  if ( CONFIG_LIB_FILESYSTEM )
    message(WARNING "Disabling Filesystem build on windows (On by default)")
    set( CONFIG_LIB_FILESYSTEM OFF CACHE BOOL "" FORCE)
  endif()

endif()

if (CONFIG_USE_LIBCXX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -stdlib=libc++ ")
endif()

if (CONFIG_USE_OPT_LIBSTDCXX)
  set(STDLIB_LINK "-L/opt/gcc4.9/lib64 -Wl,-rpath -Wl,/opt/gcc4.9/lib64")
endif()

if (CONFIG_ASAN)
  set(CONFIG_NO_LIBRARIES ON CACHE BOOL "" FORCE)
  set(CMAKE_CXX_FLAGS  " ${CMAKE_CXX_FLAGS}  -O1 -fsanitize=address ")
endif()

if (CONFIG_TSAN)
  set(CONFIG_NO_LIBRARIES ON CACHE BOOL "" FORCE)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -fsanitize=thread ")
endif() 

if (CONFIG_MSAN)
  set(CONFIG_NO_LIBRARIES ON CACHE BOOL "" FORCE)
  set(CMAKE_CXX_FLAGS " ${CMAKE_CXX_FLAGS} -O2 -fsanitize=memory -fno-omit-frame-pointer ")
endif() 

if (CONFIG_MY_BUILD)
	# I like to install in weird places 
	if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
		set(CMAKE_INSTALL_PREFIX "/usr" 
			CACHE PATH "library install prefix" FORCE)
		MESSAGE(STATUS "Using install prefix: ${CMAKE_INSTALL_PREFIX}")
	endif()
endif()
	


set( CMAKE_BUILD_TYPE DEBUG)
set( CMAKE_CXX_FLAGS_RELEASE "-O2  -DNDEBUG " )
set( CMAKE_C_FLAGS_RELEASE "-O2  -DNDEBUG " )
set( CMAKE_C_FLAGS_DEBUG " -g -fno-omit-frame-pointer -DELIB_WARN_ON " )
set( CMAKE_CXX_FLAGS_DEBUG " -g -fno-omit-frame-pointer  -DDELIB_WARN_ON " )

set(headerDir ${CMAKE_CURRENT_LIST_DIR}/elib)
include_directories(${CMAKE_CURRENT_LIST_DIR})

find_package( Threads REQUIRED )
add_definitions( -std=c++11 -Wall -Wextra -pedantic)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin) 
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin)



################################################################################
#                           Additional config
################################################################################

set(CONFIG_MP_LIMIT_MAX ON)
if (CONFIG_MP_LIMIT_MAX)
  
  add_definitions( -DELIB_MP_USE_MAX_LIMITS )
  
  if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" )
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ftemplate-depth=1024 ")
  endif()
    
endif()



################################################################################
#                           Macros & Functions
################################################################################

macro(set_dot_dir)
  set(dotDir ${CMAKE_CURRENT_LIST_DIR})
endmacro(set_dot_dir)

macro(add_library_src)
  set_dot_dir()
  aux_source_directory(${dotDir} _src)
  list(APPEND LIBRARY_SRC ${_src})
endmacro(add_library_src)

macro(add_unit_test_src)
  set_dot_dir()
  aux_source_directory(${dotDir}/unit_tests _test)
  list(APPEND UNIT_TEST_SRC ${_test})
endmacro(add_unit_test_src)

macro(add_src)
  add_library_src()
  add_unit_test_src()
endmacro(add_src)

macro(stringify_list m_list dest)
  string(REPLACE ";" " " ${dest} "${m_list}")
endmacro(stringify_list)

macro(add_flags to)
  stringify_list("${ARGN}" _TMP)
  set(${to} "${${to}} ${_TMP}")
endmacro(add_flags)


macro(include_library_if Pred CFile)
  if (${Pred})
    include(${CFile})
    add_definitions( -DELIB_${Pred} )
  endif()
endmacro(include_library_if)




add_subdirectory(src)
#add_subdirectory(test_main)


