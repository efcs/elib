#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <boost/filesystem.hpp>
#include <boost/system/error_code.hpp>

#include <elib/fs/path.hpp>
#include <elib/fs/operations.hpp>

#define ELIB_DEBUG_EVAL_FAILED
#include "elib/debug/eval.hpp"

#include <string>
#include <system_error>
#include <vector>

namespace bfs { 
using namespace boost::filesystem;
using boost::system::error_code;
}

namespace efs {
using namespace elib::fs;
using std::error_code;
}

inline bool operator==(const efs::path& epath,  const bfs::path& bpath)
{ 
  ELIB_EVAL_BEGIN()
  ELIB_EVAL(==, epath.native(), bpath.native());
  ELIB_EVAL_END()
}

inline bool operator==(const bfs::path& bpath,  const efs::path& epath)
{ 
  ELIB_EVAL_BEGIN()
  ELIB_EVAL(==, bpath.native(), epath.native());
  ELIB_EVAL_END()
}


inline bool operator==(const efs::error_code& e_ec, const bfs::error_code& b_ec)
{ 
  ELIB_EVAL_BEGIN()
  ELIB_EVAL(==, e_ec.value(), b_ec.value());
  ELIB_EVAL(==, e_ec.message(), b_ec.message());
  ELIB_EVAL_END()
}

inline bool operator==(const bfs::error_code& b_ec, const efs::error_code& e_ec)
{ 
  ELIB_EVAL_BEGIN()
  ELIB_EVAL(==, b_ec.value(), e_ec.value());
  ELIB_EVAL_END()
}



const std::vector<std::string> example_path_list = 
#if 1
# include "test_files/fs/paths_list"
#else
{ "",  "/",  ".",  "//",  "foo"};
#endif


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

BOOST_AUTO_TEST_CASE(fs_test_main)
{
    efs::path e, e1, e2;
    bfs::path b, b1, b2;
    
    efs::error_code e_ec;
    bfs::error_code b_ec;
    
    auto clear_ec = [&]() { e_ec.clear(); b_ec.clear(); };
    
    auto reset_state = [&](const std::string& s,  
          const std::string& s1,  const std::string& s2)
        {
          e  = efs::path{s};
          b  = bfs::path{s};
          e1  = efs::path{s1};
          b1  = bfs::path{s1};
          e2  = efs::path{s2};
          b2  = bfs::path{s2};
          clear_ec();
        };
    
    auto read_only_ops = [&](const std::string& s,  
          const std::string& s1,  const std::string& s2)
        {
          //BOOST_CHECK(efs::absolute(e) == bfs::absolute(b));
          reset_state(s, s1, s2);
          BOOST_CHECK(efs::exists(e, e_ec) == bfs::exists(b, b_ec));
          BOOST_CHECK(e_ec == b_ec);
          
          reset_state(s, s1, s2);
          BOOST_CHECK(efs::file_size(e, e_ec) == bfs::file_size(b, b_ec));
          BOOST_CHECK(e_ec == b_ec);
          
          reset_state(s, s1, s2);
          BOOST_CHECK(efs::hard_link_count(e, e_ec) == bfs::hard_link_count(b, b_ec));
          if (! efs::hard_link_count(e, e_ec) == bfs::hard_link_count(b, b_ec))
          std::cout <<  efs::hard_link_count(e, e_ec) << " " 
                    <<  bfs::hard_link_count(b, b_ec)
                    << " " <<  e <<  std::endl;
          BOOST_CHECK(e_ec == b_ec);
          
          //reset_state(s, s1, s2);
          //BOOST_CHECK(efs::is_block_file(e, e_ec) == bfs::is_block_file(b, b_ec));
          //BOOST_CHECK(e_ec == b_ec);
          
          //reset_state(s, s1, s2);
          //BOOST_CHECK(efs::is_character_file(e, e_ec) == bfs::is_character_file(b, b_ec));
          //BOOST_CHECK(e_ec == b_ec);
          
//           reset_state(s, s1, s2);
//           BOOST_CHECK(efs::is_directory(e, e_ec) == bfs::is_directory(b, b_ec));
//           BOOST_CHECK(e_ec == b_ec);
//           
          //reset_state(s, s1, s2);
          //BOOST_CHECK(efs::is_empty(e, e_ec) == bfs::is_empty(b, b_ec));
          //BOOST_CHECK(e_ec == b_ec);
          
          //reset_state(s, s1, s2);
          //BOOST_CHECK(efs::is_fifo(e, e_ec) == bfs::is_fifo(b, b_ec));
          //BOOST_CHECK(e_ec == b_ec);
          
//           reset_state(s, s1, s2);
//           BOOST_CHECK(efs::is_other(e, e_ec) == bfs::is_other(b, b_ec));
//           BOOST_CHECK(e_ec == b_ec);
//           
//           reset_state(s, s1, s2);
//           BOOST_CHECK(efs::is_regular_file(e, e_ec) == bfs::is_regular_file(b, b_ec));
//           BOOST_CHECK(e_ec == b_ec);
//           
          //reset_state(s, s1, s2);
          //BOOST_CHECK(efs::is_socket(e, e_ec) == bfs::is_socket(b, b_ec));
          //BOOST_CHECK(e_ec == b_ec);
          
//           reset_state(s, s1, s2);
//           BOOST_CHECK(efs::is_symlink(e, e_ec) == bfs::is_symlink(b, b_ec));
//           BOOST_CHECK(e_ec == b_ec);
//           
//           reset_state(s, s1, s2);
//           BOOST_CHECK(efs::read_symlink(e, e_ec) == bfs::read_symlink(b, b_ec));
//           BOOST_CHECK(e_ec == b_ec);
          
        } ;
        
    for (auto& s : example_path_list)
    {
      read_only_ops(s, "", "");
    }
    
}

BOOST_AUTO_TEST_SUITE_END()