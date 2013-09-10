#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>


#include <elib/fs/filesystem.h>

#include <system_error>
#include <iostream>

#define PRINTL(x) std::cout << (x) << std::endl

using namespace elib;
using namespace elib::fs;

BOOST_AUTO_TEST_SUITE(fs_operations_test_suite)

BOOST_AUTO_TEST_CASE(fs_operations_init)
{

}


BOOST_AUTO_TEST_CASE(test_mkdir)
{
    path p("/home/eric/tmp/tmp.dir");
    std::error_code ec;
    bool ret = create_directory(p, ec);
    BOOST_CHECK(ret);
    ec.clear();
    
    p = path("/home/eric/tmp/tmp.dne");
    
}
 
BOOST_AUTO_TEST_SUITE_END()