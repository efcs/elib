#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "elib/mp/algorithm.hpp"
#include "elib/mp/metafunctions.hpp"
#include "elib/mp/sequence.hpp"
#include "elib/mp/iterator.hpp"
#include "elib/mp/pack.hpp"
#include "elib/mp/list.hpp"
#include "elib/mp/vector.hpp"
#include "elib/mp/void.hpp"
#include "elib/mp/identity.hpp"
#include "elib/mp/integral_constant.hpp"

#include "mp_test_helper.hpp"

#include <iostream>
#include <boost/mpl/print.hpp>

template <class T>
struct IterCountOpImpl
{
  template <class State, class Iter>
  using apply = 
    eval_if_< 
        same_type<T, deref_t<Iter>>
      , next<State>
      , State
      >;
};

template <class T>
using IterCountOp = protect< IterCountOpImpl<T> >;

template <class P, class T>
using iter_foldl_n_count = iter_foldl_n_t<P, int_<0>, IterCountOp<T>>;
    
template <class P, class T>
using iter_foldr_n_count = iter_foldr_n_t<P, int_<0>, IterCountOp<T>>;
    
    


BOOST_AUTO_TEST_SUITE(mp_algorithm_test_suite)


////////////////////////////////////////////////////////////////////////////////
//                            Iteration                                              
////////////////////////////////////////////////////////////////////////////////


//---------------------------- iter_fold_n ----------------------------------// 

  BOOST_AUTO_TEST_CASE(mp_iter_foldl_n)
  {
    
    // pack
    {
      using T = pack<int, int, void, int, void, char>;
      CHECK( iter_foldl_n_count<T, int>()  == 3 );
      CHECK( iter_foldl_n_count<T, void>() == 2 );
      CHECK( iter_foldl_n_count<T, char>() == 1 );
      CHECK( iter_foldl_n_count<T, long>() == 0 );
      
      CHECK( iter_foldl_n_count<T, int>()  == iter_foldr_n_count<T, int >() );
      CHECK( iter_foldl_n_count<T, void>() == iter_foldr_n_count<T, void>() );
      CHECK( iter_foldl_n_count<T, char>() == iter_foldr_n_count<T, char>() );
      CHECK( iter_foldl_n_count<T, long>() == iter_foldr_n_count<T, long>() );
      
      using ET = pack<>;
      CHECK( iter_foldl_n_count<ET, void>() == 0);
      CHECK( iter_foldl_n_count<ET, void>() == iter_foldr_n_count<ET, void>());
    }
    // vector
    {
      using T = vector<int, int, void, int, void, char>;
      CHECK( iter_foldl_n_count<T, int>()  == 3 );
      CHECK( iter_foldl_n_count<T, void>() == 2 );
      CHECK( iter_foldl_n_count<T, char>() == 1 );
      CHECK( iter_foldl_n_count<T, long>() == 0 );
      
      CHECK( iter_foldl_n_count<T, int>()  == iter_foldr_n_count<T, int >() );
      CHECK( iter_foldl_n_count<T, void>() == iter_foldr_n_count<T, void>() );
      CHECK( iter_foldl_n_count<T, char>() == iter_foldr_n_count<T, char>() );
      CHECK( iter_foldl_n_count<T, long>() == iter_foldr_n_count<T, long>() );
      
      using ET = vector<>;
      CHECK( iter_foldl_n_count<ET, void>() == 0);
      CHECK( iter_foldl_n_count<ET, void>() == iter_foldr_n_count<ET, void>());
    }
    // list
    {
      using T = list<int, int, void, int, void, char>;
      CHECK( iter_foldl_n_count<T, int>()  == 3 );
      CHECK( iter_foldl_n_count<T, void>() == 2 );
      CHECK( iter_foldl_n_count<T, char>() == 1 );
      CHECK( iter_foldl_n_count<T, long>() == 0 );
      
      CHECK(  iter_foldr_n_count<T, int >() == 3 );
      CHECK(  iter_foldr_n_count<T, void>() == 2 );
      CHECK(  iter_foldr_n_count<T, char>() == 1 );
      CHECK(  iter_foldr_n_count<T, long>() == 0 );
      
      using ET = list<>;
      CHECK( iter_foldl_n_count<ET, void>() == 0);
      CHECK( iter_foldl_n_count<ET, void>() == iter_foldr_n_count<ET, void>());
    }
  }

////////////////////////////////////////////////////////////////////////////////
//                            Querying                                              
////////////////////////////////////////////////////////////////////////////////

//-------------------------------- find & find_if ------------------------// 

  BOOST_AUTO_TEST_CASE(mp_algorithm_foldl_variadic)
  {
    // pack
    {
        using T = pack<int, char, float>;
        using Int = begin_t<T>;
        using Char = next_t<Int>;
        using Float = next_t<Char>;
        using E = end_t<T>;
        
        using FInt = find_t<T, int>;
        using FChar = find_t<T, char>;
        using FFloat = find_t<T, float>;
        using FDNE = find_t<T, long>;
        
        SAME_TYPE(Int, FInt);
        SAME_TYPE(Char, FChar);
        SAME_TYPE(Float, FFloat);
        SAME_TYPE(E, FDNE);
        
        // empty
        using TE = pack<>;
        using FDNE2 = find_t<TE, int>;
        SAME_TYPE( end_t<TE>, FDNE2 );
    }
    // vector
    {
        using T = vector<int, int, int, void, int, int, int>;
        using B = begin_t<T>;
        using Void = advance_c_t<B, 3>;
        using E = end_t<T>;
        
        using Pred1 = not_< same_type<int, _1> >;
        using FVoid = find_if_t<T, Pred1>;
        SAME_TYPE(Void, FVoid);
        
        using Pred2 = lambda< same_type<char, _1> >;
        using FDNE = find_if_t<T, Pred2>;
        SAME_TYPE(FDNE, E);
        
        // empty
        using TE = vector<>;
        using FDNE2 = find_if_t<TE, Pred1>;
        SAME_TYPE( end_t<TE>, FDNE2 );
    }
    // list
    {
      using T = list<void, void, int, int, char>;
      using B = begin_t<T>;
      using Void = B;
      using Int = advance_c_t<B, 2>;
      using Char = advance_c_t<B, 4>;
      using E = end_t<T>;
      
      SAME_TYPE( find_t<T, void>, Void );
      SAME_TYPE( find_t<T, int>,  Int  );
      SAME_TYPE( find_t<T, char>, Char );
      SAME_TYPE( find_t<T, long>, E    );
      
      using ET = list<>;
      
      SAME_TYPE( find_t<ET, void>, end_t<ET> );
    }
  }                                              // mp_algorithm_foldl_dispatch
  
//-------------------------------- count --------------------------------// 

  BOOST_AUTO_TEST_CASE(mp_algorithm_count_test)
  {
    // pack
    {
      using T = pack<int, int, int, char, char, bool, int, int>;
      
      CHECK( 5 == count_t<T, int >() );
      CHECK( 2 == count_t<T, char>() );
      CHECK( 1 == count_t<T, bool>() );
      CHECK( 0 == count_t<T, void>() );
      
      using TE = pack<>;
      CHECK( 0 == count_t<TE, void>() );
    }
    // vector
    {
      using T = vector<int, int, int, char, char, bool, int, int>;
      
      CHECK( 5 == count_if_t<T, same_type<int, _1> >() );
      CHECK( 7 == count_if_t<T, not_<same_type<bool, _1>> >() );
      CHECK( 3 == count_if_t<T, or_<same_type<bool, _1>, same_type<char, _1>> >() );
      CHECK( 0 == count_if_t<T, same_type<_1, void>>() );
      
      using TE = vector<>;
      CHECK( 0 == count_if_t<TE, always<true_>>() );
    }
    // list
    {
      using T = list<int, int, void>;
      
      CHECK( count_t<T, int>() == 2 );
      CHECK( count_t<T, void>() == 1 );
      CHECK( count_t<T, unsigned>() == 0 );
      
      using E = list<>;
      
      CHECK( 0 == count_t<E, void>() );
    }
  }                                                 // mp_algorithm_count_test
  
  
//-------------------------------- sequence equal ---------------------------// 

  BOOST_AUTO_TEST_CASE(mp_algorithm_sequence_equal)
  {
    // pack tests
    {
      using T1 = pack<char, short, int, long>;
      using T2 = pack<char, short, int, long>;
      using E1 = pack<>;
      using E2 = pack<>;
      using T3 = pack<void>;
      using T4 = pack<char, long>;
      
      CHECK( sequence_equal<T1, T2>() );
      CHECK( sequence_equal<E1, E2>() );
      CHECK( !sequence_equal<T1, E1>() );
      CHECK( !sequence_equal<T1, T3>() );
      CHECK( !sequence_equal<T4, T1>() );
    }
    // vector tests
    {
      using T1 = vector_c<int, 1, 2, 3>;
      using T2 = vector< int_<1>, int_<2>, int_<3> >;
      using E1 = vector<>;
      using E2 = vector_c<int>;
      using T3 = vector< int_<1> >;
      
      CHECK( sequence_equal<T1, T2>() );
      CHECK( sequence_equal<E1, E2>() );
      CHECK( !sequence_equal<T1, E1>() );
      CHECK( !sequence_equal<T1, T3>() );
      CHECK( !sequence_equal<E1, T3>() );
    }
    // mixed
    {
      using P1 = pack<   void, char, short, int, long>;
      using V1 = vector< void, char, short, int, long>;
      using L1 = list<   void, char, short, int, long>;
      
      using EP = pack<>;
      using EV = vector<>;
      using EL = list<>;
      
      using P2 = pack< void, char >;
      using V2 = vector< short, int >;
      using L2 = list< long >;
      
      CHECK( sequence_equal<P1, V1>() );
      CHECK( sequence_equal<P1, L1>() );
      CHECK( sequence_equal<L1, V1>() );
      
      CHECK( sequence_equal<EP, EV>() );
      CHECK( sequence_equal<EP, EL>() );
      CHECK( sequence_equal<EL, EV>() );
      
      CHECK( !sequence_equal<P2, V2>() );
      CHECK( !sequence_equal<L2, P2>() );
      CHECK( !sequence_equal<L2, V2>() );
      
      CHECK( !sequence_equal<P1, EV>() );
      CHECK( !sequence_equal<P1, EL>() );
      CHECK( !sequence_equal<V1, EP>() );
      CHECK( !sequence_equal<V1, EL>() );
      CHECK( !sequence_equal<L1, EP>() );
      CHECK( !sequence_equal<L1, EV>() );
    }
  }                                              // mp_algorithm_sequence_equal

  
//-------------------------------- lower bound ------------------------------// 

  BOOST_AUTO_TEST_CASE(mp_algorithm_lower_bound_test)
  {
    // pack
    {
      using T = pack_c<int, 0, 1, 2, 3, 3, 4, 10>;
      using B = begin_t<T>;
      using Zero = B;
      using One = next_t<Zero>;
      using Two = next_t<One>;
      using Three = next_t<Two>;
      using Four = next_t< next_t<Three> >;
      using Ten = next_t< Four >;
      using E = end_t<T>;
      
      SAME_TYPE( lower_bound_t<T, int_<-1>>, B );
      SAME_TYPE( lower_bound_t<T, int_<0>>, Zero );
      SAME_TYPE( lower_bound_t<T, int_<1>>, One );
      SAME_TYPE( lower_bound_t<T, int_<2>>, Two );
      SAME_TYPE( lower_bound_t<T, int_<3>>, Three );
      SAME_TYPE( lower_bound_t<T, int_<4>>, Four );
      SAME_TYPE( lower_bound_t<T, int_<5>>, Ten);
      SAME_TYPE( lower_bound_t<T, int_<10>>, Ten);
      SAME_TYPE( lower_bound_t<T, int_<11>>, E);
      
      using ET = pack<>;
      SAME_TYPE( lower_bound_t<ET, int_<1>>, begin_t<ET> );
    }
    // vector
    {
      using T = vector_c<int, 1, 5, 10>;
      using B = begin_t<T>;
      using One = B;
      using Five = next_t<One>;
      using Ten = next_t<Five>;
      using E = end_t<T>;
      
      SAME_TYPE( lower_bound_t<T, int_<-1>>, B );
      SAME_TYPE( lower_bound_t<T, int_<1>>, One );
      SAME_TYPE( lower_bound_t<T, int_<2>>, Five );
      SAME_TYPE( lower_bound_t<T, int_<5>>, Five );
      SAME_TYPE( lower_bound_t<T, int_<6>>, Ten );
      SAME_TYPE( lower_bound_t<T, int_<10>>, Ten );
      SAME_TYPE( lower_bound_t<T, int_<50>>, E );
      
      using ET = vector<>;
      SAME_TYPE( lower_bound_t<ET, int_<-10>>, begin_t<ET> );
    }
    // list
    {
      using T = list_c<int, -1, 1>;
      using B = begin_t<T>;
      using NOne = B;
      using One = next_t<NOne>;
      using E = end_t<T>;
      
      SAME_TYPE( lower_bound_t<T, int_<-3>>, B );
      SAME_TYPE( lower_bound_t<T, int_<-1>>, NOne );
      SAME_TYPE( lower_bound_t<T, int_<0>>, One );
      SAME_TYPE( lower_bound_t<T, int_<1>>, One );
      SAME_TYPE( lower_bound_t<T, int_<3>>, E );
      
      using ET = list<>;
      SAME_TYPE( lower_bound_t<ET, int_<0>>, end_t<ET> );
    }
  }                                            // mp_algorithm_lower_bound_test
  
  
//-------------------------------- upper bound -------------------------------/
  
  BOOST_AUTO_TEST_CASE(mp_algorithm_upper_bound_test)
  {
    // pack
    {
      using T = pack_c<int, 0, 1, 1, 1, 3, 3, 4>;
      using B = begin_t<T>;
      using Zero = next_t<B>;
      using One = advance_c_t<Zero, 3>;
      using Three = advance_c_t<One, 2>;
      using Four = next_t<Three>;
      using E = end_t<T>;
      
      // sanity check
      SAME_TYPE(Four, E);
      
      SAME_TYPE( upper_bound_t<T, int_<-1>>, B );
      SAME_TYPE( upper_bound_t<T, int_<0>>, Zero );
      SAME_TYPE( upper_bound_t<T, int_<1>>, One );
      SAME_TYPE( upper_bound_t<T, int_<2>>, One );
      SAME_TYPE( upper_bound_t<T, int_<3>>, Three );
      SAME_TYPE( upper_bound_t<T, int_<4>>, Four );
      SAME_TYPE( upper_bound_t<T, int_<5>>, E );
        
      using ET = pack<>;
      SAME_TYPE( upper_bound_t<ET, int_<0>>, begin_t<ET> );
    }
    // vector
    {
      using T = vector_c<int, 0, 0, 1>;
      using B = begin_t<T>;
      using Zero = advance_c_t<B, 2>;
      using One = next_t<Zero>;
      using E = end_t<T>;
      
      // sanity check
      SAME_TYPE( One, E );
      
      SAME_TYPE( upper_bound_t<T, int_<-1>>, B );
      SAME_TYPE( upper_bound_t<T, int_<0>>, Zero );
      SAME_TYPE( upper_bound_t<T, int_<1>>, One );
      SAME_TYPE( upper_bound_t<T, int_<2>>, E );
      SAME_TYPE( upper_bound_t<T, int_<10>>, E );
      
      using ET = vector<>;
      SAME_TYPE( upper_bound_t<ET, int_<-10>>, begin_t<ET> );
    }
    // list
    {
      using T = list_c<int, 1, 2, 2>;
      using B = begin_t<T>;
      using One = next_t<B>;
      using Two = next_t< next_t<One> >;
      using E = end_t< T >;
      
      // sanity check
      SAME_TYPE( Two, E );
      
      SAME_TYPE( upper_bound_t<T, int_<0>>, B );
      SAME_TYPE( upper_bound_t<T, int_<1>>, One );
      SAME_TYPE( upper_bound_t<T, int_<2>>, Two );
      SAME_TYPE( upper_bound_t<T, int_<3>>, E );
      SAME_TYPE( upper_bound_t<T, int_<4>>, E );
      
      using ET = list<>;
      SAME_TYPE( upper_bound_t<ET, int_<10>>, begin_t<ET> );
    }
  }                                            // mp_algorithm_upper_bound_test
  
  
////////////////////////////////////////////////////////////////////////////////
//                            Transforming                                            
////////////////////////////////////////////////////////////////////////////////

  BOOST_AUTO_TEST_CASE(mp_algorithm_copy_test)
  {
    BOOST_CHECK(true);
    /*
    // copy test
    {
      using P = pack   <int, char, void>;
      using V = vector <int, char, void>;
      using L = list   <int, char, void>;
      
      using CP = copy_t<P>;
      std::cout << sequence_size<CP>() << std::endl;
      SAME_TYPE( front_t<CP>, void );
      SAME_TYPE( at_c_t<CP, 1>,  );
      SAME_TYPE( at_c_t<CP, 2>, void );
      
      CHECK( sequence_equal_t<copy_t<P>, P>() );
      CHECK( sequence_equal_t<copy_t<V>, V>() );
      CHECK( sequence_equal_t<copy_t<L>, L>() );
    }
    */
  }                                                   // mp_algorithm_copy_test
  
BOOST_AUTO_TEST_SUITE_END()
