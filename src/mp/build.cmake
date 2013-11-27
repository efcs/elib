
add_src()
set(CONFIG_MP_LIMIT_MAX ON)
if (CONFIG_MP_LIMIT_MAX)
  
  add_definitions( -DELIB_MP_USE_MAX_LIMITS )
  
  if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" )
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ftemplate-depth=1024 ")
  endif()
    
endif()