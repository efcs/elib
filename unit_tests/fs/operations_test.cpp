#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <boost/filesystem.hpp>
#include <boost/system/error_code.hpp>

#include <elib/fs/path.hpp>
#include <elib/fs/operations.hpp>

#include <elib/debug/eval.hpp>

#include <string>
#include <system_error>

namespace bfs { 
using namespace boost::filesystem;
using boost::system::error_code;
}

namespace efs {
using namespace elib::fs;
using std::error_code;
}

BOOST_AUTO_TEST_SUITE(fs_operations_test_suite)

BOOST_AUTO_TEST_CASE(fs_current_path_test)
{
  bfs::error_code bec{};
  efs::error_code eec{};
  
  auto bret = bfs::current_path(bec);
  auto eret = efs::current_path(eec);
  
  BOOST_CHECK(bret.native() == eret.native());
  BOOST_CHECK(bec.value() == eec.value());
}

BOOST_AUTO_TEST_CASE(fs_canonical_test)
{
    auto canon_test = [](const std::string& p_str)
        {
          bfs::path bp{p_str};
          bfs::error_code bec{};
          
          efs::path  ep{p_str};
          efs::error_code eec{};
          
          auto bret = bfs::canonical(bp, bec);
          auto eret = efs::canonical(ep, eec);
          
          BOOST_CHECK(bret.native() == eret.native());
          BOOST_CHECK(bec.value() == eec.value());
        };
    
    canon_test("/");
}

BOOST_AUTO_TEST_SUITE_END()