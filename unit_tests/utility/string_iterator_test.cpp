#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>


#include <elib/utility/string_iterator.hpp>

#include <string>
#include <iterator>


BOOST_AUTO_TEST_SUITE(string_iterator_test_suite)

BOOST_AUTO_TEST_CASE(test_string_iterator_construct)
{

  auto check_ctor = 
  [](const char* c_str)
  {
    std::string s{c_str};
    elib::string_iterator it{s};

    BOOST_CHECK(it.good());
    BOOST_CHECK(&it.str() == &s);
    BOOST_CHECK(it.pos() == 0);

    auto it_cp = it;
    BOOST_CHECK(it == it_cp);

    elib::string_iterator it_o{};
    BOOST_CHECK(!it_o.good());
    BOOST_CHECK(it_o.pos() == static_cast<std::size_t>(-1));

    it_o = it;
    BOOST_CHECK(it_o == it);

  };
  
  check_ctor("");
  check_ctor("a");
  check_ctor("aoeu");
}

BOOST_AUTO_TEST_CASE(test_begin_end)
{
  std::string s{""};
  elib::string_iterator b{};
  elib::string_iterator e{};
  
  BOOST_CHECK(!b.good() && b.is_end());
  BOOST_CHECK(!e.good() && e.is_end());
  BOOST_CHECK(b == e);
  
  b = elib::string_iterator{s};
  e = elib::string_iterator{s};
  
  BOOST_CHECK(b.good() && b.is_end());
  BOOST_CHECK(e.good() && e.is_end());
  BOOST_CHECK(b == e);
  
  
  b = elib::begin(b);
  e = elib::end(e);
  BOOST_CHECK(b.good() && b.is_end());
  BOOST_CHECK(e.good() && e.is_end());
  BOOST_CHECK(b == e);
  
  s = "hello";
  b = elib::begin(elib::string_iterator{s});
  e = elib::end(elib::string_iterator{s});
  
  BOOST_CHECK(b.good() && !b.is_end());
  BOOST_CHECK(e.good() && e.is_end());
  BOOST_CHECK(b.pos() == 0);
  BOOST_CHECK(e.pos() == s.size());
  BOOST_CHECK(b != e);
}


BOOST_AUTO_TEST_CASE(test_increment)
{
  
  auto test_inc =
    [](const char* c_str, std::size_t start_pos, std::size_t n, 
                          std::size_t end_pos)
    {
      std::string s{c_str};
      auto orig_it = elib::string_iterator{s, start_pos};
      auto end_it = elib::string_iterator{s, end_pos};
      
      auto it1 = orig_it;
      auto it2 = orig_it;
      auto it3 = orig_it;
      auto it4 = orig_it;
      
      for (std::size_t i=0; i < n; ++i)
      {
        ++it1;
        it2++;
        it3.increment();
      }
      
      it4 += n;
      auto it5 = orig_it + n;
      auto it6 = orig_it[n];
      
      BOOST_CHECK(it1 == end_it);
      BOOST_CHECK(it2 == end_it);
      BOOST_CHECK(it3 == end_it);
      BOOST_CHECK(it4 == end_it);
      BOOST_CHECK(it5 == end_it);
      BOOST_CHECK(it6 == end_it);
    };
    
    test_inc("", 0, 0, 0);
    test_inc("", 0, 1, 0);
    test_inc("", 0, 2, 0);
    test_inc("abc", 0, 0, 0);
    test_inc("abc", 0, 1, 1);
    test_inc("abc", 0, 2, 2);
    test_inc("abc", 0, 3, 3);
    test_inc("abc", 0, 4, 3);
    test_inc("abc", 3, 4, 3);
    
    std::string s{"hello"};
    auto it = elib::string_iterator{s};
    it += 10000000;
    BOOST_CHECK(it.pos() == s.size());

    
}

BOOST_AUTO_TEST_CASE(test_decrement)
{
   
  auto test_dec =
    [](const char* c_str, std::size_t start_pos, std::size_t n, 
                          std::size_t end_pos)
    {
      std::string s{c_str};
      auto orig_it = elib::string_iterator{s, start_pos};
      auto end_it = elib::string_iterator{s, end_pos};
      
      auto it1 = orig_it;
      auto it2 = orig_it;
      auto it3 = orig_it;
      auto it4 = orig_it;
      
      for (std::size_t i=0; i < n; ++i)
      {
        --it1;
        it2--;
        it3.decrement();
      }
      
      it4 -= n;
      auto it5 = orig_it - n;
      auto it6 = orig_it[-n];
      
      BOOST_CHECK(it1 == end_it);
      BOOST_CHECK(it2 == end_it);
      BOOST_CHECK(it3 == end_it);
      BOOST_CHECK(it4 == end_it);
      BOOST_CHECK(it5 == end_it);
      BOOST_CHECK(it6 == end_it);
    };
    
    test_dec("", 0, 0, 0);
    test_dec("", 0, 1, 0);
    test_dec("", 0, 2, 0);
    test_dec("abc", 0, 0, 0);
    test_dec("abc", 0, 1, 0);
    test_dec("abc", 0, 2, 0);
    test_dec("abc", 1, 0, 1);
    test_dec("abc", 1, 1, 0);
    test_dec("abc", 1, 2, 0);
    test_dec("abc", 2, 1, 1);
    test_dec("abc", 2, 2, 0);
    test_dec("abc", 2, 10000, 0);
}


BOOST_AUTO_TEST_CASE(string_iterator_test)
{
  std::string str{"abcd"};
  
  auto eit = elib::string_iterator{str};
  BOOST_CHECK(&eit.str() == &str);
  BOOST_CHECK(eit.pos() == 0);
  BOOST_CHECK(!eit.is_end());
  
  auto ebegin = elib::begin(elib::string_iterator{str});
  BOOST_CHECK(eit == ebegin);
  
  auto eend = elib::end(elib::string_iterator{str});
  BOOST_CHECK(&eend.str() == &str);
  BOOST_CHECK(eend.pos() == str.size());
  BOOST_CHECK(eend.is_end());

  for (auto& ch : str)
  {
    BOOST_REQUIRE(!eit.is_end());
    BOOST_CHECK(ch == *eit);
    ++eit;
  }
  
  BOOST_CHECK(eit.is_end() && eit == eend);
  BOOST_CHECK(eit != ebegin);
  
  BOOST_CHECK(eit.pos() == str.size());
  eit.increment();
  BOOST_CHECK(eit.pos() == str.size());
  eit.decrement();
}


BOOST_AUTO_TEST_CASE(test_const)
{
  std::string s{"abcd"};
  
  auto it = elib::string_iterator{s};
  *it = 'b';
  
  BOOST_CHECK(s == "bbcd");
}

BOOST_AUTO_TEST_SUITE_END()