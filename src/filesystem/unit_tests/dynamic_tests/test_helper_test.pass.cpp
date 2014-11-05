// REQUIRES: ELIB_FILESYSTEM, ELIB_PYTHON_EXECUTABLE
#include "../dynamic_test_helper.hpp"
#include "rapid-cxx-test.hpp"

TEST_SUITE(elib_filesystem_helper_test_suite)

TEST_CASE(env_test)
{
    scoped_test_env env;
    env.create_file("f1");
    env.create_dir("d1");
    env.create_symlink("f1", "s1");
    env.create_hardlink("f1", "h1");
    env.create_fifo("fifo1");
    env.create_socket("socket1");
    TEST_CHECK(true);
}

TEST_SUITE_END()