#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#if !defined(ELIB_FILESYSTEM_UNIT_TEST_PATH)
# error ELIB_FILESYSTEM_UNIT_TEST_PATH must be defined to filesystem/unit_tests/test_files
#endif

#if !defined(ELIB_ROOT_PATH)
# error ELIB_ROOT_PATH must be defined to the elib directory
#endif

#if !defined(ELIB_TEST_PATH)
# error ELIB_TEST_PATH must be defined to test file path
#endif

#include <elib/filesystem/file_status.hpp>
#include <elib/filesystem/filesystem_error.hpp>
#include <elib/filesystem/operations.hpp>
#include <elib/filesystem/path.hpp>

#include <iostream>


using namespace elib;
using namespace elib::fs;

// Some files and directories we can assume to exist
const path elib_root_path(ELIB_ROOT_PATH);
const path elib_test_path(ELIB_TEST_PATH);
const path elib_makefile_path = elib_root_path / path("Makefile");
const path not_dir_path = elib_makefile_path / path("dne");
const path dne_path("/this_file_dne");

BOOST_AUTO_TEST_SUITE(filesystem_operations_test_suite)

////////////////////////////////////////////////////////////////////////////////
//                          BASIC QUERY TESTS
////////////////////////////////////////////////////////////////////////////////

BOOST_AUTO_TEST_CASE(status_test)
{
    std::error_code ec;
    // Directory test
    {
        file_status st;
        BOOST_CHECK_NO_THROW(st = fs::status(elib_root_path));
        BOOST_CHECK(st.type() == file_type::directory);
        
        st = fs::status(elib_root_path, ec);
        BOOST_CHECK(not ec);
        BOOST_CHECK(st.type() == file_type::directory);
    }
    // Directory test 2
    {
        file_status st;
        BOOST_CHECK_NO_THROW(st = fs::status(elib_test_path));
        BOOST_CHECK(st.type() == file_type::directory);
        
        st = fs::status(elib_test_path, ec);
        BOOST_CHECK(not ec);
        BOOST_CHECK(st.type() == file_type::directory);
    }
    // file test 
    {
        file_status st;
        BOOST_CHECK_NO_THROW(st = fs::status(elib_makefile_path));
        BOOST_CHECK(st.type() == file_type::regular);
        
        st = fs::status(elib_makefile_path, ec);
        BOOST_CHECK(not ec);
        BOOST_CHECK(st.type() == file_type::regular);
    }
    // dne test
    {
        file_status st;
        BOOST_CHECK_NO_THROW(st = fs::status(dne_path));
        BOOST_CHECK(st.type() == file_type::not_found);
        
        st = fs::status(dne_path, ec);
        BOOST_CHECK(ec && ec.value() == ENOENT);
        BOOST_CHECK(st.type() == file_type::not_found);
    }
    // not dir test
    {
        file_status st;
        BOOST_CHECK_NO_THROW(st = fs::status(not_dir_path));
        BOOST_CHECK(st.type() == file_type::not_found);
        
        st = fs::status(not_dir_path, ec);
        BOOST_CHECK(ec && ec.value() == ENOTDIR);
        BOOST_CHECK(st.type() == file_type::not_found);
    }
}

// Test getting current_path()
BOOST_AUTO_TEST_CASE(current_path_get_test)
{
    // no error code
    {
        path ret;
        BOOST_CHECK_NO_THROW(ret = fs::current_path());
        BOOST_CHECK(not ret.empty());
    }
    // with error code
    {
        path ret;
        std::error_code ec;
        ret = fs::current_path(ec);
        BOOST_CHECK(not ec);
        BOOST_CHECK(not ret.empty());
    }
}

// There are 4 cases is the proposal for absolute path. 
// Each scope tests one of the cases.
BOOST_AUTO_TEST_CASE(absolute_path_test)
{
    // has_root_name() && has_root_directory()
    {
        const path p("//net/foo");
        const path base("//net/bar/baz");
        BOOST_REQUIRE(p.has_root_name());
        BOOST_REQUIRE(p.has_root_directory());
        BOOST_CHECK(p.is_absolute());
        path ret = fs::absolute(p, base);
        BOOST_CHECK(ret.is_absolute());
        BOOST_CHECK(ret == p);
    }
    // !has_root_name() && has_root_directory()
    {
        const path p("/foo");
        const path base("//net/bar");
        BOOST_REQUIRE(not p.has_root_name());
        BOOST_REQUIRE(p.has_root_directory());
        BOOST_CHECK(p.is_absolute());
        // ensure absolute(base) is not recursivly called
        BOOST_REQUIRE(base.has_root_name());
        BOOST_REQUIRE(base.has_root_directory());
        
        path ret = fs::absolute(p, base);
        BOOST_CHECK(ret.is_absolute());
        BOOST_CHECK(ret.has_root_name());
        BOOST_CHECK(ret.root_name() == path("//net"));
        BOOST_CHECK(ret.has_root_directory());
        BOOST_CHECK(ret.root_directory() == path("/"));
        BOOST_CHECK(ret == path("//net/foo"));
    }
    // has_root_name() && !has_root_directory()
    {
        const path p("//net");
        const path base("//net/foo/bar");
        BOOST_REQUIRE(p.has_root_name());
        BOOST_REQUIRE(not p.has_root_directory());
        BOOST_CHECK(not p.is_absolute());
        // absolute is called recursivly on base. The following conditions
        // must be true for it to return base unmodified
        BOOST_REQUIRE(base.has_root_name());
        BOOST_REQUIRE(base.has_root_directory());
        path ret = fs::absolute(p, base);
        const path expect("//net/foo/bar");
        BOOST_CHECK(ret.is_absolute());
        BOOST_CHECK(ret == path("//net/foo/bar"));
    }
    // !has_root_name() && !has_root_directory()
    {
        const path p("bar/baz");
        const path base("//net/foo");
        BOOST_REQUIRE(not p.has_root_name());
        BOOST_REQUIRE(not p.has_root_directory());
        BOOST_REQUIRE(base.has_root_name());
        BOOST_REQUIRE(base.has_root_directory());
        
        path ret = fs::absolute(p, base);
        BOOST_CHECK(ret.is_absolute());
        BOOST_CHECK(ret == path("//net/foo/bar/baz"));
    }
}

BOOST_AUTO_TEST_CASE(canonical_test)
{
    const path curr = current_path();
    const path dne("/baz");
    const path base("/");
    BOOST_REQUIRE(! fs::exists(dne));
    std::error_code ec;
    // Does not exists
    {
        BOOST_CHECK_THROW(fs::canonical(dne), filesystem_error);
        
        BOOST_CHECK_NO_THROW(fs::canonical(dne, ec));
        BOOST_CHECK(ec);
        
        BOOST_CHECK_NO_THROW(fs::canonical(dne, base, ec));
        BOOST_CHECK(ec);
    }
    // single dot
    {
        const path p(".");
        path ret;
        BOOST_CHECK_NO_THROW(ret = fs::canonical(p));
        BOOST_CHECK(ret == curr);
        
        ret = fs::canonical(p, ec);
        BOOST_CHECK(!ec);
        BOOST_CHECK(ret == curr);
        
        ret = fs::canonical(p, base, ec);
        BOOST_CHECK(!ec);
        BOOST_CHECK(ret == path("/"));
    }
    // double dot
    {
        const path p("..");
        path ret;
        BOOST_CHECK_NO_THROW(ret = fs::canonical(p));
        BOOST_CHECK(ret == curr.parent_path());
        
        ret = fs::canonical(p, ec);
        BOOST_CHECK(!ec);
        BOOST_CHECK(ret == curr.parent_path());
        
        ret = fs::canonical(p, path("/tmp"), ec);
        BOOST_CHECK(!ec);
        BOOST_CHECK(ret == path("/"));
    }
    // TODO symlink test
}




BOOST_AUTO_TEST_SUITE_END()