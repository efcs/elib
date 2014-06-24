// REQUIRES: ELIB_FILESYSTEM
#include <elib/filesystem/config.hpp>
#include <elib/filesystem/file_status.hpp>
#include "rapid-cxx-test.hpp"
using namespace elib::fs;

TEST_SUITE(filesystem_file_status_test_suite)

TEST_CASE(perms_test)
{
    // negate test
    {
        TEST_CHECK(~perms::none == static_cast<perms>(~0));
        TEST_CHECK(~perms::all == static_cast<perms>(~ static_cast<int>(perms::all)));
    }
    // and test
    {
        perms p = perms::owner_read & perms::owner_write;
        int ip = static_cast<int>(perms::owner_read) & static_cast<int>(perms::owner_write);
        TEST_CHECK(p == static_cast<perms>(ip));
        p = perms::owner_read;
        p &= perms::owner_write;
        TEST_CHECK(p == static_cast<perms>(ip));
    }
    // or test
    {
        perms p = perms::owner_read | perms::owner_write;
        int ip = static_cast<int>(perms::owner_read) | static_cast<int>(perms::owner_write);
        TEST_CHECK(p == static_cast<perms>(ip));
        p = perms::owner_read;
        p |= perms::owner_write;
        TEST_CHECK(p == static_cast<perms>(ip));
    }
    // xor test
    {
        perms p = perms::owner_read ^ perms::owner_write;
        int ip = static_cast<int>(perms::owner_read) ^ static_cast<int>(perms::owner_write);
        TEST_CHECK(p == static_cast<perms>(ip));
        p = perms::owner_read;
        p ^= perms::owner_write;
        TEST_CHECK(p == static_cast<perms>(ip));
    }
}

TEST_CASE(ctor_test)
{
    // default ctor test
    {
        const file_status st;
        TEST_CHECK(st.type() == file_type::none);
        TEST_CHECK(st.permissions() == perms::unknown);
    }
    // single ctor test
    {
        const file_status st(file_type::not_found);
        TEST_CHECK(st.type() == file_type::not_found);
        TEST_CHECK(st.permissions() == perms::unknown);
    }
    // double ctor test
    {
        const file_status st(file_type::regular, perms::owner_read);
        TEST_CHECK(st.type() == file_type::regular);
        TEST_CHECK(st.permissions() == perms::owner_read);
    }
}

TEST_CASE(assignment_coverage_test)
{
    const file_status st(file_type::regular);
    file_status st2;
    st2 = st;
    TEST_CHECK(st2.type() == st.type());
    st2 = file_status();
    TEST_CHECK(st2.type() == file_status().type());
}

TEST_CASE(modifiers_test)
{
    file_status st;
    
    // type test
    st.type(file_type::regular);
    TEST_CHECK(st.type() == file_type::regular);
    
    // permissions test
    st.permissions(perms::owner_read);
    TEST_CHECK(st.permissions() == perms::owner_read);
}

TEST_SUITE_END()