// REQUIRES: ELIB_FILESYSTEM_SOURCE, ELIB_BOOST_TEST
#define BOOST_TEST_MODULE Main
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <elib/filesystem.hpp>
#include <system_error>
#include "../static_test_helper.hpp"
#include <vector>
#include <set>
using namespace elib::fs;

#define _(File) directory_entry(make_static_env_path(File))
const std::set<directory_entry> file_list = 
{
    _("dir1")
  , _("empty_file")
  , _("non_empty_file")
};
#undef _

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
    
    BOOST_REQUIRE(it != directory_iterator{});
    BOOST_CHECK(file_list.count(*it));
}

BOOST_AUTO_TEST_CASE(increment_test)
{
    path const dir = make_static_env_path("");
    
    directory_iterator const end_it;
    
    {
        directory_iterator it(dir);
        BOOST_REQUIRE(it != end_it);
        BOOST_CHECK(file_list.count(*it));
        ++it;
        BOOST_REQUIRE(it != end_it);
        BOOST_CHECK(file_list.count(*it));
        ++it;
        BOOST_REQUIRE(it != end_it);
        BOOST_CHECK(file_list.count(*it));
        ++it;
        BOOST_REQUIRE(it == end_it);
    }{
        std::error_code ec;
        directory_iterator it(dir);
        BOOST_REQUIRE(it != end_it);
        BOOST_CHECK(file_list.count(*it));
        it.increment(ec);
        BOOST_REQUIRE(not ec);
        BOOST_REQUIRE(it != end_it);
        BOOST_CHECK(file_list.count(*it));
        it.increment(ec);
        BOOST_REQUIRE(not ec);
        BOOST_REQUIRE(it != end_it);
        BOOST_CHECK(file_list.count(*it));
        it.increment(ec);
        BOOST_REQUIRE(not ec);
        BOOST_REQUIRE(it == end_it);
    }{
        directory_iterator it(dir);
        directory_iterator it_cp;
        directory_entry old;
        BOOST_REQUIRE(it != end_it);
        BOOST_CHECK(file_list.count(*it));
        old = *it;
        it_cp = it++;
        BOOST_REQUIRE(it_cp != end_it);
        BOOST_CHECK(*it_cp == old);
        BOOST_REQUIRE(it != end_it);
        BOOST_CHECK(file_list.count(*it));
        old = *it;
        it_cp = it++;
        BOOST_REQUIRE(it_cp != end_it);
        BOOST_CHECK(*it_cp == old);
        BOOST_REQUIRE(it != end_it);
        BOOST_CHECK(file_list.count(*it));
        old  = *it;
        it_cp = it++;
        BOOST_REQUIRE(it_cp != end_it);
        BOOST_CHECK(*it_cp == old);
        BOOST_REQUIRE(it == end_it);
    }
}


BOOST_AUTO_TEST_CASE(cmp_test)
{
    path const dir = make_static_env_path("");
    directory_iterator it(dir);
    directory_iterator const end_it;
    
    BOOST_REQUIRE(it != end_it);
    BOOST_REQUIRE(not (it == end_it));
    BOOST_REQUIRE(it == it);
}

BOOST_AUTO_TEST_SUITE_END()