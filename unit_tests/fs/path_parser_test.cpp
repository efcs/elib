#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <elib/fs/path.hpp>
#include <elib/fs/detail/path_parser.hpp>

#include <elib/debug/dprint.hpp>

#include <vector>


using namespace elib::fs;
using namespace elib::fs::path_parser;

path
join_vect(const std::vector<std::string>& v)
{
    std::string s;
    for (auto &p : v)
        s += p;
    return path{s};
}


BOOST_AUTO_TEST_SUITE(fs_path_parser_test_suite)

BOOST_AUTO_TEST_CASE(contains_pos_test)
{
    BOOST_CHECK(contains_pos(path{"foo"}, path_pos{0, 0}));
    BOOST_CHECK(contains_pos(path{"foo"}, path_pos{0, 2}));
    BOOST_CHECK(contains_pos(path{"foo"}, path_pos{1, 2}));
    BOOST_CHECK(contains_pos(path{"foo"}, path_pos{2, 2}));
    
    BOOST_CHECK(!contains_pos(path{"foo"}, path_pos{}));
    BOOST_CHECK(!contains_pos(path{"foo"}, path_pos{0, 3}));
    BOOST_CHECK(!contains_pos(path{"foo"}, path_pos{1, 0}));
    BOOST_CHECK(!contains_pos(path{"foo"}, path_pos{3, 3}));
}

BOOST_AUTO_TEST_CASE(substr_subpath_test)
{
    path p{"/foo"};
    
    BOOST_CHECK(subpath(path{}, path_pos(0, 0)) == "");
    BOOST_CHECK(subpath(p, path_pos{}) == "");
    BOOST_CHECK(subpath(p, path_pos{0, 0}) == "/");
    BOOST_CHECK(subpath(p, path_pos{0, 1}) == "/f");
    BOOST_CHECK(subpath(p, path_pos{0, 3}) == "/foo");
    BOOST_CHECK(subpath(p, path_pos{10, 10}) == "");
    BOOST_CHECK(subpath(p, path_pos{10, 0}) == "");
    BOOST_CHECK(subpath(p, path_pos{2, 0}) == "");
}

BOOST_AUTO_TEST_CASE(parse_name_test)
{
    path p{"/foo///bar/../"};
    
    BOOST_CHECK( parse_name(path{}, 0) == path_pos{});
    BOOST_CHECK( parse_name(p, 0) == path_pos{});
    BOOST_CHECK( parse_name(p, 1) == path_pos(1, 3));
    BOOST_CHECK( parse_name(p, 2) == path_pos(2, 3));
    BOOST_CHECK( parse_name(p, 3) == path_pos(3, 3));
    BOOST_CHECK( parse_name(p, 4) == path_pos{});
    BOOST_CHECK( parse_name(p, 6) == path_pos{});
    BOOST_CHECK( parse_name(p, 7) == path_pos(7, 9));
    BOOST_CHECK( parse_name(p, 11) == path_pos(11, 12));
    BOOST_CHECK( parse_name(p, 13) == path_pos{});
    BOOST_CHECK( parse_name(p, 14) == path_pos{});
    BOOST_CHECK( parse_name(p, 10000) == path_pos{});
    BOOST_CHECK( parse_name(p, path_pos::npos) == path_pos{});
} 


BOOST_AUTO_TEST_CASE(parse_separator_test)
{
    path p{"/foo///bar/../"};
    
    BOOST_CHECK( parse_separator(path{}, 0) == path_pos{});
    BOOST_CHECK( parse_separator(p, 0) == path_pos(0, 0));
    BOOST_CHECK( parse_separator(p, 1) == path_pos{});
    BOOST_CHECK( parse_separator(p, 3) == path_pos{});
    BOOST_CHECK( parse_separator(p, 4) == path_pos(4, 6));
    BOOST_CHECK( parse_separator(p, 7) == path_pos{});
    BOOST_CHECK( parse_separator(p, 10) == path_pos(10, 10));
    BOOST_CHECK( parse_separator(p, 12) == path_pos{});
    BOOST_CHECK( parse_separator(p, 13) == path_pos(13, 13));
    BOOST_CHECK( parse_separator(p, 14) == path_pos{});
    BOOST_CHECK( parse_separator(p, 10000) == path_pos{});
    BOOST_CHECK( parse_separator(p, path_pos::npos) == path_pos{});
}

BOOST_AUTO_TEST_CASE(parse_root_name_test)
{
    path p{""};
    BOOST_CHECK(( parse_root_name(p, 0) == path_pos{} ));
    BOOST_CHECK(( parse_root_name(p, path_pos::npos) == path_pos{} ));
    
    p = path{"//"};
    BOOST_CHECK(( parse_root_name(p, 0) == path_pos{0, 1} ));
    BOOST_CHECK(( parse_root_name(p, path_pos::npos) == path_pos{} ));
    
    p = path{"//net/not//root/"};
    
    BOOST_CHECK( parse_root_name(p, 0) == path_pos(0, 4));
    BOOST_CHECK( parse_root_name(p, 1) == path_pos{});
    BOOST_CHECK( parse_root_name(p, 2) == path_pos{});
    BOOST_CHECK( parse_root_name(p, 6) == path_pos{});
    BOOST_CHECK( parse_root_name(p, 9) == path_pos{}); // "//root"
    BOOST_CHECK( parse_root_name(p, 10) == path_pos{}); // "//root"
    BOOST_CHECK( parse_root_name(p, p.native().size()) == path_pos{});
    BOOST_CHECK( parse_root_name(p, 10000) == path_pos{}); // "//root"
    BOOST_CHECK( parse_root_name(p, path_pos::npos) == path_pos{});
    
    p = path{"/foo/bar"};
    BOOST_CHECK(( parse_root_name(p, 0) == path_pos{} ));
    BOOST_CHECK(( parse_root_name(p, 1) == path_pos{} ));
    BOOST_CHECK(( parse_root_name(p, 4) == path_pos{} ));
    BOOST_CHECK(( parse_root_name(p, 1000) == path_pos{} ));
    
    p = path{"foo//bar"};
    BOOST_CHECK(( parse_root_name(p, 0) == path_pos{} ));
    BOOST_CHECK(( parse_root_name(p, 3) == path_pos{} ));
    BOOST_CHECK(( parse_root_name(p, 4) == path_pos{} ));
    BOOST_CHECK(( parse_root_name(p, 5) == path_pos{} ));
}

BOOST_AUTO_TEST_CASE(parse_root_separator_test)
{
    path p{""};
    
    BOOST_CHECK((parse_root_separator(p, 0) == path_pos{}));
    BOOST_CHECK((parse_root_separator(p, 1) == path_pos{}));
    BOOST_CHECK((parse_root_separator(p, 100) == path_pos{}));
    BOOST_CHECK((parse_root_separator(p, path_pos::npos) == path_pos{}));
    
    p = path{"/"};
    BOOST_CHECK(( parse_root_separator(p, 0) == path_pos{0, 0} ));
    BOOST_CHECK(( parse_root_separator(p, 1) == path_pos{} ));
    
    p = path{"//"};
    BOOST_CHECK(( parse_root_separator(p, 0) == path_pos{} ));
    BOOST_CHECK(( parse_root_separator(p, path_pos::npos) == path_pos{} ));
    
    p = path{"/foo/"};
    BOOST_CHECK((parse_root_separator(p, 0) == path_pos{0, 0}));
    BOOST_CHECK((parse_root_separator(p, 1) == path_pos{}));
    BOOST_CHECK((parse_root_separator(p, 4) == path_pos{}));
    BOOST_CHECK((parse_root_separator(p, 5) == path_pos{}));
    BOOST_CHECK((parse_root_separator(p, path_pos::npos) == path_pos{}));
    
    p = path{"//foo/"};
    BOOST_CHECK(( parse_root_separator(p, 0) == path_pos{} ));
    BOOST_CHECK(( parse_root_separator(p, 1) == path_pos{} ));
    BOOST_CHECK(( parse_root_separator(p, 2) == path_pos{} ));
    BOOST_CHECK(( parse_root_separator(p, 5) == path_pos{5, 5} ));
    BOOST_CHECK(( parse_root_separator(p, 6) == path_pos{} ));
    
    p = path{"//foo///"};
    BOOST_CHECK(( parse_root_separator(p, 0) == path_pos{} ));
    BOOST_CHECK(( parse_root_separator(p, 5) == path_pos{5, 7} ));
    BOOST_CHECK(( parse_root_separator(p, 8) == path_pos{} ));
    
    p = path{"///foo///bar"};
    BOOST_CHECK((parse_root_separator(p, 0) == path_pos{0, 2}));
    BOOST_CHECK((parse_root_separator(p, 3) == path_pos{}));
    BOOST_CHECK((parse_root_separator(p, 6) == path_pos{}));
    BOOST_CHECK((parse_root_separator(p, 7) == path_pos{}));
    BOOST_CHECK((parse_root_separator(p, 8) == path_pos{}));
    BOOST_CHECK((parse_root_separator(p, 9) == path_pos{}));
    BOOST_CHECK((parse_root_separator(p, 12) == path_pos{}));
    BOOST_CHECK((parse_root_separator(p, path_pos::npos) == path_pos{}));
}

BOOST_AUTO_TEST_CASE(index_of_next_test)
{
    BOOST_CHECK( index_of_next(path{"/foo/bar"}, path_pos{}) == path_pos::npos);
    BOOST_CHECK( index_of_next(path{}, path_pos{0, 0}) == path_pos::npos);
    BOOST_CHECK( index_of_next(path{"/"}, path_pos{0, 0}) == path_pos::npos);
    BOOST_CHECK( index_of_next(path{"/foo"}, path_pos{0, 0}) == 1);
    BOOST_CHECK( index_of_next(path{"/foo"}, path_pos{1, 3}) == path_pos::npos);
    
    path p{};
    path_pos pp{};
    
    std::vector<std::string> parts =
        { "/", "foo", "///", "bar", "/" };
        
    p = join_vect(parts);
    pp = path_pos{0, 0};
    
    for (std::size_t i=0; i < parts.size(); ++i) {
        DPRINT(pp.begin);
        DPRINT(pp.end);
        auto ppos = parse(p, pp.begin);
        DPRINT(ppos.begin);
        DPRINT(ppos.end);
        
        BOOST_CHECK(pp == ppos);
        
        pp.begin = index_of_next(p, ppos);
        
        if (pp.begin == path_pos::npos)
            pp.end = pp.begin;
        else if (i + 1 != parts.size()) 
            pp.end = pp.begin + parts[i+1].size() - 1;
        
    }
    
    BOOST_CHECK(pp == path_pos{});
}

BOOST_AUTO_TEST_CASE(index_of_prev_test)
{
    
}

BOOST_AUTO_TEST_SUITE_END()
