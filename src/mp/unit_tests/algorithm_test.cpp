#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "mp_test_config.hpp"
#include <elib/mp/algorithm.hpp>

#if ELIB_MP_BOOST_MLP_TESTS
# // Inserters
# include <boost/mpl/inserter.hpp>
# include <boost/mpl/front_inserter.hpp>
# include <boost/mpl/back_inserter.hpp>
# // Iteration
# include <boost/mpl/fold.hpp>
# include <boost/mpl/iter_fold.hpp>
# include <boost/mpl/reverse_fold.hpp>
# include <boost/mpl/reverse_iter_fold.hpp>
# include <boost/mpl/accumulate.hpp>
# // Querying
# include <boost/mpl/find.hpp>
# include <boost/mpl/find_if.hpp>
# include <boost/mpl/contains.hpp>
# include <boost/mpl/count.hpp>
# include <boost/mpl/count_if.hpp>
# include <boost/mpl/lower_bound.hpp>
# include <boost/mpl/upper_bound.hpp>
# include <boost/mpl/min_element.hpp>
# include <boost/mpl/max_element.hpp>
# include <boost/mpl/equal.hpp>
# // Transformations
# include <boost/mpl/copy.hpp>
# include <boost/mpl/copy_if.hpp>
# include <boost/mpl/transform.hpp>
# include <boost/mpl/replace.hpp>
# include <boost/mpl/replace_if.hpp>
# include <boost/mpl/remove.hpp>
# include <boost/mpl/remove_if.hpp>
# include <boost/mpl/unique.hpp>
# include <boost/mpl/partition.hpp>
# include <boost/mpl/stable_partition.hpp>
# include <boost/mpl/sort.hpp>
# // Reverse Transformations
# include <boost/mpl/reverse_copy.hpp>
# include <boost/mpl/reverse_copy_if.hpp>
# include <boost/mpl/reverse_transform.hpp>
# include <boost/mpl/reverse_replace.hpp>
# include <boost/mpl/reverse_replace_if.hpp>
# include <boost/mpl/reverse_remove.hpp>
# include <boost/mpl/reverse_remove_if.hpp>
# include <boost/mpl/reverse_unique.hpp>
# include <boost/mpl/reverse_partition.hpp>
# include <boost/mpl/reverse_stable_partition.hpp>
# 
# endif                                              // ELIB_MP_BOOST_MLP_TESTS



BOOST_AUTO_TEST_SUITE(mp_algorithm_test_suite)

  //TODO
  BOOST_AUTO_TEST_CASE(todo_test)
  {
    BOOST_CHECK(true);
  }

BOOST_AUTO_TEST_SUITE_END()