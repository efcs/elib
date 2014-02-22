#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <boost/filesystem.hpp>
#include <boost/system/error_code.hpp>

#include "elib/config.hpp"
#include "elib/filesystem.hpp"

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
  return (epath.native() == bpath.native());
}

inline bool operator==(const bfs::path& bpath,  const efs::path& epath)
{ 
    return (bpath.native() == epath.native());
}

inline bool operator==(const efs::error_code& e_ec, const bfs::error_code& b_ec)
{ 
  return (e_ec.value() == b_ec.value());
}

inline bool operator==(const bfs::error_code& b_ec, const efs::error_code& e_ec)
{ 
  return (b_ec.value() == e_ec.value());
}

inline bool operator==(const efs::directory_entry& e_de, 
                        const bfs::directory_entry& b_de)
{
  return (e_de.path() == b_de.path());
}

inline bool operator==(const bfs::directory_entry& b_de, 
                      const efs::directory_entry& e_de)
{
  return (b_de.path() == e_de.path());
}



const std::vector<std::string> example_path_list = 
  {
# if !defined(ELIB_CONFIG_APPLE)
#   include "test_files/long_paths_list"
# else 
#   include "test_files/short_paths_list"
# endif
  };



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
    
    efs::directory_entry e_de;
    bfs::directory_entry b_de;
    
    efs::directory_iterator e_dit, e_end;
    bfs::directory_iterator b_dit, b_end;
    
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
          e_de.assign(efs::path{});
          b_de.assign(bfs::path{});
          e_dit = efs::directory_iterator();
          e_end = efs::directory_iterator();
          b_dit = bfs::directory_iterator();
          b_end = bfs::directory_iterator();
          clear_ec();
        };
     
  auto set_iters = [&]()
        {
          clear_ec();
          e_dit = efs::directory_iterator(e, e_ec);
          b_dit = bfs::directory_iterator(b, b_ec);
          if (e_dit != e_end && b_dit != b_end)
            BOOST_CHECK(*e_dit == *b_dit);
          BOOST_CHECK(e_ec == b_ec);
        };
        
  auto dir_iter_test = [&](const std::string& s,  
                          const std::string& s1,  const std::string& s2)
        {
          reset_state(s, s1, s2);

          set_iters();
          while (e_dit != e_end && b_dit != b_end)
          {
            clear_ec();
            BOOST_CHECK(e_dit->path() == b_dit->path());
            BOOST_CHECK(e_ec == b_ec);
            ++e_dit;
            ++b_dit;
          }
          
          /* Boost and I currently do not agree on what the behaviour should 
           * be for the empty string. Boost treats it as if it were ".",  while
           * I return the end iterator.
           */
          if (s != "")
          {
            BOOST_CHECK(e_dit == e_end);
            BOOST_CHECK(b_dit == b_end);
          }
        };
          
          
    
  auto read_only_ops = [&](const std::string& s,  
    const std::string& s1,  const std::string& s2)
        {
          BOOST_CHECK(efs::absolute(e) == bfs::absolute(b));
          reset_state(s, s1, s2);
          BOOST_CHECK(efs::exists(e, e_ec) == bfs::exists(b, b_ec));
          BOOST_CHECK(e_ec == b_ec);
          
          reset_state(s, s1, s2);
          BOOST_CHECK(efs::file_size(e, e_ec) == bfs::file_size(b, b_ec));
          BOOST_CHECK(e_ec == b_ec);
          
          reset_state(s, s1, s2);
          BOOST_CHECK(efs::hard_link_count(e, e_ec) == bfs::hard_link_count(b, b_ec));
          BOOST_CHECK(e_ec == b_ec);
          
          //reset_state(s, s1, s2);
          //BOOST_CHECK(efs::is_block_file(e, e_ec) == bfs::is_block_file(b, b_ec));
          //BOOST_CHECK(e_ec == b_ec);
          
          //reset_state(s, s1, s2);
          //BOOST_CHECK(efs::is_character_file(e, e_ec) == bfs::is_character_file(b, b_ec));
          //BOOST_CHECK(e_ec == b_ec);
          
          reset_state(s, s1, s2);
          BOOST_CHECK(efs::is_directory(e, e_ec) == bfs::is_directory(b, b_ec));
          BOOST_CHECK(e_ec == b_ec);
          
          reset_state(s, s1, s2);
          BOOST_CHECK(efs::is_empty(e, e_ec) == bfs::is_empty(b, b_ec));
          BOOST_CHECK(e_ec == b_ec);
          
          //reset_state(s, s1, s2);
          //BOOST_CHECK(efs::is_fifo(e, e_ec) == bfs::is_fifo(b, b_ec));
          //BOOST_CHECK(e_ec == b_ec);
          
          reset_state(s, s1, s2);
          BOOST_CHECK(efs::is_other(e, e_ec) == bfs::is_other(b, b_ec));
          BOOST_CHECK(e_ec == b_ec);
          
          reset_state(s, s1, s2);
          BOOST_CHECK(efs::is_regular_file(e, e_ec) == bfs::is_regular_file(b, b_ec));
          BOOST_CHECK(e_ec == b_ec);
          
          //reset_state(s, s1, s2);
          //BOOST_CHECK(efs::is_socket(e, e_ec) == bfs::is_socket(b, b_ec));
          //BOOST_CHECK(e_ec == b_ec);
          
          reset_state(s, s1, s2);
          BOOST_CHECK(efs::is_symlink(e, e_ec) == bfs::is_symlink(b, b_ec));
          BOOST_CHECK(e_ec == b_ec);
          
          reset_state(s, s1, s2);
          BOOST_CHECK(efs::read_symlink(e, e_ec) == bfs::read_symlink(b, b_ec));
          BOOST_CHECK(e_ec == b_ec);
          
        } ;
        
    for (auto& s : example_path_list)
    {
      dir_iter_test(s, "", "");
      read_only_ops(s, "", "");
    }
    
}

BOOST_AUTO_TEST_SUITE_END()