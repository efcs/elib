#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>


#include <elib/aux/enable_if.hpp>
#include <elib/aux/integral_constant.hpp>
#include <elib/aux/static_assert.hpp>
#include <elib/aux/type_pair.hpp>
#include <elib/aux/traits/is_same.hpp>

using namespace elib::aux;

struct empty {};
struct lazy {};
struct lazy_holder { using type = lazy; };

template <class T, class Type = typename T::type>
auto try_get_type_impl(int) -> type_pair<true_, Type>;

template <class T>
auto try_get_type_impl(long) -> type_pair<false_, empty>;

template <class T>
using try_get_type = decltype(try_get_type_impl<T>(0));

template <class T>
constexpr bool enabled() noexcept { return try_get_type<T>::first::value; }

template <class T>
constexpr bool disabled() noexcept { return try_get_type<T>::first::value; }


BOOST_AUTO_TEST_SUITE(elib_aux_enable_if_test_suite)

BOOST_AUTO_TEST_CASE(enable_if_default_type_test)
{
    {
        using T = try_get_type<enable_if<true_>>;
        ELIB_STATIC_ASSERT(enabled<T>());
        ELIB_STATIC_ASSERT(is_same<T::second, void>::value);
    }
    {
        using T = enable_if_t<true_>;
        ELIB_STATIC_ASSERT(is_same<T, void>::value);
    }
    {
        using T = try_get_type<enable_if_c<true>>;
        ELIB_STATIC_ASSERT(enabled<T>());
        ELIB_STATIC_ASSERT(is_same<T::second, void>::value);
    }
    {
        using T = enable_if_c_t<true>;
        ELIB_STATIC_ASSERT(is_same<T, void>::value);
    }
    {
        using T = try_get_type<enable_if<false_>>;
        ELIB_STATIC_ASSERT(disabled<T>());
    }
    {
        using T = try_get_type<enable_if_c<false>>;
        ELIB_STATIC_ASSERT(disabled<T>());
    }
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(enable_if_custom_type)
{
    {
        using T = try_get_type<enable_if<true_, int>>;
        ELIB_STATIC_ASSERT(enabled<T>());
        ELIB_STATIC_ASSERT(is_same<T::second, int>::value);
    }
    {
        using T = enable_if_t<true_, int>;
        ELIB_STATIC_ASSERT(is_same<T, int>::value);
    }
    {
        using T = try_get_type<enable_if_c<true, int>>;
        ELIB_STATIC_ASSERT(enabled<T>());
        ELIB_STATIC_ASSERT(is_same<T::second, int>::value);
    }
    {
        using T = enable_if_c_t<true, int>;
        ELIB_STATIC_ASSERT(is_same<T, int>::value);
    }
    {
        using T = try_get_type<enable_if<false_, int>>;
        ELIB_STATIC_ASSERT(disabled<T>());
    }
    {
        using T = try_get_type<enable_if_c<false, int>>;
        ELIB_STATIC_ASSERT(disabled<T>());
    }
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(lazy_enable_if_default_test)
{
    {
        using T = try_get_type<lazy_enable_if<true_>>;
        ELIB_STATIC_ASSERT(enabled<T>());
        ELIB_STATIC_ASSERT(is_same<T::second, void>::value);
    }
    {
        using T = lazy_enable_if_t<true_>;
        ELIB_STATIC_ASSERT(is_same<T, void>::value);
    }
    {
        using T = try_get_type<lazy_enable_if_c<true>>;
        ELIB_STATIC_ASSERT(enabled<T>());
        ELIB_STATIC_ASSERT(is_same<T::second, void>::value);
    }
    {
        using T = lazy_enable_if_c_t<true>;
        ELIB_STATIC_ASSERT(is_same<T, void>::value);
    }
    {
        using T = try_get_type<lazy_enable_if<false_>>;
        ELIB_STATIC_ASSERT(disabled<T>());
    }
    {
        using T = try_get_type<lazy_enable_if_c<false>>;
        ELIB_STATIC_ASSERT(disabled<T>());
    }
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(lazy_enable_if_custom_type_test)
{
    {
        using T = try_get_type<lazy_enable_if<true_, lazy_holder>>;
        ELIB_STATIC_ASSERT(enabled<T>());
        ELIB_STATIC_ASSERT(is_same<T::second, lazy>::value);
    }
    {
        using T = lazy_enable_if_t<true_, lazy_holder>;
        ELIB_STATIC_ASSERT(is_same<T, lazy>::value);
    }
    {
        using T = try_get_type<lazy_enable_if_c<true, lazy_holder>>;
        ELIB_STATIC_ASSERT(enabled<T>());
        ELIB_STATIC_ASSERT(is_same<T::second, lazy>::value);
    }
    {
        using T = lazy_enable_if_c_t<true, lazy_holder>;
        ELIB_STATIC_ASSERT(is_same<T, lazy>::value);
    }
    {
        using T = try_get_type<lazy_enable_if<false_, empty>>;
        ELIB_STATIC_ASSERT(disabled<T>());
    }
    {
        using T = try_get_type<lazy_enable_if_c<false, empty>>;
        ELIB_STATIC_ASSERT(disabled<T>());
    }
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(disable_if_default_type_test)
{
    {
        using T = try_get_type<disable_if<false_>>;
        ELIB_STATIC_ASSERT(enabled<T>());
        ELIB_STATIC_ASSERT(is_same<T::second, void>::value);
    }
    {
        using T = disable_if_t<false_>;
        ELIB_STATIC_ASSERT(is_same<T, void>::value);
    }
    {
        using T = try_get_type<disable_if_c<false>>;
        ELIB_STATIC_ASSERT(enabled<T>());
        ELIB_STATIC_ASSERT(is_same<T::second, void>::value);
    }
    {
        using T = disable_if_c_t<false>;
        ELIB_STATIC_ASSERT(is_same<T, void>::value);
    }
    {
        using T = try_get_type<disable_if<true_>>;
        ELIB_STATIC_ASSERT(disabled<T>());
    }
    {
        using T = try_get_type<disable_if_c<true>>;
        ELIB_STATIC_ASSERT(disabled<T>());
    }
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(disable_if_custom_type_test)
{
    {
        using T = try_get_type<disable_if<false_, int>>;
        ELIB_STATIC_ASSERT(enabled<T>());
        ELIB_STATIC_ASSERT(is_same<T::second, int>::value);
    }
    {
        using T = disable_if_t<false_, int>;
        ELIB_STATIC_ASSERT(is_same<T, int>::value);
    }
    {
        using T = try_get_type<disable_if_c<false, int>>;
        ELIB_STATIC_ASSERT(enabled<T>());
        ELIB_STATIC_ASSERT(is_same<T::second, int>::value);
    }
    {
        using T = disable_if_c_t<false, int>;
        ELIB_STATIC_ASSERT(is_same<T, int>::value);
    }
    {
        using T = try_get_type<disable_if<true_, int>>;
        ELIB_STATIC_ASSERT(disabled<T>());
    }
    {
        using T = try_get_type<disable_if_c<true, int>>;
        ELIB_STATIC_ASSERT(disabled<T>());
    }
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(lazy_disable_if_default_type_test)
{
    {
        using T = try_get_type<lazy_disable_if<false_>>;
        ELIB_STATIC_ASSERT(enabled<T>());
        ELIB_STATIC_ASSERT(is_same<T::second, void>::value);
    }
    {
        using T = lazy_disable_if_t<false_>;
        ELIB_STATIC_ASSERT(is_same<T, void>::value);
    }
    {
        using T = try_get_type<lazy_disable_if_c<false>>;
        ELIB_STATIC_ASSERT(enabled<T>());
        ELIB_STATIC_ASSERT(is_same<T::second, void>::value);
    }
    {
        using T = lazy_disable_if_c_t<false>;
        ELIB_STATIC_ASSERT(is_same<T, void>::value);
    }
    {
        using T = try_get_type<lazy_disable_if<true_>>;
        ELIB_STATIC_ASSERT(disabled<T>());
    }
    {
        using T = try_get_type<lazy_disable_if_c<true>>;
        ELIB_STATIC_ASSERT(disabled<T>());
    }
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(lazy_disable_if_custom_type_test)
{
    {
        using T = try_get_type<lazy_disable_if<false_, lazy_holder>>;
        ELIB_STATIC_ASSERT(enabled<T>());
        ELIB_STATIC_ASSERT(is_same<T::second, lazy>::value);
    }
    {
        using T = lazy_disable_if_t<false_, lazy_holder>;
        ELIB_STATIC_ASSERT(is_same<T, lazy>::value);
    }
    {
        using T = try_get_type<lazy_disable_if_c<false, lazy_holder>>;
        ELIB_STATIC_ASSERT(enabled<T>());
        ELIB_STATIC_ASSERT(is_same<T::second, lazy>::value);
    }
    {
        using T = lazy_disable_if_c_t<false, lazy_holder>;
        ELIB_STATIC_ASSERT(is_same<T, lazy>::value);
    }
    {
        using T = try_get_type<lazy_disable_if<true_, empty>>;
        ELIB_STATIC_ASSERT(disabled<T>());
    }
    {
        using T = try_get_type<lazy_disable_if_c<true, empty>>;
        ELIB_STATIC_ASSERT(disabled<T>());
    }
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_SUITE_END()