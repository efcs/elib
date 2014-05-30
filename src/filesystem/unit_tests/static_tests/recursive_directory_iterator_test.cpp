#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <elib/filesystem.hpp>
#include <system_error>
#include "../static_test_helper.hpp"
#include <vector>
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
    
    it.disable_recursion_pending();
    
    BOOST_CHECK_EQUAL_COLLECTIONS(
        it, end_it
      , expected.begin(), expected.end()
      );
}
#undef _

BOOST_AUTO_TEST_SUITE_END()