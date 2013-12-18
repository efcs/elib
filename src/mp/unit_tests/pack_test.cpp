#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <elib/mp/pack.hpp>
#include <elib/mp/arg.hpp>
#include <elib/mp/iterator.hpp>
#include "mp_test_helper.hpp"


template <class Pack, std::size_t N>
using p_iter = pack_iterator<Pack, N>;

BOOST_AUTO_TEST_SUITE(mp_pack_test_suite)


  BOOST_AUTO_TEST_CASE(mp_pack_construction)
  {
    using namespace elib::mp::placeholders;
    using T0 = pack<>;
    using C0 = pack_c<bool>;
    SAME_TYPE(T0, C0);
    SAME_TYPE(typename T0::type, T0);
    
    using T1 = pack<int_<1>>;
    using C1 = pack_c<int, 1>;
    SAME_TYPE(T1, C1);
    SAME_TYPE(typename T1::type, T1);
    
    using T2 = pack<true_, false_>;
    using C2 = pack_c<bool, true, false>;
    SAME_TYPE(T2, C2);
    SAME_TYPE(typename T2::type, T2);
  }                                                     // mp_pack_construction

  
  BOOST_AUTO_TEST_CASE(mp_pack_intrinsics)
  {
    // empty
    {
      using T = pack<>;
      // observers
      CHECK(sequence_size_t<T>::value == 0);
      CHECK(empty_t<T>::value);
      SAME_TYPE(begin_t<T>, pack_iterator<T, 0>);
      SAME_TYPE(end_t<T>, pack_iterator<T, 0>);
      // mutators
      SAME_TYPE(clear_t<T>, pack<>);
      SAME_TYPE(push_back_t<T, int>, pack<int>);
      SAME_TYPE(push_front_t<T, long>, pack<long>);
      SAME_TYPE(concat_t<T, pack<>>, pack<>);
      SAME_TYPE(concat_t<T, pack<bool>>, pack<bool>);
    }
    // single item
    {
      using T = pack<void>;
      // observers
      CHECK(sequence_size_t<T>::value == 1);
      CHECK(empty_t<T>::value == false);
      SAME_TYPE(begin_t<T>, pack_iterator<T, 0>);
      SAME_TYPE(end_t<T>, pack_iterator<T, 1>);
      SAME_TYPE(front_t<T>, void);
      SAME_TYPE(back_t<T>, void);
      // modifiers
      SAME_TYPE(clear_t<T>, pack<>);
      SAME_TYPE(push_back_t<T, bool>, pack<void, bool>);
      SAME_TYPE(pop_back_t<T>, pack<>);
      SAME_TYPE(push_front_t<T, bool>, pack<bool, void>);
      SAME_TYPE(pop_front_t<T>, pack<>);
      SAME_TYPE(drop_t<T, 0>, pack<void>);
      SAME_TYPE(drop_t<T, 1>, pack<>);
      SAME_TYPE(take_t<T, 0>, pack<>);
      SAME_TYPE(take_t<T, 1>, pack<void>);
      SAME_TYPE(slice_t<T, 0, 0>, pack<>);
      SAME_TYPE(slice_t<T, 0, 1>, pack<void>);
    }
    // two items
    {
      using T = pack<true_, false_>;
      // observers
      CHECK(sequence_size_t<T>::value == 2);
      CHECK(empty_t<T>::value == false);
      SAME_TYPE(begin_t<T>, pack_iterator<T, 0>);
      SAME_TYPE(end_t<T>, pack_iterator<T, 2>);
      SAME_TYPE(front_t<T>, true_);
      SAME_TYPE(back_t<T>, false_);
      // modifiers
      SAME_TYPE(clear_t<T>, pack<>);
      // push & pop back
      SAME_TYPE(push_back_t<T, void>, pack<true_, false_, void>);
      SAME_TYPE(pop_back_t<T>, pack<true_>);
      // push & pop front
      SAME_TYPE(push_front_t<T, void>, pack<void, true_, false_>);
      SAME_TYPE(pop_front_t<T>, pack<false_>);
      // drop
      SAME_TYPE(drop_t<T, 0>, pack<true_, false_>);
      SAME_TYPE(drop_t<T, 1>, pack<false_>);
      SAME_TYPE(drop_t<T, 2>, pack<>);
      // take
      SAME_TYPE(take_t<T, 0>, pack<>);
      SAME_TYPE(take_t<T, 1>, pack<true_>);
      SAME_TYPE(take_t<T, 2>, pack<true_, false_>);
      // slice
      SAME_TYPE(slice_t<T, 0, 0>, pack<>);
      SAME_TYPE(slice_t<T, 0, 1>, pack<true_>);
      SAME_TYPE(slice_t<T, 0, 2>, pack<true_, false_>);
      SAME_TYPE(slice_t<T, 1, 1>, pack<>);
      SAME_TYPE(slice_t<T, 1, 2>, pack<false_>);
    }
    // Multi-item
    {
      using T = pack<bool, char, short, int, long>;
      // observers
      CHECK(sequence_size_t<T>::value == 5);
      CHECK(empty_t<T>::value == false);
      SAME_TYPE(begin_t<T>, pack_iterator<T, 0>);
      SAME_TYPE(end_t<T>, pack_iterator<T, 5>);
      SAME_TYPE(front_t<T>, bool);
      SAME_TYPE(back_t<T>, long);
      // modifiers
      SAME_TYPE(clear_t<T>, pack<>);
      SAME_TYPE(push_back_t<T, void>, pack<bool, char, short, int, long, void>);
      SAME_TYPE(pop_back_t<T>, pack<bool, char, short, int>);
      SAME_TYPE(push_front_t<T, void>, pack<void, bool, char, short, int, long>);
      SAME_TYPE(pop_front_t<T>, pack<char, short, int, long>);
      // drop
      SAME_TYPE(drop_t<T, 0>, T);
      SAME_TYPE(drop_t<T, 1>, pop_front_t<T>);
      SAME_TYPE(drop_t<T, 2>, pack<short, int, long>);
      SAME_TYPE(drop_t<T, 3>, pack<int, long>);
      SAME_TYPE(drop_t<T, 4>, pack<long>);
      SAME_TYPE(drop_t<T, 5>, pack<>);
      // take
      SAME_TYPE(take_t<T, 0>, pack<>);
      SAME_TYPE(take_t<T, 1>, pack<bool>);
      SAME_TYPE(take_t<T, 2>, pack<bool, char>);
      SAME_TYPE(take_t<T, 3>, pack<bool, char, short>);
      SAME_TYPE(take_t<T, 4>, pack<bool, char, short, int>);
      SAME_TYPE(take_t<T, 5>, T);
      // slice
      SAME_TYPE(slice_t<T, 0, 0>, pack<>);
      SAME_TYPE(slice_t<T, 0, 2>, pack<bool, char>);
      SAME_TYPE(slice_t<T, 3, 5>, pack<int, long>);
      SAME_TYPE(slice_t<T, 0, 5>, T);
    }
    // TODO insert and erase tests
  }                                                       // mp_pack_intrinsics

  BOOST_AUTO_TEST_CASE(mp_pack_iterator_intrinsics)
  {
    // category test
    {
      using T = pack<int, long, char>;
      using B = begin_t<T>;
      using E = end_t<T>;
      SAME_TYPE(typename B::category, random_access_iterator_tag);
      SAME_TYPE(typename B::category, typename E::category);
    }
    // empty
    {
      using T = pack<>;
      using Begin = begin_t<T>;
      using End = end_t<T>;
      
      SAME_TYPE(Begin, p_iter<T, 0>);
      SAME_TYPE(Begin, p_iter<T, 0>);
      SAME_TYPE(Begin, End);
    }
    // size = 1
    {
      using T = pack<int>;
      using Begin = begin_t<T>;
      using End = end_t<T>;
      
      SAME_TYPE(Begin, p_iter<T, 0>);
      SAME_TYPE(End, p_iter<T, 1>);
      // deref
      SAME_TYPE(deref_t<Begin>, int);
      // next & prior
      SAME_TYPE(next_t<Begin>, End);
      SAME_TYPE(prior_t<End>, Begin);
      // advance & advance_c
      SAME_TYPE(advance_t<Begin, long_<0>>, Begin);
      SAME_TYPE(advance_t<Begin, long_<1>>, End);
      SAME_TYPE(advance_t<End, long_<0>>, End);
      SAME_TYPE(advance_t<End, long_<-1>>, Begin);
      SAME_TYPE(advance_c_t<Begin, 0>, Begin);
      SAME_TYPE(advance_c_t<Begin, 1>, End);
      SAME_TYPE(advance_c_t<End, 0>, End);
      SAME_TYPE(advance_c_t<End, -1>, Begin);
      // distance
      CHECK(distance_t<Begin, End>::value == 1);
      CHECK(distance_t<End, Begin>::value == -1);
      CHECK(distance_t<Begin, Begin>::value == 0);
      CHECK(distance_t<End, End>::value == 0);
    }
    // other sizes
    {
      using namespace elib::mp::placeholders;
      using T = pack<_1, _2, _3, _4>;
      using B = begin_t<T>;
      using E = end_t<T>;
      // begin & end
      SAME_TYPE(B, p_iter<T, 0>);
      SAME_TYPE(E, p_iter<T, 4>);
      // next & deref
      SAME_TYPE(deref_t<B>, _1);
      using N1 = next_t<B>;
      SAME_TYPE(N1, p_iter<T, 1>);
      SAME_TYPE(deref_t<N1>, _2);
      using N2 = next_t<N1>;
      SAME_TYPE(N2, p_iter<T, 2>);
      SAME_TYPE(deref_t<N2>, _3);
      using N3 = next_t<N2>;
      SAME_TYPE(N3, p_iter<T, 3>);
      SAME_TYPE(deref_t<N3>, _4);
      using N4 = next_t<N3>;
      SAME_TYPE(N4, p_iter<T, 4>);
      SAME_TYPE(N4, E);
      // prior
      using P1 = prior_t<E>;
      SAME_TYPE(P1, N3);
      using P2 = prior_t<P1>;
      SAME_TYPE(P2, N2);
      using P3 = prior_t<P2>;
      SAME_TYPE(P3, N1);
      using P4 = prior_t<P3>;
      SAME_TYPE(P4, B);
      // advance
      SAME_TYPE(B, advance_t<B, long_<0>>);
      SAME_TYPE(next_t<B>, advance_c_t<B, 1>);
      SAME_TYPE(advance_t<B, long_<4>>, E);
      SAME_TYPE(advance_c_t<E, -4>, B);
      SAME_TYPE(advance_t<E, long_<-1>>, advance_c_t<B, 3>);
    }
  }                                              // mp_pack_iterator_intrinsics
  
BOOST_AUTO_TEST_SUITE_END()