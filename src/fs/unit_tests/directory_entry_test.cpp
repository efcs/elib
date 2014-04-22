#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "elib/fs/directory_entry.hpp"
#include "elib/fs/file_status.hpp"
#include "elib/fs/path.hpp"

using namespace elib::fs;

BOOST_AUTO_TEST_SUITE(fs_directory_entry_test_suite)

BOOST_AUTO_TEST_CASE(fs_directory_entry_ctor_test)
{
    // single arg ctor test
    {
        const path p{"/usr/bin"};
        const directory_entry ent(p);
        BOOST_CHECK(ent.path() == p);
    }
    
}

BOOST_AUTO_TEST_SUITE_END()