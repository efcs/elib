// REQUIRES: ELIB_FILESYSTEM_SOURCE
#define BOOST_TEST_MODULE Main
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <elib/filesystem.hpp>
using namespace elib;
using namespace elib::fs;

BOOST_AUTO_TEST_SUITE(elib_filesystem_static_canonical_path_test_suite)

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
        
        /// NOTE: on mac /tmp's canonical path is not /tmp.
        /// So to make this test path,  we have to find tmp's canonical path.
        path canon_tmp = fs::canonical("/tmp");
        ret = fs::canonical(p, canon_tmp, ec);
        BOOST_CHECK(!ec);
        BOOST_CHECK(ret == canon_tmp.parent_path());
    }
    // TODO symlink test
}

BOOST_AUTO_TEST_SUITE_END()
