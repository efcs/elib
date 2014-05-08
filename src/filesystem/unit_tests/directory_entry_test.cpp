#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <elib/filesystem/directory_entry.hpp>
#include <elib/filesystem/file_status.hpp>
#include <elib/filesystem/filesystem_error.hpp>
#include <elib/filesystem/path.hpp>
#include <elib/aux.hpp>

#ifndef ELIB_FS_UNIT_TEST_PATH
# error ELIB_FS_UNIT_TEST_PATH must be set to the directory of this file
# endif

using namespace elib::fs;

inline bool operator==(file_status lhs, file_status rhs) noexcept
{
    return lhs.type() == rhs.type() && lhs.permissions() == rhs.permissions();
}

inline bool operator!=(file_status lhs, file_status rhs) noexcept
{
    return lhs.type() != rhs.type() || lhs.permissions() != rhs.permissions();
}

BOOST_AUTO_TEST_SUITE(filesystem_directory_entry_test_suite)

BOOST_AUTO_TEST_CASE(constructor_tests)
{
    const path p("/foo/bar");
    
    {
        const directory_entry d(p);
        BOOST_CHECK(d.path() == p);
    }
    {
        directory_entry d;
        BOOST_CHECK(d.path() == path());
    }
    {
        const directory_entry d(p);
        const directory_entry d2(d);
        BOOST_CHECK(d2 == d);
    }
    {
        directory_entry d(p);
        const directory_entry d2(elib::move(d));
        BOOST_CHECK(d2.path() == p);
    }
}

BOOST_AUTO_TEST_CASE(assignment_tests)
{
    const path p("/foo/bar/baz.txt");
    {
        const directory_entry d(p);
        directory_entry d2;
        d2 = d;
        BOOST_CHECK(d2 == d);
    }
    {
        directory_entry d(p);
        directory_entry d2;
        d2 = elib::move(d);
        BOOST_CHECK(d2.path() == p);
    }
    {
        directory_entry d;
        d.assign(p);
        BOOST_CHECK(d.path() == p);
    }
}

BOOST_AUTO_TEST_CASE(replace_filename_test)
{
    const path p("/foo/bar/baz.txt");
    directory_entry d(p);
    d.replace_filename("hello.txt");
    BOOST_CHECK(d.path() == path("/foo/bar/hello.txt"));
}

BOOST_AUTO_TEST_CASE(status_test)
{
    const file_status good_st(file_type::regular, perms::all);
    const file_status bad_st(file_type::none, perms::unknown);
    const file_status symlink_st(file_type::symlink, perms::none);
    
    // status known - no errc
    {
        const directory_entry d("/bar/baz", good_st, bad_st);
        file_status ret = d.status();
        BOOST_CHECK(ret == good_st);
    }
    // status known - w/ errc
    {
        const directory_entry d("/bar/baz", good_st, bad_st);
        std::error_code ec;
        file_status ret = d.status(ec);
        BOOST_CHECK(!ec);
        BOOST_CHECK(ret == good_st);
    }
    // symlink status known w/o errc
    {
        const directory_entry d("/bar/baz", bad_st, good_st);
        file_status ret = d.status();
        BOOST_CHECK(ret == good_st);
    }
    // symlink status known w/ errc
    {
        const directory_entry d("/bar/baz", bad_st, good_st);
        std::error_code ec;
        file_status ret = d.status(ec);
        BOOST_CHECK(not ec);
        BOOST_CHECK(ret == good_st);
    }
    // symlink status known and is symlink w/o errc
    {
        const directory_entry d(ELIB_FS_UNIT_TEST_PATH, bad_st, symlink_st);
        file_status ret;
        BOOST_CHECK_NO_THROW(ret = d.status())
        BOOST_CHECK(ret.type() == file_type::directory);
    }
    // symlink status known and is symlink w/ errc
    {
        const directory_entry d(ELIB_FS_UNIT_TEST_PATH, bad_st, symlink_st);
        std::error_code ec;
        file_status ret = d.status(ec);
        BOOST_CHECK(not ec);
        BOOST_CHECK(ret.type() == file_type::directory);
    }
    // no status known w/o errc
    {
        const directory_entry d(ELIB_FS_UNIT_TEST_PATH, bad_st, bad_st);
        file_status ret;
        BOOST_CHECK_NO_THROW(ret = d.status());
        BOOST_CHECK(ret.type() == file_type::directory);
    }
    // no status known w/ errc
    {
        const directory_entry d(ELIB_FS_UNIT_TEST_PATH, bad_st, bad_st);
        std::error_code ec;
        file_status ret = d.status(ec);
        BOOST_CHECK(not ec);
        BOOST_CHECK(ret.type() == file_type::directory);
    }
}

BOOST_AUTO_TEST_CASE(symlink_status_test)
{
    const file_status good_st(file_type::regular, perms::all);
    const file_status bad_st(file_type::none, perms::unknown);
    // status known w/o errc
    {
        const directory_entry d("/bar/baz", bad_st, good_st);
        file_status ret = d.symlink_status();
        BOOST_CHECK(ret == good_st);
    }
    // status known w/ errc
    {
        const directory_entry d("/bar/baz", bad_st, good_st);
        std::error_code ec;
        file_status ret = d.symlink_status(ec);
        BOOST_CHECK(not ec);
        BOOST_CHECK(ret == good_st);
    }
    // status unknown w/o errc
    {
        const directory_entry d(ELIB_FS_UNIT_TEST_PATH, bad_st, bad_st);
        file_status ret;
        BOOST_CHECK_NO_THROW(ret = d.symlink_status());
        BOOST_CHECK(ret.type() == file_type::directory);
    }
    // status unknown w/ errc
    {
        const directory_entry d(ELIB_FS_UNIT_TEST_PATH, bad_st, bad_st);
        std::error_code ec;
        file_status ret = d.symlink_status(ec);
        BOOST_CHECK(not ec);
        BOOST_CHECK(ret.type() == file_type::directory);
    }
}


BOOST_AUTO_TEST_CASE(comparison_tests)
{
    const path p1("/foo/bar/baz.txt");
    const path p2("/tada");
    const directory_entry d1(p1);
    const directory_entry d2(p2);
    
    BOOST_CHECK((p1 == p1) == (d1 == d1));
    BOOST_CHECK((p1 == p2) == (d1 == d2));
    BOOST_CHECK((p2 == p1) == (d2 == d1));
    
    BOOST_CHECK((p1 != p1) == (d1 != d1));
    BOOST_CHECK((p1 != p2) == (d1 != d2));
    BOOST_CHECK((p2 != p1) == (d2 != d1));
    
    BOOST_CHECK((p1 < p1) == (d1 < d1));
    BOOST_CHECK((p1 < p2) == (d1 < d2));
    BOOST_CHECK((p2 < p1) == (d2 < d1));
    
    BOOST_CHECK((p1 > p1) == (d1 > d1));
    BOOST_CHECK((p1 > p2) == (d1 > d2));
    BOOST_CHECK((p2 > p1) == (d2 > d1));
    
    BOOST_CHECK((p1 <= p1) == (d1 <= d1));
    BOOST_CHECK((p1 <= p2) == (d1 <= d2));
    BOOST_CHECK((p2 <= p1) == (d2 <= d1));
    
    BOOST_CHECK((p1 >= p1) == (d1 >= d1));
    BOOST_CHECK((p1 >= p2) == (d1 >= d2));
    BOOST_CHECK((p2 >= p1) == (d2 >= d1));
}


BOOST_AUTO_TEST_SUITE_END()