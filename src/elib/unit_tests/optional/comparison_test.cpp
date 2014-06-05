#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <elib/optional.hpp>
using elib::optional;
using elib::nullopt;


BOOST_AUTO_TEST_SUITE(elib_optional_comparison_test_suite)

BOOST_AUTO_TEST_CASE(empty_identity_compare_test)
{
    const optional<int> o1;
    
    BOOST_CHECK( o1 == o1 );
    BOOST_CHECK( not (o1 != o1) );
    BOOST_CHECK( not (o1 < o1) );
    BOOST_CHECK( not (o1 > o1) );
    BOOST_CHECK( o1 <= o1 );
    BOOST_CHECK( o1 >= o1 );
}

BOOST_AUTO_TEST_CASE(non_empty_identity_compare_test)
{
    const optional<int> o1(0);
    
    BOOST_CHECK( o1 == o1 );
    BOOST_CHECK( not (o1 != o1) );
    BOOST_CHECK( not (o1 < o1) );
    BOOST_CHECK( not (o1 > o1) );
    BOOST_CHECK( o1 <= o1 );
    BOOST_CHECK( o1 >= o1 );
}

BOOST_AUTO_TEST_CASE(compare_against_empty_test)
{
    const optional<int> o1;
    const optional<int> o2(0);
    
    BOOST_CHECK( not (o1 == o2) );
    BOOST_CHECK( not (o2 == o1) );
        
    BOOST_CHECK( o1 != o2 );
    BOOST_CHECK( o2 != o1 );
        
    BOOST_CHECK( o1 < o2 );
    BOOST_CHECK( not (o2 < o1) );
        
    BOOST_CHECK( not (o1 > o2) );
    BOOST_CHECK( o2 > o1 );
        
    BOOST_CHECK( o1 <= o2 );
    BOOST_CHECK( not (o2 <= o1) );
        
    BOOST_CHECK( not (o1 >= o2) );
    BOOST_CHECK( o2 >= o1 );
}

BOOST_AUTO_TEST_CASE(compare_against_non_equal_test)
{
    const optional<int> o2(0);
    const optional<int> o3(1);
    
    BOOST_CHECK( not (o2 == o3) );
    BOOST_CHECK( not (o3 == o2) );
        
    BOOST_CHECK( o2 != o3 );
    BOOST_CHECK( o3 != o2 );
    
    BOOST_CHECK( o2 < o3 );
    BOOST_CHECK( not (o3 < o2) );
        
    BOOST_CHECK( not (o2 > o3) );
    BOOST_CHECK( o3 > o2 );
        
    BOOST_CHECK( o2 <= o3 );
    BOOST_CHECK( not (o3 <= o2) );
        
    BOOST_CHECK( not (o2 >= o3) );
    BOOST_CHECK( o3 >= o2 );
}

BOOST_AUTO_TEST_CASE(nullopt_compare_empty_test)
{
    const optional<int> o1;
    
    BOOST_CHECK( o1 == nullopt );
    BOOST_CHECK( nullopt == o1 );
    
    BOOST_CHECK( not (o1 != nullopt) );
    BOOST_CHECK( not (nullopt != o1) );
        
    BOOST_CHECK( not (o1 < nullopt) );
    BOOST_CHECK( not (nullopt < o1) );
        
    BOOST_CHECK( not (o1 > nullopt) );
    BOOST_CHECK( not (nullopt > o1) );
        
    BOOST_CHECK( o1 <= nullopt );
    BOOST_CHECK( nullopt <= o1 );
        
    BOOST_CHECK( o1 >= nullopt );
    BOOST_CHECK( nullopt >= o1 );
}

BOOST_AUTO_TEST_CASE(nullopt_compare_non_empty_test)
{
    const optional<int> o2(0);
    
    BOOST_CHECK( not (o2 == nullopt) );
    BOOST_CHECK( not (nullopt == o2) );
        
    BOOST_CHECK( o2 != nullopt );
    BOOST_CHECK( nullopt != o2 );
        
    BOOST_CHECK( not (o2 < nullopt) );
    BOOST_CHECK( nullopt < o2 );
        
    BOOST_CHECK( o2 > nullopt );
    BOOST_CHECK( not (nullopt > o2) );
        
    BOOST_CHECK( not (o2 <= nullopt) );
    BOOST_CHECK( nullopt <= o2 );
        
    BOOST_CHECK( o2 >= nullopt );
    BOOST_CHECK( not (nullopt >= o2) );
}

BOOST_AUTO_TEST_CASE(empty_compare_value_test)
{
    const optional<int> o1;
    
    BOOST_CHECK( not (o1 == 0) );
    BOOST_CHECK( not (0 == o1) );
    
    BOOST_CHECK( o1 != 0 );
    BOOST_CHECK( 0 != o1 );
        
    BOOST_CHECK( o1 < 0 );
    BOOST_CHECK( not (0 < o1) );
        
    BOOST_CHECK( not (o1 > 0) );
    BOOST_CHECK( 0 > o1 );
        
    BOOST_CHECK( o1 <= 0 );
    BOOST_CHECK( not (0 <= o1) );
        
    BOOST_CHECK( not (o1 >= 0) );
    BOOST_CHECK( 0 >= o1 );
}

BOOST_AUTO_TEST_CASE(non_empty_compare_with_value_test)
{
    optional<int> const o2(0);
    
    BOOST_CHECK( o2 == 0 );
    BOOST_CHECK( 0 == o2 );
    BOOST_CHECK( not (o2 == 1) );
    BOOST_CHECK( not (1 == o2) );

    BOOST_CHECK( not (o2 != 0) );
    BOOST_CHECK( not (0 != o2) );
    BOOST_CHECK( o2 != 1 );
    BOOST_CHECK( 1 != o2 );

    BOOST_CHECK( not (o2 < 0) );
    BOOST_CHECK( not (0 < o2) );
    BOOST_CHECK( -1 < o2 );
    BOOST_CHECK( not (1 < o2) );
    BOOST_CHECK( o2 < 1 );
    BOOST_CHECK( not (o2 < -1) );

    BOOST_CHECK( not (o2 > 0) );
    BOOST_CHECK( not (0 > o2) );
    BOOST_CHECK( 1 > o2 );
    BOOST_CHECK( not (-1 > o2) );
    BOOST_CHECK( o2 > -1 );
    BOOST_CHECK( not (o2 > 1) );

    BOOST_CHECK( o2 <= 0 );
    BOOST_CHECK( 0 <= o2 );
    BOOST_CHECK( -1 <= o2 );
    BOOST_CHECK( not (1 <= o2) );
    BOOST_CHECK( o2 <= 1 );
    BOOST_CHECK( not (o2 <= -1) );

    BOOST_CHECK( o2 >= 0 );
    BOOST_CHECK( 0 >= o2 );
    BOOST_CHECK( 1 >= o2 );
    BOOST_CHECK( not (-1 >= o2) );
    BOOST_CHECK( o2 >= -1 );
    BOOST_CHECK( not (o2 >= 1) );
}

BOOST_AUTO_TEST_SUITE_END()