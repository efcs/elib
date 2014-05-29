#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "../dynamic_test_helper.hpp"

BOOST_AUTO_TEST_SUITE(elib_filesystem_helper_test_suite)

BOOST_AUTO_TEST_CASE(python_test)
{
    scoped_test_env env;
    python_create_file("f1");
    python_create_dir("d1");
    python_create_symlink("f1", "s1");
    python_create_hardlink("f1", "h1");
    python_create_fifo("fifo1");
    python_create_socket("socket1");
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_SUITE_END()