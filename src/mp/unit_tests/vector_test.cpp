#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <elib/mp/vector.hpp>
#include <elib/mp/arg.hpp>
#include <elib/mp/iterator.hpp>
#include <elib/mp/sequence.hpp>
#include <elib/mp/sequence_traits.hpp>
#include "mp_test_helper.hpp"
#include <cstddef>


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


BOOST_AUTO_TEST_SUITE(mp_vector_test_suite)

  BOOST_AUTO_TEST_CASE(mp_vector_construction)
  {
    using T0 = vector<>;
    using C0 = vector_c<int>;
    SAME_TYPE(T0, C0);
    SAME_TYPE(typename T0::type, T0);
    
    using T1 = vector<size_type_<0>>;
    using C1 = vector_c<std::size_t, 0>;
    SAME_TYPE(T1, C1);
    SAME_TYPE(typename T1::type, T1);
    
    using T2 = vector<true_, false_>;
    using C2 = vector_c<bool, true, false>;
    SAME_TYPE(T2, C2);
    SAME_TYPE(typename T2::type, T2);
  }                                                   // mp_vector_construction

  BOOST_AUTO_TEST_CASE(mp_vector_intrinsics)
  {
    // empty
    {
      using T = vector<>;
      // observers
      CHECK(sequence_size_t<T>::value == 0);
      CHECK(empty_t<T>::value);
      SAME_TYPE(begin_t<T>, v_iter<T, 0>);
      SAME_TYPE(end_t<T>, v_iter<T, 0>);
      SAME_TYPE(begin_t<T>, end_t<T>);
      // modifiers
      SAME_TYPE(clear_t<T>, vector<>);
      SAME_TYPE(push_back_t<T, void>, back_item<void, T>);
      SAME_TYPE(push_front_t<T, void>, front_item<void, T>);
    }
    // size = 1
    {
      using T = vector<true_>;
      // observers
      CHECK(sequence_size_t<T>::value == 1);
      CHECK(empty_t<T>::value == false);
      SAME_TYPE(begin_t<T>, v_iter<T, 0>);
      SAME_TYPE(end_t<T>, v_iter<T, 1>);
      SAME_TYPE(front_t<T>, true_);
      SAME_TYPE(back_t<T>, true_);
      SAME_TYPE(at_t<T, int_<0>>, true_);
      SAME_TYPE(at_c_t<T, 0>, true_);
      // modifiers
      SAME_TYPE(clear_t<T>, vector<>);
      // push back
      using PushB = push_back_t<T, false_>;
      SAME_TYPE(PushB, back_item<false_, T>);
      SAME_TYPE(typename PushB::type, PushB);
      CHECK(sequence_size_t<PushB>::value == 2);
      SAME_TYPE(at_c_t<PushB, 0>, true_);
      SAME_TYPE(at_t<PushB, int_<1>>, false_);
      // pop back
      using PopB = pop_back_t<T>;
      SAME_TYPE(PopB, back_mask<T>);
      SAME_TYPE(typename PopB::type, PopB);
      CHECK(sequence_size_t<PopB>::value == 0);
      CHECK(empty_t<PopB>::value);
      // push front
      using PushF = push_front_t<T, false_>;
      SAME_TYPE(PushF, front_item<false_, T>);
      SAME_TYPE(typename PushF::type, PushF);
      CHECK(sequence_size_t<PushF>::value == 2);
      SAME_TYPE(at_c_t<PushF, 0>, false_);
      SAME_TYPE(at_t<PushF, int_<1>>, true_);
      // pop front
      using PopF = pop_front_t<T>;
      SAME_TYPE(PopF, front_mask<T>);
      SAME_TYPE(typename PopF::type, PopF);
      CHECK(sequence_size_t<PopF>::value == 0);
      CHECK(empty_t<PopF>::value);
    }
    // multi
    {
      using namespace elib::mp::placeholders;
      using T = vector<_1, _2, _3, _4>;
      // observers
      CHECK(sequence_size_t<T>::value == 4);
      CHECK(empty_t<T>::value == false);
      SAME_TYPE(begin_t<T>, v_iter<T, 0>);
      SAME_TYPE(end_t<T>, v_iter<T, 4>);
      SAME_TYPE(front_t<T>, _1);
      SAME_TYPE(back_t<T>, _4);
      SAME_TYPE(at_t<T, int_<0>>, _1);
      SAME_TYPE(at_c_t<T, 1>, _2);
      SAME_TYPE(at_c_t<T, 2>, _3);
      SAME_TYPE(at_t<T, int_<3>>, _4);
      // modifiers
      SAME_TYPE(clear_t<T>, vector<>);
      // push back
      using PushB = push_back_t<T, _5>;
      SAME_TYPE(PushB, back_item<_5, T>);
      SAME_TYPE(typename PushB::type, PushB);
      CHECK(sequence_size_t<PushB>::value == 5);
      SAME_TYPE(back_t<PushB>, _5);
      SAME_TYPE(front_t<PushB>, _1);
      SAME_TYPE(at_c_t<PushB, 4>, _5);
      SAME_TYPE(at_c_t<PushB, 3>, _4);
      SAME_TYPE(at_c_t<PushB, 0>, _1);
      // pop back
      using PopB = pop_back_t<T>;
      SAME_TYPE(PopB, back_mask<T>);
      SAME_TYPE(typename PopB::type, PopB);
      CHECK(sequence_size_t<PopB>::value == 3);
      SAME_TYPE(back_t<PopB>, _3);
      SAME_TYPE(front_t<PopB>, _1);
      SAME_TYPE(at_c_t<PopB, 0>, _1);
      SAME_TYPE(at_c_t<PopB, 1>, _2);
      SAME_TYPE(at_c_t<PopB, 2>, _3);
      // push front
      using PushF = push_front_t<T, void>;
      SAME_TYPE(PushF, front_item<void, T>);
      SAME_TYPE(typename PushF::type, PushF);
      CHECK(sequence_size_t<PushF>::value == 5);
      SAME_TYPE(front_t<PushF>, void);
      SAME_TYPE(back_t<PushF>, _4);
      SAME_TYPE(at_c_t<PushF, 0>, void);
      SAME_TYPE(at_c_t<PushF, 1>, _1);
      SAME_TYPE(at_c_t<PushF, 4>, _4);
      // pop front
      using PopF = pop_front_t<T>;
      SAME_TYPE(PopF, front_mask<T>);
      SAME_TYPE(typename PopF::type, PopF);
      CHECK(sequence_size_t<PopF>::value == 3);
      SAME_TYPE(front_t<PopF>, _2);
      SAME_TYPE(back_t<PopF>, _4);
      SAME_TYPE(at_c_t<PopF, 0>, _2);
      SAME_TYPE(at_c_t<PopF, 1>, _3);
      SAME_TYPE(at_c_t<PopF, 2>, _4);
    }
    // TODO insert & erase
  }                                                     // mp_vector_intrinsics
  
  
  BOOST_AUTO_TEST_CASE(mp_vector_iterator_intrinsics)
  {
    // model_type
    {
      using T = vector_c<bool, true, true, false>;
      using B = begin_t<T>;
      using E = end_t<T>;
      SAME_TYPE(typename B::model_type, model::default_random_access_iterator);
      SAME_TYPE(typename B::model_type, typename E::model_type);
    }
    // empty
    {
      using T = vector<>;
      using B = begin_t<T>;
      using E = end_t<T>;
      SAME_TYPE(B, v_iter<T, 0>);
      SAME_TYPE(E, v_iter<T, 0>);
      SAME_TYPE(B, E);
    }
    // one elem
    {
      using T = vector<void>;
      using B = begin_t<T>;
      using E = end_t<T>;
      SAME_TYPE(B, v_iter<T, 0>);
      SAME_TYPE(E, v_iter<T, 1>);
      // deref
      SAME_TYPE(deref_t<B>, void);
      // next_t & prior_t
      using B1 = next_t<B>;
      SAME_TYPE(B1, E);
      using E1 = prior_t<E>;
      SAME_TYPE(E1, B);
      SAME_TYPE(deref_t<E1>, void);
      // advance
      SAME_TYPE(advance_c_t<B, 0>, B);
      SAME_TYPE(advance_t<B, aux::long_<1>>, E);
      SAME_TYPE(advance_t<E, aux::long_<-1>>, B);
      // distance
      CHECK(distance_t<B, B>::value == 0);
      CHECK(distance_t<E, E>::value == 0);
      CHECK(distance_t<B, E>::value == 1);
      CHECK(distance_t<E, B>::value == -1);
    }
    // multi-elem
    {
      using namespace elib::mp::placeholders;
      using T = vector<_1, _2, _3>;
      using B = begin_t<T>;
      using E = end_t<T>;
      SAME_TYPE(B, v_iter<T, 0>);
      SAME_TYPE(E, v_iter<T, 3>);
      // deref & next
      SAME_TYPE(deref_t<B>, _1);
      using B1 = next_t<B>;
      SAME_TYPE(deref_t<B1>, _2);
      using B2 = next_t<B1>;
      SAME_TYPE(deref_t<B2>, _3);
      using B3 = next_t<B2>;
      SAME_TYPE(B3, E);
      // prior
      using E1 = prior_t<E>;
      SAME_TYPE(E1, B2);
      using E2 = prior_t<E1>;
      SAME_TYPE(E2, B1);
      using E3 = prior_t<E2>;
      SAME_TYPE(E3, B);
      // advance
      SAME_TYPE(advance_t<B, int_<2>>, B2);
      SAME_TYPE(advance_t<E, aux::long_<-3>>, B);
      SAME_TYPE(advance_c_t<E, -2>, B1);
      // distance
      CHECK(distance_t<B, E>::value == 3);
      CHECK(distance_t<E, B>::value == -3);
      CHECK(distance_t<B, E1>::value == 2);
    }
  }                                            // mp_vector_iterator_intrinsics
  
  
# define CHECK_TRAITS(...)                           \
  do {                                               \
    using T = __VA_ARGS__;                           \
    SAME_TYPE(typename T::class_type, vector_tag);   \
    SAME_TYPE(typename T::model_type, vector_model); \
  } while (false)
#
 
  BOOST_AUTO_TEST_CASE(mp_vector_sequence_traits)
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
      CHECK( is_sequence_t<T>() );
      CHECK( !is_variadic_t<T>() );
      CHECK( is_forward_sequence_t<T>() );
      CHECK( is_bidirectional_sequence_t<T>() );
      CHECK( is_random_access_sequence_t<T>() );
      CHECK( !is_associative_sequence_t<T>() );
      CHECK( is_front_extensible_sequence<T>() );
      CHECK( !is_front_extensible_variadic_sequence_t<T>() );
      CHECK( is_back_extensible_sequence<T>() );
      CHECK( !is_back_extensible_variadic_sequence_t<T>() );
      CHECK( !is_associative_extensible_sequence_t<T>() );
    }
  }
  
# undef CHECK_TRAITS
  
BOOST_AUTO_TEST_SUITE_END()