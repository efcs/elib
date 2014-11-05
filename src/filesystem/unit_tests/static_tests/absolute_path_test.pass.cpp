// REQUIRES: ELIB_FILESYSTEM
#include <elib/filesystem.hpp>
#include "rapid-cxx-test.hpp"
using namespace elib;
using namespace elib::fs;


TEST_SUITE(elib_filesystem_static_absolute_path_test_suite)

// There are 4 cases is the proposal for absolute path. 
// Each scope tests one of the cases.
TEST_CASE(absolute_path_test)
{
    // has_root_name() && has_root_directory()
    {
        const path p("//net/foo");
        const path base("//net/bar/baz");
        TEST_REQUIRE(p.has_root_name());
        TEST_REQUIRE(p.has_root_directory());
        TEST_CHECK(p.is_absolute());
        path ret = fs::absolute(p, base);
        TEST_CHECK(ret.is_absolute());
        TEST_CHECK(ret == p);
    }
    // !has_root_name() && has_root_directory()
    {
        const path p("/foo");
        const path base("//net/bar");
        TEST_REQUIRE(not p.has_root_name());
        TEST_REQUIRE(p.has_root_directory());
        TEST_CHECK(p.is_absolute());
        // ensure absolute(base) is not recursivly called
        TEST_REQUIRE(base.has_root_name());
        TEST_REQUIRE(base.has_root_directory());
        
        path ret = fs::absolute(p, base);
        TEST_CHECK(ret.is_absolute());
        TEST_CHECK(ret.has_root_name());
        TEST_CHECK(ret.root_name() == path("//net"));
        TEST_CHECK(ret.has_root_directory());
        TEST_CHECK(ret.root_directory() == path("/"));
        TEST_CHECK(ret == path("//net/foo"));
    }
    // has_root_name() && !has_root_directory()
    {
        const path p("//net");
        const path base("//net/foo/bar");
        TEST_REQUIRE(p.has_root_name());
        TEST_REQUIRE(not p.has_root_directory());
        TEST_CHECK(not p.is_absolute());
        // absolute is called recursivly on base. The following conditions
        // must be true for it to return base unmodified
        TEST_REQUIRE(base.has_root_name());
        TEST_REQUIRE(base.has_root_directory());
        path ret = fs::absolute(p, base);
        const path expect("//net/foo/bar");
        TEST_CHECK(ret.is_absolute());
        TEST_CHECK(ret == path("//net/foo/bar"));
    }
    // !has_root_name() && !has_root_directory()
    {
        const path p("bar/baz");
        const path base("//net/foo");
        TEST_REQUIRE(not p.has_root_name());
        TEST_REQUIRE(not p.has_root_directory());
        TEST_REQUIRE(base.has_root_name());
        TEST_REQUIRE(base.has_root_directory());
        
        path ret = fs::absolute(p, base);
        TEST_CHECK(ret.is_absolute());
        TEST_CHECK(ret == path("//net/foo/bar/baz"));
    }
}

TEST_SUITE_END()