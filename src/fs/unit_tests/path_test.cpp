#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <boost/filesystem.hpp>
#include <boost/system/error_code.hpp>

#include "elib/filesystem.hpp"


#include <string>
#include <system_error>
#include <utility>
#include <fstream>
#include <iostream>


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
  

const std::vector<std::string> example_path_list = 
  {
#   include "test_files/long_paths_list"
  };



BOOST_AUTO_TEST_SUITE(path_test_suite)


template <typename... Args>
void ctor_test(Args&&... args)
{
  auto e = efs::path{std::forward<Args>(args)...};         
  auto b = bfs::path{std::forward<Args>(args)...};         
  BOOST_CHECK(e == b);                   
  auto e2 = e;                           
  auto b2 = b;                           
  BOOST_CHECK(e2 == b2);                 
  auto e3 = std::move(e2);               
  auto b3 = std::move(b2);               
  BOOST_CHECK(e3 == b3);                 
  efs::path e4 = std::string{std::forward<Args>(args)...}; 
  bfs::path b4 = std::string{std::forward<Args>(args)...}; 
  BOOST_CHECK(e4 == b4);         
}


BOOST_AUTO_TEST_CASE(path_constructor_test)
{
  ctor_test();
  ctor_test("");
  ctor_test("/");
  ctor_test("/foo");
  ctor_test("//net");
}



void append_test(const std::string& lhs, const std::string& rhs)
{
  auto e = efs::path{lhs};
  auto b = bfs::path{lhs};
  
  BOOST_CHECK( (efs::path{lhs} / efs::path{rhs}) ==
               (bfs::path{lhs} / bfs::path{rhs}));
               
  BOOST_CHECK( ( e / efs::path{rhs}) ==
               ( b / bfs::path{rhs}));
    
  e /= efs::path{rhs};
  b /= bfs::path{rhs};
  
  BOOST_CHECK(e == b);
}


BOOST_AUTO_TEST_CASE(path_append_test)
{
  append_test("",  "");
  append_test("",  "/");
  append_test("/", "");
  append_test("//", "");
  append_test("",  "//");
  append_test("/foo", "bar");
  append_test("//net",  "/");
}


void iter_test(const std::string& str)
{
  auto e = efs::path{str};
  auto b = bfs::path{str};
  
  auto et = e.begin();
  auto bt = b.begin();
  while (et != e.end() && bt != b.end())
  {
    BOOST_CHECK(*et == *bt);
    ++et;
    ++bt;
  }
  
  BOOST_CHECK(bt == b.end());
  BOOST_CHECK(et == e.end());
  BOOST_CHECK(*--et == *--bt);
  
  et = e.end();
  bt = b.end();
  
  do {
    --et;
    --bt;
    BOOST_CHECK(*et == *bt);
  } while (et != e.begin() || bt != b.begin());
}

void decomp_test(const std::string& s)
{
  auto e = efs::path{s};
  auto b = bfs::path{s};

  BOOST_CHECK(e.root_name() == b.root_name());
  BOOST_CHECK(e.root_directory() == b.root_directory());
  BOOST_CHECK(e.root_path() == b.root_path());
  BOOST_CHECK(e.relative_path() == b.relative_path());
  BOOST_CHECK(e.parent_path() == b.parent_path());
  BOOST_CHECK(e.filename() == b.filename());
  BOOST_CHECK(e.stem() == b.stem());
  BOOST_CHECK(e.extension() == b.extension());

}

void query_test(const std::string& s)
{
  auto e = efs::path{s};
  auto b = bfs::path{s};

  BOOST_CHECK(e.empty() == b.empty());
  BOOST_CHECK(e.has_root_name() == b.has_root_name());
  BOOST_CHECK(e.has_root_directory() == b.has_root_directory());
  BOOST_CHECK(e.has_root_path() == b.has_root_path());
  BOOST_CHECK(e.has_relative_path() == b.has_relative_path());
  BOOST_CHECK(e.has_parent_path() == b.has_parent_path());
  BOOST_CHECK(e.has_filename() == b.has_filename());
  BOOST_CHECK(e.has_stem() == b.has_stem());
  BOOST_CHECK(e.has_extension() == b.has_extension());
  BOOST_CHECK(e.is_absolute() == b.is_absolute());
  BOOST_CHECK(e.is_relative() == b.is_relative());
  
}

void modifier_test(const std::string& s)
{
  auto e = efs::path{s};
  auto b = bfs::path{s};
  
  BOOST_CHECK(e.make_preferred() == b.make_preferred());
  e = efs::path{s};
  b = bfs::path{s};
  BOOST_CHECK(e.remove_filename() == b.remove_filename());
  e = efs::path{s};
  b = bfs::path{s};
  
  BOOST_CHECK(e.replace_extension() == b.replace_extension());
  e = efs::path{s};
  b = bfs::path{s};

}

BOOST_AUTO_TEST_CASE(fs_path_iter_test)
{
  for (auto& s : example_path_list) {
    iter_test(s);
    decomp_test(s);
    query_test(s);
    modifier_test(s);
  }
}




#if 0

bool
check(const std::string & ctor,
  const std::string & iter,
  const std::string & str,
  const std::string & root_path,
  const std::string & root_name,
  const std::string & root_dir,
  const std::string & rel_path,
  const std::string & parent_path,
  const std::string & filename)
{
  efs::path p(ctor);

  std::string iter_join;
  for (auto& s : p) {
    iter_join += s.native() + ",";
    }
  if (! iter_join.empty())
  iter_join.erase(--iter_join.end());

  ELIB_EVAL_BEGIN()
  ELIB_EVAL(==, iter_join, iter);
  ELIB_EVAL(==, p.native(), str);
  ELIB_EVAL(==, p.root_path().native(), root_path);
  ELIB_EVAL(==, p.root_name().native(), root_name);
  ELIB_EVAL(==, p.root_directory().native(), root_dir);
  ELIB_EVAL(==, p.relative_path().native(), rel_path);
  ELIB_EVAL(==, p.parent_path().native(), parent_path);
  ELIB_EVAL(==, p.filename().native(), filename);
  ELIB_EVAL_END()
}


BOOST_AUTO_TEST_CASE(path_table)
{
    BOOST_CHECK(check("", "", "", "", "",  "", "", "", ""));
    BOOST_CHECK(check(".", ".", ".", "", "",  "", ".", "", "."));
    BOOST_CHECK(check("..", "..", "..", "", "",  "", "..", "", ".."));
    BOOST_CHECK(check("foo", "foo", "foo", "", "",  "", "foo", "", "foo"));
    BOOST_CHECK(check("/", "/", "/", "/", "",  "/", "", "", "/"));
    BOOST_CHECK(check("/foo", "/,foo", "/foo", "/", "",  "/", "foo", "/", "foo"));
    BOOST_CHECK(check("foo/", "foo,.", "foo/", "", "",  "", "foo/", "foo", "."));
    BOOST_CHECK(check("/foo/", "/,foo,.", "/foo/", "/", "",  "/", "foo/", "/foo", "."));
    BOOST_CHECK(check("foo/bar", "foo,bar", "foo/bar", "", "",  "", "foo/bar", "foo", "bar"));
    BOOST_CHECK(check("/foo/bar", "/,foo,bar", "/foo/bar", "/", "",  "/", "foo/bar", "/foo", "bar"));
    BOOST_CHECK(check("//net", "//net", "//net", "//net", "//net",  "", "", "", "//net"));
    BOOST_CHECK(check("//net/foo", "//net,/,foo", "//net/foo", "//net/", "//net",  "/", "foo", "//net/", "foo"));
    BOOST_CHECK(check("///foo///", "/,foo,.", "///foo///", "/", "",  "/", "foo///", "///foo", "."));
    BOOST_CHECK(check("///foo///bar", "/,foo,bar", "///foo///bar", "/", "",  "/", "foo///bar", "///foo", "bar"));
    BOOST_CHECK(check("/.", "/,.", "/.", "/", "",  "/", ".", "/", "."));
    BOOST_CHECK(check("./", ".,.", "./", "", "",  "", "./", ".", "."));
    BOOST_CHECK(check("/..", "/,..", "/..", "/", "",  "/", "..", "/", ".."));
    BOOST_CHECK(check("../", "..,.", "../", "", "",  "", "../", "..", "."));
    BOOST_CHECK(check("foo/.", "foo,.", "foo/.", "", "",  "", "foo/.", "foo", "."));
    BOOST_CHECK(check("foo/..", "foo,..", "foo/..", "", "",  "", "foo/..", "foo", ".."));
    BOOST_CHECK(check("foo/./", "foo,.,.", "foo/./", "", "",  "", "foo/./", "foo/.", "."));
    BOOST_CHECK(check("foo/./bar", "foo,.,bar", "foo/./bar", "", "",  "", "foo/./bar", "foo/.", "bar"));
    BOOST_CHECK(check("foo/..", "foo,..", "foo/..", "", "",  "", "foo/..", "foo", ".."));
    BOOST_CHECK(check("foo/../", "foo,..,.", "foo/../", "", "",  "", "foo/../", "foo/..", "."));
    BOOST_CHECK(check("foo/../bar", "foo,..,bar", "foo/../bar", "", "",  "", "foo/../bar", "foo/..", "bar"));
}

#endif /* table */

BOOST_AUTO_TEST_SUITE_END()

