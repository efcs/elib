// REQUIRES: ELIB_MP_SOURCE, ELIB_BOOST_TEST
#define BOOST_TEST_MODULE Main
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <elib/mp/list.hpp>
#include <elib/mp/arg.hpp>
#include <elib/mp/iterator.hpp>
#include "mp_test_helper.hpp"

using aux::long_;

template <class ...Args>
using l_iter = list_iterator<Args...>;

BOOST_AUTO_TEST_SUITE(mp_list_test_suite)

  BOOST_AUTO_TEST_CASE(mp_list_construction)
  {
    using T0 = list<>;
    using C0 = list_c<int>;
    SAME_TYPE(T0, C0);
    SAME_TYPE(typename T0::type, T0);
    
    using T1 = list<int_<0>>;
    using C1 = list_c<int, 0>;
    SAME_TYPE(T1, C1);
    SAME_TYPE(typename T1::type, T1);
    
    using T2 = list<true_, false_>;
    using C2 = list_c<bool, true, false>;
    SAME_TYPE(T2, C2);
    SAME_TYPE(typename T2::type, T2);
  }                                                     // mp_list_construction
  

  BOOST_AUTO_TEST_CASE(mp_list_intrinsics)
  {
    // empty
    {
      using T = list<>;
      // observers
      CHECK(sequence_size_t<T>::value == 0);
      CHECK(empty_t<T>::value);
      SAME_TYPE(begin_t<T>, l_iter<>);
      SAME_TYPE(end_t<T>, l_iter<>);
      SAME_TYPE(begin_t<T>, end_t<T>);
      // modifiers
      SAME_TYPE(clear_t<T>, list<>);
      SAME_TYPE(push_front_t<T, int>, list<int>);
    }
    // one item
    {
      using T = list<void>;
      // observers
      CHECK(sequence_size_t<T>::value == 1);
      CHECK(empty_t<T>::value == false);
      SAME_TYPE(begin_t<T>, l_iter<void>);
      SAME_TYPE(end_t<T>, l_iter<>);
      SAME_TYPE(front_t<T>, void);
      // modifiers
      SAME_TYPE(clear_t<T>, list<>);
      SAME_TYPE(push_front_t<T, int>, list<int, void>);
      SAME_TYPE(pop_front_t<T>, list<>);
    }
    // multi item
    {
      using namespace elib::mp::placeholders;
      using T = list<_1, _2, _3, _4, _5>;
      // observers
      CHECK(sequence_size_t<T>::value == 5);
      CHECK(empty_t<T>::value == false);
      SAME_TYPE(begin_t<T>, l_iter<_1, _2, _3, _4, _5>);
      SAME_TYPE(end_t<T>, l_iter<>);
      SAME_TYPE(front_t<T>, _1);
      // modifiers
      SAME_TYPE(clear_t<T>, list<>);
      SAME_TYPE(push_front_t<T, void>, list<void, _1, _2, _3, _4, _5>);
      SAME_TYPE(pop_front_t<T>, list<_2, _3, _4, _5>);
    }
    // TODO insert & erase
  }                                                      // mp_list_intrinsics

  
  BOOST_AUTO_TEST_CASE(mp_list_iterator_intrinsics)
  {
    // model_of
    {
      using T = list_c<int, 1, 2, 3>;
      using B = begin_t<T>;
      using E = end_t<T>;
      SAME_TYPE(typename B::model_type, model::forward_iterator);
      SAME_TYPE(typename B::model_type, typename E::model_type);
    }
    // empty
    {
      using T = list<>;
      using B = begin_t<T>;
      using E = end_t<T>;
      
      SAME_TYPE(B, l_iter<>);
      SAME_TYPE(E, l_iter<>);
      SAME_TYPE(B, E);
      
      CHECK(distance_t<B, E>::value == 0);
    }
    // size = 1
    {
      using T = list_c<bool, true>;
      using B = begin_t<T>;
      using E = end_t<T>;
      SAME_TYPE(B, l_iter<true_>);
      SAME_TYPE(E, l_iter<>);
      // deref
      SAME_TYPE(deref_t<B>, true_);
      // next
      SAME_TYPE(next_t<B>, E);
      // advance
      SAME_TYPE(advance_t<B, long_<0>>, B);
      SAME_TYPE(advance_c_t<B, 1>, E);
      SAME_TYPE(advance_c_t<E, 0>, E);
      // distance
      CHECK(distance_t<B, B>::value == 0);
      CHECK(distance_t<E, E>::value == 0);
      CHECK(distance_t<B, E>::value == 1);
      CHECK(distance_t<E, B>::value == -1);
    }
    // multi
    {
      using namespace elib::mp::placeholders;
      using T = list<_1, _2, _3>;
      using B = begin_t<T>;
      using E = end_t<T>;
      SAME_TYPE(B, l_iter<_1, _2, _3>);
      SAME_TYPE(E, l_iter<>);
      // deref and next
      SAME_TYPE(deref_t<B>, _1);
      using B1 = next_t<B>;
      SAME_TYPE(B1, l_iter<_2, _3>);
      SAME_TYPE(deref_t<B1>, _2);
      using B2 = next_t<B1>;
      SAME_TYPE(B2, l_iter<_3>);
      SAME_TYPE(deref_t<B2>, _3);
      using B3 = next_t<B2>;
      SAME_TYPE(B3, E);
      // advance
      SAME_TYPE(advance_t<B, long_<0>>, B);
      SAME_TYPE(advance_c_t<B, 1>, B1);
      SAME_TYPE(advance_t<B1, long_<2>>, B3);
      // distance
      CHECK(distance_t<B, E>::value == 3);
      CHECK(distance_t<B1, B2>::value == 1);
      CHECK(distance_t<B3, B1>::value == -2);
      CHECK(distance_t<B, B>::value == 0);
    }
  }                                              // mp_list_iterator_intrinsics
  
    
#define CHECK_TRAITS(...)                                        \
  do {                                                           \
    using T = __VA_ARGS__;                                       \
    SAME_TYPE( typename T::class_type, list_tag );               \
    SAME_TYPE( typename T::model_type, list_model);              \
  } while (false)
  
  BOOST_AUTO_TEST_CASE(mp_list_sequence_traits)
  {
    // empty
    CHECK_TRAITS(list<>);
    // one elem
    CHECK_TRAITS(list<int>);
    // after insert
    CHECK_TRAITS(push_front_t<list<void>, int>);
    // after erase
    CHECK_TRAITS( pop_front_t<list<int>> );
    // all 
    {
      using T = list<>;
      CHECK( is_sequence_t<T>() );
      CHECK( is_variadic_t<T>() );
      CHECK( is_forward_sequence_t<T>() );
      CHECK( !is_bidirectional_sequence_t<T>() );
      CHECK( !is_random_access_sequence_t<T>() );
      CHECK( !is_associative_sequence_t<T>() );
      CHECK( is_front_extensible_sequence<T>() );
      CHECK( is_front_extensible_variadic_sequence_t<T>() );
      CHECK( !is_back_extensible_sequence<T>() );
      CHECK( !is_back_extensible_variadic_sequence_t<T>() );
      CHECK( !is_associative_extensible_sequence_t<T>() );
    }
  }                                                  // mp_list_sequence_traits
  
#undef CHECK_TRAITS
  
  
BOOST_AUTO_TEST_SUITE_END()