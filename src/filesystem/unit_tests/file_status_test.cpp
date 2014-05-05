#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <elib/filesystem/config.hpp>
#include <elib/filesystem/file_status.hpp>

using namespace elib::fs;

BOOST_AUTO_TEST_SUITE(fs_file_status_test_suite)

BOOST_AUTO_TEST_CASE(fs_file_status_ctor_test)
{
    // default ctor test
    {
        const file_status st;
        BOOST_CHECK(st.type() == file_type::none);
        BOOST_CHECK(st.permissions() == perms::unknown);
    }
    // single ctor test
    {
        const file_status st(file_type::not_found);
        BOOST_CHECK(st.type() == file_type::not_found);
        BOOST_CHECK(st.permissions() == perms::unknown);
    }
    // double ctor test
    {
        const file_status st(file_type::regular, perms::owner_read);
        BOOST_CHECK(st.type() == file_type::regular);
        BOOST_CHECK(st.permissions() == perms::owner_read);
    }
}

BOOST_AUTO_TEST_CASE(fs_file_status_modifiers)
{
    file_status st;
    
    // type test
    st.type(file_type::regular);
    BOOST_CHECK(st.type() == file_type::regular);
    
    // permissions test
    st.permissions(perms::owner_read);
    BOOST_CHECK(st.permissions() == perms::owner_read);
}

BOOST_AUTO_TEST_SUITE_END()