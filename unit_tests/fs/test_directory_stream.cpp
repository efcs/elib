#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <elib/fs/path.hpp>
#include <elib/fs/detail/directory_stream.hpp>

#include <vector>
#include <string>
#include <iostream>

using namespace elib::fs;
using namespace elib::fs::detail;


#define PRINTL(x) std::cout << (x) << std::endl


BOOST_AUTO_TEST_SUITE(fs_directory_stream_test_suite)

BOOST_AUTO_TEST_CASE(fs_directory_stream_init)
{
    path p("/home/eric/tmp");
    path p2("Hello");
    
    directory_stream s;
    s.open(p);
    
    std::vector<path> ent_list;
    
    BOOST_REQUIRE(s.is_open());
    BOOST_CHECK(s.good());
    
    while (s.good()) {
        auto&& ret = s.advance();
        if (!ret.empty()) {
            ent_list.push_back(ret);
        } else {
            BOOST_CHECK(s.eof());
        }
    }
    
    BOOST_CHECK(s.is_open());
    BOOST_CHECK(s.eof());
    BOOST_CHECK(!s.fail());
    BOOST_CHECK(!s.bad());
    
    
    s.advance();
    BOOST_CHECK(s.eof());
    BOOST_CHECK(s.fail());
    BOOST_CHECK(!s.bad());
    
    
    s.rewind();
    BOOST_CHECK(s.good());
    

    unsigned count = 0;
    while (s.good()) {
        auto ret = s.advance();
        if (!ret.empty()) {
            BOOST_CHECK(ret == ent_list[count]);
        }
        count++;
    }
    --count;
    
    BOOST_CHECK(count == ent_list.size());
    
    
    BOOST_CHECK(s.is_open());
    BOOST_CHECK(!s.fail());
    BOOST_CHECK(!s.bad());
    
    s.close();
    BOOST_CHECK(!s.is_open());
    BOOST_CHECK(s.good());
    
    s.close();
    BOOST_CHECK(!s.good());
}

BOOST_AUTO_TEST_SUITE_END()