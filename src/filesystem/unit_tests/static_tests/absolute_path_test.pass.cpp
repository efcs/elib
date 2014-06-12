// REQUIRES: ELIB_FILESYSTEM_SOURCE
#define BOOST_TEST_MODULE Main
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <elib/filesystem.hpp>
using namespace elib;
using namespace elib::fs;


BOOST_AUTO_TEST_SUITE(elib_filesystem_static_absolute_path_test_suite)

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

BOOST_AUTO_TEST_SUITE_END()