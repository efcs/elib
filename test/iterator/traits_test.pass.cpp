#define BOOST_TEST_MODULE Main
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <elib/iterator.hpp>
#include <elib/aux/integral_constant.hpp>
#include <elib/aux/static_assert.hpp>
#include <elib/aux/traits/is_same.hpp>
#include <iterator>
using namespace elib::iter;

struct input_it : std::iterator<std::input_iterator_tag, int> {};
struct output_it : std::iterator<std::output_iterator_tag, int> {};
struct forward_it : std::iterator<std::forward_iterator_tag, int> {};
struct bidir_it : std::iterator<std::bidirectional_iterator_tag, int> {};
struct random_it : std::iterator<std::random_access_iterator_tag, int> {};
struct not_it {};

struct convert_from_it : std::iterator<std::forward_iterator_tag, int, long> {};

struct convert_to_it : std::iterator<std::forward_iterator_tag, int, unsigned long>
{
    convert_to_it() = default;
    convert_to_it(convert_from_it const &) {}
};

struct convert_to_none : std::iterator<std::forward_iterator_tag, int> {};

BOOST_AUTO_TEST_SUITE(elib_iterator_traits_test_suite)

#define ASSERT_SAME(...) ELIB_STATIC_ASSERT(::elib::aux::is_same<__VA_ARGS__>::value)

BOOST_AUTO_TEST_CASE(iterator_traits_t_test)
{
    using T = input_it;
    using Tr = std::iterator_traits<T>;
    
    ASSERT_SAME(iterator_category_t<T>, Tr::iterator_category);
    ASSERT_SAME(iterator_difference_t<T>, Tr::difference_type);
    ASSERT_SAME(iterator_value_t<T>, Tr::value_type);
    ASSERT_SAME(iterator_reference_t<T>, Tr::reference);
    ASSERT_SAME(iterator_pointer_t<T>, Tr::pointer);
    
    BOOST_CHECK(true);
}
#undef ASSERT_SAME

BOOST_AUTO_TEST_CASE(tag_traits_test)
{
    {
        ELIB_STATIC_ASSERT(is_input_tag<std::input_iterator_tag>::value);
        ELIB_STATIC_ASSERT(not is_input_tag<std::output_iterator_tag>::value);
        ELIB_STATIC_ASSERT(is_input_tag<std::forward_iterator_tag>::value);
        ELIB_STATIC_ASSERT(is_input_tag<std::bidirectional_iterator_tag>::value);
        ELIB_STATIC_ASSERT(is_input_tag<std::random_access_iterator_tag>::value);
    }{
        ELIB_STATIC_ASSERT(not is_output_tag<std::input_iterator_tag>::value);
        ELIB_STATIC_ASSERT(is_output_tag<std::output_iterator_tag>::value);
        ELIB_STATIC_ASSERT(not is_output_tag<std::forward_iterator_tag>::value);
        ELIB_STATIC_ASSERT(not is_output_tag<std::bidirectional_iterator_tag>::value);
        ELIB_STATIC_ASSERT(not is_output_tag<std::random_access_iterator_tag>::value);
    }{
        ELIB_STATIC_ASSERT(not is_forward_tag<std::input_iterator_tag>::value);
        ELIB_STATIC_ASSERT(not is_forward_tag<std::output_iterator_tag>::value);
        ELIB_STATIC_ASSERT(is_forward_tag<std::forward_iterator_tag>::value);
        ELIB_STATIC_ASSERT(is_forward_tag<std::bidirectional_iterator_tag>::value);
        ELIB_STATIC_ASSERT(is_forward_tag<std::random_access_iterator_tag>::value);
    }{ 
        ELIB_STATIC_ASSERT(not is_bidirectional_tag<std::input_iterator_tag>::value);
        ELIB_STATIC_ASSERT(not is_bidirectional_tag<std::output_iterator_tag>::value);
        ELIB_STATIC_ASSERT(not is_bidirectional_tag<std::forward_iterator_tag>::value);
        ELIB_STATIC_ASSERT(is_bidirectional_tag<std::bidirectional_iterator_tag>::value);
        ELIB_STATIC_ASSERT(is_bidirectional_tag<std::random_access_iterator_tag>::value);
    }{
        ELIB_STATIC_ASSERT(not is_random_access_tag<std::input_iterator_tag>::value);
        ELIB_STATIC_ASSERT(not is_random_access_tag<std::output_iterator_tag>::value);
        ELIB_STATIC_ASSERT(not is_random_access_tag<std::forward_iterator_tag>::value);
        ELIB_STATIC_ASSERT(not is_random_access_tag<std::bidirectional_iterator_tag>::value);
        ELIB_STATIC_ASSERT(is_random_access_tag<std::random_access_iterator_tag>::value);
    }
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(iterator_tag_traits_test)
{
    {
        ELIB_STATIC_ASSERT(is_input_iterator<input_it>::value);
        ELIB_STATIC_ASSERT(not is_input_iterator<output_it>::value);
        ELIB_STATIC_ASSERT(is_input_iterator<forward_it>::value);
        ELIB_STATIC_ASSERT(is_input_iterator<bidir_it>::value);
        ELIB_STATIC_ASSERT(is_input_iterator<random_it>::value);
    }{
        ELIB_STATIC_ASSERT(not is_output_iterator<input_it>::value);
        ELIB_STATIC_ASSERT(is_output_iterator<output_it>::value);
        ELIB_STATIC_ASSERT(not is_output_iterator<forward_it>::value);
        ELIB_STATIC_ASSERT(not is_output_iterator<bidir_it>::value);
        ELIB_STATIC_ASSERT(not is_output_iterator<random_it>::value);
    }{
        ELIB_STATIC_ASSERT(not is_forward_iterator<input_it>::value);
        ELIB_STATIC_ASSERT(not is_forward_iterator<output_it>::value);
        ELIB_STATIC_ASSERT(is_forward_iterator<forward_it>::value);
        ELIB_STATIC_ASSERT(is_forward_iterator<bidir_it>::value);
        ELIB_STATIC_ASSERT(is_forward_iterator<random_it>::value);
    }{
        ELIB_STATIC_ASSERT(not is_bidirectional_iterator<input_it>::value);
        ELIB_STATIC_ASSERT(not is_bidirectional_iterator<output_it>::value);
        ELIB_STATIC_ASSERT(not is_bidirectional_iterator<forward_it>::value);
        ELIB_STATIC_ASSERT(is_bidirectional_iterator<bidir_it>::value);
        ELIB_STATIC_ASSERT(is_bidirectional_iterator<random_it>::value);
    }{
        ELIB_STATIC_ASSERT(not is_random_access_iterator<input_it>::value);
        ELIB_STATIC_ASSERT(not is_random_access_iterator<output_it>::value);
        ELIB_STATIC_ASSERT(not is_random_access_iterator<forward_it>::value);
        ELIB_STATIC_ASSERT(not is_random_access_iterator<bidir_it>::value);
        ELIB_STATIC_ASSERT(is_random_access_iterator<random_it>::value);
    }
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(is_iteroperable_test)
{
    ELIB_STATIC_ASSERT(is_interoperable<convert_from_it, convert_to_it>::value);
    ELIB_STATIC_ASSERT(not is_interoperable<convert_from_it, convert_to_none>::value);
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(choose_iterator_traits_test)
{
    using T = choose_iterator_traits<convert_from_it, convert_to_it>;
    using E = std::iterator_traits<convert_to_it>;
    ELIB_STATIC_ASSERT(elib::aux::is_same<T, E>::value);
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(choose_difference_type_test)
{
    using T = choose_difference_type<convert_from_it, convert_to_it>;
    using E = unsigned long;
    ELIB_STATIC_ASSERT(elib::aux::is_same<T, E>::value);
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_SUITE_END()