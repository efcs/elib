#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <elib/mp/sequence.hpp>
#include <elib/mp/iterator.hpp>
#include <elib/mp/containers.hpp>
#include <elib/mp/metafunctions.hpp>
#include <elib/mp/integral_constant.hpp>

#include <elib/mp/single_view.hpp>
#include <elib/mp/empty_sequence.hpp>
#include <elib/mp/iterator_range.hpp>

#include "mp_test_helper.hpp"


BOOST_AUTO_TEST_SUITE(mp_view_test_suite)
  
  BOOST_AUTO_TEST_CASE(mp_view_empty_sequence_test)
  {
    using T = empty_sequence;
    using B = begin_t<T>;
    using E = end_t<T>;
    
    SAME_TYPE(B, E);
    CHECK( sequence_size_t<T>() == 0 );
    CHECK( empty_t<T>() );
    SAME_TYPE(advance_c_t<B, 0>, E );
  }

  BOOST_AUTO_TEST_CASE(mp_view_single_view_test)
  {
    using T = single_view<true_>;
    using B = begin_t<T>;
    using E = end_t<T>;
    using Front = front_t<T>;
    using Back = back_t<T>;
    
    SAME_TYPE( typename T::type, T );
    SAME_TYPE( Front, Back );
    SAME_TYPE( Front, true_ );
    SAME_TYPE( at_t<T, int_<0>>, true_ );
    SAME_TYPE( at_c_t<T, 0>, true_ );
    
    SAME_TYPE( deref_t<B>, true_);
    SAME_TYPE( next_t<B>, E );
    SAME_TYPE( prior_t<E>, B );
    SAME_TYPE( advance_t<B, int_<1>>, E );
    SAME_TYPE( advance_t<B, int_<0>>, B );
    SAME_TYPE( advance_t<E, int_<0>>, E );
    SAME_TYPE( advance_t<E, int_<-1>>, B );
    CHECK( distance_t<B, E>() == 1 );
    CHECK( distance_t<B, B>() == 0 );
    CHECK( distance_t<E, E>() == 0 );
    CHECK( distance_t<E, B>() == -1 );
  }                                                 // mp_view_single_view_test

BOOST_AUTO_TEST_SUITE_END()
