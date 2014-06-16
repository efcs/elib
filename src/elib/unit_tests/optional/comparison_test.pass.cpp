// REQUIRES: ELIB_SOURCE
#include <elib/optional.hpp>
#include "rapid-cxx-test.hpp"
using elib::optional;
using elib::nullopt;


TEST_SUITE(elib_optional_comparison_test_suite)

TEST_CASE(empty_identity_compare_test)
{
    const optional<int> o1;
    
    TEST_CHECK( o1 == o1 );
    TEST_CHECK( not (o1 != o1) );
    TEST_CHECK( not (o1 < o1) );
    TEST_CHECK( not (o1 > o1) );
    TEST_CHECK( o1 <= o1 );
    TEST_CHECK( o1 >= o1 );
}

TEST_CASE(non_empty_identity_compare_test)
{
    const optional<int> o1(0);
    
    TEST_CHECK( o1 == o1 );
    TEST_CHECK( not (o1 != o1) );
    TEST_CHECK( not (o1 < o1) );
    TEST_CHECK( not (o1 > o1) );
    TEST_CHECK( o1 <= o1 );
    TEST_CHECK( o1 >= o1 );
}

TEST_CASE(compare_against_empty_test)
{
    const optional<int> o1;
    const optional<int> o2(0);
    
    TEST_CHECK( not (o1 == o2) );
    TEST_CHECK( not (o2 == o1) );
        
    TEST_CHECK( o1 != o2 );
    TEST_CHECK( o2 != o1 );
        
    TEST_CHECK( o1 < o2 );
    TEST_CHECK( not (o2 < o1) );
        
    TEST_CHECK( not (o1 > o2) );
    TEST_CHECK( o2 > o1 );
        
    TEST_CHECK( o1 <= o2 );
    TEST_CHECK( not (o2 <= o1) );
        
    TEST_CHECK( not (o1 >= o2) );
    TEST_CHECK( o2 >= o1 );
}

TEST_CASE(compare_against_non_equal_test)
{
    const optional<int> o2(0);
    const optional<int> o3(1);
    
    TEST_CHECK( not (o2 == o3) );
    TEST_CHECK( not (o3 == o2) );
        
    TEST_CHECK( o2 != o3 );
    TEST_CHECK( o3 != o2 );
    
    TEST_CHECK( o2 < o3 );
    TEST_CHECK( not (o3 < o2) );
        
    TEST_CHECK( not (o2 > o3) );
    TEST_CHECK( o3 > o2 );
        
    TEST_CHECK( o2 <= o3 );
    TEST_CHECK( not (o3 <= o2) );
        
    TEST_CHECK( not (o2 >= o3) );
    TEST_CHECK( o3 >= o2 );
}

TEST_CASE(nullopt_compare_empty_test)
{
    const optional<int> o1;
    
    TEST_CHECK( o1 == nullopt );
    TEST_CHECK( nullopt == o1 );
    
    TEST_CHECK( not (o1 != nullopt) );
    TEST_CHECK( not (nullopt != o1) );
        
    TEST_CHECK( not (o1 < nullopt) );
    TEST_CHECK( not (nullopt < o1) );
        
    TEST_CHECK( not (o1 > nullopt) );
    TEST_CHECK( not (nullopt > o1) );
        
    TEST_CHECK( o1 <= nullopt );
    TEST_CHECK( nullopt <= o1 );
        
    TEST_CHECK( o1 >= nullopt );
    TEST_CHECK( nullopt >= o1 );
}

TEST_CASE(nullopt_compare_non_empty_test)
{
    const optional<int> o2(0);
    
    TEST_CHECK( not (o2 == nullopt) );
    TEST_CHECK( not (nullopt == o2) );
        
    TEST_CHECK( o2 != nullopt );
    TEST_CHECK( nullopt != o2 );
        
    TEST_CHECK( not (o2 < nullopt) );
    TEST_CHECK( nullopt < o2 );
        
    TEST_CHECK( o2 > nullopt );
    TEST_CHECK( not (nullopt > o2) );
        
    TEST_CHECK( not (o2 <= nullopt) );
    TEST_CHECK( nullopt <= o2 );
        
    TEST_CHECK( o2 >= nullopt );
    TEST_CHECK( not (nullopt >= o2) );
}

TEST_CASE(empty_compare_value_test)
{
    const optional<int> o1;
    
    TEST_CHECK( not (o1 == 0) );
    TEST_CHECK( not (0 == o1) );
    
    TEST_CHECK( o1 != 0 );
    TEST_CHECK( 0 != o1 );
        
    TEST_CHECK( o1 < 0 );
    TEST_CHECK( not (0 < o1) );
        
    TEST_CHECK( not (o1 > 0) );
    TEST_CHECK( 0 > o1 );
        
    TEST_CHECK( o1 <= 0 );
    TEST_CHECK( not (0 <= o1) );
        
    TEST_CHECK( not (o1 >= 0) );
    TEST_CHECK( 0 >= o1 );
}

TEST_CASE(non_empty_compare_with_value_test)
{
    optional<int> const o2(0);
    
    TEST_CHECK( o2 == 0 );
    TEST_CHECK( 0 == o2 );
    TEST_CHECK( not (o2 == 1) );
    TEST_CHECK( not (1 == o2) );

    TEST_CHECK( not (o2 != 0) );
    TEST_CHECK( not (0 != o2) );
    TEST_CHECK( o2 != 1 );
    TEST_CHECK( 1 != o2 );

    TEST_CHECK( not (o2 < 0) );
    TEST_CHECK( not (0 < o2) );
    TEST_CHECK( -1 < o2 );
    TEST_CHECK( not (1 < o2) );
    TEST_CHECK( o2 < 1 );
    TEST_CHECK( not (o2 < -1) );

    TEST_CHECK( not (o2 > 0) );
    TEST_CHECK( not (0 > o2) );
    TEST_CHECK( 1 > o2 );
    TEST_CHECK( not (-1 > o2) );
    TEST_CHECK( o2 > -1 );
    TEST_CHECK( not (o2 > 1) );

    TEST_CHECK( o2 <= 0 );
    TEST_CHECK( 0 <= o2 );
    TEST_CHECK( -1 <= o2 );
    TEST_CHECK( not (1 <= o2) );
    TEST_CHECK( o2 <= 1 );
    TEST_CHECK( not (o2 <= -1) );

    TEST_CHECK( o2 >= 0 );
    TEST_CHECK( 0 >= o2 );
    TEST_CHECK( 1 >= o2 );
    TEST_CHECK( not (-1 >= o2) );
    TEST_CHECK( o2 >= -1 );
    TEST_CHECK( not (o2 >= 1) );
}

TEST_SUITE_END()