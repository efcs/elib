// REQUIRES: ELIB_MP_SOURCE
#include <elib/mp/algorithm.hpp>
#include <elib/mp/metafunctions.hpp>
#include <elib/mp/sequence.hpp>
#include <elib/mp/iterator.hpp>
#include <elib/mp/pack.hpp>
#include <elib/mp/list.hpp>
#include <elib/mp/vector.hpp>
#include <elib/mp/void.hpp>
#include <elib/mp/identity.hpp>

#include "mp_test_helper.hpp"
#include "test/helper.hpp"

#include <iostream>

using namespace elib;

template <class T>
struct IterCountOpImpl
{
  template <class State, class Iter>
  using apply = 
    eval_if< 
        aux::is_same<T, deref_t<Iter>>
      , next<State>
      , identity< State >
      >;
};

template <class T>
using IterCountOp = protect< IterCountOpImpl<T> >;


template <class P, class T>
using iter_foldl_n_count = iter_foldl_n_t<P, int_<0>, IterCountOp<T>>;
    
template <class P, class T>
using iter_foldr_n_count = iter_foldr_n_t<P, int_<0>, IterCountOp<T>>;
    
    
template <class P, class T>
using iter_foldl_if_count = iter_foldl_if_t<P, int_<0>, IterCountOp<T>>;

template <class P, class T>
using iter_foldr_if_count = iter_foldr_if_t<P, int_<0>, IterCountOp<T>>;


template <class P, class T>
using iter_foldl_count = iter_foldl_t<P, int_<0>, IterCountOp<T>>;

template <class P, class T>
using iter_foldr_count = iter_foldr_t<P, int_<0>, IterCountOp<T>>;


template <class T>
struct CountOpImpl
{
  template <class State, class Item>
  using apply = 
    eval_if< 
        aux::is_same<T, Item>
      , next<State>
      , identity< State >
      >;
};

template <class T>
using CountOp = protect< CountOpImpl<T> >;


template <class P, class T>
using foldl_n_count = foldl_n_t<P, int_<0>, CountOp<T>>;
    
template <class P, class T>
using foldr_n_count = foldr_n_t<P, int_<0>, CountOp<T>>;
    
    
template <class P, class T>
using foldl_if_count = foldl_if_t<P, int_<0>, CountOp<T>>;


template <class P, class T>
using foldr_if_count = foldr_if_t<P, int_<0>, CountOp<T>>;


template <class P, class T>
using foldl_count = foldl_t<P, int_<0>, CountOp<T>>;

template <class P, class T>
using foldr_count = foldr_t<P, int_<0>, CountOp<T>>;

template <class N>
struct is_odd : bool_<(N::value % 2)>
  {};
  
  
template <class P, class P1>
using pair_equal_t = 
    and_< 
        sequence_equal<first_t<P>, first_t<P1>>
      , sequence_equal<second_t<P>, second_t<P1>>
      >;


TEST_CASE(mp_algorithm_test_suite)
{


////////////////////////////////////////////////////////////////////////////////
//                            Iteration                                              
////////////////////////////////////////////////////////////////////////////////


//---------------------------- iter_fold_n ----------------------------------// 

  // mp_iter_foldl_n)
  {
    // pack
    {
      using T = pack<int, int, void, int, void, char>;
      TEST_CHECK( iter_foldl_n_count<T, int>()  == 3 );
      TEST_CHECK( iter_foldl_n_count<T, void>() == 2 );
      TEST_CHECK( iter_foldl_n_count<T, char>() == 1 );
      TEST_CHECK( iter_foldl_n_count<T, long>() == 0 );
      
      TEST_CHECK( iter_foldl_n_count<T, int>()  == iter_foldr_n_count<T, int >() );
      TEST_CHECK( iter_foldl_n_count<T, void>() == iter_foldr_n_count<T, void>() );
      TEST_CHECK( iter_foldl_n_count<T, char>() == iter_foldr_n_count<T, char>() );
      TEST_CHECK( iter_foldl_n_count<T, long>() == iter_foldr_n_count<T, long>() );
      
      using ET = pack<>;
      TEST_CHECK( iter_foldl_n_count<ET, void>() == 0);
      TEST_CHECK( iter_foldl_n_count<ET, void>() == iter_foldr_n_count<ET, void>());
    }
    // vector
    {
      using T = vector<int, int, void, int, void, char>;
      TEST_CHECK( iter_foldl_n_count<T, int>()  == 3 );
      TEST_CHECK( iter_foldl_n_count<T, void>() == 2 );
      TEST_CHECK( iter_foldl_n_count<T, char>() == 1 );
      TEST_CHECK( iter_foldl_n_count<T, long>() == 0 );
      
      TEST_CHECK( iter_foldl_n_count<T, int>()  == iter_foldr_n_count<T, int >() );
      TEST_CHECK( iter_foldl_n_count<T, void>() == iter_foldr_n_count<T, void>() );
      TEST_CHECK( iter_foldl_n_count<T, char>() == iter_foldr_n_count<T, char>() );
      TEST_CHECK( iter_foldl_n_count<T, long>() == iter_foldr_n_count<T, long>() );
      
      using ET = vector<>;
      TEST_CHECK( iter_foldl_n_count<ET, void>() == 0);
      TEST_CHECK( iter_foldl_n_count<ET, void>() == iter_foldr_n_count<ET, void>());
    }
    // list
    {
      using T = list<int, int, void, int, void, char>;
      TEST_CHECK( iter_foldl_n_count<T, int>()  == 3 );
      TEST_CHECK( iter_foldl_n_count<T, void>() == 2 );
      TEST_CHECK( iter_foldl_n_count<T, char>() == 1 );
      TEST_CHECK( iter_foldl_n_count<T, long>() == 0 );
      
      TEST_CHECK(  iter_foldr_n_count<T, int >() == 3 );
      TEST_CHECK(  iter_foldr_n_count<T, void>() == 2 );
      TEST_CHECK(  iter_foldr_n_count<T, char>() == 1 );
      TEST_CHECK(  iter_foldr_n_count<T, long>() == 0 );
      
      using ET = list<>;
      TEST_CHECK( iter_foldl_n_count<ET, void>() == 0);
      TEST_CHECK( iter_foldl_n_count<ET, void>() == iter_foldr_n_count<ET, void>());
      
    }
  }

  
//-------------------------------- iter_fold_if -----------------------------// 

  // mp_iter_foldl_if)
  {
    // pack
    {
      using T = pack<int, int, void, int, void, char>;
      TEST_CHECK( iter_foldl_if_count<T, int>()  == 3 );
      TEST_CHECK( iter_foldl_if_count<T, void>() == 2 );
      TEST_CHECK( iter_foldl_if_count<T, char>() == 1 );
      TEST_CHECK( iter_foldl_if_count<T, long>() == 0 );
      
      TEST_CHECK( iter_foldl_if_count<T, int>()  == iter_foldr_if_count<T, int >() );
      TEST_CHECK( iter_foldl_if_count<T, void>() == iter_foldr_if_count<T, void>() );
      TEST_CHECK( iter_foldl_if_count<T, char>() == iter_foldr_if_count<T, char>() );
      TEST_CHECK( iter_foldl_if_count<T, long>() == iter_foldr_if_count<T, long>() );
      
      using ET = pack<>;
      TEST_CHECK( iter_foldl_if_count<ET, void>() == 0);
      TEST_CHECK( iter_foldl_if_count<ET, void>() == iter_foldr_if_count<ET, void>());
    }
    // vector
    {
      using T = vector<int, int, void, int, void, char>;
      TEST_CHECK( iter_foldl_if_count<T, int>()  == 3 );
      TEST_CHECK( iter_foldl_if_count<T, void>() == 2 );
      TEST_CHECK( iter_foldl_if_count<T, char>() == 1 );
      TEST_CHECK( iter_foldl_if_count<T, long>() == 0 );
      
      TEST_CHECK( iter_foldl_if_count<T, int>()  == iter_foldr_if_count<T, int >() );
      TEST_CHECK( iter_foldl_if_count<T, void>() == iter_foldr_if_count<T, void>() );
      TEST_CHECK( iter_foldl_if_count<T, char>() == iter_foldr_if_count<T, char>() );
      TEST_CHECK( iter_foldl_if_count<T, long>() == iter_foldr_if_count<T, long>() );
      
      using ET = vector<>;
      TEST_CHECK( iter_foldl_if_count<ET, void>() == 0);
      TEST_CHECK( iter_foldl_if_count<ET, void>() == iter_foldr_if_count<ET, void>());
    }
    // list
    {
      using T = list<int, int, void, int, void, char>;
      TEST_CHECK( iter_foldl_if_count<T, int>()  == 3 );
      TEST_CHECK( iter_foldl_if_count<T, void>() == 2 );
      TEST_CHECK( iter_foldl_if_count<T, char>() == 1 );
      TEST_CHECK( iter_foldl_if_count<T, long>() == 0 );
      
      TEST_CHECK(  iter_foldr_if_count<T, int >() == 3 );
      TEST_CHECK(  iter_foldr_if_count<T, void>() == 2 );
      TEST_CHECK(  iter_foldr_if_count<T, char>() == 1 );
      TEST_CHECK(  iter_foldr_if_count<T, long>() == 0 );
      
      using ET = list<>;
      TEST_CHECK( iter_foldl_if_count<ET, void>() == 0);
      TEST_CHECK( iter_foldl_if_count<ET, void>() == iter_foldr_if_count<ET, void>());
    }
  }
  
//-------------------------------- iter_fold --------------------------------// 

   // mp_iter_foldl)
  {
    // pack
    {
      using T = pack<int, int, void, int, void, char>;
      TEST_CHECK( iter_foldl_count<T, int>()  == 3 );
      TEST_CHECK( iter_foldl_count<T, void>() == 2 );
      TEST_CHECK( iter_foldl_count<T, char>() == 1 );
      TEST_CHECK( iter_foldl_count<T, long>() == 0 );
      
      TEST_CHECK( iter_foldl_count<T, int>()  == iter_foldr_count<T, int >() );
      TEST_CHECK( iter_foldl_count<T, void>() == iter_foldr_count<T, void>() );
      TEST_CHECK( iter_foldl_count<T, char>() == iter_foldr_count<T, char>() );
      TEST_CHECK( iter_foldl_count<T, long>() == iter_foldr_count<T, long>() );
      
      using ET = pack<>;
      TEST_CHECK( iter_foldl_count<ET, void>() == 0);
      TEST_CHECK( iter_foldl_count<ET, void>() == iter_foldr_count<ET, void>());
    }
    // vector
    {
      using T = vector<int, int, void, int, void, char>;
      TEST_CHECK( iter_foldl_count<T, int>()  == 3 );
      TEST_CHECK( iter_foldl_count<T, void>() == 2 );
      TEST_CHECK( iter_foldl_count<T, char>() == 1 );
      TEST_CHECK( iter_foldl_count<T, long>() == 0 );
      
      TEST_CHECK( iter_foldl_count<T, int>()  == iter_foldr_count<T, int >() );
      TEST_CHECK( iter_foldl_count<T, void>() == iter_foldr_count<T, void>() );
      TEST_CHECK( iter_foldl_count<T, char>() == iter_foldr_count<T, char>() );
      TEST_CHECK( iter_foldl_count<T, long>() == iter_foldr_count<T, long>() );
      
      using ET = vector<>;
      TEST_CHECK( iter_foldl_count<ET, void>() == 0);
      TEST_CHECK( iter_foldl_count<ET, void>() == iter_foldr_count<ET, void>());
    }
    // list
    {
      using T = list<int, int, void, int, void, char>;
      TEST_CHECK( iter_foldl_count<T, int>()  == 3 );
      TEST_CHECK( iter_foldl_count<T, void>() == 2 );
      TEST_CHECK( iter_foldl_count<T, char>() == 1 );
      TEST_CHECK( iter_foldl_count<T, long>() == 0 );
      
      TEST_CHECK(  iter_foldr_count<T, int >() == 3 );
      TEST_CHECK(  iter_foldr_count<T, void>() == 2 );
      TEST_CHECK(  iter_foldr_count<T, char>() == 1 );
      TEST_CHECK(  iter_foldr_count<T, long>() == 0 );
      
      using ET = list<>;
      TEST_CHECK( iter_foldl_count<ET, void>() == 0);
      TEST_CHECK( iter_foldl_count<ET, void>() == iter_foldr_count<ET, void>());
    }
  }
  
  
//---------------------------- fold_n ----------------------------------// 

  // mp_foldl_n)
  {
    // pack
    {
      using T = pack<int, int, void, int, void, char>;
      TEST_CHECK( foldl_n_count<T, int>()  == 3 );
      TEST_CHECK( foldl_n_count<T, void>() == 2 );
      TEST_CHECK( foldl_n_count<T, char>() == 1 );
      TEST_CHECK( foldl_n_count<T, long>() == 0 );
      
      TEST_CHECK( foldl_n_count<T, int>()  == foldr_n_count<T, int >() );
      TEST_CHECK( foldl_n_count<T, void>() == foldr_n_count<T, void>() );
      TEST_CHECK( foldl_n_count<T, char>() == foldr_n_count<T, char>() );
      TEST_CHECK( foldl_n_count<T, long>() == foldr_n_count<T, long>() );
      
      using ET = pack<>;
      TEST_CHECK( foldl_n_count<ET, void>() == 0);
      TEST_CHECK( foldl_n_count<ET, void>() == foldr_n_count<ET, void>());
    }
    // vector
    {
      using T = vector<int, int, void, int, void, char>;
      TEST_CHECK( foldl_n_count<T, int>()  == 3 );
      TEST_CHECK( foldl_n_count<T, void>() == 2 );
      TEST_CHECK( foldl_n_count<T, char>() == 1 );
      TEST_CHECK( foldl_n_count<T, long>() == 0 );
      
      TEST_CHECK( foldl_n_count<T, int>()  == foldr_n_count<T, int >() );
      TEST_CHECK( foldl_n_count<T, void>() == foldr_n_count<T, void>() );
      TEST_CHECK( foldl_n_count<T, char>() == foldr_n_count<T, char>() );
      TEST_CHECK( foldl_n_count<T, long>() == foldr_n_count<T, long>() );
      
      using ET = vector<>;
      TEST_CHECK( foldl_n_count<ET, void>() == 0);
      TEST_CHECK( foldl_n_count<ET, void>() == foldr_n_count<ET, void>());
    }
    // list
    {
      using T = list<int, int, void, int, void, char>;
      TEST_CHECK( foldl_n_count<T, int>()  == 3 );
      TEST_CHECK( foldl_n_count<T, void>() == 2 );
      TEST_CHECK( foldl_n_count<T, char>() == 1 );
      TEST_CHECK( foldl_n_count<T, long>() == 0 );
      
      TEST_CHECK(  foldr_n_count<T, int >() == 3 );
      TEST_CHECK(  foldr_n_count<T, void>() == 2 );
      TEST_CHECK(  foldr_n_count<T, char>() == 1 );
      TEST_CHECK(  foldr_n_count<T, long>() == 0 );
      
      using ET = list<>;
      TEST_CHECK( foldl_n_count<ET, void>() == 0);
      TEST_CHECK( foldl_n_count<ET, void>() == foldr_n_count<ET, void>());
    }
  }

  
//-------------------------------- fold_if -----------------------------// 

  // mp_foldl_if)
  {
    // pack
    {
      using T = pack<int, int, void, int, void, char>;
      TEST_CHECK( foldl_if_count<T, int>()  == 3 );
      TEST_CHECK( foldl_if_count<T, void>() == 2 );
      TEST_CHECK( foldl_if_count<T, char>() == 1 );
      TEST_CHECK( foldl_if_count<T, long>() == 0 );
      
      TEST_CHECK( foldl_if_count<T, int>()  == foldr_if_count<T, int >() );
      TEST_CHECK( foldl_if_count<T, void>() == foldr_if_count<T, void>() );
      TEST_CHECK( foldl_if_count<T, char>() == foldr_if_count<T, char>() );
      TEST_CHECK( foldl_if_count<T, long>() == foldr_if_count<T, long>() );
      
      using ET = pack<>;
      TEST_CHECK( foldl_if_count<ET, void>() == 0);
      TEST_CHECK( foldl_if_count<ET, void>() == foldr_if_count<ET, void>());
    }
    // vector
    {
      using T = vector<int, int, void, int, void, char>;
      TEST_CHECK( foldl_if_count<T, int>()  == 3 );
      TEST_CHECK( foldl_if_count<T, void>() == 2 );
      TEST_CHECK( foldl_if_count<T, char>() == 1 );
      TEST_CHECK( foldl_if_count<T, long>() == 0 );
      
      TEST_CHECK( foldl_if_count<T, int>()  == foldr_if_count<T, int >() );
      TEST_CHECK( foldl_if_count<T, void>() == foldr_if_count<T, void>() );
      TEST_CHECK( foldl_if_count<T, char>() == foldr_if_count<T, char>() );
      TEST_CHECK( foldl_if_count<T, long>() == foldr_if_count<T, long>() );
      
      using ET = vector<>;
      TEST_CHECK( foldl_if_count<ET, void>() == 0);
      TEST_CHECK( foldl_if_count<ET, void>() == foldr_if_count<ET, void>());
    }
    // list
    {
      using T = list<int, int, void, int, void, char>;
      TEST_CHECK( foldl_if_count<T, int>()  == 3 );
      TEST_CHECK( foldl_if_count<T, void>() == 2 );
      TEST_CHECK( foldl_if_count<T, char>() == 1 );
      TEST_CHECK( foldl_if_count<T, long>() == 0 );
      
      TEST_CHECK(  foldr_if_count<T, int >() == 3 );
      TEST_CHECK(  foldr_if_count<T, void>() == 2 );
      TEST_CHECK(  foldr_if_count<T, char>() == 1 );
      TEST_CHECK(  foldr_if_count<T, long>() == 0 );
      
      using ET = list<>;
      TEST_CHECK( foldl_if_count<ET, void>() == 0);
      TEST_CHECK( foldl_if_count<ET, void>() == foldr_if_count<ET, void>());
    }
  }
  
  
  
//-------------------------------- fold --------------------------------// 

   // mp_foldl)
  {
    // pack
    {
      using T = pack<int, int, void, int, void, char>;
      TEST_CHECK( foldl_count<T, int>()  == 3 );
      TEST_CHECK( foldl_count<T, void>() == 2 );
      TEST_CHECK( foldl_count<T, char>() == 1 );
      TEST_CHECK( foldl_count<T, long>() == 0 );
      
      TEST_CHECK( foldl_count<T, int>()  == foldr_count<T, int >() );
      TEST_CHECK( foldl_count<T, void>() == foldr_count<T, void>() );
      TEST_CHECK( foldl_count<T, char>() == foldr_count<T, char>() );
      TEST_CHECK( foldl_count<T, long>() == foldr_count<T, long>() );
      
      using ET = pack<>;
      TEST_CHECK( foldl_count<ET, void>() == 0);
      TEST_CHECK( foldl_count<ET, void>() == foldr_count<ET, void>());
    }
    // vector
    {
      using T = vector<int, int, void, int, void, char>;
      TEST_CHECK( foldl_count<T, int>()  == 3 );
      TEST_CHECK( foldl_count<T, void>() == 2 );
      TEST_CHECK( foldl_count<T, char>() == 1 );
      TEST_CHECK( foldl_count<T, long>() == 0 );
      
      TEST_CHECK( foldl_count<T, int>()  == foldr_count<T, int >() );
      TEST_CHECK( foldl_count<T, void>() == foldr_count<T, void>() );
      TEST_CHECK( foldl_count<T, char>() == foldr_count<T, char>() );
      TEST_CHECK( foldl_count<T, long>() == foldr_count<T, long>() );
      
      using ET = vector<>;
      TEST_CHECK( foldl_count<ET, void>() == 0);
      TEST_CHECK( foldl_count<ET, void>() == foldr_count<ET, void>());
    }
    // list
    {
      using T = list<int, int, void, int, void, char>;
      TEST_CHECK( foldl_count<T, int>()  == 3 );
      TEST_CHECK( foldl_count<T, void>() == 2 );
      TEST_CHECK( foldl_count<T, char>() == 1 );
      TEST_CHECK( foldl_count<T, long>() == 0 );
      
      TEST_CHECK(  foldr_count<T, int >() == 3 );
      TEST_CHECK(  foldr_count<T, void>() == 2 );
      TEST_CHECK(  foldr_count<T, char>() == 1 );
      TEST_CHECK(  foldr_count<T, long>() == 0 );
      
      using ET = list<>;
      TEST_CHECK( foldl_count<ET, void>() == 0);
      TEST_CHECK( foldl_count<ET, void>() == foldr_count<ET, void>());
    }
  }
  
  
  
////////////////////////////////////////////////////////////////////////////////
//                            Querying                                              
////////////////////////////////////////////////////////////////////////////////

//-------------------------------- find & find_if ------------------------// 

  // mp_algorithm_foldl_variadic)
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
        
        TEST_SAME_TYPE(Int, FInt);
        TEST_SAME_TYPE(Char, FChar);
        TEST_SAME_TYPE(Float, FFloat);
        TEST_SAME_TYPE(E, FDNE);
        
        // empty
        using TE = pack<>;
        using FDNE2 = find_t<TE, int>;
        TEST_SAME_TYPE( end_t<TE>, FDNE2 );
    }
    // vector
    {
        using T = vector<int, int, int, void, int, int, int>;
        using B = begin_t<T>;
        using Void = advance_c_t<B, 3>;
        using E = end_t<T>;
        
        using Pred1 = not_< aux::is_same<int, _1> >;
        using FVoid = find_if_t<T, Pred1>;
        TEST_SAME_TYPE(Void, FVoid);
        
        using Pred2 = lambda< aux::is_same<char, _1> >;
        using FDNE = find_if_t<T, Pred2>;
        TEST_SAME_TYPE(FDNE, E);
        
        // empty
        using TE = vector<>;
        using FDNE2 = find_if_t<TE, Pred1>;
        TEST_SAME_TYPE( end_t<TE>, FDNE2 );
    }
    // list
    {
      using T = list<void, void, int, int, char>;
      using B = begin_t<T>;
      using Void = B;
      using Int = advance_c_t<B, 2>;
      using Char = advance_c_t<B, 4>;
      using E = end_t<T>;
      
      TEST_SAME_TYPE( find_t<T, void>, Void );
      TEST_SAME_TYPE( find_t<T, int>,  Int  );
      TEST_SAME_TYPE( find_t<T, char>, Char );
      TEST_SAME_TYPE( find_t<T, long>, E    );
      
      using ET = list<>;
      
      TEST_SAME_TYPE( find_t<ET, void>, end_t<ET> );
    }
  }                                              // mp_algorithm_foldl_dispatch
  
//-------------------------------- count --------------------------------// 

  // mp_algorithm_count_test)
  {
    // pack
    {
      using T = pack<int, int, int, char, char, bool, int, int>;
      
      TEST_CHECK( 5 == count_t<T, int >() );
      TEST_CHECK( 2 == count_t<T, char>() );
      TEST_CHECK( 1 == count_t<T, bool>() );
      TEST_CHECK( 0 == count_t<T, void>() );
      
      using TE = pack<>;
      TEST_CHECK( 0 == count_t<TE, void>() );
    }
    // vector
    {
      using T = vector<int, int, int, char, char, bool, int, int>;
      
      TEST_CHECK( 5 == count_if_t<T, aux::is_same<int, _1> >() );
      TEST_CHECK( 7 == count_if_t<T, not_<aux::is_same<bool, _1>> >() );
      TEST_CHECK( 3 == count_if_t<T, or_<aux::is_same<bool, _1>, aux::is_same<char, _1>> >() );
      TEST_CHECK( 0 == count_if_t<T, aux::is_same<_1, void>>() );
      
      using TE = vector<>;
      TEST_CHECK( 0 == count_if_t<TE, always<true_>>() );
    }
    // list
    {
      using T = list<int, int, void>;
      
      TEST_CHECK( count_t<T, int>() == 2 );
      TEST_CHECK( count_t<T, void>() == 1 );
      TEST_CHECK( count_t<T, unsigned>() == 0 );
      
      using E = list<>;
      
      TEST_CHECK( 0 == count_t<E, void>() );
    }
  }                                                 // mp_algorithm_count_test
  
  
//-------------------------------- sequence equal ---------------------------// 

  // mp_algorithm_sequence_equal)
  {
    // pack tests
    {
      using T1 = pack<char, short, int, long>;
      using T2 = pack<char, short, int, long>;
      using E1 = pack<>;
      using E2 = pack<>;
      using T3 = pack<void>;
      using T4 = pack<char, long>;
      
      TEST_CHECK( sequence_equal<T1, T2>() );
      TEST_CHECK( sequence_equal<E1, E2>() );
      TEST_CHECK( !sequence_equal<T1, E1>() );
      TEST_CHECK( !sequence_equal<T1, T3>() );
      TEST_CHECK( !sequence_equal<T4, T1>() );
    }
    // vector tests
    {
      using T1 = vector_c<int, 1, 2, 3>;
      using T2 = vector< int_<1>, int_<2>, int_<3> >;
      using E1 = vector<>;
      using E2 = vector_c<int>;
      using T3 = vector< int_<1> >;
      
      TEST_CHECK( sequence_equal<T1, T2>() );
      TEST_CHECK( sequence_equal<E1, E2>() );
      TEST_CHECK( !sequence_equal<T1, E1>() );
      TEST_CHECK( !sequence_equal<T1, T3>() );
      TEST_CHECK( !sequence_equal<E1, T3>() );
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
      
      TEST_CHECK( sequence_equal<P1, V1>() );
      TEST_CHECK( sequence_equal<P1, L1>() );
      TEST_CHECK( sequence_equal<L1, V1>() );
      
      TEST_CHECK( sequence_equal<EP, EV>() );
      TEST_CHECK( sequence_equal<EP, EL>() );
      TEST_CHECK( sequence_equal<EL, EV>() );
      
      TEST_CHECK( !sequence_equal<P2, V2>() );
      TEST_CHECK( !sequence_equal<L2, P2>() );
      TEST_CHECK( !sequence_equal<L2, V2>() );
      
      TEST_CHECK( !sequence_equal<P1, EV>() );
      TEST_CHECK( !sequence_equal<P1, EL>() );
      TEST_CHECK( !sequence_equal<V1, EP>() );
      TEST_CHECK( !sequence_equal<V1, EL>() );
      TEST_CHECK( !sequence_equal<L1, EP>() );
      TEST_CHECK( !sequence_equal<L1, EV>() );
    }
  }                                              // mp_algorithm_sequence_equal

  
//-------------------------------- lower bound ------------------------------// 

  // mp_algorithm_lower_bound_test)
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
      
      TEST_SAME_TYPE( lower_bound_t<T, int_<-1>>, B );
      TEST_SAME_TYPE( lower_bound_t<T, int_<0>>, Zero );
      TEST_SAME_TYPE( lower_bound_t<T, int_<1>>, One );
      TEST_SAME_TYPE( lower_bound_t<T, int_<2>>, Two );
      TEST_SAME_TYPE( lower_bound_t<T, int_<3>>, Three );
      TEST_SAME_TYPE( lower_bound_t<T, int_<4>>, Four );
      TEST_SAME_TYPE( lower_bound_t<T, int_<5>>, Ten);
      TEST_SAME_TYPE( lower_bound_t<T, int_<10>>, Ten);
      TEST_SAME_TYPE( lower_bound_t<T, int_<11>>, E);
      
      using ET = pack<>;
      TEST_SAME_TYPE( lower_bound_t<ET, int_<1>>, begin_t<ET> );
    }
    // vector
    {
      using T = vector_c<int, 1, 5, 10>;
      using B = begin_t<T>;
      using One = B;
      using Five = next_t<One>;
      using Ten = next_t<Five>;
      using E = end_t<T>;
      
      TEST_SAME_TYPE( lower_bound_t<T, int_<-1>>, B );
      TEST_SAME_TYPE( lower_bound_t<T, int_<1>>, One );
      TEST_SAME_TYPE( lower_bound_t<T, int_<2>>, Five );
      TEST_SAME_TYPE( lower_bound_t<T, int_<5>>, Five );
      TEST_SAME_TYPE( lower_bound_t<T, int_<6>>, Ten );
      TEST_SAME_TYPE( lower_bound_t<T, int_<10>>, Ten );
      TEST_SAME_TYPE( lower_bound_t<T, int_<50>>, E );
      
      using ET = vector<>;
      TEST_SAME_TYPE( lower_bound_t<ET, int_<-10>>, begin_t<ET> );
    }
    // list
    {
      using T = list_c<int, -1, 1>;
      using B = begin_t<T>;
      using NOne = B;
      using One = next_t<NOne>;
      using E = end_t<T>;
      
      TEST_SAME_TYPE( lower_bound_t<T, int_<-3>>, B );
      TEST_SAME_TYPE( lower_bound_t<T, int_<-1>>, NOne );
      TEST_SAME_TYPE( lower_bound_t<T, int_<0>>, One );
      TEST_SAME_TYPE( lower_bound_t<T, int_<1>>, One );
      TEST_SAME_TYPE( lower_bound_t<T, int_<3>>, E );
      
      using ET = list<>;
      TEST_SAME_TYPE( lower_bound_t<ET, int_<0>>, end_t<ET> );
    }
  }                                            // mp_algorithm_lower_bound_test
  
  
//-------------------------------- upper bound -------------------------------/
  
  // mp_algorithm_upper_bound_test)
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
      TEST_SAME_TYPE(Four, E);
      
      TEST_SAME_TYPE( upper_bound_t<T, int_<-1>>, B );
      TEST_SAME_TYPE( upper_bound_t<T, int_<0>>, Zero );
      TEST_SAME_TYPE( upper_bound_t<T, int_<1>>, One );
      TEST_SAME_TYPE( upper_bound_t<T, int_<2>>, One );
      TEST_SAME_TYPE( upper_bound_t<T, int_<3>>, Three );
      TEST_SAME_TYPE( upper_bound_t<T, int_<4>>, Four );
      TEST_SAME_TYPE( upper_bound_t<T, int_<5>>, E );
        
      using ET = pack<>;
      TEST_SAME_TYPE( upper_bound_t<ET, int_<0>>, begin_t<ET> );
    }
    // vector
    {
      using T = vector_c<int, 0, 0, 1>;
      using B = begin_t<T>;
      using Zero = advance_c_t<B, 2>;
      using One = next_t<Zero>;
      using E = end_t<T>;
      
      // sanity check
      TEST_SAME_TYPE( One, E );
      
      TEST_SAME_TYPE( upper_bound_t<T, int_<-1>>, B );
      TEST_SAME_TYPE( upper_bound_t<T, int_<0>>, Zero );
      TEST_SAME_TYPE( upper_bound_t<T, int_<1>>, One );
      TEST_SAME_TYPE( upper_bound_t<T, int_<2>>, E );
      TEST_SAME_TYPE( upper_bound_t<T, int_<10>>, E );
      
      using ET = vector<>;
      TEST_SAME_TYPE( upper_bound_t<ET, int_<-10>>, begin_t<ET> );
    }
    // list
    {
      using T = list_c<int, 1, 2, 2>;
      using B = begin_t<T>;
      using One = next_t<B>;
      using Two = next_t< next_t<One> >;
      using E = end_t< T >;
      
      // sanity check
      TEST_SAME_TYPE( Two, E );
      
      TEST_SAME_TYPE( upper_bound_t<T, int_<0>>, B );
      TEST_SAME_TYPE( upper_bound_t<T, int_<1>>, One );
      TEST_SAME_TYPE( upper_bound_t<T, int_<2>>, Two );
      TEST_SAME_TYPE( upper_bound_t<T, int_<3>>, E );
      TEST_SAME_TYPE( upper_bound_t<T, int_<4>>, E );
      
      using ET = list<>;
      TEST_SAME_TYPE( upper_bound_t<ET, int_<10>>, begin_t<ET> );
    }
  }                                            // mp_algorithm_upper_bound_test
  
  
////////////////////////////////////////////////////////////////////////////////
//                            Transforming                                            
////////////////////////////////////////////////////////////////////////////////


  // mp_algorithm_copy_test)
  {
    // copy test
    {
      using P = pack   <int, char, void>;
      using V = vector <int, char, void>;
      using L = list   <int, char, void>;
      
      using R = pack<void, char, int>;
      
      TEST_CHECK( sequence_equal_t<copy_t<P>, P>() );
      TEST_CHECK( sequence_equal_t<copy_t<V>, V>() );
      TEST_CHECK( sequence_equal_t<copy_t<L>, L>() );
      
      TEST_CHECK( sequence_equal_t<reverse_copy_t<P>, R>() );
      TEST_CHECK( sequence_equal_t<reverse_copy_t<V>, R>() );
      TEST_CHECK( sequence_equal_t<reverse_copy_t<L>, R>() );
    }
  }                                                   // mp_algorithm_copy_test
  

  // mp_algorithm_remove_test)
  {
    using P = pack  <int, void, void, int, int, void, int>;
    using V = vector<int, void, void, int, int, void, int>;
    using L = list  <int, void, void, int, int, void, int>;
    
    using E = pack<void, void, void>;
    
    TEST_CHECK( sequence_equal_t<remove_t<P, int>, E>() );
    TEST_CHECK( sequence_equal_t<remove_t<V, int>, E>() );
    TEST_CHECK( sequence_equal_t<remove_t<L, int>, E>() );
    
    TEST_CHECK( sequence_equal_t<reverse_remove_t<P, int>, E>() );
    TEST_CHECK( sequence_equal_t<reverse_remove_t<V, int>, E>() );
    TEST_CHECK( sequence_equal_t<reverse_remove_t<L, int>, E>() );
  }                                                 // mp_algorithm_remove_test
  

  // mp_algorithm_replace_test)
  {
    using P = pack  <int, void, void, int, int, void, int>;
    using V = vector<int, void, void, int, int, void, int>;
    using L = list  <int, void, void, int, int, void, int>;
    
    using E = pack  <long, void, void, long, long, void, long>;
    
    TEST_CHECK( sequence_equal_t<replace_t<P, int, long>, E>() );
    TEST_CHECK( sequence_equal_t<replace_t<V, int, long>, E>() );
    TEST_CHECK( sequence_equal_t<replace_t<L, int, long>, E>() );
    
    TEST_CHECK( sequence_equal_t<reverse_replace_t<P, int, long>, E>() );
    TEST_CHECK( sequence_equal_t<reverse_replace_t<V, int, long>, E>() );
    TEST_CHECK( sequence_equal_t<reverse_replace_t<L, int, long>, E>() );
  }                                                 // mp_algorithm_replace_test
  
  
  // mp_algorithm_unique_test)
  {
    using P = pack< int, long, long, long, void, void, char, void >;
    using V = vector< int, long, long, long, void, void, char, void >;
    using L = list< int, long, long, long, void, void, char, void >;
    
    using E = pack< int, long, void, char, void >;
    TEST_CHECK( sequence_equal_t<unique_t<P, not_<aux::is_same<_1, _2>>>, E>() );
    TEST_CHECK( sequence_equal_t<unique_t<V, not_<aux::is_same<_1, _2>>>, E>() );
    TEST_CHECK( sequence_equal_t<unique_t<L, not_<aux::is_same<_1, _2>>>, E>() );
    
    
    TEST_CHECK( sequence_equal_t<reverse_unique_t<P, not_<aux::is_same<_1, _2>>>, E>() );
    TEST_CHECK( sequence_equal_t<reverse_unique_t<V, not_<aux::is_same<_1, _2>>>, E>() );
    TEST_CHECK( sequence_equal_t<reverse_unique_t<L, not_<aux::is_same<_1, _2>>>, E>() );
  }                                                // mp_algorithm_unique_test
  
  /* For some reason, this section makes cov-build hang */
#if !defined(ELIB_CONFIG_COVERITY_SCAN)
  // mp_algorithm_transform_test)
  {
    // unary
    {
      using P = pack  < int, int, int, int, void, void, int, void >;
      using V = vector< int, int, int, int, void, void, int, void >;
      using L = list  < int, int, int, int, void, void, int, void >;
      
      using E = pack< void, void, void, void, int, int, void, int >;
      
      using Tr = 
        if_<
            aux::is_same<int, _1>
          , void
          , int
        >;
      
      TEST_CHECK( sequence_equal_t<transform_t<P, Tr>, E>() );
      TEST_CHECK( sequence_equal_t<transform_t<V, Tr>, E>() );
      TEST_CHECK( sequence_equal_t<transform_t<L, Tr>, E>() );
      
      TEST_CHECK( sequence_equal_t<reverse_transform_t<P, Tr>, E>() );
      TEST_CHECK( sequence_equal_t<reverse_transform_t<V, Tr>, E>() );
      TEST_CHECK( sequence_equal_t<reverse_transform_t<L, Tr>, E>() );
    }
    // binary
    {
      using P = pack  < int, char, long, void >;
      using V = vector< int, char, long, void >;
      using L = list  < int, char, long, void >;
      
      using E = 
        pack<
          pair<int, int>, pair<char, char>
        , pair<long, long>, pair<void, void>
        >;
        
      using Tr = pair<_1, _2>;
      TEST_CHECK( sequence_equal_t<transform_t<P, P, Tr>, E>() );
      TEST_CHECK( sequence_equal_t<transform_t<V, L, Tr>, E>() );
      TEST_CHECK( sequence_equal_t<transform_t<L, P, Tr>, E>() );
      
      TEST_CHECK( sequence_equal_t<reverse_transform_t<P, V, Tr>, E>() );
      TEST_CHECK( sequence_equal_t<reverse_transform_t<V, P, Tr>, E>() );
      TEST_CHECK( sequence_equal_t<reverse_transform_t<L, V, Tr>, E>() );
    }
  }                                                // mp_algorithm_transform_test
  

  // mp_algorithm_partition_test)
  {
    using P = pack_c   <int, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10>;
    using V = vector_c <int, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10>;
    using L = list_c   <int, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10>;
    
    using E1 = pack_c<int, 1, 3, 5, 7, 9>;
    using E2 = pack_c<int, 2, 4, 6, 8, 10>;
    using EP = pair< E1, E2 >;
    
    TEST_CHECK( pair_equal_t<partition_t<P, is_odd<_1>>, EP>() );
    TEST_CHECK( pair_equal_t<partition_t<V, is_odd<_1>>, EP>() );
    TEST_CHECK( pair_equal_t<partition_t<L, is_odd<_1>>, EP>() );
    
    TEST_CHECK( pair_equal_t<reverse_partition_t<P, is_odd<_1>>, EP>() );
    TEST_CHECK( pair_equal_t<reverse_partition_t<V, is_odd<_1>>, EP>() );
    TEST_CHECK( pair_equal_t<reverse_partition_t<L, is_odd<_1>>, EP>() );
  }                                              // mp_algorithm_partition_test
  
#endif /* ELIB_CONFIG_COVERITY_SCAN_HPP */
}
