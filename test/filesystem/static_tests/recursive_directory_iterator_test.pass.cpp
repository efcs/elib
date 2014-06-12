#define BOOST_TEST_MODULE Main
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <elib/filesystem.hpp>
#include <system_error>
#include "../static_test_helper.hpp"
#include <set>
#include <cstddef>
using namespace elib::fs;

#define _(File) directory_entry(make_static_env_path(File))
namespace {
const std::set<directory_entry> file_list =
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
    
const std::set<directory_entry> top_level_files =
    {
        _("empty_file")
      , _("dir1")
      , _("non_empty_file")
    };
    
#undef _
}

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

BOOST_AUTO_TEST_CASE(simple_iterate_test)
{
    recursive_directory_iterator it(static_test_env_path);
    recursive_directory_iterator const end_it;
    
    std::set<directory_entry> seen;
    
    for (auto & part : it) {
        BOOST_REQUIRE(not seen.count(part));
        seen.insert(part);
    }
    
    BOOST_REQUIRE(seen == file_list);
}

BOOST_AUTO_TEST_CASE(disable_recursion_pending_test)
{
    
    recursive_directory_iterator it(static_test_env_path);
    recursive_directory_iterator const end_it;
    
    std::set<directory_entry> seen;
    
    for (; it != end_it; ++it) {
        BOOST_REQUIRE(not seen.count(*it));
        seen.insert(*it);
        it.disable_recursion_pending();
    }
    
    BOOST_CHECK(seen == top_level_files);
}

BOOST_AUTO_TEST_CASE(walk_dir_test)
{
    
    recursive_directory_iterator const end_it;
    
    {
        recursive_directory_iterator it(make_static_env_path(""));
        BOOST_REQUIRE(it != end_it);
        BOOST_CHECK(file_list.count(*it));
                ++it;
        BOOST_REQUIRE(it != end_it);
        BOOST_CHECK(file_list.count(*it));
                ++it;
        BOOST_REQUIRE(it != end_it);
        BOOST_CHECK(file_list.count(*it));
                ++it;
        BOOST_REQUIRE(it != end_it);
        BOOST_CHECK(file_list.count(*it));
                ++it;
        BOOST_REQUIRE(it != end_it);
        BOOST_CHECK(file_list.count(*it));
        ++it;
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
        recursive_directory_iterator it(make_static_env_path(""));
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
        recursive_directory_iterator it(make_static_env_path(""));
        recursive_directory_iterator it_cp;
        directory_entry old;
        
        BOOST_REQUIRE(it != end_it);
        BOOST_CHECK(file_list.count(*it));
        
        old = *it;
        it_cp = it++;
        BOOST_CHECK(*it_cp == old);
        BOOST_REQUIRE(it != end_it);
        BOOST_CHECK(file_list.count(*it));
        
        old = *it;
        it_cp = it++;
        BOOST_CHECK(*it_cp == old);
        BOOST_REQUIRE(it != end_it);
        BOOST_CHECK(file_list.count(*it));
        
        old = *it;
        it_cp = it++;
        BOOST_CHECK(*it_cp == old);
        BOOST_REQUIRE(it != end_it);
        BOOST_CHECK(file_list.count(*it));

        old = *it;
        it_cp = it++;
        BOOST_CHECK(*it_cp == old);
        BOOST_REQUIRE(it != end_it);
        BOOST_CHECK(file_list.count(*it));
        
        old = *it;
        it_cp = it++;
        BOOST_CHECK(*it_cp == old);
        BOOST_REQUIRE(it != end_it);
        BOOST_CHECK(file_list.count(*it));
        
        old = *it;
        it_cp = it++;
        BOOST_CHECK(*it_cp == old);
        BOOST_REQUIRE(it != end_it);
        BOOST_CHECK(file_list.count(*it));
        
        old = *it;
        it_cp = it++;
        BOOST_CHECK(*it_cp == old);
        BOOST_REQUIRE(it != end_it);
        BOOST_CHECK(file_list.count(*it));
        
        old = *it;
        it_cp = it++;
        BOOST_CHECK(*it_cp == old);
        BOOST_REQUIRE(it == end_it);
    }
}

BOOST_AUTO_TEST_CASE(pop_test)
{
    
    recursive_directory_iterator const end_it;
    recursive_directory_iterator it(make_static_env_path(""));
    
    std::set<directory_entry> seen;
    while (it != end_it && top_level_files.count(*it)) {
        BOOST_REQUIRE(not seen.count(*it));
        seen.insert(*it);
        ++it;
    }
    BOOST_REQUIRE(it != end_it);
    BOOST_REQUIRE(not top_level_files.count(*it));
    it.pop();
    while (it != end_it) {
        BOOST_REQUIRE(not seen.count(*it));
        seen.insert(*it);
        ++it;
    }
    BOOST_REQUIRE(seen == top_level_files);
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