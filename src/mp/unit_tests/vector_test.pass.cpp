// REQUIRES: ELIB_MP_SOURCE
#include <elib/mp/vector.hpp>
#include <elib/mp/arg.hpp>
#include <elib/mp/iterator.hpp>
#include <elib/mp/sequence.hpp>
#include <elib/mp/sequence_traits.hpp>
#include <elib/aux/integral_constant.hpp>
#include <cstddef>
#include "rapid-cxx-test.hpp"

using namespace elib;
using namespace elib::mp;


template <class T, class V>
using front_item = detail::vector_item<detail::vector_front_tag, T, V>;

template <class T, class V>
using back_item = detail::vector_item<detail::vector_back_tag, T, V>;

template <class V>
using front_mask = detail::vector_mask<detail::vector_front_tag, V>;

template <class V>
using back_mask = detail::vector_mask<detail::vector_back_tag, V>;

template <class Vector, std::size_t N>
using v_iter = vector_iterator<Vector, N>;


TEST_SUITE(mp_vector_test_suite)

  TEST_CASE(mp_vector_construction)
  {
    using T0 = vector<>;
    using C0 = vector_c<int>;
    TEST_SAME_TYPE(T0, C0);
    TEST_SAME_TYPE(typename T0::type, T0);
    
    using T1 = vector<size_type_<0>>;
    using C1 = vector_c<std::size_t, 0>;
    TEST_SAME_TYPE(T1, C1);
    TEST_SAME_TYPE(typename T1::type, T1);
    
    using T2 = vector<true_, false_>;
    using C2 = vector_c<bool, true, false>;
    TEST_SAME_TYPE(T2, C2);
    TEST_SAME_TYPE(typename T2::type, T2);
  }                                                   // mp_vector_construction

  TEST_CASE(mp_vector_intrinsics)
  {
    // empty
    {
      using T = vector<>;
      // observers
      TEST_CHECK(sequence_size_t<T>::value == 0);
      TEST_CHECK(empty_t<T>::value);
      TEST_SAME_TYPE(begin_t<T>, v_iter<T, 0>);
      TEST_SAME_TYPE(end_t<T>, v_iter<T, 0>);
      TEST_SAME_TYPE(begin_t<T>, end_t<T>);
      // modifiers
      TEST_SAME_TYPE(clear_t<T>, vector<>);
      TEST_SAME_TYPE(push_back_t<T, void>, back_item<void, T>);
      TEST_SAME_TYPE(push_front_t<T, void>, front_item<void, T>);
    }
    // size = 1
    {
      using T = vector<true_>;
      // observers
      TEST_CHECK(sequence_size_t<T>::value == 1);
      TEST_CHECK(empty_t<T>::value == false);
      TEST_SAME_TYPE(begin_t<T>, v_iter<T, 0>);
      TEST_SAME_TYPE(end_t<T>, v_iter<T, 1>);
      TEST_SAME_TYPE(front_t<T>, true_);
      TEST_SAME_TYPE(back_t<T>, true_);
      TEST_SAME_TYPE(at_t<T, int_<0>>, true_);
      TEST_SAME_TYPE(at_c_t<T, 0>, true_);
      // modifiers
      TEST_SAME_TYPE(clear_t<T>, vector<>);
      // push back
      using PushB = push_back_t<T, false_>;
      TEST_SAME_TYPE(PushB, back_item<false_, T>);
      TEST_SAME_TYPE(typename PushB::type, PushB);
      TEST_CHECK(sequence_size_t<PushB>::value == 2);
      TEST_SAME_TYPE(at_c_t<PushB, 0>, true_);
      TEST_SAME_TYPE(at_t<PushB, int_<1>>, false_);
      // pop back
      using PopB = pop_back_t<T>;
      TEST_SAME_TYPE(PopB, back_mask<T>);
      TEST_SAME_TYPE(typename PopB::type, PopB);
      TEST_CHECK(sequence_size_t<PopB>::value == 0);
      TEST_CHECK(empty_t<PopB>::value);
      // push front
      using PushF = push_front_t<T, false_>;
      TEST_SAME_TYPE(PushF, front_item<false_, T>);
      TEST_SAME_TYPE(typename PushF::type, PushF);
      TEST_CHECK(sequence_size_t<PushF>::value == 2);
      TEST_SAME_TYPE(at_c_t<PushF, 0>, false_);
      TEST_SAME_TYPE(at_t<PushF, int_<1>>, true_);
      // pop front
      using PopF = pop_front_t<T>;
      TEST_SAME_TYPE(PopF, front_mask<T>);
      TEST_SAME_TYPE(typename PopF::type, PopF);
      TEST_CHECK(sequence_size_t<PopF>::value == 0);
      TEST_CHECK(empty_t<PopF>::value);
    }
    // multi
    {
      using namespace elib::mp::placeholders;
      using T = vector<_1, _2, _3, _4>;
      // observers
      TEST_CHECK(sequence_size_t<T>::value == 4);
      TEST_CHECK(empty_t<T>::value == false);
      TEST_SAME_TYPE(begin_t<T>, v_iter<T, 0>);
      TEST_SAME_TYPE(end_t<T>, v_iter<T, 4>);
      TEST_SAME_TYPE(front_t<T>, _1);
      TEST_SAME_TYPE(back_t<T>, _4);
      TEST_SAME_TYPE(at_t<T, int_<0>>, _1);
      TEST_SAME_TYPE(at_c_t<T, 1>, _2);
      TEST_SAME_TYPE(at_c_t<T, 2>, _3);
      TEST_SAME_TYPE(at_t<T, int_<3>>, _4);
      // modifiers
      TEST_SAME_TYPE(clear_t<T>, vector<>);
      // push back
      using PushB = push_back_t<T, _5>;
      TEST_SAME_TYPE(PushB, back_item<_5, T>);
      TEST_SAME_TYPE(typename PushB::type, PushB);
      TEST_CHECK(sequence_size_t<PushB>::value == 5);
      TEST_SAME_TYPE(back_t<PushB>, _5);
      TEST_SAME_TYPE(front_t<PushB>, _1);
      TEST_SAME_TYPE(at_c_t<PushB, 4>, _5);
      TEST_SAME_TYPE(at_c_t<PushB, 3>, _4);
      TEST_SAME_TYPE(at_c_t<PushB, 0>, _1);
      // pop back
      using PopB = pop_back_t<T>;
      TEST_SAME_TYPE(PopB, back_mask<T>);
      TEST_SAME_TYPE(typename PopB::type, PopB);
      TEST_CHECK(sequence_size_t<PopB>::value == 3);
      TEST_SAME_TYPE(back_t<PopB>, _3);
      TEST_SAME_TYPE(front_t<PopB>, _1);
      TEST_SAME_TYPE(at_c_t<PopB, 0>, _1);
      TEST_SAME_TYPE(at_c_t<PopB, 1>, _2);
      TEST_SAME_TYPE(at_c_t<PopB, 2>, _3);
      // push front
      using PushF = push_front_t<T, void>;
      TEST_SAME_TYPE(PushF, front_item<void, T>);
      TEST_SAME_TYPE(typename PushF::type, PushF);
      TEST_CHECK(sequence_size_t<PushF>::value == 5);
      TEST_SAME_TYPE(front_t<PushF>, void);
      TEST_SAME_TYPE(back_t<PushF>, _4);
      TEST_SAME_TYPE(at_c_t<PushF, 0>, void);
      TEST_SAME_TYPE(at_c_t<PushF, 1>, _1);
      TEST_SAME_TYPE(at_c_t<PushF, 4>, _4);
      // pop front
      using PopF = pop_front_t<T>;
      TEST_SAME_TYPE(PopF, front_mask<T>);
      TEST_SAME_TYPE(typename PopF::type, PopF);
      TEST_CHECK(sequence_size_t<PopF>::value == 3);
      TEST_SAME_TYPE(front_t<PopF>, _2);
      TEST_SAME_TYPE(back_t<PopF>, _4);
      TEST_SAME_TYPE(at_c_t<PopF, 0>, _2);
      TEST_SAME_TYPE(at_c_t<PopF, 1>, _3);
      TEST_SAME_TYPE(at_c_t<PopF, 2>, _4);
    }
    // TODO insert & erase
  }                                                     // mp_vector_intrinsics
  
  
  TEST_CASE(mp_vector_iterator_intrinsics)
  {
    // model_type
    {
      using T = vector_c<bool, true, true, false>;
      using B = begin_t<T>;
      using E = end_t<T>;
      TEST_SAME_TYPE(typename B::model_type, model::default_random_access_iterator);
      TEST_SAME_TYPE(typename B::model_type, typename E::model_type);
    }
    // empty
    {
      using T = vector<>;
      using B = begin_t<T>;
      using E = end_t<T>;
      TEST_SAME_TYPE(B, v_iter<T, 0>);
      TEST_SAME_TYPE(E, v_iter<T, 0>);
      TEST_SAME_TYPE(B, E);
    }
    // one elem
    {
      using T = vector<void>;
      using B = begin_t<T>;
      using E = end_t<T>;
      TEST_SAME_TYPE(B, v_iter<T, 0>);
      TEST_SAME_TYPE(E, v_iter<T, 1>);
      // deref
      TEST_SAME_TYPE(deref_t<B>, void);
      // next_t & prior_t
      using B1 = next_t<B>;
      TEST_SAME_TYPE(B1, E);
      using E1 = prior_t<E>;
      TEST_SAME_TYPE(E1, B);
      TEST_SAME_TYPE(deref_t<E1>, void);
      // advance
      TEST_SAME_TYPE(advance_c_t<B, 0>, B);
      TEST_SAME_TYPE(advance_t<B, aux::long_<1>>, E);
      TEST_SAME_TYPE(advance_t<E, aux::long_<-1>>, B);
      // distance
      TEST_CHECK(distance_t<B, B>::value == 0);
      TEST_CHECK(distance_t<E, E>::value == 0);
      TEST_CHECK(distance_t<B, E>::value == 1);
      TEST_CHECK(distance_t<E, B>::value == -1);
    }
    // multi-elem
    {
      using namespace elib::mp::placeholders;
      using T = vector<_1, _2, _3>;
      using B = begin_t<T>;
      using E = end_t<T>;
      TEST_SAME_TYPE(B, v_iter<T, 0>);
      TEST_SAME_TYPE(E, v_iter<T, 3>);
      // deref & next
      TEST_SAME_TYPE(deref_t<B>, _1);
      using B1 = next_t<B>;
      TEST_SAME_TYPE(deref_t<B1>, _2);
      using B2 = next_t<B1>;
      TEST_SAME_TYPE(deref_t<B2>, _3);
      using B3 = next_t<B2>;
      TEST_SAME_TYPE(B3, E);
      // prior
      using E1 = prior_t<E>;
      TEST_SAME_TYPE(E1, B2);
      using E2 = prior_t<E1>;
      TEST_SAME_TYPE(E2, B1);
      using E3 = prior_t<E2>;
      TEST_SAME_TYPE(E3, B);
      // advance
      TEST_SAME_TYPE(advance_t<B, int_<2>>, B2);
      TEST_SAME_TYPE(advance_t<E, aux::long_<-3>>, B);
      TEST_SAME_TYPE(advance_c_t<E, -2>, B1);
      // distance
      TEST_CHECK(distance_t<B, E>::value == 3);
      TEST_CHECK(distance_t<E, B>::value == -3);
      TEST_CHECK(distance_t<B, E1>::value == 2);
    }
  }                                            // mp_vector_iterator_intrinsics
  
  
# define CHECK_TRAITS(...)                           \
  do {                                               \
    using T = __VA_ARGS__;                           \
    TEST_SAME_TYPE(typename T::class_type, vector_tag);   \
    TEST_SAME_TYPE(typename T::model_type, vector_model); \
  } while (false)
#
 
  TEST_CASE(mp_vector_sequence_traits)
  {
    // empty
    CHECK_TRAITS(vector<>);
    // 1 elem
    CHECK_TRAITS(vector<void>);
    // vector_item
    CHECK_TRAITS(push_front_t<vector<>, void>);
    // vector_mask
    CHECK_TRAITS(pop_front_t<vector<void, int>>);
    // all 
    {
      using T = vector<>;
      TEST_CHECK( is_sequence_t<T>() );
      TEST_CHECK( !is_variadic_t<T>() );
      TEST_CHECK( is_forward_sequence_t<T>() );
      TEST_CHECK( is_bidirectional_sequence_t<T>() );
      TEST_CHECK( is_random_access_sequence_t<T>() );
      TEST_CHECK( !is_associative_sequence_t<T>() );
      TEST_CHECK( is_front_extensible_sequence<T>() );
      TEST_CHECK( !is_front_extensible_variadic_sequence_t<T>() );
      TEST_CHECK( is_back_extensible_sequence<T>() );
      TEST_CHECK( !is_back_extensible_variadic_sequence_t<T>() );
      TEST_CHECK( !is_associative_extensible_sequence_t<T>() );
    }
  }
  
# undef CHECK_TRAITS
  
TEST_SUITE_END()