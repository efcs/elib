#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>


#include <elib/optional.hpp>
using namespace elib;

#if defined(ELIB_CONFIG_COVERITY_SCAN)
# define ELIB_OPTIONAL_CONSTEXPR
#else
# define ELIB_OPTIONAL_CONSTEXPR constexpr
#endif
/// Try and create constexpr optional instances
namespace cexpr_test
{
    using opt = optional<int>;
    ELIB_OPTIONAL_CONSTEXPR int x = 0;
    
    ELIB_OPTIONAL_CONSTEXPR opt o1;
    ELIB_OPTIONAL_CONSTEXPR opt o2(nullopt);
    ELIB_OPTIONAL_CONSTEXPR opt o3(x);
    ELIB_OPTIONAL_CONSTEXPR opt o4(0);
    ELIB_OPTIONAL_CONSTEXPR opt o5(in_place, x);
    ELIB_OPTIONAL_CONSTEXPR opt o6(in_place, 0);
}
#undef ELIB_OPTIONAL_CONSTEXPR

using namespace cexpr_test;

BOOST_AUTO_TEST_SUITE(elib_optional_constexpr_test_suite)

BOOST_AUTO_TEST_CASE(check_good_compile_time)
{
    static_assert(not o1.good(), "");
    static_assert(not o2.good(), "");
    static_assert(o3.good(), "");
    static_assert(o4.good(), "");
    static_assert(o5.good(), "");
    static_assert(o6.good(), "");
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(check_good_runtime)
{
    BOOST_CHECK(not o1.good());
    BOOST_CHECK(not o2.good());
    BOOST_CHECK(o3.good());
    BOOST_CHECK(o4.good());
    BOOST_CHECK(o5.good());
    BOOST_CHECK(o6.good());
}

BOOST_AUTO_TEST_SUITE_END()