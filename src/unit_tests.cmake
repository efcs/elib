
################################################################################

# SAMPLEOBJ is used by lit.cfg to create a template build rule. 
# When we LIT builds a negative compilation test it uses the flags for SAMPLEOBJ
add_executable(SAMPLEOBJ sample_test.pass.cpp)
target_include_directories(SAMPLEOBJ PUBLIC ${ELIB_ROOT_PATH}/packages/rapid-cxx-test/)
target_link_libraries(SAMPLEOBJ elib ${CMAKE_THREAD_LIBS_INIT} )
set_target_properties(SAMPLEOBJ PROPERTIES EXCLUDE_FROM_ALL ON EXCLUDE_FROM_DEFAULT_BUILD ON)

# We actually need to give sample_test a target that matches the naming convention
# for tests. 
add_test_target(sample_test sample_test.pass.cpp)

if (PYTHONINTERP_FOUND)

  set(SAMPLE_OBJECT "SAMPLEOBJ")

  configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/lit.site.cfg.in
    ${CMAKE_CURRENT_BINARY_DIR}/lit.site.cfg
    @ONLY)

  configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/check-lit.mk.in
    ${ELIB_MAKEFILE_RULE_PATH}/check-lit.mk
    @ONLY)

  add_custom_target(check-lit-depends DEPENDS elib)
  add_dependencies(check-all-depends check-lit-depends)

  set(ELIB_TEST_SUITES "${ELIB_TEST_SUITES} ${CMAKE_CURRENT_BINARY_DIR}" PARENT_SCOPE)
else()
  message(WARNING "Could not find Python, no check target will be available!")
endif()