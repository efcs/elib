################################################################################
##                             Library Parts
################################################################################
set(LIBRARY_SRC "")
set(LIBRARY_FLAGS "")

include_library_if(ELIB_SOURCE             src/elib/build.cmake         )
include_library_if(ELIB_AUX_SOURCE         src/aux/build.cmake          )
include_library_if(ELIB_CONTAINER_SOURCE   src/container/build.cmake    )
include_library_if(ELIB_ENUMERATION_SOURCE src/enumeration/build.cmake  )
include_library_if(ELIB_EXCEPTION_SOURCE   src/exception/build.cmake    )
include_library_if(ELIB_FILESYSTEM_SOURCE  src/filesystem/build.cmake   )
include_library_if(ELIB_FUNCTIONAL_SOURCE  src/functional/build.cmake   )
include_library_if(ELIB_ITERATOR_SOURCE    src/iterator/build.cmake     )
include_library_if(ELIB_LOGGING_SOURCE     src/logging/build.cmake      )
include_library_if(ELIB_MEMORY_SOURCE      src/memory/build.cmake       )
include_library_if(ELIB_MP_SOURCE          src/mp/build.cmake           )
include_library_if(ELIB_PP_SOURCE          src/preprocessor/build.cmake )


if (CONFIG_ENABLE_EXPERIMENTAL)
  include_library_if(ELIB_CONTRACT_ASSERT_SOURCE 
                     src/experimental/contract_assert/build.cmake)
  include_library_if(ELIB_WEB_SOURCE
                     src/experimental/web/build.cmake)
endif()