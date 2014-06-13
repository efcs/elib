// REQUIRES: ELIB_MP_SOURCE
#include <elib/mp/sequence.hpp>
#include <elib/mp/iterator.hpp>
#include <elib/mp/containers.hpp>
#include <elib/mp/metafunctions.hpp>
#include <elib/mp/algorithm/sequence_equal.hpp>
#include <elib/mp/views.hpp>
#include <elib/mp/print.hpp>
#include <elib/aux.hpp>
#include "mp_test_helper.hpp"
#include "test/helper.hpp"


TEST_CASE(mp_view_test_suite)
{
  // mp_view_empty_sequence_test)
  {
    // general
    {
      using T = empty_sequence;
      using B = begin_t<T>;
      using E = end_t<T>;
      
      TEST_SAME_TYPE(B, E);
      TEST_CHECK( sequence_size_t<T>() == 0 );
      TEST_CHECK( empty_t<T>() );
      TEST_SAME_TYPE(advance_c_t<B, 0>, E );
    }
    // model_of
    {
      using T = empty_sequence;
      TEST_SAME_TYPE( typename T::class_type, empty_sequence_tag );
      TEST_SAME_TYPE( typename T::model_type, empty_sequence_model );
      TEST_CHECK( is_sequence_t<T>() );
      TEST_CHECK( !is_iterator<T>() );
      TEST_CHECK( !is_variadic_t<T>() );
      TEST_CHECK( is_forward_sequence_t<T>() );
      TEST_CHECK( is_bidirectional_sequence_t<T>() );
      TEST_CHECK( is_random_access_sequence_t<T>() );
      TEST_CHECK( !is_associative_sequence_t<T>() );
      
      TEST_CHECK( !is_front_extensible_sequence<T>() );
      TEST_CHECK( !is_front_extensible_variadic_sequence_t<T>() );
      TEST_CHECK( !is_back_extensible_sequence<T>() );
      TEST_CHECK( !is_back_extensible_variadic_sequence_t<T>() );
      TEST_CHECK( !is_associative_extensible_sequence_t<T>() );
      
      using B = begin_t<T>;
      using E = end_t<T>;
      TEST_SAME_TYPE( typename B::model_type, typename E::model_type );
      TEST_CHECK( is_iterator_t<B>() );
      TEST_CHECK( !is_sequence<B>() );
      TEST_CHECK( is_forward_iterator_t<B>() );
      TEST_CHECK( is_bidirectional_iterator_t<B>() );
      TEST_CHECK( is_random_access_iterator_t<B>() );
      TEST_CHECK( !is_default_random_access_iterator_t<B>() );
    }
  }

  // mp_view_filter_view_test)
  {
    // general
    {
      using P1 = pack< float, int, int, float, float, int, float>;
      using P = filter_view<P1, aux::is_same<float, _1>>;
      using V1 = vector< float, int, int, float, float, int, float>;
      using V = filter_view<V1, aux::is_same<float, _1>>;
      using L1 = list< float, int, int, float, float, int, float>;
      using L = filter_view<L1, aux::is_same<float, _1>>;
      
      using E = pack<float, float, float, float>;
      
      TEST_CHECK( sequence_size_t<P>() == 4 );
      TEST_CHECK( sequence_size_t<V>() == 4 );
      TEST_CHECK( sequence_size_t<L>() == 4 );
      
      TEST_CHECK( sequence_equal_t<P, E>() );
      TEST_CHECK( sequence_equal_t<V, E>() );
      TEST_CHECK( sequence_equal_t<L, E>() );
    }
    // model_of
    {
      using T1 = pack<float, int, float, int, int, float>;
      using T = filter_view< T1, aux::is_same<float, _1>>;
      TEST_SAME_TYPE( typename T::class_type, filter_view_tag );
      TEST_SAME_TYPE( typename T::model_type, filter_view_model );
      TEST_CHECK( is_sequence_t<T>() );
      TEST_CHECK( !is_iterator<T>() );
      TEST_CHECK( !is_variadic_t<T>() );
      TEST_CHECK( is_forward_sequence_t<T>() );
      TEST_CHECK( !is_bidirectional_sequence_t<T>() );
      TEST_CHECK( !is_random_access_sequence_t<T>() );
      TEST_CHECK( !is_associative_sequence_t<T>() );
      
      TEST_CHECK( !is_front_extensible_sequence<T>() );
      TEST_CHECK( !is_front_extensible_variadic_sequence_t<T>() );
      TEST_CHECK( !is_back_extensible_sequence<T>() );
      TEST_CHECK( !is_back_extensible_variadic_sequence_t<T>() );
      TEST_CHECK( !is_associative_extensible_sequence_t<T>() );
      
      using B = begin_t<T>;
      using E = end_t<T>;
      TEST_SAME_TYPE( typename B::model_type, typename E::model_type );
      TEST_CHECK( is_iterator_t<B>() );
      TEST_CHECK( !is_sequence<B>() );
      TEST_CHECK( is_forward_iterator_t<B>() );
      TEST_CHECK( !is_bidirectional_iterator_t<B>() );
      TEST_CHECK( !is_random_access_iterator_t<B>() );
      TEST_CHECK( !is_default_random_access_iterator_t<B>() );
    }
  }                                                 // mp_view_filter_view_test
  
  
  // mp_view_single_view_test)
  {
    // general
    {
      using T = single_view<true_>;
      using B = begin_t<T>;
      using E = end_t<T>;
      using Front = front_t<T>;
      using Back = back_t<T>;
      
      TEST_SAME_TYPE( typename T::type, T );
      TEST_SAME_TYPE( Front, Back );
      TEST_SAME_TYPE( Front, true_ );
      TEST_SAME_TYPE( at_t<T, int_<0>>, true_ );
      TEST_SAME_TYPE( at_c_t<T, 0>, true_ );
      
      TEST_SAME_TYPE( deref_t<B>, true_);
      TEST_SAME_TYPE( next_t<B>, E );
      TEST_SAME_TYPE( prior_t<E>, B );
      TEST_SAME_TYPE( advance_t<B, int_<1>>, E );
      TEST_SAME_TYPE( advance_t<B, int_<0>>, B );
      TEST_SAME_TYPE( advance_t<E, int_<0>>, E );
      TEST_SAME_TYPE( advance_t<E, int_<-1>>, B );
      TEST_CHECK( distance_t<B, E>() == 1 );
      TEST_CHECK( distance_t<B, B>() == 0 );
      TEST_CHECK( distance_t<E, E>() == 0 );
      TEST_CHECK( distance_t<E, B>() == -1 );
    }
    // model
    {
      using T = single_view<void>;
      TEST_SAME_TYPE( typename T::class_type, single_view_tag );
      TEST_SAME_TYPE( typename T::model_type, single_view_model );
      TEST_CHECK( is_sequence_t<T>() );
      TEST_CHECK( !is_iterator<T>() );
      TEST_CHECK( !is_variadic_t<T>() );
      TEST_CHECK( is_forward_sequence_t<T>() );
      TEST_CHECK( is_bidirectional_sequence_t<T>() );
      TEST_CHECK( is_random_access_sequence_t<T>() );
      TEST_CHECK( !is_associative_sequence_t<T>() );
      
      TEST_CHECK( !is_front_extensible_sequence<T>() );
      TEST_CHECK( !is_front_extensible_variadic_sequence_t<T>() );
      TEST_CHECK( !is_back_extensible_sequence<T>() );
      TEST_CHECK( !is_back_extensible_variadic_sequence_t<T>() );
      TEST_CHECK( !is_associative_extensible_sequence_t<T>() );
      
      using B = begin_t<T>;
      using E = end_t<T>;
      TEST_SAME_TYPE( typename B::model_type, typename E::model_type );
      TEST_CHECK( is_iterator_t<B>() );
      TEST_CHECK( !is_sequence<B>() );
      TEST_CHECK( is_forward_iterator_t<B>() );
      TEST_CHECK( is_bidirectional_iterator_t<B>() );
      TEST_CHECK( is_random_access_iterator_t<B>() );
      TEST_CHECK( !is_default_random_access_iterator_t<B>() );
    }
  }                                                 // mp_view_single_view_test
  

  // mp_view_joint_view_test)
  {
    // general
    {
      using P1 = pack_c<int, 0, 1, 2>;
      using P2 = pack_c<int, 3, 4, 5>;
      using P = joint_view<P1, P2>;
      
      using V1 = vector_c<int, 0, 1, 2>;
      using V2 = vector_c<int, 3, 4, 5>;
      using V = joint_view<V1, V2>;
      
      using L1 = list_c<int, 0, 1, 2>;
      using L2 = list_c<int, 3, 4, 5>;
      using L = joint_view<L1, L2>;
      
      using E = pack_c<int, 0, 1, 2, 3, 4, 5>;
      
      TEST_CHECK( sequence_size_t<P>() == 6 );
      TEST_CHECK( empty_t<P>() == false );
      TEST_SAME_TYPE( front_t<P>, int_<0> );
      
      TEST_CHECK( sequence_size_t<V>() == 6 );
      TEST_CHECK( empty_t<V>() == false );
      TEST_SAME_TYPE( front_t<V>, int_<0> );
      
      TEST_CHECK( sequence_size_t<L>() == 6 );
      TEST_CHECK( empty_t<L>() == false );
      TEST_SAME_TYPE( front_t<L>, int_<0> );
      
      TEST_CHECK( sequence_equal_t<P, E>() );
      TEST_CHECK( sequence_equal_t<V, E>() );
      TEST_CHECK( sequence_equal_t<L, E>() );
    }
    // model
    {
      using P1 = pack_c<int, 1, 2, 3>;
      using P2 = pack_c<int, 4, 5, 6>;
      using T = joint_view<P1, P2>;
      TEST_SAME_TYPE( typename T::class_type, joint_view_tag );
      TEST_SAME_TYPE( typename T::model_type, joint_view_model );
      TEST_CHECK( is_sequence_t<T>() );
      TEST_CHECK( !is_iterator<T>() );
      TEST_CHECK( !is_variadic_t<T>() );
      TEST_CHECK( is_forward_sequence_t<T>() );
      TEST_CHECK( !is_bidirectional_sequence_t<T>() );
      TEST_CHECK( !is_random_access_sequence_t<T>() );
      TEST_CHECK( !is_associative_sequence_t<T>() );
      
      TEST_CHECK( !is_front_extensible_sequence<T>() );
      TEST_CHECK( !is_front_extensible_variadic_sequence_t<T>() );
      TEST_CHECK( !is_back_extensible_sequence<T>() );
      TEST_CHECK( !is_back_extensible_variadic_sequence_t<T>() );
      TEST_CHECK( !is_associative_extensible_sequence_t<T>() );
      
      using B = begin_t<T>;
      using E = end_t<T>;
      TEST_SAME_TYPE( typename B::model_type, typename E::model_type );
      TEST_CHECK( is_iterator_t<B>() );
      TEST_CHECK( !is_sequence<B>() );
      TEST_CHECK( is_forward_iterator_t<B>() );
      TEST_CHECK( !is_bidirectional_iterator_t<B>() );
      TEST_CHECK( !is_random_access_iterator_t<B>() );
      TEST_CHECK( !is_default_random_access_iterator_t<B>() );
    }
  }                                                  // mp_view_joint_view_test
  
  // mp_view_transform_view_test)
  {
    // general
    {
      using P1 = pack  < char, short, int, long, long long >;
      using P = transform_view<P1, sizeof_<_1>>;
      using V1 = vector< char, short, int, long, long long >;
      using V = transform_view<V1, sizeof_<_1>>;
      using L1 = list  < char, short, int, long, long long >;
      using L = transform_view<L1, sizeof_<_1>>;
      
      using E = pack< 
          sizeof_t<char>, sizeof_t<short>
        , sizeof_t<int>, sizeof_t<long>
        , sizeof_t<long long>
        >;
      
      TEST_CHECK( sequence_equal_t< P, E >() );
      TEST_CHECK( sequence_equal_t< V, E >() );
      TEST_CHECK( sequence_equal_t< L, E >() );
    }
    // model
    {
      using T = transform_view< pack<char, int>, sizeof_<_1> >;
      TEST_SAME_TYPE( typename T::class_type, transform_view_tag );
      TEST_SAME_TYPE( typename T::model_type, transform_view_model );
      TEST_CHECK( is_sequence_t<T>() );
      TEST_CHECK( !is_iterator<T>() );
      TEST_CHECK( !is_variadic_t<T>() );
      TEST_CHECK( is_forward_sequence_t<T>() );
      TEST_CHECK( !is_bidirectional_sequence_t<T>() );
      TEST_CHECK( !is_random_access_sequence_t<T>() );
      TEST_CHECK( !is_associative_sequence_t<T>() );
      
      TEST_CHECK( !is_front_extensible_sequence<T>() );
      TEST_CHECK( !is_front_extensible_variadic_sequence_t<T>() );
      TEST_CHECK( !is_back_extensible_sequence<T>() );
      TEST_CHECK( !is_back_extensible_variadic_sequence_t<T>() );
      TEST_CHECK( !is_associative_extensible_sequence_t<T>() );
      
      using B = begin_t<T>;
      using E = end_t<T>;
      TEST_SAME_TYPE( typename B::model_type, typename E::model_type );
      TEST_CHECK( is_iterator_t<B>() );
      TEST_CHECK( !is_sequence<B>() );
      TEST_CHECK( is_forward_iterator_t<B>() );
      TEST_CHECK( !is_bidirectional_iterator_t<B>() );
      TEST_CHECK( !is_random_access_iterator_t<B>() );
      TEST_CHECK( !is_default_random_access_iterator_t<B>() );
    }
  }                                              // mp_view_transform_view_test

  
# if !defined(ELIB_CONFIG_COVERITY_SCAN) 
  // mp_view_zip_view_test)
  {
    // general
    {
      using P1 = pack_c<int, 1, 1, 1>;
      using P2 = pack_c<int, 2, 2, 2>;
      using P3 = pack_c<int, 3, 3, 3>;
      using P = zip_view< pack<P1, P2, P3> >;
      
      using V1 = vector_c<int, 1, 1, 1>;
      using V2 = vector_c<int, 2, 2, 2>;
      using V3 = vector_c<int, 3, 3, 3>;
      using V = zip_view< vector<V1, V2, V3> >;
      
      using L1 = list_c<int, 1, 1, 1>;
      using L2 = list_c<int, 2, 2, 2>;
      using L3 = list_c<int, 3, 3, 3>;
      using L = zip_view< list<L1, L2, L3> >;
      
      using EP = pack< 
          pack_c<int, 1, 2, 3>
        , pack_c<int, 1, 2, 3>
        , pack_c<int, 1, 2, 3>
        >;
    
      /*
      using EV = vector< 
          vector_c<int, 1, 2, 3>
        , vector_c<int, 1, 2, 3>
        , vector_c<int, 1, 2, 3>
        >;
      */
      
      using EL = list< 
          list_c<int, 1, 2, 3>
        , list_c<int, 1, 2, 3>
        , list_c<int, 1, 2, 3>
        >;

      TEST_CHECK( sequence_size_t<P>() == 3 );
      TEST_CHECK( sequence_size_t<V>() == 3 );
      TEST_CHECK( sequence_size_t<L>() == 3 );
      
      
      TEST_CHECK( sequence_equal_t<P, EP>() );
      //TEST_CHECK( sequence_equal_t<V, EV>() );
      TEST_CHECK( sequence_equal_t<L, EL>() );
    }
    // model
    {
      using T1 = pack_c<int, 1, 2>;
      using T2 = pack_c<int, 1, 2>;
      using T3 = pack_c<int, 1, 2>;
      using T = zip_view< pack<T1, T2, T3> >;
      TEST_SAME_TYPE( typename T::class_type, zip_view_tag );
      TEST_SAME_TYPE( typename T::model_type, zip_view_model );
      TEST_CHECK( is_sequence_t<T>() );
      TEST_CHECK( !is_iterator<T>() );
      TEST_CHECK( !is_variadic_t<T>() );
      TEST_CHECK( is_forward_sequence_t<T>() );
      TEST_CHECK( !is_bidirectional_sequence_t<T>() );
      TEST_CHECK( !is_random_access_sequence_t<T>() );
      TEST_CHECK( !is_associative_sequence_t<T>() );
      
      TEST_CHECK( !is_front_extensible_sequence<T>() );
      TEST_CHECK( !is_front_extensible_variadic_sequence_t<T>() );
      TEST_CHECK( !is_back_extensible_sequence<T>() );
      TEST_CHECK( !is_back_extensible_variadic_sequence_t<T>() );
      TEST_CHECK( !is_associative_extensible_sequence_t<T>() );
      
      using B = begin_t<T>;
      using E = end_t<T>;
      TEST_SAME_TYPE( typename B::model_type, typename E::model_type );
      TEST_CHECK( is_iterator_t<B>() );
      TEST_CHECK( !is_sequence<B>() );
      TEST_CHECK( is_forward_iterator_t<B>() );
      TEST_CHECK( !is_bidirectional_iterator_t<B>() );
      TEST_CHECK( !is_random_access_iterator_t<B>() );
      TEST_CHECK( !is_default_random_access_iterator_t<B>() );
    }
  }                                                    // mp_view_zip_view_test
# endif /* ELIB_CONFIG_COVERITY_SCAN */
}
