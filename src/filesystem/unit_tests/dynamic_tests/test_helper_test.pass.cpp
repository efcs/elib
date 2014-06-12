// REQUIRES: ELIB_FILESYSTEM_SOURCE
#define BOOST_TEST_MODULE Main
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "../dynamic_test_helper.hpp"

BOOST_AUTO_TEST_SUITE(elib_filesystem_helper_test_suite)

BOOST_AUTO_TEST_CASE(env_test)
{
    scoped_test_env env;
    env.create_file("f1");
    env.create_dir("d1");
    env.create_symlink("f1", "s1");
    env.create_hardlink("f1", "h1");
    env.create_fifo("fifo1");
    env.create_socket("socket1");
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_SUITE_END()