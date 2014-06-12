#define BOOST_TEST_MODULE Main
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <elib/filesystem/config.hpp>
#include <elib/filesystem/file_status.hpp>

using namespace elib::fs;

BOOST_AUTO_TEST_SUITE(filesystem_file_status_test_suite)

BOOST_AUTO_TEST_CASE(perms_test)
{
    // negate test
    {
        BOOST_CHECK(~perms::none == static_cast<perms>(~0));
        BOOST_CHECK(~perms::all == static_cast<perms>(~ static_cast<int>(perms::all)));
    }
    // and test
    {
        perms p = perms::owner_read & perms::owner_write;
        int ip = static_cast<int>(perms::owner_read) & static_cast<int>(perms::owner_write);
        BOOST_CHECK(p == static_cast<perms>(ip));
        p = perms::owner_read;
        p &= perms::owner_write;
        BOOST_CHECK(p == static_cast<perms>(ip));
    }
    // or test
    {
        perms p = perms::owner_read | perms::owner_write;
        int ip = static_cast<int>(perms::owner_read) | static_cast<int>(perms::owner_write);
        BOOST_CHECK(p == static_cast<perms>(ip));
        p = perms::owner_read;
        p |= perms::owner_write;
        BOOST_CHECK(p == static_cast<perms>(ip));
    }
    // xor test
    {
        perms p = perms::owner_read ^ perms::owner_write;
        int ip = static_cast<int>(perms::owner_read) ^ static_cast<int>(perms::owner_write);
        BOOST_CHECK(p == static_cast<perms>(ip));
        p = perms::owner_read;
        p ^= perms::owner_write;
        BOOST_CHECK(p == static_cast<perms>(ip));
    }
}

BOOST_AUTO_TEST_CASE(ctor_test)
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

BOOST_AUTO_TEST_CASE(assignment_coverage_test)
{
    const file_status st(file_type::regular);
    file_status st2;
    st2 = st;
    BOOST_CHECK(st2.type() == st.type());
    st2 = file_status();
    BOOST_CHECK(st2.type() == file_status().type());
}

BOOST_AUTO_TEST_CASE(modifiers_test)
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