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

BOOST_AUTO_TEST_SUITE(mp_algorithm_test_suite)

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
        
        static_assert( is_lambda_expression< deref_wrapper<same_type<int, _1>> >::value, 
                      " must me lambda expression ");
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
  }                                              // mp_algorithm_foldl_dispatch
  
//-------------------------------- count --------------------------------// 

  BOOST_AUTO_TEST_CASE(mp_algorithm_count_test)
  {
    // pack
    {
      using T = pack<int, int, int, char, char, bool, int, int>;
      using IntC = int_<5>;
      using CharC = int_<2>;
      using BoolC = int_<1>;
      using VoidC = int_<0>;
      
      CHECK( 5 == count_t<T, int >() );
      CHECK( 2 == count_t<T, char>() );
      CHECK( 1 == count_t<T, bool>() );
      CHECK( 0 == count_t<T, void>() );
      
      using TE = pack<>;
      CHECK( 0 == count_t<T, void>() );
    }
    // vector
    {
      using T = vector<int, int, int, char, char, bool, int, int>;
      using IntC = int_<5>;
      using CharC = int_<2>;
      using BoolC = int_<1>;
      using VoidC = int_<0>;
      
      CHECK( 5 == count_if_t<T, same_type<int, _1> >() );
      CHECK( 7 == count_if_t<T, not_<same_type<bool, _1>> >() );
      CHECK( 3 == count_if_t<T, or_<same_type<bool, _1>, same_type<char, _1>> >() );
      CHECK( 0 == count_if_t<T, same_type<_1, void>>() );
      
      using TE = vector<>;
      CHECK( 0 == count_if_t<TE, always<true_>>() );
    }
  }                                                 // mp_algorithm_count_test
  
BOOST_AUTO_TEST_SUITE_END()
