// REQUIRES: ELIB_AUX_SOURCE, ELIB_BOOST_TEST
#define BOOST_TEST_MODULE Main
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <elib/aux/type_list.hpp>
#include <elib/aux/static_assert.hpp>
#include <elib/aux/traits/is_same.hpp>

using namespace elib;


BOOST_AUTO_TEST_SUITE(elib_aux_type_list_test_suite)

BOOST_AUTO_TEST_CASE(empty_list_test)
{
    using L = aux::type_list<>;
    ELIB_STATIC_ASSERT(
        aux::is_same<L::type, L>::value
      );
    ELIB_STATIC_ASSERT(
        L::size::value == 0
      );
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(single_item_list_test)
{
    using L = aux::type_list<void>;
    ELIB_STATIC_ASSERT(
        aux::is_same<L::type, L>::value
      );
    ELIB_STATIC_ASSERT(
        L::size::value == 1
      );
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(two_item_list_test)
{
    using L = aux::type_list<void, int>;
    ELIB_STATIC_ASSERT(
        aux::is_same<L::type, L>::value
      );
    ELIB_STATIC_ASSERT(
        L::size::value == 2
      );
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_SUITE_END()