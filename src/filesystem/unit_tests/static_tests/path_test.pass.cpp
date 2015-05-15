// REQUIRES: ELIB_FILESYSTEM_SOURCE
#include <elib/filesystem.hpp>
#include <elib/aux.hpp>
#include <string>
#include <vector>
#include <sstream>
#include "../static_test_helper.hpp"
#include "rapid-cxx-test.hpp"
using namespace elib::fs;


TEST_SUITE(elib_filesystem_path_test_suite)

TEST_CASE(default_ctor_test)
{
    path p;
    TEST_CHECK(p.empty());
}

TEST_CASE(copy_ctor_test)
{
    path p("my_path");
    path p2(p);
    TEST_CHECK(p == p2);
}

TEST_CASE(move_ctor_test)
{
    path p("my_path");
    path p2(elib::move(p));
    TEST_CHECK(p2 == path("my_path"));
}

TEST_CASE(string_ctor_test)
{
    std::string str_path("my_path");
    path p(str_path);
    TEST_CHECK(p == str_path);
}

TEST_CASE(iterator_ctor_test)
{
    std::string str_path("my_path");
    path p(str_path.begin(), str_path.end());
    TEST_CHECK(p== str_path);
}

TEST_CASE(dentry_ctor_test)
{
    directory_entry d(".");
    path const p(d);
    TEST_CHECK(p == d.path());
}


TEST_CASE(assign_test)
{
    // assign operator copy
    {
        std::string expect("my_path");
        path p;
        const path p2(expect);
        p = p2;
        TEST_CHECK(p == expect);
    }
    // assign operator move
    {
        std::string expect("my_path");
        path p;
        path p2(expect);
        p = elib::move(p2);
        TEST_CHECK(p == expect);
    }
    // assign string test
    {
        std::string expect("my_path");
        path p;
        p.assign(expect);
        TEST_CHECK(p == expect);
    }
#if 0
    // assign source type test
    {
        std::string expect("my_path");
        std::vector<char> source(expect.begin(), expect.end());
        path p;
        p.assign(source);
        TEST_CHECK(p == expect);
    }
    // assign source type operator test
    {
        std::string expect("my_path");
        std::vector<char> source(expect.begin(), expect.end());
        path p;
        p = source;
        TEST_CHECK(p == expect);
    }
#endif
    // assign iterator
    {
        std::string expect("my_path");
        path p;
        p.assign(expect.begin(), expect.end());
        TEST_CHECK(p == expect);
    }
}

TEST_CASE(append_operator_test)
{
    struct append_operator_testcase
    {
        std::string lhs;
        std::string rhs;
        std::string expect;
    };
    
    const std::vector<append_operator_testcase> testcases =
    {
        {"", "", ""}
      , {"p1", "p2", "p1/p2"}
      , {"p1/", "p2", "p1/p2"}
      , {"p1", "/p2", "p1/p2"}
      , {"p1/", "/p2", "p1//p2"}
      , {"p1", "\\p2", "p1\\p2"}
      , {"p1", "", "p1"}
      , {"", "p2", "p2"}
    };
    
    for (auto const & testcase : testcases) {
        path lhs(testcase.lhs);
        path rhs(testcase.rhs);
        lhs /= rhs;
        TEST_CHECK(lhs == testcase.expect);
    }
}

TEST_CASE(append_string_operator_test)
{
    std::string expect("p1/p2");
    path p1("p1");
    std::string p2("p2");
    p1 /= p2;
    TEST_CHECK(p1 == expect);
}

TEST_CASE(append_string_method_test)
{
    std::string expect("p1/p2");
    path p1("p1");
    std::string p2("p2");
    p1.append(p2);
    TEST_CHECK(p1 == expect);
}

TEST_CASE(append_iterator_method_test)
{
    std::string expect("p1/p2");
    path p1("p1");
    std::string p2("p2");
    p1.append(p2.begin(), p2.end());
    TEST_CHECK(p1 == expect);
}

TEST_CASE(concat_test)
{
    const std::string expect("p1/p2");
    const std::string s1("p1/");
    const std::string s2("p2");
    
    // concat path
    {
        path p1(s1);
        path p2(s2);
        p1 += p2;
        TEST_CHECK(p1 == expect);
    }
    // concat string
    {
        path p1(s1);
        std::string p2(s2);
        p1 += p2;
        TEST_CHECK(p1 == expect);
    }
    // concat c string
    {
        path p1(s1);
        p1 += s2.c_str();
        TEST_CHECK(p1 == expect);
    }
#if 0
    // concat source type
    {
        path p1(s1);
        std::vector<char> p2(s2.begin(), s2.end());
        p1 += p2;
        TEST_CHECK(p1 == expect);
    }
#endif
    // concat char
    {
        path p1(s1);
        p1 += 'p';
        TEST_CHECK(p1 == path("p1/p"));
    }
    // concat wide char
    {
        path p(s1);
        p += L'p';
        TEST_CHECK(p == path("p1/p"));
    }
#if 0
    // concat source member type
    {
        path p1(s1);
        std::vector<char> p2(s2.begin(), s2.end());
        p1.concat(p2);
        TEST_CHECK(p1 == expect);
    }
    // concat iterator member type
    {
        path p1(s1);
        std::vector<char> p2(s2.begin(), s2.end());
        p1.concat(p2.begin(), p2.end());
        TEST_CHECK(p1 == expect);
    }
#endif
}

TEST_CASE(clear_test)
{
    path p1("non-empty");
    TEST_REQUIRE(not p1.empty());
    p1.clear();
    TEST_CHECK(p1.empty());
}

TEST_CASE(make_preferred_test)
{
    struct make_preferred_testcase
    {
        std::string raw;
        std::string expect;
    };
    
    const std::vector<make_preferred_testcase> testcases =
    {
        {"", ""}
      , {"hello_world", "hello_world"}
      , {"/", "/"}
      , {"/foo/bar/baz/", "/foo/bar/baz/"}
      , {"\\", "/"}
      , {"\\foo\\bar\\baz\\", "/foo/bar/baz/"}
      , {"\\foo/bar\\/baz\\", "/foo/bar//baz/"}
    };
    
    for (auto const & testcase : testcases) {
        path p(testcase.raw);
        p.make_preferred();
        TEST_CHECK(p == testcase.expect);
    }
}

TEST_CASE(remove_filename_test)
{
    struct remove_filename_testcase
    {
        std::string raw;
        std::string expect;
    };
    
    const std::vector<remove_filename_testcase> testcases =
    {
        {"", ""}
      , {"/", ""}
      , {"\\", ""}
      , {".", ""}
      , {"..", ""}
      , {"/foo", "/"}
      , {"/foo/", "/foo"}
      , {"/foo/.", "/foo"}
      , {"/foo/..", "/foo"}
      , {"/foo/////", "/foo"}
      , {"/foo\\\\", "/"}
      , {"/foo//\\/", "/foo//\\"}
      , {"file.txt", ""}
      , {"bar/../baz/./file.txt", "bar/../baz/."}
    };
    
    for (auto const & testcase :  testcases) {
        path p(testcase.raw);
        p.remove_filename();
        TEST_CHECK(p == testcase.expect);
        if (p != testcase.expect) {
            std::cout << "raw: " << testcase.raw << std::endl;
            std::cout << "expect: " << testcase.expect << std::endl;
            std::cout << "got: " << p << std::endl;
        }
    }
}

TEST_CASE(replace_filename_test)
{
    struct replace_filename_testcase
    {
        std::string raw;
        std::string expect;
        std::string filename;
    };
    
    const std::vector<replace_filename_testcase> testcases =
    {
        {"/foo", "/bar", "bar"}
      , {"/", "bar", "bar"}
      , {"\\", "bar", "bar"}
      , {"///", "bar", "bar"}
      , {"\\\\", "bar", "bar"}
      , {".", "bar", "bar"}
      , {"..", "bar", "bar"}
      , {"/foo\\baz/bong/", "/foo\\baz/bong/bar", "bar"}
      , {"/foo\\baz/bong", "/foo\\baz/bar", "bar"}
    };
    
    for (auto const & testcase : testcases) {
        path p(testcase.raw);
        p.replace_filename(testcase.filename);
        TEST_CHECK(p == testcase.expect);
    }
}

TEST_CASE(replace_extension_test)
{
    struct extension_testcase
    {
        std::string raw;
        std::string expect;
        std::string extension;
    };
    
    const std::vector<extension_testcase> testcases =
    {
        {"", "", ""}
      , {"", ".txt", "txt"}
      , {"", ".txt", ".txt"}
      , {"/foo", "/foo.txt", ".txt"}
      , {"/foo", "/foo.txt", "txt"}
      , {"/foo.cpp", "/foo.txt", ".txt"}
      , {"/foo.cpp", "/foo.txt", "txt"}
    };
    
    for (auto const & testcase : testcases) {
        path p(testcase.raw);
        p.replace_extension(testcase.extension);
        TEST_CHECK(p == testcase.expect);
    }
}

TEST_CASE(swap_test)
{
    path p1("hello");
    path p2("world");
    
    p1.swap(p2);
    TEST_CHECK(p1 == "world");
    TEST_CHECK(p2 == "hello");
    
    swap(p1, p2);
    TEST_CHECK(p1 == "hello");
    TEST_CHECK(p2 == "world");
}

TEST_CASE(to_string_converters_test)
{
    const std::string expect("/foo/bar/baz");
    const path p(expect);
    TEST_CHECK(p.native() == expect);
    TEST_CHECK(p.c_str() == expect);
    TEST_CHECK(static_cast<std::string>(p) == expect);
    TEST_CHECK(p.string() == expect);
}

TEST_CASE(compare_test)
{
    const std::string s1("/foo/./bar/baz");
    const std::string s2("/foo/bar/baz");
    const path p1(s1);
    const path p2(s2);
    
    TEST_CHECK(p1.compare(p2) < 0);
    TEST_CHECK(p1.compare(p1) == 0);
    TEST_CHECK(p2.compare(p1) > 0);
    
    TEST_CHECK(p1.compare(s2) < 0);
    TEST_CHECK(p1.compare(s1) == 0);
    TEST_CHECK(p2.compare(s1) > 0);
    
    TEST_CHECK(p1.compare(s2.c_str()) < 0);
    TEST_CHECK(p1.compare(s1.c_str()) == 0);
    TEST_CHECK(p2.compare(s1.c_str()) > 0);
    
    TEST_CHECK(p1 < p2);
    TEST_CHECK(p1 <= p2);
    TEST_CHECK(not (p1 > p2));
    TEST_CHECK(not (p1 >= p2));
    TEST_CHECK(not (p1 == p2));
    TEST_CHECK(p1 != p2);
    
    TEST_CHECK(not (p2 < p1));
    TEST_CHECK(not (p2 <= p1));
    TEST_CHECK(p2 > p1);
    TEST_CHECK(p2 >= p1);
    TEST_CHECK(not (p2 == p1));
    TEST_CHECK(p2 != p1);
    
    TEST_CHECK(p1 == p1);
    TEST_CHECK(not (p1 != p1));
    TEST_CHECK(not (p1 < p1));
    TEST_CHECK(p1 <= p1);
    TEST_CHECK(not (p1 > p1));
    TEST_CHECK(p1 >= p1);
}

TEST_CASE(hash_value_test)
{
    const path p1("/foo/./bar");
    const path p2("/foo/bar");
    
    auto const h1 = hash_value(p1);
    auto const h2 = hash_value(p2);

    TEST_CHECK(h1 != h2);
    TEST_CHECK(h1 == hash_value(p1));
    TEST_CHECK(h2 == hash_value(p2));
}

TEST_CASE(path_decomp_test)
{
    struct path_decomp_testcase
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
    /// http://www.boost.org/doc/libs/1_55_0/libs/filesystem/doc/
    /// reference.html#Path-decomposition-table
    const std::vector<path_decomp_testcase> testcases =
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
      , {"c:", {"c:"}, "", "", "", "c:", "", "c:"}
      , {"c:/", {"c:", "."}, "", "", "", "c:/", "c:", "."}
      , {"c:foo", {"c:foo"}, "", "", "", "c:foo", "", "c:foo"}
      , {"c:/foo", {"c:", "foo"}, "", "", "", "c:/foo", "c:", "foo"}
      , {"c:foo/", {"c:foo", "."}, "", "", "", "c:foo/", "c:foo", "."}
      , {"c:/foo/", {"c:", "foo", "."}, "", "", "", "c:/foo/",  "c:/foo", "."}
      , {"c:/foo/bar", {"c:", "foo", "bar"}, "", "", "", "c:/foo/bar", "c:/foo", "bar"}
      , {"prn:", {"prn:"}, "", "", "", "prn:", "", "prn:"}
      , {"c:\\", {"c:\\"}, "", "", "", "c:\\", "", "c:\\"}
      , {"c:\\foo", {"c:\\foo"}, "", "", "", "c:\\foo", "", "c:\\foo"}
      , {"c:foo\\", {"c:foo\\"}, "", "", "", "c:foo\\", "", "c:foo\\"}
      , {"c:\\foo\\", {"c:\\foo\\"}, "", "", "", "c:\\foo\\", "", "c:\\foo\\"}
      , {"c:\\foo/",  {"c:\\foo", "."}, "", "", "", "c:\\foo/", "c:\\foo", "."}
      , {"c:/foo\\bar", {"c:", "foo\\bar"}, "", "", "", "c:/foo\\bar", "c:", "foo\\bar"}
      
      , {"//", {"//"}, "//", "//", "", "", "", "//"}
    };
    
    for (auto const & testcase : testcases) {
        path p(testcase.raw);
        TEST_REQUIRE(p == testcase.raw);
        
        TEST_CHECK(p.root_path() == testcase.root_path);
        TEST_CHECK(p.has_root_path() == not testcase.root_path.empty());
        
        TEST_CHECK(p.root_name() == testcase.root_name);
        TEST_CHECK(p.has_root_name() == not testcase.root_name.empty());
        
        TEST_CHECK(p.root_directory() == testcase.root_directory);
        TEST_CHECK(p.has_root_directory() == not testcase.root_directory.empty());
        
        TEST_CHECK(p.relative_path() == testcase.relative_path);
        TEST_CHECK(p.has_relative_path() == not testcase.relative_path.empty());
        
        TEST_CHECK(p.parent_path() == testcase.parent_path);
        TEST_CHECK(p.has_parent_path() == not testcase.parent_path.empty());
        
        TEST_CHECK(p.filename() == testcase.filename);
        TEST_CHECK(p.has_filename() == not testcase.filename.empty());
        
        TEST_CHECK(p.is_absolute() == p.has_root_directory());
        TEST_CHECK(p.is_relative() == not p.is_absolute());
        
        TEST_CHECK_EQUAL_COLLECTIONS(
            p.begin(), p.end()
          , testcase.elements.begin(), testcase.elements.end()
          );
    }
}

TEST_CASE(filename_decomp_test)
{
    struct filename_decomp_testcase
    {
        std::string raw;
        std::string filename;
        std::string stem;
        std::string extension;
    };
    
    const std::vector<filename_decomp_testcase> testcases = 
    {
        {"", "", "", ""}
      , {".", ".", ".", ""}
      , {"..", "..", "..", ""}
      , {"/", "/", "/", ""}
      , {"foo", "foo", "foo", ""}
      , {"/foo/bar.txt", "bar.txt", "bar", ".txt"}
      , {"foo..txt", "foo..txt", "foo.", ".txt"}
    };
    
    for (auto const & testcase : testcases) {
        path p(testcase.raw);
        TEST_REQUIRE(p == testcase.raw);
        
        TEST_CHECK(p.filename() == testcase.filename);
        TEST_CHECK(p.has_filename() == not testcase.filename.empty());
        
        TEST_CHECK(p.stem() == testcase.stem);
        TEST_CHECK(p.has_stem() == not testcase.stem.empty());
        
        TEST_CHECK(p.extension() == testcase.extension);
        TEST_CHECK(p.has_extension() == not testcase.extension.empty());
    }
}

TEST_CASE(output_stream_test)
{
    const std::string s("/foo/bar/baz");
    const path p(s);
    
    std::stringstream ss;
    ss << p;
    TEST_REQUIRE(ss);
    TEST_CHECK(ss.str() == p.native());
}

TEST_CASE(input_stream_test)
{
    const std::string s("/foo/bar/baz");
    const path expect(s);
    path p;
    
    std::stringstream ss;
    ss << s;
    ss >> p;
    TEST_REQUIRE(ss);
    TEST_CHECK(p == expect);
}

TEST_SUITE_END()