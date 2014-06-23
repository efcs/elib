
set(ELIB_AVAILABLE_FEATURES ${ELIB_LIBRARIES})

add_executable(SAMPLEOBJHEADER sample_test.pass.cpp)
set_target_properties(SAMPLEOBJHEADER PROPERTIES EXCLUDE_FROM_ALL ON EXCLUDE_FROM_DEFAULT_BUILD ON)

set(SAMPLE_OBJECT "SAMPLEOBJHEADER")

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/lit.site.cfg.in
    ${CMAKE_CURRENT_BINARY_DIR}/lit.site.cfg
    @ONLY)

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/check-headers.mk.in
    ${ELIB_MAKEFILE_RULE_PATH}/check-headers.mk
    @ONLY)

add_custom_target(check-headers-depends
    COMMAND rm -rf ${CMAKE_CURRENT_LIST_DIR}/elib
    COMMAND cp -R ${ELIB_ROOT_PATH}/elib ${CMAKE_CURRENT_LIST_DIR})

add_dependencies(check-all-depends check-headers-depends)

set(ELIB_TEST_SUITES "${ELIB_TEST_SUITES} ${CMAKE_CURRENT_BINARY_DIR}" PARENT_SCOPE)
