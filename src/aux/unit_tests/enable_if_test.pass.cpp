// REQUIRES: ELIB_AUX_SOURCE
#include <elib/aux/enable_if.hpp>
#include <elib/aux/integral_constant.hpp>
#include <elib/aux/type_pair.hpp>
#include <elib/aux/traits/is_same.hpp>
#include "rapid-cxx-test.hpp"


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


TEST_SUITE(elib_aux_enable_if_test_suite)

TEST_CASE(enable_if_default_type_test)
{
    {
        using T = try_get_type<enable_if<true_>>;
        TEST_STATIC_ASSERT(enabled<T>());
        TEST_STATIC_ASSERT(is_same<T::second, void>::value);
    }
    {
        using T = enable_if_t<true_>;
        TEST_STATIC_ASSERT(is_same<T, void>::value);
    }
    {
        using T = try_get_type<enable_if_c<true>>;
        TEST_STATIC_ASSERT(enabled<T>());
        TEST_STATIC_ASSERT(is_same<T::second, void>::value);
    }
    {
        using T = enable_if_c_t<true>;
        TEST_STATIC_ASSERT(is_same<T, void>::value);
    }
    {
        using T = try_get_type<enable_if<false_>>;
        TEST_STATIC_ASSERT(disabled<T>());
    }
    {
        using T = try_get_type<enable_if_c<false>>;
        TEST_STATIC_ASSERT(disabled<T>());
    }
    TEST_CHECK(true);
}

TEST_CASE(enable_if_custom_type)
{
    {
        using T = try_get_type<enable_if<true_, int>>;
        TEST_STATIC_ASSERT(enabled<T>());
        TEST_STATIC_ASSERT(is_same<T::second, int>::value);
    }
    {
        using T = enable_if_t<true_, int>;
        TEST_STATIC_ASSERT(is_same<T, int>::value);
    }
    {
        using T = try_get_type<enable_if_c<true, int>>;
        TEST_STATIC_ASSERT(enabled<T>());
        TEST_STATIC_ASSERT(is_same<T::second, int>::value);
    }
    {
        using T = enable_if_c_t<true, int>;
        TEST_STATIC_ASSERT(is_same<T, int>::value);
    }
    {
        using T = try_get_type<enable_if<false_, int>>;
        TEST_STATIC_ASSERT(disabled<T>());
    }
    {
        using T = try_get_type<enable_if_c<false, int>>;
        TEST_STATIC_ASSERT(disabled<T>());
    }
    TEST_CHECK(true);
}

TEST_CASE(lazy_enable_if_default_test)
{
    {
        using T = try_get_type<lazy_enable_if<true_>>;
        TEST_STATIC_ASSERT(enabled<T>());
        TEST_STATIC_ASSERT(is_same<T::second, void>::value);
    }
    {
        using T = lazy_enable_if_t<true_>;
        TEST_STATIC_ASSERT(is_same<T, void>::value);
    }
    {
        using T = try_get_type<lazy_enable_if_c<true>>;
        TEST_STATIC_ASSERT(enabled<T>());
        TEST_STATIC_ASSERT(is_same<T::second, void>::value);
    }
    {
        using T = lazy_enable_if_c_t<true>;
        TEST_STATIC_ASSERT(is_same<T, void>::value);
    }
    {
        using T = try_get_type<lazy_enable_if<false_>>;
        TEST_STATIC_ASSERT(disabled<T>());
    }
    {
        using T = try_get_type<lazy_enable_if_c<false>>;
        TEST_STATIC_ASSERT(disabled<T>());
    }
    TEST_CHECK(true);
}

TEST_CASE(lazy_enable_if_custom_type_test)
{
    {
        using T = try_get_type<lazy_enable_if<true_, lazy_holder>>;
        TEST_STATIC_ASSERT(enabled<T>());
        TEST_STATIC_ASSERT(is_same<T::second, lazy>::value);
    }
    {
        using T = lazy_enable_if_t<true_, lazy_holder>;
        TEST_STATIC_ASSERT(is_same<T, lazy>::value);
    }
    {
        using T = try_get_type<lazy_enable_if_c<true, lazy_holder>>;
        TEST_STATIC_ASSERT(enabled<T>());
        TEST_STATIC_ASSERT(is_same<T::second, lazy>::value);
    }
    {
        using T = lazy_enable_if_c_t<true, lazy_holder>;
        TEST_STATIC_ASSERT(is_same<T, lazy>::value);
    }
    {
        using T = try_get_type<lazy_enable_if<false_, empty>>;
        TEST_STATIC_ASSERT(disabled<T>());
    }
    {
        using T = try_get_type<lazy_enable_if_c<false, empty>>;
        TEST_STATIC_ASSERT(disabled<T>());
    }
    TEST_CHECK(true);
}

TEST_CASE(disable_if_default_type_test)
{
    {
        using T = try_get_type<disable_if<false_>>;
        TEST_STATIC_ASSERT(enabled<T>());
        TEST_STATIC_ASSERT(is_same<T::second, void>::value);
    }
    {
        using T = disable_if_t<false_>;
        TEST_STATIC_ASSERT(is_same<T, void>::value);
    }
    {
        using T = try_get_type<disable_if_c<false>>;
        TEST_STATIC_ASSERT(enabled<T>());
        TEST_STATIC_ASSERT(is_same<T::second, void>::value);
    }
    {
        using T = disable_if_c_t<false>;
        TEST_STATIC_ASSERT(is_same<T, void>::value);
    }
    {
        using T = try_get_type<disable_if<true_>>;
        TEST_STATIC_ASSERT(disabled<T>());
    }
    {
        using T = try_get_type<disable_if_c<true>>;
        TEST_STATIC_ASSERT(disabled<T>());
    }
    TEST_CHECK(true);
}

TEST_CASE(disable_if_custom_type_test)
{
    {
        using T = try_get_type<disable_if<false_, int>>;
        TEST_STATIC_ASSERT(enabled<T>());
        TEST_STATIC_ASSERT(is_same<T::second, int>::value);
    }
    {
        using T = disable_if_t<false_, int>;
        TEST_STATIC_ASSERT(is_same<T, int>::value);
    }
    {
        using T = try_get_type<disable_if_c<false, int>>;
        TEST_STATIC_ASSERT(enabled<T>());
        TEST_STATIC_ASSERT(is_same<T::second, int>::value);
    }
    {
        using T = disable_if_c_t<false, int>;
        TEST_STATIC_ASSERT(is_same<T, int>::value);
    }
    {
        using T = try_get_type<disable_if<true_, int>>;
        TEST_STATIC_ASSERT(disabled<T>());
    }
    {
        using T = try_get_type<disable_if_c<true, int>>;
        TEST_STATIC_ASSERT(disabled<T>());
    }
    TEST_CHECK(true);
}

TEST_CASE(lazy_disable_if_default_type_test)
{
    {
        using T = try_get_type<lazy_disable_if<false_>>;
        TEST_STATIC_ASSERT(enabled<T>());
        TEST_STATIC_ASSERT(is_same<T::second, void>::value);
    }
    {
        using T = lazy_disable_if_t<false_>;
        TEST_STATIC_ASSERT(is_same<T, void>::value);
    }
    {
        using T = try_get_type<lazy_disable_if_c<false>>;
        TEST_STATIC_ASSERT(enabled<T>());
        TEST_STATIC_ASSERT(is_same<T::second, void>::value);
    }
    {
        using T = lazy_disable_if_c_t<false>;
        TEST_STATIC_ASSERT(is_same<T, void>::value);
    }
    {
        using T = try_get_type<lazy_disable_if<true_>>;
        TEST_STATIC_ASSERT(disabled<T>());
    }
    {
        using T = try_get_type<lazy_disable_if_c<true>>;
        TEST_STATIC_ASSERT(disabled<T>());
    }
    TEST_CHECK(true);
}

TEST_CASE(lazy_disable_if_custom_type_test)
{
    {
        using T = try_get_type<lazy_disable_if<false_, lazy_holder>>;
        TEST_STATIC_ASSERT(enabled<T>());
        TEST_STATIC_ASSERT(is_same<T::second, lazy>::value);
    }
    {
        using T = lazy_disable_if_t<false_, lazy_holder>;
        TEST_STATIC_ASSERT(is_same<T, lazy>::value);
    }
    {
        using T = try_get_type<lazy_disable_if_c<false, lazy_holder>>;
        TEST_STATIC_ASSERT(enabled<T>());
        TEST_STATIC_ASSERT(is_same<T::second, lazy>::value);
    }
    {
        using T = lazy_disable_if_c_t<false, lazy_holder>;
        TEST_STATIC_ASSERT(is_same<T, lazy>::value);
    }
    {
        using T = try_get_type<lazy_disable_if<true_, empty>>;
        TEST_STATIC_ASSERT(disabled<T>());
    }
    {
        using T = try_get_type<lazy_disable_if_c<true, empty>>;
        TEST_STATIC_ASSERT(disabled<T>());
    }
    TEST_CHECK(true);
}

TEST_SUITE_END()