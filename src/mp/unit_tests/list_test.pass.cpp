// REQUIRES: ELIB_MP_SOURCE
#include <elib/mp/list.hpp>
#include <elib/mp/arg.hpp>
#include <elib/mp/iterator.hpp>
#include <elib/aux/integral_constant.hpp>
#include "rapid-cxx-test.hpp"

using namespace elib;
using namespace elib::mp;

using aux::long_;

template <class ...Args>
using l_iter = list_iterator<Args...>;

TEST_SUITE(mp_list_test_suite)

  TEST_CASE(mp_list_construction)
  {
    using T0 = list<>;
    using C0 = list_c<int>;
    TEST_SAME_TYPE(T0, C0);
    TEST_SAME_TYPE(typename T0::type, T0);
    
    using T1 = list<int_<0>>;
    using C1 = list_c<int, 0>;
    TEST_SAME_TYPE(T1, C1);
    TEST_SAME_TYPE(typename T1::type, T1);
    
    using T2 = list<true_, false_>;
    using C2 = list_c<bool, true, false>;
    TEST_SAME_TYPE(T2, C2);
    TEST_SAME_TYPE(typename T2::type, T2);
  }                                                     // mp_list_construction
  

  TEST_CASE(mp_list_intrinsics)
  {
    // empty
    {
      using T = list<>;
      // observers
      TEST_CHECK(sequence_size_t<T>::value == 0);
      TEST_CHECK(empty_t<T>::value);
      TEST_SAME_TYPE(begin_t<T>, l_iter<>);
      TEST_SAME_TYPE(end_t<T>, l_iter<>);
      TEST_SAME_TYPE(begin_t<T>, end_t<T>);
      // modifiers
      TEST_SAME_TYPE(clear_t<T>, list<>);
      TEST_SAME_TYPE(push_front_t<T, int>, list<int>);
    }
    // one item
    {
      using T = list<void>;
      // observers
      TEST_CHECK(sequence_size_t<T>::value == 1);
      TEST_CHECK(empty_t<T>::value == false);
      TEST_SAME_TYPE(begin_t<T>, l_iter<void>);
      TEST_SAME_TYPE(end_t<T>, l_iter<>);
      TEST_SAME_TYPE(front_t<T>, void);
      // modifiers
      TEST_SAME_TYPE(clear_t<T>, list<>);
      TEST_SAME_TYPE(push_front_t<T, int>, list<int, void>);
      TEST_SAME_TYPE(pop_front_t<T>, list<>);
    }
    // multi item
    {
      using namespace elib::mp::placeholders;
      using T = list<_1, _2, _3, _4, _5>;
      // observers
      TEST_CHECK(sequence_size_t<T>::value == 5);
      TEST_CHECK(empty_t<T>::value == false);
      TEST_SAME_TYPE(begin_t<T>, l_iter<_1, _2, _3, _4, _5>);
      TEST_SAME_TYPE(end_t<T>, l_iter<>);
      TEST_SAME_TYPE(front_t<T>, _1);
      // modifiers
      TEST_SAME_TYPE(clear_t<T>, list<>);
      TEST_SAME_TYPE(push_front_t<T, void>, list<void, _1, _2, _3, _4, _5>);
      TEST_SAME_TYPE(pop_front_t<T>, list<_2, _3, _4, _5>);
    }
    // TODO insert & erase
  }                                                      // mp_list_intrinsics

  
  TEST_CASE(mp_list_iterator_intrinsics)
  {
    // model_of
    {
      using T = list_c<int, 1, 2, 3>;
      using B = begin_t<T>;
      using E = end_t<T>;
      TEST_SAME_TYPE(typename B::model_type, model::forward_iterator);
      TEST_SAME_TYPE(typename B::model_type, typename E::model_type);
    }
    // empty
    {
      using T = list<>;
      using B = begin_t<T>;
      using E = end_t<T>;
      
      TEST_SAME_TYPE(B, l_iter<>);
      TEST_SAME_TYPE(E, l_iter<>);
      TEST_SAME_TYPE(B, E);
      
      TEST_CHECK(distance_t<B, E>::value == 0);
    }
    // size = 1
    {
      using T = list_c<bool, true>;
      using B = begin_t<T>;
      using E = end_t<T>;
      TEST_SAME_TYPE(B, l_iter<true_>);
      TEST_SAME_TYPE(E, l_iter<>);
      // deref
      TEST_SAME_TYPE(deref_t<B>, true_);
      // next
      TEST_SAME_TYPE(next_t<B>, E);
      // advance
      TEST_SAME_TYPE(advance_t<B, long_<0>>, B);
      TEST_SAME_TYPE(advance_c_t<B, 1>, E);
      TEST_SAME_TYPE(advance_c_t<E, 0>, E);
      // distance
      TEST_CHECK(distance_t<B, B>::value == 0);
      TEST_CHECK(distance_t<E, E>::value == 0);
      TEST_CHECK(distance_t<B, E>::value == 1);
      TEST_CHECK(distance_t<E, B>::value == -1);
    }
    // multi
    {
      using namespace elib::mp::placeholders;
      using T = list<_1, _2, _3>;
      using B = begin_t<T>;
      using E = end_t<T>;
      TEST_SAME_TYPE(B, l_iter<_1, _2, _3>);
      TEST_SAME_TYPE(E, l_iter<>);
      // deref and next
      TEST_SAME_TYPE(deref_t<B>, _1);
      using B1 = next_t<B>;
      TEST_SAME_TYPE(B1, l_iter<_2, _3>);
      TEST_SAME_TYPE(deref_t<B1>, _2);
      using B2 = next_t<B1>;
      TEST_SAME_TYPE(B2, l_iter<_3>);
      TEST_SAME_TYPE(deref_t<B2>, _3);
      using B3 = next_t<B2>;
      TEST_SAME_TYPE(B3, E);
      // advance
      TEST_SAME_TYPE(advance_t<B, long_<0>>, B);
      TEST_SAME_TYPE(advance_c_t<B, 1>, B1);
      TEST_SAME_TYPE(advance_t<B1, long_<2>>, B3);
      // distance
      TEST_CHECK(distance_t<B, E>::value == 3);
      TEST_CHECK(distance_t<B1, B2>::value == 1);
      TEST_CHECK(distance_t<B3, B1>::value == -2);
      TEST_CHECK(distance_t<B, B>::value == 0);
    }
  }                                              // mp_list_iterator_intrinsics
  
    
#define CHECK_TRAITS(...)                                        \
  do {                                                           \
    using T = __VA_ARGS__;                                       \
    TEST_SAME_TYPE( typename T::class_type, list_tag );               \
    TEST_SAME_TYPE( typename T::model_type, list_model);              \
  } while (false)
  
  TEST_CASE(mp_list_sequence_traits)
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
      TEST_CHECK( is_sequence_t<T>() );
      TEST_CHECK( is_variadic_t<T>() );
      TEST_CHECK( is_forward_sequence_t<T>() );
      TEST_CHECK( !is_bidirectional_sequence_t<T>() );
      TEST_CHECK( !is_random_access_sequence_t<T>() );
      TEST_CHECK( !is_associative_sequence_t<T>() );
      TEST_CHECK( is_front_extensible_sequence<T>() );
      TEST_CHECK( is_front_extensible_variadic_sequence_t<T>() );
      TEST_CHECK( !is_back_extensible_sequence<T>() );
      TEST_CHECK( !is_back_extensible_variadic_sequence_t<T>() );
      TEST_CHECK( !is_associative_extensible_sequence_t<T>() );
    }
  }                                                  // mp_list_sequence_traits
  
#undef CHECK_TRAITS
  
  
TEST_SUITE_END()