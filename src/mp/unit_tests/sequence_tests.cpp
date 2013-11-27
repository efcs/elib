#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "mp_test_config.hpp"
#include <elib/mp/types.hpp>
#include <elib/mp/sequences.hpp>

struct no_tag
{};

struct nested_begin
{
  using begin = void;
};


BOOST_AUTO_TEST_SUITE(mp_sequence_test_suite)
  
//-------------------------------- sequence_tag --------------------------------// 
  BOOST_AUTO_TEST_CASE(sequence_tag_test)
  {
    using namespace e;
    // list
    using List = list<INT(0), LONG(1), CHAR(5), BOOL(false)>;
    SAME_TYPE(sequence_tag_t<List>, detail::list_tag);
    using List1 = list<>;
    SAME_TYPE(sequence_tag_t<List1>, detail::list_tag);
    // list_iter_tag
    using ListIter = begin_t<List>;
    SAME_TYPE(sequence_tag_t<ListIter>, detail::list_iter_tag);
    // vector
    using Vect = vector<INT(0), INT(1), INT(2)>;
    SAME_TYPE(sequence_tag_t<Vect>, detail::vector_tag);
    // std::integral_constant
    using IntC = std::integral_constant<bool, false>;
    SAME_TYPE(sequence_tag_t<IntC>, detail::integral_constant_tag);
    // nested begin tag
    SAME_TYPE(sequence_tag_t<nested_begin>, detail::nested_begin_tag);
    using I1 = int_<0>;
    using I2 = int_<10>;
    using R = iterator_range<I1, I2>;
    SAME_TYPE(sequence_tag_t<R>, detail::iterator_range_tag);
    // no tag
    SAME_TYPE(sequence_tag_t<no_tag>, detail::non_seq_tag);
  }                                                        // sequence_tag_test

  
  BOOST_AUTO_TEST_CASE(size_test)
  {
    using namespace e;
    // list
    {
      using L0 = list<>;
      using L1 = list<int_<0>>;
      using L2 = list_c<int, 1, 2>;
      
      BOOST_CHECK(size_t<L0>() == 0);
      BOOST_CHECK(size_t<L1>() == 1);
      BOOST_CHECK(size_t<L2>() == 2);
      
      BOOST_CHECK(nested_size_t<L0>() == 0);
      BOOST_CHECK(nested_size_t<L1>() == 1);
      BOOST_CHECK(nested_size_t<L2>() == 2);
    }
    // iterator_range
    {
      using I1 = INTC(0);
      using I2 = INTC(10);
      using R = iterator_range<I1, I2>;
      
      BOOST_CHECK(size_t<R>() == 10);
    }
  }                                                         // list_size_test


////////////////////////////////////////////////////////////////////////////////
//                  integral_constant & iterator_range                                              
////////////////////////////////////////////////////////////////////////////////


BOOST_AUTO_TEST_SUITE_END()