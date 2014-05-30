#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <elib/filesystem.hpp>
#include <system_error>
#include "../static_test_helper.hpp"
#include <vector>
#include <cstddef>
using namespace elib::fs;


BOOST_AUTO_TEST_SUITE(elib_filesystem_static_recursive_directory_iterator_test_suite)

BOOST_AUTO_TEST_CASE(dne_test)
{
    path const dir = make_static_env_path("dne");
    recursive_directory_iterator const end_it;
    {
        std::error_code ec;
        recursive_directory_iterator it(dir, ec);
        BOOST_REQUIRE(ec);
        BOOST_CHECK(it == end_it);
    }{
        recursive_directory_iterator it;
        BOOST_CHECK_THROW(it = recursive_directory_iterator(dir), filesystem_error);
    }
}


#define _(File) directory_entry(make_static_env_path(File))
BOOST_AUTO_TEST_CASE(simple_iterate_test)
{
    const std::vector<directory_entry> expected =
    {
        _("empty_file")
      , _("dir1")
      , _("dir1/file1")
      , _("dir1/dir2")
      , _("dir1/dir2/dir3")
      , _("dir1/dir2/dir3/.git_keep")
      , _("dir1/file2")
      , _("non_empty_file")
    };
    
    recursive_directory_iterator it(static_test_env_path);
    recursive_directory_iterator const end_it;
    
    BOOST_CHECK_EQUAL_COLLECTIONS(
        it, end_it
      , expected.begin(), expected.end()
      );
}

BOOST_AUTO_TEST_CASE(disable_recursion_pending_test)
{
    const std::vector<directory_entry> expected =
    {
        _("empty_file")
      , _("dir1")
      , _("non_empty_file")
    };
    
    recursive_directory_iterator it(static_test_env_path);
    recursive_directory_iterator const end_it;
    
    std::size_t index = 0;
    for (; it != end_it; ++it) {
        BOOST_REQUIRE(index < expected.size());
        BOOST_REQUIRE(*it == expected[index]);
        ++index;
        it.disable_recursion_pending();
    }
}

BOOST_AUTO_TEST_CASE(walk_dir_test)
{
    const std::vector<directory_entry> expected =
    {
        _("empty_file")
      , _("dir1")
      , _("dir1/file1")
      , _("dir1/dir2")
      , _("dir1/dir2/dir3")
      , _("dir1/dir2/dir3/.git_keep")
      , _("dir1/file2")
      , _("non_empty_file")
    };
    
    recursive_directory_iterator const end_it;
    
    {
        recursive_directory_iterator it(make_static_env_path(""));
        BOOST_REQUIRE(it != end_it);
        BOOST_REQUIRE(*it == expected[0]);
        BOOST_CHECK(it.depth() == 0);
        ++it;
        BOOST_REQUIRE(it != end_it);
        BOOST_REQUIRE(*it == expected[1]);
        BOOST_CHECK(it.depth() == 0);
        ++it;
        BOOST_REQUIRE(it != end_it);
        BOOST_REQUIRE(*it == expected[2]);
        BOOST_CHECK(it.depth() == 1);
        ++it;
        BOOST_REQUIRE(it != end_it);
        BOOST_REQUIRE(*it == expected[3]);
        BOOST_CHECK(it.depth() == 1);
        ++it;
        BOOST_REQUIRE(it != end_it);
        BOOST_REQUIRE(*it == expected[4]);
        ++it;
        BOOST_REQUIRE(it != end_it);
        BOOST_REQUIRE(*it == expected[5]);
        ++it;
        BOOST_REQUIRE(it != end_it);
        BOOST_REQUIRE(*it == expected[6]);
        ++it;
        BOOST_REQUIRE(it != end_it);
        BOOST_REQUIRE(*it == expected[7]);
        ++it;
        BOOST_REQUIRE(it == end_it);
    }{ 
        std::error_code ec;
        recursive_directory_iterator it(make_static_env_path(""));
        BOOST_REQUIRE(it != end_it);
        BOOST_REQUIRE(*it == expected[0]);
        BOOST_CHECK(it.depth() == 0);
        
        it.increment(ec);
        BOOST_REQUIRE(not ec);
        BOOST_REQUIRE(it != end_it);
        BOOST_REQUIRE(*it == expected[1]);
        BOOST_CHECK(it.depth() == 0);
        
        it.increment(ec);
        BOOST_REQUIRE(not ec);
        BOOST_REQUIRE(it != end_it);
        BOOST_REQUIRE(*it == expected[2]);
        BOOST_CHECK(it.depth() == 1);
        
        it.increment(ec);
        BOOST_REQUIRE(not ec);
        BOOST_REQUIRE(it != end_it);
        BOOST_REQUIRE(*it == expected[3]);
        BOOST_CHECK(it.depth() == 1);
        
        it.increment(ec);
        BOOST_REQUIRE(not ec);
        BOOST_REQUIRE(it != end_it);
        BOOST_REQUIRE(*it == expected[4]);
        BOOST_CHECK(it.depth() == 2);
        
        it.increment(ec);
        BOOST_REQUIRE(not ec);
        BOOST_REQUIRE(it != end_it);
        BOOST_REQUIRE(*it == expected[5]);
        BOOST_CHECK(it.depth() == 3);
        
        it.increment(ec);
        BOOST_REQUIRE(not ec);
        BOOST_REQUIRE(it != end_it);
        BOOST_REQUIRE(*it == expected[6]);
        BOOST_CHECK(it.depth() == 1);
        
        it.increment(ec);
        BOOST_REQUIRE(not ec);
        BOOST_REQUIRE(it != end_it);
        BOOST_REQUIRE(*it == expected[7]);
        BOOST_CHECK(it.depth() == 0);
        
        it.increment(ec);
        BOOST_REQUIRE(not ec);
        BOOST_REQUIRE(it == end_it);
    }{ 
        recursive_directory_iterator it(make_static_env_path(""));
        decltype(it++) it_cp;
        BOOST_REQUIRE(it != end_it);
        BOOST_REQUIRE(*it == expected[0]);
        BOOST_CHECK(it.depth() == 0);
        it_cp = it++;
        
        BOOST_REQUIRE(*it_cp == expected[0]);
        BOOST_REQUIRE(it != end_it);
        BOOST_REQUIRE(*it == expected[1]);
        BOOST_CHECK(it.depth() == 0);
        it_cp = it++;
        BOOST_REQUIRE(*it_cp == expected[1]);
        BOOST_REQUIRE(it != end_it);
        BOOST_REQUIRE(*it == expected[2]);
        BOOST_CHECK(it.depth() == 1);
        it_cp = it++;
        BOOST_REQUIRE(*it_cp == expected[2]);
        BOOST_REQUIRE(it != end_it);
        BOOST_REQUIRE(*it == expected[3]);
        BOOST_CHECK(it.depth() == 1);
        it_cp = it++;
        BOOST_REQUIRE(*it_cp == expected[3]);
        BOOST_REQUIRE(it != end_it);
        BOOST_REQUIRE(*it == expected[4]);
        BOOST_CHECK(it.depth() == 2);
        it_cp = it++;
        BOOST_REQUIRE(*it_cp == expected[4]);
        BOOST_REQUIRE(it != end_it);
        BOOST_REQUIRE(*it == expected[5]);
        BOOST_CHECK(it.depth() == 3);
        it_cp = it++;
        BOOST_REQUIRE(*it_cp == expected[5]);
        BOOST_REQUIRE(it != end_it);
        BOOST_REQUIRE(*it == expected[6]);
        BOOST_CHECK(it.depth() == 1);
        it_cp = it++;
        BOOST_REQUIRE(*it_cp == expected[6]);
        BOOST_REQUIRE(it != end_it);
        BOOST_REQUIRE(*it == expected[7]);
        BOOST_CHECK(it.depth() == 0);
        it_cp = it++;
        BOOST_REQUIRE(*it_cp == expected[7]);
        BOOST_REQUIRE(it == end_it);
    }
}

BOOST_AUTO_TEST_CASE(pop_test)
{
    const std::vector<directory_entry> expected =
    {
        _("empty_file")
      , _("dir1")
      , _("dir1/file1")
      , _("non_empty_file")
    };
    
    recursive_directory_iterator const end_it;
    recursive_directory_iterator it(make_static_env_path(""));
    
    
    BOOST_REQUIRE(*it == expected[0]);
    ++it;
    BOOST_REQUIRE(it != end_it);
    BOOST_REQUIRE(*it == expected[1]);
    ++it;
    BOOST_REQUIRE(it != end_it);
    BOOST_REQUIRE(*it == expected[2]);
    BOOST_CHECK(it.depth() == 1);
    it.pop();
    BOOST_REQUIRE(it != end_it);
    BOOST_REQUIRE(*it == expected[3]);
    BOOST_CHECK(it.depth() == 0);
}

#undef _

BOOST_AUTO_TEST_CASE(cmp_test)
{
    recursive_directory_iterator const end_it;
    recursive_directory_iterator it(make_static_env_path(""));
    
    BOOST_REQUIRE(it != end_it);
    BOOST_REQUIRE(not (it == end_it));
}

BOOST_AUTO_TEST_SUITE_END()