#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>


#include "elib/detail/_path_helper.h"
#include "elib/elog.h"


using namespace elib;
using namespace elib::detail;


using pp = path_part;
using pp_e = path_part_e;
using ph = path_helper;


#define CHECK(begin, raw, end, enum, canon) \
do { \
    std::string __str(begin); \
    path_part __p{static_cast<unsigned>(__str.size()), enum, raw, canon}; \
    __str += raw; \
    __str += end; \
    BOOST_CHECK(check(__p, __str)); \
} while (false)
    

#define CHECKP(begin, raw, end, enum, canon) \
do { \
    std::string __str(begin); \
    path_part __p{static_cast<unsigned>(__str.size()), enum, raw, canon}; \
    __str += raw; \
    __str += end; \
    BOOST_CHECK(checkp(__p, __str)); \
} while (false)
   
   
#define EVAL_BEGIN() \
    { \
        bool __ret = true;
    
        
#define EVAL_END() \
        return __ret; \
    }
    
    
#define EVALP(p) \
do { \
    if (! (p)) { \
        elog::raw_out("FAILED: " #p); \
        __ret = false; \
    } \
} while (false)


#define EVALS(p) \
do { \
    if (! (p)) { \
        __ret = false; \
    } \
} while(false)


#define EVAL(p) EVALP(p)


inline bool
check_next(const pp & curr, const pp & next, const std::string & s)
{
    auto other = ph::next(s, curr);
    auto other_pos = ph::index_of_next(s, curr.pos);
    EVAL_BEGIN()
    EVAL(next.pos == other.pos);
    EVAL(next.pos == other_pos);
    EVAL(next.type == other.type);
    EVAL(next.raw_part == other.raw_part);
    EVAL(next.canon_part == other.canon_part);
    EVAL_END();
}

inline bool
check_prev(const pp & curr, const pp & prev, const std::string & s)
{
    auto other = ph::prev(s, curr);
    auto other_pos = ph::index_of_prev(s, curr.pos);
    EVAL_BEGIN()
    EVAL(prev.pos == other.pos);
    //elog::raw_out("%u != %u", prev.pos, other.pos);
    EVAL(prev.pos == other_pos);
    //elog::raw_out("%u != %u", prev.pos, other_pos);
    EVAL(prev.type == other.type);
    EVAL(prev.raw_part == other.raw_part);
    //elog::raw_out("%s != %s", prev.raw_part.c_str(), other.raw_part.c_str());
    EVAL(prev.canon_part == other.canon_part);
    //elog::raw_out("%s != %s", prev.canon_part.c_str(), other.canon_part.c_str());
    EVAL_END();
}

inline bool
check(const pp & p, const std::string & s)
{
    
    auto other = ph::part(s, p.pos);
    EVAL_BEGIN()
    EVAL(p.pos == other.pos);
    EVAL(p.type == other.type);
    EVAL(p.raw_part == other.raw_part);
    EVAL(p.canon_part == other.canon_part);
    EVAL_END()
}



BOOST_AUTO_TEST_SUITE(path_helper_test_suite)

BOOST_AUTO_TEST_CASE(test_is_path_delim)
{
    BOOST_CHECK(is_path_delim("/"));
    BOOST_CHECK(is_path_delim("//"));
    BOOST_CHECK(is_path_delim("///"));
    BOOST_CHECK(is_path_delim("////"));
    
    BOOST_CHECK(! is_path_delim(""));
    BOOST_CHECK(! is_path_delim("\\"));
    BOOST_CHECK(! is_path_delim(" /"));
    BOOST_CHECK(! is_path_delim(" "));
}

BOOST_AUTO_TEST_CASE(test_is_path_name)
{
    BOOST_CHECK(is_path_name("foo"));
    BOOST_CHECK(is_path_name("\\"));
    BOOST_CHECK(is_path_name(" "));
    BOOST_CHECK(is_path_name(" .. "));
    
    BOOST_CHECK(! is_path_name(""));
    BOOST_CHECK(! is_path_name("/"));
    BOOST_CHECK(! is_path_name("//foo"));
    BOOST_CHECK(! is_path_name("."));
    BOOST_CHECK(! is_path_name(".."));
}


BOOST_AUTO_TEST_CASE(test_is_path_root_name)
{
    BOOST_CHECK(is_path_root_name("//"));
    BOOST_CHECK(is_path_root_name("//foo"));
    BOOST_CHECK(is_path_root_name("//a"));
    
    BOOST_CHECK(! is_path_root_name(""));
    BOOST_CHECK(! is_path_root_name(" "));
    BOOST_CHECK(! is_path_root_name("/"));
    BOOST_CHECK(! is_path_root_name("/ /"));
    BOOST_CHECK(! is_path_root_name("///foo"));
    BOOST_CHECK(! is_path_root_name("."));
    BOOST_CHECK(! is_path_root_name(".."));
}


////////////////////////////////////////////////////////////////////////////////
//                                                                        
////////////////////////////////////////////////////////////////////////////////


BOOST_AUTO_TEST_CASE(path_helper_root_delim)
{   
    CHECK("", "/", "", pp_e::root_delim, "/");
    CHECK("", "///", "",  pp_e::root_delim, "/");
    CHECK("", "////", "",  pp_e::root_delim, "/");
}

BOOST_AUTO_TEST_CASE(test_root_name)
{
    CHECK("", "//", "", pp_e::root_name, "//");
    CHECK("", "//name", "/foo", pp_e::root_name, "//name");
    CHECK("", "//..", "/foo///bar//hello", pp_e::root_name, "//..");
}

BOOST_AUTO_TEST_CASE(test_other_first)
{
    CHECK("", "hello", "//world", pp_e::name, "hello");
    CHECK("", ".", "", pp_e::dot, ".");
    CHECK("", "..", "/..", pp_e::double_dot, "..");
    CHECK("", " hell o ..", "/////", pp_e::name, " hell o ..");
}

BOOST_AUTO_TEST_CASE(test_root_delim_with_root_name)
{
    CHECK("//name", "/", "foo", pp_e::root_delim, "/");
    CHECK("//..", "///", "foo", pp_e::root_delim, "/");
    CHECK("//a", "//", ".", pp_e::root_delim, "/");
    CHECK("//.", "/", "", pp_e::root_delim, "/");
}

BOOST_AUTO_TEST_CASE(test_trailing_delim)
{
    CHECK("foo/bar", "/", "", pp_e::trailing_delim, ".");
    CHECK("..", "/////", "", pp_e::trailing_delim, ".");
    CHECK("/foo/..", "/", "", pp_e::trailing_delim, ".");
}

BOOST_AUTO_TEST_CASE(test_regular_delim)
{
    CHECK("//name/foo", "/", "bar", pp_e::delim, "/");
    CHECK("/hello", "/", "bar", pp_e::delim, "/");
    CHECK("foo", "/////", "bar", pp_e::delim, "/");
    CHECK("/..", "//", "..", pp_e::delim, "/");
}

BOOST_AUTO_TEST_CASE(test_dot)
{
    CHECK("foo/", ".", "/bar", pp_e::dot, ".");
    CHECK("", ".", "", pp_e::dot, ".");
    CHECK("/", ".", "", pp_e::dot, ".");
    CHECK("foo/bar/", ".", "/baz", pp_e::dot, ".");
}

BOOST_AUTO_TEST_CASE(test_double_dot)
{
    CHECK("", "..", "", pp_e::double_dot, "..");
    CHECK("/", "..", "/bar", pp_e::double_dot, "..");
    CHECK("//bar/", "..", "", pp_e::double_dot, "..");
}


////////////////////////////////////////////////////////////////////////////////
//                                                                          
////////////////////////////////////////////////////////////////////////////////


#define CHECK_NEXT(begin, curr, next, end, enum, canon) \
do { \
    std::string __str(begin); \
    path_part __curr{static_cast<unsigned>(__str.size()), enum, curr, ""}; \
    __str += curr; \
    path_part __next{static_cast<unsigned>(__str.size()), enum, next, canon}; \
    __str += next; \
    __str += end; \
    BOOST_CHECK(check_next(__curr, __next, __str)); \
} while (false)


BOOST_AUTO_TEST_CASE(test_next)
{
    CHECK_NEXT("", ".", "//", "foo", pp_e::delim, "/");
}


#define CHECK_PREV(begin, prev, curr, end, enum, canon) \
do { \
    std::string __str(begin); \
    path_part __prev{static_cast<unsigned>(__str.size()), enum, prev, canon}; \
    __str += prev; \
    path_part __curr{static_cast<unsigned>(__str.size()), enum, curr, ""}; \
    __str += curr; \
    __str += end; \
    BOOST_CHECK(check_prev(__curr, __prev, __str)); \
} while (false)


BOOST_AUTO_TEST_CASE(test_prev)
{
    CHECK_PREV("", "//name", "/", "foo", pp_e::root_name, "//name");
}

BOOST_AUTO_TEST_CASE(test_index_of_last)
{
    BOOST_CHECK(ph::index_of_last("") == static_cast<unsigned>(-1));
    BOOST_CHECK(ph::index_of_last("//") == 0);
    BOOST_CHECK(ph::index_of_last("//name") == 0);
    BOOST_CHECK(ph::index_of_last("//name/") == 6);
    BOOST_CHECK(ph::index_of_last("ba/") == 2);
    BOOST_CHECK(ph::index_of_last("foo/bar") == 4);
    BOOST_CHECK(ph::index_of_last("/") == 0);
    BOOST_CHECK(ph::index_of_last("foo") == 0);
    BOOST_CHECK(ph::index_of_last(".") == 0);
    BOOST_CHECK(ph::index_of_last("..") == 0);
}





BOOST_AUTO_TEST_SUITE_END()
