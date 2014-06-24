// REQUIRES: ELIB_FILESYSTEM
#include <elib/filesystem.hpp>
#include <system_error>
#include <set>
#include <cstddef>
#include "../static_test_helper.hpp"
#include "rapid-cxx-test.hpp"

#if defined(__clang__)
# pragma clang diagnostic ignored "-Wglobal-constructors"
# pragma clang diagnostic ignored "-Wexit-time-destructors"
#endif

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

TEST_SUITE(elib_filesystem_static_recursive_directory_iterator_test_suite)

TEST_CASE(dne_test)
{
    path const dir = make_static_env_path("dne");
    recursive_directory_iterator const end_it;
    {
        std::error_code ec;
        recursive_directory_iterator it(dir, ec);
        TEST_REQUIRE(ec);
        TEST_CHECK(it == end_it);
    }{
        recursive_directory_iterator it;
        TEST_CHECK_THROW(filesystem_error, it = recursive_directory_iterator(dir));
    }
}

TEST_CASE(simple_iterate_test)
{
    recursive_directory_iterator it(static_test_env_path());
    recursive_directory_iterator const end_it;
    
    std::set<directory_entry> seen;
    
    for (auto & part : it) {
        TEST_REQUIRE(not seen.count(part));
        seen.insert(part);
    }
    
    TEST_REQUIRE(seen == file_list);
}

TEST_CASE(disable_recursion_pending_test)
{
    
    recursive_directory_iterator it(static_test_env_path());
    recursive_directory_iterator const end_it;
    
    std::set<directory_entry> seen;
    
    for (; it != end_it; ++it) {
        TEST_REQUIRE(not seen.count(*it));
        seen.insert(*it);
        it.disable_recursion_pending();
    }
    
    TEST_CHECK(seen == top_level_files);
}

TEST_CASE(walk_dir_test)
{
    
    recursive_directory_iterator const end_it;
    
    {
        recursive_directory_iterator it(make_static_env_path(""));
        TEST_REQUIRE(it != end_it);
        TEST_CHECK(file_list.count(*it));
                ++it;
        TEST_REQUIRE(it != end_it);
        TEST_CHECK(file_list.count(*it));
                ++it;
        TEST_REQUIRE(it != end_it);
        TEST_CHECK(file_list.count(*it));
                ++it;
        TEST_REQUIRE(it != end_it);
        TEST_CHECK(file_list.count(*it));
                ++it;
        TEST_REQUIRE(it != end_it);
        TEST_CHECK(file_list.count(*it));
        ++it;
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
        recursive_directory_iterator it(make_static_env_path(""));
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
        recursive_directory_iterator it(make_static_env_path(""));
        recursive_directory_iterator it_cp;
        directory_entry old;
        
        TEST_REQUIRE(it != end_it);
        TEST_CHECK(file_list.count(*it));
        
        old = *it;
        it_cp = it++;
        TEST_CHECK(*it_cp == old);
        TEST_REQUIRE(it != end_it);
        TEST_CHECK(file_list.count(*it));
        
        old = *it;
        it_cp = it++;
        TEST_CHECK(*it_cp == old);
        TEST_REQUIRE(it != end_it);
        TEST_CHECK(file_list.count(*it));
        
        old = *it;
        it_cp = it++;
        TEST_CHECK(*it_cp == old);
        TEST_REQUIRE(it != end_it);
        TEST_CHECK(file_list.count(*it));

        old = *it;
        it_cp = it++;
        TEST_CHECK(*it_cp == old);
        TEST_REQUIRE(it != end_it);
        TEST_CHECK(file_list.count(*it));
        
        old = *it;
        it_cp = it++;
        TEST_CHECK(*it_cp == old);
        TEST_REQUIRE(it != end_it);
        TEST_CHECK(file_list.count(*it));
        
        old = *it;
        it_cp = it++;
        TEST_CHECK(*it_cp == old);
        TEST_REQUIRE(it != end_it);
        TEST_CHECK(file_list.count(*it));
        
        old = *it;
        it_cp = it++;
        TEST_CHECK(*it_cp == old);
        TEST_REQUIRE(it != end_it);
        TEST_CHECK(file_list.count(*it));
        
        old = *it;
        it_cp = it++;
        TEST_CHECK(*it_cp == old);
        TEST_REQUIRE(it == end_it);
    }
}

TEST_CASE(pop_test)
{
    
    recursive_directory_iterator const end_it;
    recursive_directory_iterator it(make_static_env_path(""));
    
    std::set<directory_entry> seen;
    while (it != end_it && top_level_files.count(*it)) {
        TEST_REQUIRE(not seen.count(*it));
        seen.insert(*it);
        ++it;
    }
    TEST_REQUIRE(it != end_it);
    TEST_REQUIRE(not top_level_files.count(*it));
    it.pop();
    while (it != end_it) {
        TEST_REQUIRE(not seen.count(*it));
        seen.insert(*it);
        ++it;
    }
    TEST_REQUIRE(seen == top_level_files);
}

#undef _

TEST_CASE(cmp_test)
{
    recursive_directory_iterator const end_it;
    recursive_directory_iterator it(make_static_env_path(""));
    
    TEST_REQUIRE(it != end_it);
    TEST_REQUIRE(not (it == end_it));
}

TEST_SUITE_END()