// REQUIRES: ELIB_FILESYSTEM_SOURCE
#include <elib/filesystem.hpp>
#include <system_error>
#include <vector>
#include <set>
#include "../static_test_helper.hpp"
#include "rapid-cxx-test.hpp"
using namespace elib::fs;

#if defined(__clang__)
# pragma clang diagnostic ignored "-Wglobal-constructors"
# pragma clang diagnostic ignored "-Wexit-time-destructors"
#endif

#define _(File) directory_entry(make_static_env_path(File))
const std::set<directory_entry> file_list = 
{
    _("dir1")
  , _("empty_file")
  , _("non_empty_file")
};
#undef _

TEST_SUITE(elib_filesystem_static_directory_iterator_test_suite)

TEST_CASE(dne_test)
{
    path const dir = make_static_env_path("dne");
    directory_iterator const end_it;
    {
        std::error_code ec;
        directory_iterator it(dir, ec);
        TEST_REQUIRE(ec);
        TEST_CHECK(it == end_it);
    }{
        directory_iterator it;
        TEST_CHECK_THROW(filesystem_error, it = directory_iterator(dir));
    }
}

TEST_CASE(deref_test)
{
    directory_entry expected(make_static_env_path("empty_file"));
    path const dir = make_static_env_path("");
    directory_iterator it(dir);
    
    TEST_REQUIRE(it != directory_iterator{});
    TEST_CHECK(file_list.count(*it));
}

TEST_CASE(increment_test)
{
    path const dir = make_static_env_path("");
    
    directory_iterator const end_it;
    
    {
        directory_iterator it(dir);
        TEST_REQUIRE(it != end_it);
        TEST_CHECK(file_list.count(*it));
        ++it;
        TEST_REQUIRE(it != end_it);
        TEST_CHECK(file_list.count(*it));
        ++it;
        TEST_REQUIRE(it != end_it);
        TEST_CHECK(file_list.count(*it));
        ++it;
        TEST_REQUIRE(it == end_it);
    }{
        std::error_code ec;
        directory_iterator it(dir);
        TEST_REQUIRE(it != end_it);
        TEST_CHECK(file_list.count(*it));
        it.increment(ec);
        TEST_REQUIRE(not ec);
        TEST_REQUIRE(it != end_it);
        TEST_CHECK(file_list.count(*it));
        it.increment(ec);
        TEST_REQUIRE(not ec);
        TEST_REQUIRE(it != end_it);
        TEST_CHECK(file_list.count(*it));
        it.increment(ec);
        TEST_REQUIRE(not ec);
        TEST_REQUIRE(it == end_it);
    }{
        directory_iterator it(dir);
        directory_iterator it_cp;
        directory_entry old;
        TEST_REQUIRE(it != end_it);
        TEST_CHECK(file_list.count(*it));
        old = *it;
        it_cp = it++;
        TEST_REQUIRE(it_cp != end_it);
        TEST_CHECK(*it_cp == old);
        TEST_REQUIRE(it != end_it);
        TEST_CHECK(file_list.count(*it));
        old = *it;
        it_cp = it++;
        TEST_REQUIRE(it_cp != end_it);
        TEST_CHECK(*it_cp == old);
        TEST_REQUIRE(it != end_it);
        TEST_CHECK(file_list.count(*it));
        old  = *it;
        it_cp = it++;
        TEST_REQUIRE(it_cp != end_it);
        TEST_CHECK(*it_cp == old);
        TEST_REQUIRE(it == end_it);
    }
}


TEST_CASE(cmp_test)
{
    path const dir = make_static_env_path("");
    directory_iterator it(dir);
    directory_iterator const end_it;
    
    TEST_REQUIRE(it != end_it);
    TEST_REQUIRE(not (it == end_it));
    TEST_REQUIRE(it == it);
}

TEST_SUITE_END()