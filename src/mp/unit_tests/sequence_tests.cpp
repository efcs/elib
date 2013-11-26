#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "mp_test_config.hpp"
#include <elib/mp/sequences.hpp>

struct no_tag
{};

BOOST_AUTO_TEST_SUITE(mp_sequence_test_suite)
  
//-------------------------------- sequence_tag --------------------------------// 
  BOOST_AUTO_TEST_CASE(sequence_tag_test)
  {
    {
      using E1 = typename e::sequence_tag<e::vector<int>>::type;
      using E2 = e::sequence_tag_t<e::vector_c<int, 0>>;
      using E3 = e::sequence_tag_t<e::deque<int>>;
      SAME_TYPE(E1, e::detail::vector_tag);
      SAME_TYPE(E2, e::detail::vector_tag);
      SAME_TYPE(E3, e::detail::vector_tag);
    }
    {
      using E1 = e::sequence_tag_t<e::list<int>>;
      using E2 = e::sequence_tag_t<e::list_c<int, 0>>;
      SAME_TYPE(E1, e::detail::list_tag);
      SAME_TYPE(E2, e::detail::list_tag);
    }
    {
      using E1 = e::sequence_tag_t<e::set<int>>;
      using E2 = e::sequence_tag_t<e::set_c<int, 0>>;
      SAME_TYPE(E1, e::detail::set_tag);
      SAME_TYPE(E2, e::detail::set_tag);
    }
    {
      using E1 = e::sequence_tag_t<e::map<int>>;
      SAME_TYPE(E1, e::detail::map_tag);
      
      using E2 = e::sequence_tag_t<e::range_c<int, 0, 1>>;
      SAME_TYPE(E2, e::detail::range_c_tag);
    }
    {
      using E1 = e::sequence_tag_t<no_tag>;
      SAME_TYPE(E1, e::detail::no_seq_tag);
    }
  }                                                           // sequence_tag_test

BOOST_AUTO_TEST_SUITE_END()