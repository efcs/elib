#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "mp_test_config.hpp"
#include <elib/mp/vector.hpp>
#include <elib/mp/intrinsic.hpp>
#include <elib/mp/iterator.hpp>
#include <elib/mp/detail/has_size.hpp>
#include <elib/mp/detail/has_begin.hpp>

#include <typeinfo>
#include <iostream>


BOOST_AUTO_TEST_SUITE(mp_vector_test_suite)

  BOOST_AUTO_TEST_CASE(create_test)
  {
    using e::vector;
    using e::vector_c;
    
    using T1 = vector<>;
    using T2 = vector<true_>;
    using T3 = vector<int_<1>, int_<2>, int_<3>>;
    
    using T4 = vector_c<void>;
    using T5 = vector_c<bool, true>;
    using T6 = vector_c<int, 1, 2, 3>;
    
    SAME_TYPE(T1, T4);
    SAME_TYPE(T2, T5);
    SAME_TYPE(T3, T6);
  }
  
  BOOST_AUTO_TEST_CASE(size_test)
  {
    using e::vector;
    using e::vector_c;
    using e::size;
    using e::size_t;
    using e::nested_size;
    using e::nested_size_t;
    
    using T1 = vector<>;
    using T2 = vector<void>;
    using T3 = vector<true_, true_, false_, false_>;
    
    BOOST_CHECK(e::detail::has_size<T1>::type::value);
    BOOST_CHECK(e::detail::has_size<T2>::type::value);
    
    BOOST_CHECK(size_t<T1>::value == 0);
    BOOST_CHECK(size_t<T2>::value == 1);
    BOOST_CHECK(size_t<T3>::value == 4);
    
    BOOST_CHECK(nested_size_t<T1>::value == 0);
    BOOST_CHECK(nested_size_t<T2>::value == 1);
    BOOST_CHECK(nested_size_t<T3>::value == 4);
    
    using T4 = vector_c<int>;
    using T5 = vector_c<int, 0>;
    using T6 = vector_c<int, 1, 2, 3, 4>;
    
    BOOST_CHECK(e::detail::has_size<T4>::type::value);
    BOOST_CHECK(e::detail::has_size<T5>::type::value);
    
    BOOST_CHECK(size_t<T4>::value == 0);
    BOOST_CHECK(size_t<T5>::value == 1);
    BOOST_CHECK(size_t<T6>::value == 4);
    
    BOOST_CHECK(nested_size_t<T4>::value == 0);
    BOOST_CHECK(nested_size_t<T5>::value == 1);
    BOOST_CHECK(nested_size_t<T6>::value == 4);
  }
  
  BOOST_AUTO_TEST_CASE(empty_test)
  {
    using e::vector;
    using e::vector_c;
    using e::empty_t;
    
    using T1 = vector<>;
    using T2 = vector_c<int>;
    
    BOOST_CHECK(empty_t<T1>::value);
    BOOST_CHECK(empty_t<T2>::value);
    
    using T3 = vector<vector<>>;
    using T4 = vector_c<int, 1, 2, 3>;
    
    BOOST_CHECK(empty_t<T3>::value == false);
    BOOST_CHECK(empty_t<T4>::value == false);
  }
  
  BOOST_AUTO_TEST_CASE(front_back_test)
  {
    using e::vector;
    using e::vector_c;
    using e::front;
    using e::front_t;
    using e::back;
    using e::back_t;
    
    using T1 = vector<int>;
    using T2 = vector<true_, false_>;
    using T3 = vector<true_, int, int, int, int, false_>;
    
    SAME_TYPE(front_t<T1>, int);
    SAME_TYPE(back_t<T1>, int);
    
    SAME_TYPE(front_t<T2>, true_);
    SAME_TYPE(back_t<T2>, false_);
    
    SAME_TYPE(front_t<T3>, true_);
    SAME_TYPE(back_t<T3>, false_);
  }
  
  BOOST_AUTO_TEST_CASE(at_test)
  {
    using e::vector;
    using e::vector_c;
    using e::at_t;
    
    using T1 = vector<int>;
    using T2 = vector<bool, char, short, int, long>;
    using T3 = vector_c<bool, true, false>;
    
    using AT_T1 = at_t<T1, int_<0>>;
    SAME_TYPE(AT_T1, int);
    
    
    using AT0_T2 = at_t<T2, int_<0>>;
    using AT1_T2 = at_t<T2, int_<1>>;
    using AT2_T2 = at_t<T2, int_<2>>;
    using AT3_T2 = at_t<T2, int_<3>>;
    using AT4_T2 = at_t<T2, int_<4>>;
    SAME_TYPE(AT0_T2, bool);
    SAME_TYPE(AT1_T2, char);
    SAME_TYPE(AT2_T2, short);
    SAME_TYPE(AT3_T2, int);
    SAME_TYPE(AT4_T2, long);
    
    using AT0_T3 = at_t<T3, int_<0>>;
    using AT1_T3 = at_t<T3, int_<1>>;
    SAME_TYPE(AT0_T3, true_);
    SAME_TYPE(AT1_T3, false_);
  }
  
  
  BOOST_AUTO_TEST_CASE(clear_test)
  {
    using e::vector;
    using e::vector_c;
    using e::clear_t;
    
    using T1 = vector<>;
    using T2 = vector_c<void>;
    using T3 = vector<int, void, true_>;
    using T4 = vector_c<int, 0>;
    
    SAME_TYPE(clear_t<T1>, vector<>);
    SAME_TYPE(clear_t<T2>, vector<>);
    SAME_TYPE(clear_t<T3>, vector<>);
    SAME_TYPE(clear_t<T4>, vector<>);
  }
  
  BOOST_AUTO_TEST_CASE(pop_push_front_test)
  {
    //TODO
    BOOST_CHECK(true);
  }
  
  BOOST_AUTO_TEST_CASE(pop_push_back_test)
  {
    //TODO
    BOOST_CHECK(true);
  }

BOOST_AUTO_TEST_SUITE_END()