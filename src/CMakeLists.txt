# Author: Eric Fiselier

set(UNIT_TEST_FLAGS "")
set(HEADER_TEST_SRC "")
set(UNIT_TEST_SRC "")

include(libraries.cmake)


if (CONFIG_UNIT_TESTS)
    include(unit_tests.cmake)
endif()
