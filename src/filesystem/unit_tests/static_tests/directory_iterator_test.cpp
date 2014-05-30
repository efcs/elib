#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <elib/filesystem.hpp>
#include <system_error>
#include "../static_test_helper.hpp"
#include <vector>
using namespace elib::fs;


BOOST_AUTO_TEST_SUITE(elib_filesystem_static_directory_iterator_test_suite)

BOOST_AUTO_TEST_CASE(dne_test)
{
    path const dir = make_static_env_path("dne");
    directory_iterator const end_it;
    {
        std::error_code ec;
        directory_iterator it(dir, ec);
        BOOST_REQUIRE(ec);
        BOOST_CHECK(it == end_it);
    }{
        directory_iterator it;
        BOOST_CHECK_THROW(it = directory_iterator(dir), filesystem_error);
    }
}

BOOST_AUTO_TEST_CASE(deref_test)
{
    directory_entry expected(make_static_env_path("empty_file"));
    path const dir = make_static_env_path("");
    directory_iterator it(dir);
    
    BOOST_REQUIRE(*it == expected);
    BOOST_REQUIRE(it->path() == expected.path());
}

BOOST_AUTO_TEST_CASE(increment_test)
{
    directory_entry const expected_first(make_static_env_path("empty_file"));
    directory_entry const expected_second(make_static_env_path("dir1"));
    directory_entry const expected_third(make_static_env_path("non_empty_file"));
    path const dir = make_static_env_path("");
    
    directory_iterator const end_it;
    
    {
        directory_iterator it(dir);
        BOOST_REQUIRE(it != end_it);
        BOOST_REQUIRE(*it == expected_first);
        ++it;
        BOOST_REQUIRE(it != end_it);
        BOOST_REQUIRE(*it == expected_second);
        ++it;
        BOOST_REQUIRE(it != end_it);
        BOOST_REQUIRE(*it == expected_third);
        ++it;
        BOOST_REQUIRE(it == end_it);
    }{
        std::error_code ec;
        directory_iterator it(dir);
        BOOST_REQUIRE(it != end_it);
        BOOST_REQUIRE(*it == expected_first);
        it.increment(ec);
        BOOST_REQUIRE(not ec);
        BOOST_REQUIRE(it != end_it);
        BOOST_REQUIRE(*it == expected_second);
        it.increment(ec);
        BOOST_REQUIRE(not ec);
        BOOST_REQUIRE(it != end_it);
        BOOST_REQUIRE(*it == expected_third);
        it.increment(ec);
        BOOST_REQUIRE(not ec);
        BOOST_REQUIRE(it == end_it);
    }{
        directory_iterator it(dir);
        directory_iterator it_cp;
        BOOST_REQUIRE(it != end_it);
        BOOST_REQUIRE(*it == expected_first);
        it_cp = it++;
        BOOST_REQUIRE(it_cp != end_it);
        BOOST_REQUIRE(*it_cp == expected_first);
        BOOST_REQUIRE(it != end_it);
        BOOST_REQUIRE(*it == expected_second);
        it_cp = it++;
        BOOST_REQUIRE(it_cp != end_it);
        BOOST_REQUIRE(*it_cp == expected_second);
        BOOST_REQUIRE(it != end_it);
        BOOST_REQUIRE(*it == expected_third);
        it_cp = it++;
        BOOST_REQUIRE(it_cp != end_it);
        BOOST_REQUIRE(*it_cp == expected_third);
        BOOST_REQUIRE(it == end_it);
    }
}

BOOST_AUTO_TEST_CASE(iterate_test)
{
    const std::vector<directory_entry> expected =
    {
        directory_entry(make_static_env_path("empty_file"))
      , directory_entry(make_static_env_path("dir1"))
      , directory_entry(make_static_env_path("non_empty_file"))
    };
    path const dir = make_static_env_path("");
    directory_iterator it(dir);
    directory_iterator const end_it;
    
    BOOST_CHECK_EQUAL_COLLECTIONS(
        it, end_it
      , expected.begin(), expected.end()
      );
}


BOOST_AUTO_TEST_SUITE_END()