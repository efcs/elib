// REQUIRES: ELIB_MP_SOURCE, ELIB_BOOST_TEST
#define BOOST_TEST_MODULE Main
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <elib/mp/pack.hpp>
#include <elib/mp/arg.hpp>
#include <elib/mp/iterator.hpp>
#include <elib/mp/sequence.hpp>
#include <elib/mp/sequence_traits.hpp>
#include "mp_test_helper.hpp"
#include "test/helper.hpp"


template <class Pack, std::size_t N>
using p_iter = pack_iterator<Pack, N>;

BOOST_AUTO_TEST_SUITE(mp_pack_test_suite)


  BOOST_AUTO_TEST_CASE(mp_pack_construction)
  {
    using namespace elib::mp::placeholders;
    using T0 = pack<>;
    using C0 = pack_c<bool>;
    TEST_SAME_TYPE(T0, C0);
    TEST_SAME_TYPE(typename T0::type, T0);
    
    using T1 = pack<int_<1>>;
    using C1 = pack_c<int, 1>;
    TEST_SAME_TYPE(T1, C1);
    TEST_SAME_TYPE(typename T1::type, T1);
    
    using T2 = pack<true_, false_>;
    using C2 = pack_c<bool, true, false>;
    TEST_SAME_TYPE(T2, C2);
    TEST_SAME_TYPE(typename T2::type, T2);
  }                                                     // mp_pack_construction

  BOOST_AUTO_TEST_CASE(mp_pack_intrinsics)
  {
    // empty
    {
      using T = pack<>;
      // observers
      TEST_CHECK(sequence_size_t<T>::value == 0);
      TEST_CHECK(empty_t<T>::value);
      TEST_SAME_TYPE(begin_t<T>, pack_iterator<T, 0>);
      TEST_SAME_TYPE(end_t<T>, pack_iterator<T, 0>);
      // mutators
      TEST_SAME_TYPE(clear_t<T>, pack<>);
      TEST_SAME_TYPE(push_back_t<T, int>, pack<int>);
      TEST_SAME_TYPE(push_front_t<T, long>, pack<long>);
      TEST_SAME_TYPE(concat_t<T, pack<>>, pack<>);
      TEST_SAME_TYPE(concat_t<T, pack<bool>>, pack<bool>);
    }
    // single item
    {
      using T = pack<void>;
      // observers
      TEST_CHECK(sequence_size_t<T>::value == 1);
      TEST_CHECK(empty_t<T>::value == false);
      TEST_SAME_TYPE(begin_t<T>, pack_iterator<T, 0>);
      TEST_SAME_TYPE(end_t<T>, pack_iterator<T, 1>);
      TEST_SAME_TYPE(front_t<T>, void);
      TEST_SAME_TYPE(back_t<T>, void);
      // modifiers
      TEST_SAME_TYPE(clear_t<T>, pack<>);
      TEST_SAME_TYPE(push_back_t<T, bool>, pack<void, bool>);
      TEST_SAME_TYPE(pop_back_t<T>, pack<>);
      TEST_SAME_TYPE(push_front_t<T, bool>, pack<bool, void>);
      TEST_SAME_TYPE(pop_front_t<T>, pack<>);
      TEST_SAME_TYPE(drop_t<T, 0>, pack<void>);
      TEST_SAME_TYPE(drop_t<T, 1>, pack<>);
      TEST_SAME_TYPE(take_t<T, 0>, pack<>);
      TEST_SAME_TYPE(take_t<T, 1>, pack<void>);
      TEST_SAME_TYPE(slice_t<T, 0, 0>, pack<>);
      TEST_SAME_TYPE(slice_t<T, 0, 1>, pack<void>);
    }
    // two items
    {
      using T = pack<true_, false_>;
      // observers
      TEST_CHECK(sequence_size_t<T>::value == 2);
      TEST_CHECK(empty_t<T>::value == false);
      TEST_SAME_TYPE(begin_t<T>, pack_iterator<T, 0>);
      TEST_SAME_TYPE(end_t<T>, pack_iterator<T, 2>);
      TEST_SAME_TYPE(front_t<T>, true_);
      TEST_SAME_TYPE(back_t<T>, false_);
      // modifiers
      TEST_SAME_TYPE(clear_t<T>, pack<>);
      // push & pop back
      TEST_SAME_TYPE(push_back_t<T, void>, pack<true_, false_, void>);
      TEST_SAME_TYPE(pop_back_t<T>, pack<true_>);
      // push & pop front
      TEST_SAME_TYPE(push_front_t<T, void>, pack<void, true_, false_>);
      TEST_SAME_TYPE(pop_front_t<T>, pack<false_>);
      // drop
      TEST_SAME_TYPE(drop_t<T, 0>, pack<true_, false_>);
      TEST_SAME_TYPE(drop_t<T, 1>, pack<false_>);
      TEST_SAME_TYPE(drop_t<T, 2>, pack<>);
      // take
      TEST_SAME_TYPE(take_t<T, 0>, pack<>);
      TEST_SAME_TYPE(take_t<T, 1>, pack<true_>);
      TEST_SAME_TYPE(take_t<T, 2>, pack<true_, false_>);
      // slice
      TEST_SAME_TYPE(slice_t<T, 0, 0>, pack<>);
      TEST_SAME_TYPE(slice_t<T, 0, 1>, pack<true_>);
      TEST_SAME_TYPE(slice_t<T, 0, 2>, pack<true_, false_>);
      TEST_SAME_TYPE(slice_t<T, 1, 1>, pack<>);
      TEST_SAME_TYPE(slice_t<T, 1, 2>, pack<false_>);
    }
    // Multi-item
    {
      using T = pack<bool, char, short, int, long>;
      // observers
      TEST_CHECK(sequence_size_t<T>::value == 5);
      TEST_CHECK(empty_t<T>::value == false);
      TEST_SAME_TYPE(begin_t<T>, pack_iterator<T, 0>);
      TEST_SAME_TYPE(end_t<T>, pack_iterator<T, 5>);
      TEST_SAME_TYPE(front_t<T>, bool);
      TEST_SAME_TYPE(back_t<T>, long);
      // modifiers
      TEST_SAME_TYPE(clear_t<T>, pack<>);
      TEST_SAME_TYPE(push_back_t<T, void>, pack<bool, char, short, int, long, void>);
      TEST_SAME_TYPE(pop_back_t<T>, pack<bool, char, short, int>);
      TEST_SAME_TYPE(push_front_t<T, void>, pack<void, bool, char, short, int, long>);
      TEST_SAME_TYPE(pop_front_t<T>, pack<char, short, int, long>);
      // drop
      TEST_SAME_TYPE(drop_t<T, 0>, T);
      TEST_SAME_TYPE(drop_t<T, 1>, pop_front_t<T>);
      TEST_SAME_TYPE(drop_t<T, 2>, pack<short, int, long>);
      TEST_SAME_TYPE(drop_t<T, 3>, pack<int, long>);
      TEST_SAME_TYPE(drop_t<T, 4>, pack<long>);
      TEST_SAME_TYPE(drop_t<T, 5>, pack<>);
      // take
      TEST_SAME_TYPE(take_t<T, 0>, pack<>);
      TEST_SAME_TYPE(take_t<T, 1>, pack<bool>);
      TEST_SAME_TYPE(take_t<T, 2>, pack<bool, char>);
      TEST_SAME_TYPE(take_t<T, 3>, pack<bool, char, short>);
      TEST_SAME_TYPE(take_t<T, 4>, pack<bool, char, short, int>);
      TEST_SAME_TYPE(take_t<T, 5>, T);
      // slice
      TEST_SAME_TYPE(slice_t<T, 0, 0>, pack<>);
      TEST_SAME_TYPE(slice_t<T, 0, 2>, pack<bool, char>);
      TEST_SAME_TYPE(slice_t<T, 3, 5>, pack<int, long>);
      TEST_SAME_TYPE(slice_t<T, 0, 5>, T);
    }
    // TODO insert and erase tests
  }                                                       // mp_pack_intrinsics

  BOOST_AUTO_TEST_CASE(mp_pack_iterator_intrinsics)
  {
    // model_type test
    {
      using T = pack<int, long, char>;
      using B = begin_t<T>;
      using E = end_t<T>;
      TEST_SAME_TYPE(typename B::model_type, model::default_random_access_iterator);
      TEST_SAME_TYPE(typename B::model_type, typename E::model_type);
    }
    // empty
    {
      using T = pack<>;
      using Begin = begin_t<T>;
      using End = end_t<T>;
      
      TEST_SAME_TYPE(Begin, p_iter<T, 0>);
      TEST_SAME_TYPE(Begin, p_iter<T, 0>);
      TEST_SAME_TYPE(Begin, End);
    }
    // size = 1
    {
      using T = pack<int>;
      using Begin = begin_t<T>;
      using End = end_t<T>;
      
      TEST_SAME_TYPE(Begin, p_iter<T, 0>);
      TEST_SAME_TYPE(End, p_iter<T, 1>);
      // deref
      TEST_SAME_TYPE(deref_t<Begin>, int);
      // next & prior
      TEST_SAME_TYPE(next_t<Begin>, End);
      TEST_SAME_TYPE(prior_t<End>, Begin);
      // advance & advance_c
      TEST_SAME_TYPE(advance_t<Begin, aux::long_<0>>, Begin);
      TEST_SAME_TYPE(advance_t<Begin, aux::long_<1>>, End);
      TEST_SAME_TYPE(advance_t<End, aux::long_<0>>, End);
      TEST_SAME_TYPE(advance_t<End, aux::long_<-1>>, Begin);
      TEST_SAME_TYPE(advance_c_t<Begin, 0>, Begin);
      TEST_SAME_TYPE(advance_c_t<Begin, 1>, End);
      TEST_SAME_TYPE(advance_c_t<End, 0>, End);
      TEST_SAME_TYPE(advance_c_t<End, -1>, Begin);
      // distance
      TEST_CHECK(distance_t<Begin, End>::value == 1);
      TEST_CHECK(distance_t<End, Begin>::value == -1);
      TEST_CHECK(distance_t<Begin, Begin>::value == 0);
      TEST_CHECK(distance_t<End, End>::value == 0);
    }
    // other sizes
    {
      using namespace elib::mp::placeholders;
      using T = pack<_1, _2, _3, _4>;
      using B = begin_t<T>;
      using E = end_t<T>;
      // begin & end
      TEST_SAME_TYPE(B, p_iter<T, 0>);
      TEST_SAME_TYPE(E, p_iter<T, 4>);
      // next & deref
      TEST_SAME_TYPE(deref_t<B>, _1);
      using N1 = next_t<B>;
      TEST_SAME_TYPE(N1, p_iter<T, 1>);
      TEST_SAME_TYPE(deref_t<N1>, _2);
      using N2 = next_t<N1>;
      TEST_SAME_TYPE(N2, p_iter<T, 2>);
      TEST_SAME_TYPE(deref_t<N2>, _3);
      using N3 = next_t<N2>;
      TEST_SAME_TYPE(N3, p_iter<T, 3>);
      TEST_SAME_TYPE(deref_t<N3>, _4);
      using N4 = next_t<N3>;
      TEST_SAME_TYPE(N4, p_iter<T, 4>);
      TEST_SAME_TYPE(N4, E);
      // prior
      using P1 = prior_t<E>;
      TEST_SAME_TYPE(P1, N3);
      using P2 = prior_t<P1>;
      TEST_SAME_TYPE(P2, N2);
      using P3 = prior_t<P2>;
      TEST_SAME_TYPE(P3, N1);
      using P4 = prior_t<P3>;
      TEST_SAME_TYPE(P4, B);
      // advance
      TEST_SAME_TYPE(B, advance_t<B, aux::long_<0>>);
      TEST_SAME_TYPE(next_t<B>, advance_c_t<B, 1>);
      TEST_SAME_TYPE(advance_t<B, aux::long_<4>>, E);
      TEST_SAME_TYPE(advance_c_t<E, -4>, B);
      TEST_SAME_TYPE(advance_t<E, aux::long_<-1>>, advance_c_t<B, 3>);
    }
  }                                              // mp_pack_iterator_intrinsics
  
  
#define TEST_CHECK_TRAITS(...)                           \
  do {                                              \
    using T = __VA_ARGS__;                          \
    TEST_SAME_TYPE( typename T::class_type, pack_tag );  \
    TEST_SAME_TYPE( typename T::model_type, pack_model); \
  } while (false)
#
  
  BOOST_AUTO_TEST_CASE(mp_pack_sequence_traits)
  {
    // empty
    TEST_CHECK_TRAITS( pack<> );
    // non-empty
    TEST_CHECK_TRAITS( pack<int> );
    // all 
    {
      using T = pack<>;
      TEST_CHECK( is_sequence_t<T>() );
      TEST_CHECK( is_variadic_t<T>() );
      TEST_CHECK( is_forward_sequence_t<T>() );
      TEST_CHECK( is_bidirectional_sequence_t<T>() );
      TEST_CHECK( is_random_access_sequence_t<T>() );
      TEST_CHECK( !is_associative_sequence_t<T>() );
      TEST_CHECK( is_front_extensible_sequence<T>() );
      TEST_CHECK( is_front_extensible_variadic_sequence_t<T>() );
      TEST_CHECK( is_back_extensible_sequence<T>() );
      TEST_CHECK( is_back_extensible_variadic_sequence_t<T>() );
      TEST_CHECK( !is_associative_extensible_sequence_t<T>() );
    }
  }                                                  // mp_pack_sequence_traits
  
#undef TEST_CHECK_TRAITS

  
BOOST_AUTO_TEST_SUITE_END()