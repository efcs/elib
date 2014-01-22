#ifndef ELIB_MP_UNIT_TESTS_MP_TEST_HELPER_HPP
#define ELIB_MP_UNIT_TESTS_MP_TEST_HELPER_HPP

namespace elib { namespace mp { } }
# include <elib/aux.hpp>

# include <type_traits>

using namespace elib;
using namespace elib::mp;

using std::is_same;

# define SAME_TYPE(...) BOOST_CHECK((is_same<__VA_ARGS__>::value))
# define NOT_SAME_TYPE(...) BOOST_CHECK((!is_same<__VA_ARGS__>::value))
# define CHECK(...) BOOST_CHECK((__VA_ARGS__));

#endif /* ELIB_MP_UNIT_TESTS_MP_TEST_HELPER_HPP */