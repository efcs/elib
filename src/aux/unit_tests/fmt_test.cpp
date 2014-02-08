#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <elib/fmt.hpp>
#include <string>
#include <iostream>

BOOST_AUTO_TEST_SUITE(fmt_test_suite)


//TODO
BOOST_AUTO_TEST_CASE(fmt_init)
{
    BOOST_CHECK(true);
    
    elib::fmt(
        "%d %i %u %o %x %X %c"
      , 0, 1, 2, 3, 4, 5, 6
    );
    
    elib::fmt(
        "%f %F %e %E %g %G %a %A"
       , 0.0, 1.0, 1.1, 1.0f, 2.0, 0.0f, 0.2f, 0.0
    );
    
    elib::fmt(
        "%s %s"
      , "Hello", std::string{"World!"}
    );
  
    int x;
    elib::fmt("%p", &x);
    elib::fmt("%n", &x);
}

BOOST_AUTO_TEST_SUITE_END()