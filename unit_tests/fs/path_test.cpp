#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>


#include "elib/fs/path.hpp"
#include "elib/debug/eval.hpp"


#if 0

using namespace elib;
using namespace elib::fs;


bool
check(const std::string & ctor,
      const std::string & iter,
      const std::string & str,
      const std::string & root_path,
      const std::string & root_name,
      const std::string & root_dir,
      const std::string & rel_path,
      const std::string & parent_path,
      const std::string & filename)
{
    path p(ctor);
    
    std::string iter_join;
    for (auto & s : p) {
        iter_join += s.str() + ",";
    }
    if (! iter_join.empty())
        iter_join.erase(--iter_join.end());
    
    EVAL_BEGIN()
    EVAL(==, iter_join, iter);
    EVAL(==, p.str(), str);
    EVAL(==, p.root_path().str(), root_path);
    EVAL(==, p.root_name().str(), root_name);
    EVAL(==, p.root_directory().str(), root_dir);
    EVAL(==, p.relative_path().str(), rel_path);
    EVAL(==, p.parent_path().str(), parent_path);
    EVAL(==, p.filename().str(), filename);
    EVAL_END()
}

BOOST_AUTO_TEST_SUITE(path_test_suite)

BOOST_AUTO_TEST_CASE(path_table)
{
    BOOST_CHECK(check("", "", "", "", "",  "", "", "", ""));
    BOOST_CHECK(check(".", ".", ".", "", "",  "", ".", "", "."));
    BOOST_CHECK(check("..", "..", "..", "", "",  "", "..", "", ".."));
    BOOST_CHECK(check("foo", "foo", "foo", "", "",  "", "foo", "", "foo"));
    BOOST_CHECK(check("/", "/", "/", "/", "",  "/", "", "", "/"));
    BOOST_CHECK(check("/foo", "/,foo", "/foo", "/", "",  "/", "foo", "/", "foo"));
    BOOST_CHECK(check("foo/", "foo,.", "foo/", "", "",  "", "foo/", "foo", "."));
    BOOST_CHECK(check("/foo/", "/,foo,.", "/foo/", "/", "",  "/", "foo/", "/foo", "."));
    BOOST_CHECK(check("foo/bar", "foo,bar", "foo/bar", "", "",  "", "foo/bar", "foo", "bar"));
    BOOST_CHECK(check("/foo/bar", "/,foo,bar", "/foo/bar", "/", "",  "/", "foo/bar", "/foo", "bar"));
    BOOST_CHECK(check("//net", "//net", "//net", "//net", "//net",  "", "", "", "//net"));
    BOOST_CHECK(check("//net/foo", "//net,/,foo", "//net/foo", "//net/", "//net",  "/", "foo", "//net/", "foo"));
    BOOST_CHECK(check("///foo///", "/,foo,.", "///foo///", "/", "",  "/", "foo///", "///foo", "."));
    BOOST_CHECK(check("///foo///bar", "/,foo,bar", "///foo///bar", "/", "",  "/", "foo///bar", "///foo", "bar"));
    BOOST_CHECK(check("/.", "/,.", "/.", "/", "",  "/", ".", "/", "."));
    BOOST_CHECK(check("./", ".,.", "./", "", "",  "", "./", ".", "."));
    BOOST_CHECK(check("/..", "/,..", "/..", "/", "",  "/", "..", "/", ".."));
    BOOST_CHECK(check("../", "..,.", "../", "", "",  "", "../", "..", "."));
    BOOST_CHECK(check("foo/.", "foo,.", "foo/.", "", "",  "", "foo/.", "foo", "."));
    BOOST_CHECK(check("foo/..", "foo,..", "foo/..", "", "",  "", "foo/..", "foo", ".."));
    BOOST_CHECK(check("foo/./", "foo,.,.", "foo/./", "", "",  "", "foo/./", "foo/.", "."));
    BOOST_CHECK(check("foo/./bar", "foo,.,bar", "foo/./bar", "", "",  "", "foo/./bar", "foo/.", "bar"));
    BOOST_CHECK(check("foo/..", "foo,..", "foo/..", "", "",  "", "foo/..", "foo", ".."));
    BOOST_CHECK(check("foo/../", "foo,..,.", "foo/../", "", "",  "", "foo/../", "foo/..", "."));
    BOOST_CHECK(check("foo/../bar", "foo,..,bar", "foo/../bar", "", "",  "", "foo/../bar", "foo/..", "bar"));
}

BOOST_AUTO_TEST_SUITE_END()

#endif
