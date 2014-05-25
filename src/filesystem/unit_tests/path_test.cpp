#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "filesystem_test_helper.hpp"

#include <elib/filesystem/path.hpp>
#include <elib/aux.hpp>
#include <string>
#include <vector>
using namespace elib::fs;


    


BOOST_AUTO_TEST_SUITE(elib_filesystem_path_test_suite)

BOOST_AUTO_TEST_CASE(default_ctor_test)
{
    path p;
    BOOST_CHECK(p.empty());
}

BOOST_AUTO_TEST_CASE(copy_ctor_test)
{
    path p("my_path");
    path p2(p);
    BOOST_CHECK(p == p2);
}

BOOST_AUTO_TEST_CASE(move_ctor_test)
{
    path p("my_path");
    path p2(elib::move(p));
    BOOST_CHECK(p2 == path("my_path"));
}

BOOST_AUTO_TEST_CASE(string_ctor_test)
{
    std::string str_path("my_path");
    path p(str_path);
    BOOST_CHECK(p.native() == str_path);
}

BOOST_AUTO_TEST_CASE(iterator_ctor_test)
{
    std::string str_path("my_path");
    path p(str_path.begin(), str_path.end());
    BOOST_CHECK(p.native() == str_path);
}

BOOST_AUTO_TEST_CASE(assign_operator_copy_test)
{
    std::string expect("my_path");
    path p;
    const path p2(expect);
    p = p2;
    BOOST_CHECK(p.native() == expect);
}

BOOST_AUTO_TEST_CASE(assign_operator_move_test)
{
    std::string expect("my_path");
    path p;
    path p2(expect);
    p = elib::move(p2);
    BOOST_CHECK(p.native() == expect);
}

BOOST_AUTO_TEST_CASE(assign_string_test)
{
    std::string expect("my_path");
    path p;
    p.assign(expect);
    BOOST_CHECK(p.native() == expect);
}

BOOST_AUTO_TEST_CASE(assign_iterator_test)
{
    std::string expect("my_path");
    path p;
    p.assign(expect.begin(), expect.end());
    BOOST_CHECK(p.native() == expect);
}

BOOST_AUTO_TEST_CASE(append_operator_test)
{
    {
        std::string expect("p1/p2");
        path p1("p1");
        path p2("p2");
        p1 /= p2;
        BOOST_CHECK(p1.native() == expect);
    }
    // redundant sep on lhs
    {
        std::string expect("p1/p2");
        path p1("p1/");
        path p2("p2");
        p1 /= p2;
        BOOST_CHECK(p1.native() == expect);
    }
    // redundant sep on rhs
    {
        std::string expect("p1/p2");
        path p1("p1");
        path p2("/p2");
        p1 /= p2;
        BOOST_CHECK(p1.native() == expect);
    }
    // redundant sep on both
    {
        std::string expect("p1//p2");
        path p1("p1/");
        path p2("/p2");
        p1 /= p2;
        BOOST_CHECK(p1.native() == expect);
    }
    // redundant sep on rhs (windows sep)
    {
        std::string expect("p1\\p2"); 
        path p1("p1");
        path p2("\\p2");
        p1 /= p2;
        BOOST_CHECK(p1.native() == expect);
    }
    // p is empty
    {
        std::string expect("p1");
        path p1("p1");
        path p2;
        p1 /= p2;
        BOOST_CHECK(p1.native() == expect);
    }
    // p2 is empty
    {
        std::string expect("p2");
        path p1;
        path p2("p2");
        p1 /= p2;
        BOOST_CHECK(p1.native() == expect);
    }
    // both empty
    {
        std::string expect;
        path p1;
        path p2;
        p1 /= p2;
        BOOST_CHECK(p1.native() == expect);
    }
}

BOOST_AUTO_TEST_CASE(append_string_operator_test)
{
    std::string expect("p1/p2");
    path p1("p1");
    std::string p2("p2");
    p1 /= p2;
    BOOST_CHECK(p1.native() == expect);
}

BOOST_AUTO_TEST_CASE(append_string_method_test)
{
    std::string expect("p1/p2");
    path p1("p1");
    std::string p2("p2");
    p1.append(p2);
    BOOST_CHECK(p1.native() == expect);
}

BOOST_AUTO_TEST_CASE(append_iterator_method_test)
{
    std::string expect("p1/p2");
    path p1("p1");
    std::string p2("p2");
    p1.append(p2.begin(), p2.end());
    BOOST_CHECK(p1.native() == expect);
}

BOOST_AUTO_TEST_CASE(concat_test)
{
    const std::string expect("p1/p2");
    const std::string s1("p1/");
    const std::string s2("p2");
    
    // concat path
    {
        path p1(s1);
        path p2(s2);
        p1 += p2;
        BOOST_CHECK(p1 == expect);
    }
    // concat string
    {
        path p1(s1);
        std::string p2(s2);
        p1 += p2;
        BOOST_CHECK(p1 == expect);
    }
    // concat c string
    {
        path p1(s1);
        p1 += s2.c_str();
        BOOST_CHECK(p1 == expect);
    }
    // concat source type
    {
        path p1(s1);
        std::vector<char> p2(s2.begin(), s2.end());
        p1 += p2;
        BOOST_CHECK(p1 == expect);
    }
    // concat char
    {
        path p1(s1);
        p1 += 'p';
        BOOST_CHECK(p1 == path("p1/p"));
    }
    // concat source member type
    {
        path p1(s1);
        std::vector<char> p2(s2.begin(), s2.end());
        p1.concat(p2);
        BOOST_CHECK(p1 == expect);
    }
    // concat iterator member type
    {
        path p1(s1);
        std::vector<char> p2(s2.begin(), s2.end());
        p1.concat(p2.begin(), p2.end());
        BOOST_CHECK(p1 == expect);
    }
}

BOOST_AUTO_TEST_CASE(clear_test)
{
    path p1("non-empty");
    BOOST_REQUIRE(not p1.empty());
    p1.clear();
    BOOST_CHECK(p1.empty());
}

BOOST_AUTO_TEST_CASE(make_preferred_test)
{
    // empty test
    {
        path expect;
        path p;
        p.make_preferred();
        BOOST_CHECK(p == expect);
    }
    // no seperator test
    {
        path expect("hello_world");
        path p(expect);
        p.make_preferred();
        BOOST_CHECK(p == expect);
    }
    // only prefered seperator
    {
        path expect("/");
        path p(expect);
        p.make_preferred();
        BOOST_CHECK(p == expect);
    }
    // preferred seperator in path
    {
        path expect("/foo/bar/baz/");
        path p(expect);
        p.make_preferred();
        BOOST_CHECK(p == expect);
    }
    // only non-preferred seperator
    {
        path expect("/");
        path p("\\");
        p.make_preferred();
        BOOST_CHECK(p == expect);
    }
    // non-preferred in path
    {
        path expect("/foo/bar/baz/");
        path p("\\foo\\bar\\baz\\");
        p.make_preferred();
        BOOST_CHECK(p == expect);
    }
    // mixed
    {
        path expect("/foo/bar//baz/");
        path p("\\foo/bar\\/baz\\");
        p.make_preferred();
        BOOST_CHECK(p == expect);
    }
}

BOOST_AUTO_TEST_CASE(remove_filename_test)
{
    // empty string test
    {
        path expect;
        path p;
        p.remove_filename();
        BOOST_CHECK(p == expect);
        BOOST_CHECK(not p.has_filename());
    }
    // root path test
    {
        path expect;
        path p("/");
        p.remove_filename();
        BOOST_CHECK(p == expect);
        BOOST_CHECK(not p.has_filename());
    }
    // root path test (other seperator)
    {
        path expect;
        path p("\\");
        p.remove_filename();
        BOOST_CHECK(p == expect);
        BOOST_CHECK(not p.has_filename());
    }
    // dot test
    {
        path expect;
        path p(".");
        p.remove_filename();
        BOOST_CHECK(p == expect);
        BOOST_CHECK(not p.has_filename());
    }
    // double dot test
    {
        path expect;
        path p("..");
        p.remove_filename();
        BOOST_CHECK(p == expect);
        BOOST_CHECK(not p.has_filename());
    }
    // with filename test
    {
        path expect("/");
        path p("/foo");
        BOOST_REQUIRE(p.has_filename());
        p.remove_filename();
        BOOST_CHECK(p == expect);
    }
    // with slash test
    {
        path expect("/foo");
        path p("/foo/");
        BOOST_REQUIRE(p.has_filename());
        p.remove_filename();
        BOOST_CHECK(p == expect);
    }
    // with dot after path
    {
        path expect("/foo");
        path p("/foo/.");
        BOOST_REQUIRE(p.has_filename());
        p.remove_filename();
        BOOST_CHECK(p == expect);
    }
    // with double dot after path
    {
        path expect("/foo");
        path p("/foo/..");
        BOOST_REQUIRE(p.has_filename());
        p.remove_filename();
        BOOST_CHECK(p == expect);
    }
    // with multiple seperators
    {
        path expect("/foo");
        path p("/foo/////");
        BOOST_REQUIRE(p.has_filename());
        p.remove_filename();
        BOOST_CHECK(p == expect);
    }
    // with mixed seperator
    {
        path expect("/foo");
        path p("/foo//\\/");
        BOOST_REQUIRE(p.has_filename());
        p.remove_filename();
        BOOST_CHECK(p == expect);
    }
    // pure file name
    {
        path expect;
        path p("file.txt");
        BOOST_REQUIRE(p.has_filename());
        p.remove_filename();
        BOOST_CHECK(p == expect);
    }
    // path with file name
    {
        path expect("bar/../baz/.");
        path p("bar/../baz/./file.txt");
        BOOST_REQUIRE(p.has_filename());
        p.remove_filename();
        BOOST_CHECK(p == expect);
    }
}

BOOST_AUTO_TEST_CASE(replace_filename_test)
{
    // with filename test
    {
        path expect("/bar");
        path p("/foo");
        p.replace_filename("bar");
        BOOST_CHECK(p == expect);
    }
    // with root as filename
    {
        path expect("bar");
        path p("/");
        p.replace_filename("bar");
        BOOST_CHECK(p == expect);
    }
    // with non-preferred root
    {
        path expect("bar");
        path p("\\");
        p.replace_filename("bar");
        BOOST_CHECK(p == expect);
    }
    // with multi token seperator
    {
        path expect("bar");
        path p("///");
        p.replace_filename("bar");
        BOOST_CHECK(p == expect);
    }
    // with multi token non-prefered seperator
    {
        path expect("bar");
        path p("\\\\");
        p.replace_filename("bar");
        BOOST_CHECK(p == expect);
    }
    // dot 
    {
        path expect("bar");
        path p(".");
        p.replace_filename("bar");
        BOOST_CHECK(p == expect);
    }
    // double dot
    {
        path expect("bar");
        path p("..");
        p.replace_filename("bar");
        BOOST_CHECK(p == expect);
    }
    // multi part path
    {
        path expect("/foo\\baz/bong/bar");
        path p("/foo\\baz/bong/");
        p.replace_filename("bar");
        BOOST_CHECK(p == expect);
    }
    // multi part path
    {
        path expect("/foo\\baz/bar");
        path p("/foo\\baz/bong");
        p.replace_filename("bar");
        BOOST_CHECK(p == expect);
    }
}

BOOST_AUTO_TEST_CASE(replace_extension_test)
{
    // empty test
    {
        path expect;
        path p;
        p.replace_extension();
        BOOST_CHECK(p == expect);
    }
    // empty path test no dot
    {
        path expect(".txt");
        path p;
        p.replace_extension("txt");
        BOOST_CHECK(p == expect);
    }
    // empty path with dot
    {
        path expect(".txt");
        path p;
        p.replace_extension(".txt");
        BOOST_CHECK(p == expect);
    }
    // non-empty path with no extension
    {
        path expect("/foo.txt");
        path p("/foo");
        p.replace_extension(".txt");
        BOOST_CHECK(p == expect);
    }
    // non-empty path with no extension no dot
    {
        path expect("/foo.txt");
        path p("/foo");
        p.replace_extension("txt");
        BOOST_CHECK(p == expect);
    }
    // non-empty path with extension
    {
        path expect("/foo.txt");
        path p("/foo.cpp");
        p.replace_extension(".txt");
        BOOST_CHECK(p == expect);
    }
    // non-empty path with extension no dot
    {
        path expect("/foo.txt");
        path p("/foo.cpp");
        p.replace_extension("txt");
        BOOST_CHECK(p == expect);
    }
}

BOOST_AUTO_TEST_CASE(swap_test)
{
    path p1("hello");
    path p2("world");
    p1.swap(p2);
    BOOST_CHECK(p1 == "world");
    BOOST_CHECK(p2 == "hello");
}

BOOST_AUTO_TEST_CASE(to_string_converters_test)
{
    const std::string expect("/foo/bar/baz");
    const path p(expect);
    BOOST_CHECK(p.native() == expect);
    BOOST_CHECK(p.c_str() == expect);
    BOOST_CHECK(static_cast<std::string>(p) == expect);
    BOOST_CHECK(p.string() == expect);
}

BOOST_AUTO_TEST_CASE(compare_test)
{
    const std::string s1("/foo/./bar/baz");
    const std::string s2("/foo/bar/baz");
    const path p1(s1);
    const path p2(s2);
    
    BOOST_CHECK(p1.compare(p2) < 0);
    BOOST_CHECK(p1.compare(p1) == 0);
    BOOST_CHECK(p2.compare(p1) > 0);
    
    BOOST_CHECK(p1.compare(s2) < 0);
    BOOST_CHECK(p1.compare(s1) == 0);
    BOOST_CHECK(p2.compare(s1) > 0);
    
    BOOST_CHECK(p1.compare("/foo/bar/baz") < 0);
    BOOST_CHECK(p1.compare("/foo/./bar/baz") == 0);
    BOOST_CHECK(p2.compare("/foo/./bar/baz") > 0);
}



BOOST_AUTO_TEST_CASE(path_decomp_test)
{
    
    struct path_decomp
    {
        std::string raw;
        std::vector<std::string> elements;
        std::string root_path;
        std::string root_name;
        std::string root_directory;
        std::string relative_path;
        std::string parent_path;
        std::string filename;
    };

    /// Path decomp table is given in boost filesystem documentation.
    const std::vector<path_decomp> path_decomp_list =
    {
        {"", {}, "", "", "", "", "", ""}
      , {".", {"."}, "", "", "", ".", "", "."}
      , {"..", {".."}, "", "", "", "..", "", ".."}
      , {"foo", {"foo"}, "", "", "", "foo", "", "foo"}
      , {"/", {"/"}, "/", "", "/", "", "", "/"}
      , {"/foo", {"/", "foo"}, "/", "", "/", "foo", "/", "foo"}
      , {"foo/", {"foo", "."}, "", "", "", "foo/", "foo", "."}
      , {"/foo/", {"/", "foo", "."}, "/", "", "/", "foo/", "/foo", "."}
      , {"foo/bar", {"foo","bar"}, "",  "", "",  "foo/bar", "foo", "bar"}
      , {"/foo/bar", {"/","foo","bar"}, "/", "", "/", "foo/bar", "/foo", "bar"}
      , {"//net", {"//net"}, "//net", "//net", "", "", "", "//net"}
      , {"//net/foo", {"//net", "/", "foo"}, "//net/", "//net", "/", "foo", "//net/", "foo"}
      , {"///foo///", {"/", "foo", "."}, "/", "", "/", "foo///", "///foo", "."}
      , {"///foo///bar", {"/", "foo", "bar"}, "/", "", "/", "foo///bar", "///foo", "bar"}
      , {"/.", {"/", "."}, "/", "", "/", ".", "/", "."}
      , {"./", {".", "."}, "", "", "", "./", ".", "."}
      , {"/..", {"/", ".."}, "/", "", "/", "..", "/", ".."}
      , {"../", {"..", "."}, "", "", "", "../", "..", "."}
      , {"foo/.", {"foo", "."}, "", "", "", "foo/.", "foo", "."}
      , {"foo/..", {"foo", ".."}, "", "", "", "foo/..", "foo", ".."}
      , {"foo/./", {"foo", ".", "."}, "", "", "", "foo/./", "foo/.", "."}
      , {"foo/./bar", {"foo", ".", "bar"}, "", "", "", "foo/./bar", "foo/.", "bar"}
      , {"foo/../", {"foo", "..", "."}, "", "", "", "foo/../", "foo/..", "."}
      , {"foo/../bar", {"foo", "..", "bar"}, "", "", "", "foo/../bar", "foo/..", "bar"}
    };
    
    for (auto const & decomp : path_decomp_list) {
        path p(decomp.raw);
        BOOST_REQUIRE(p == decomp.raw);
        
        BOOST_CHECK(p.root_path() == decomp.root_path);
        BOOST_CHECK(p.has_root_path() == not decomp.root_path.empty());
        
        BOOST_CHECK(p.root_name() == decomp.root_name);
        BOOST_CHECK(p.has_root_name() == not decomp.root_name.empty());
        
        BOOST_CHECK(p.root_directory() == decomp.root_directory);
        BOOST_CHECK(p.has_root_directory() == not decomp.root_directory.empty());
        
        BOOST_CHECK(p.relative_path() == decomp.relative_path);
        BOOST_CHECK(p.has_relative_path() == not decomp.relative_path.empty());
        
        BOOST_CHECK(p.parent_path() == decomp.parent_path);
        BOOST_CHECK(p.has_parent_path() == not decomp.parent_path.empty());
        
        BOOST_CHECK(p.filename() == decomp.filename);
        BOOST_CHECK(p.has_filename() == not decomp.filename.empty());
        
        BOOST_CHECK(p.is_absolute() == p.has_root_directory());
        BOOST_CHECK(p.is_relative() == not p.is_absolute());
    }
}

BOOST_AUTO_TEST_CASE(filename_decomp_test)
{
    struct filename_decomp
    {
        std::string raw;
        std::string filename;
        std::string stem;
        std::string extension;
    };
    
    const std::vector<filename_decomp> filename_decomp_list = 
    {
        {"", "", "", ""}
      , {".", ".", ".", ""}
      , {"..", "..", "..", ""}
      , {"/", "/", "/", ""}
      , {"foo", "foo", "foo", ""}
      , {"/foo/bar.txt", "bar.txt", "bar", ".txt"}
      , {"foo..txt", "foo..txt", "foo.", ".txt"}
    };
    
    for (auto const & decomp : filename_decomp_list) {
        path p(decomp.raw);
        BOOST_REQUIRE(p == decomp.raw);
        
        BOOST_CHECK(p.filename() == decomp.filename);
        BOOST_CHECK(p.has_filename() == not decomp.filename.empty());
        
        BOOST_CHECK(p.stem() == decomp.stem);
        BOOST_CHECK(p.has_stem() == not decomp.stem.empty());
        
        BOOST_CHECK(p.extension() == decomp.extension);
        BOOST_CHECK(p.has_extension() == not decomp.extension.empty());
    }
}

BOOST_AUTO_TEST_SUITE_END()