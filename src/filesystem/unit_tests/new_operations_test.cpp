#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <elib/filesystem/file_status.hpp>
#include <elib/filesystem/filesystem_error.hpp>
#include <elib/filesystem/operations.hpp>
#include <elib/filesystem/path.hpp>

#if !defined(ELIB_FILESYSTEM_UNIT_TEST_PATH)
# error ELIB_FILESYSTEM_UNIT_TEST_PATH must be defined to filesystem/unit_tests/test_files
#endif

#if !defined(ELIB_TEST_PATH)
# error ELIB_TEST_PATH must be defined to test file path
#endif

using namespace elib;
using namespace elib::fs;

BOOST_AUTO_TEST_SUITE(filesystem_operations_test_suite)

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