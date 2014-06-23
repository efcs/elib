################################################################################
# Use the library configuration option to selectivly 
# build build a library. 
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


set(ELIB_LIBRARIES ${ELIB_LIBRARIES} PARENT_SCOPE)
