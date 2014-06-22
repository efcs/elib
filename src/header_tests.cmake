################################################################################
#                            Header Tests
################################################################################

add_library(HeaderTestLib OBJECT ${HEADER_TEST_SRC})
set_target_properties(HeaderTestLib PROPERTIES COMPILE_FLAGS "-fsyntax-only")
