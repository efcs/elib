// REQUIRES: ELIB_ITERATOR_SOURCE
#include <elib/iterator.hpp>
#include <elib/aux/integral_constant.hpp>
#include <elib/aux/static_assert.hpp>
#include <elib/aux/traits/is_same.hpp>
#include <iterator>
#include "test/helper.hpp"
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

TEST_CASE(elib_iterator_traits_test_suite)
{

    // iterator_traits_t_test)
    {
        using T = input_it;
        using Tr = std::iterator_traits<T>;
        
        TEST_SAME_TYPE(iterator_category_t<T>, Tr::iterator_category);
        TEST_SAME_TYPE(iterator_difference_t<T>, Tr::difference_type);
        TEST_SAME_TYPE(iterator_value_t<T>, Tr::value_type);
        TEST_SAME_TYPE(iterator_reference_t<T>, Tr::reference);
        TEST_SAME_TYPE(iterator_pointer_t<T>, Tr::pointer);
    }

    // tag_traits_test)
    {
        {
            TEST_STATIC_ASSERT(is_input_tag<std::input_iterator_tag>::value);
            TEST_STATIC_ASSERT(not is_input_tag<std::output_iterator_tag>::value);
            TEST_STATIC_ASSERT(is_input_tag<std::forward_iterator_tag>::value);
            TEST_STATIC_ASSERT(is_input_tag<std::bidirectional_iterator_tag>::value);
            TEST_STATIC_ASSERT(is_input_tag<std::random_access_iterator_tag>::value);
        }{
            TEST_STATIC_ASSERT(not is_output_tag<std::input_iterator_tag>::value);
            TEST_STATIC_ASSERT(is_output_tag<std::output_iterator_tag>::value);
            TEST_STATIC_ASSERT(not is_output_tag<std::forward_iterator_tag>::value);
            TEST_STATIC_ASSERT(not is_output_tag<std::bidirectional_iterator_tag>::value);
            TEST_STATIC_ASSERT(not is_output_tag<std::random_access_iterator_tag>::value);
        }{
            TEST_STATIC_ASSERT(not is_forward_tag<std::input_iterator_tag>::value);
            TEST_STATIC_ASSERT(not is_forward_tag<std::output_iterator_tag>::value);
            TEST_STATIC_ASSERT(is_forward_tag<std::forward_iterator_tag>::value);
            TEST_STATIC_ASSERT(is_forward_tag<std::bidirectional_iterator_tag>::value);
            TEST_STATIC_ASSERT(is_forward_tag<std::random_access_iterator_tag>::value);
        }{ 
            TEST_STATIC_ASSERT(not is_bidirectional_tag<std::input_iterator_tag>::value);
            TEST_STATIC_ASSERT(not is_bidirectional_tag<std::output_iterator_tag>::value);
            TEST_STATIC_ASSERT(not is_bidirectional_tag<std::forward_iterator_tag>::value);
            TEST_STATIC_ASSERT(is_bidirectional_tag<std::bidirectional_iterator_tag>::value);
            TEST_STATIC_ASSERT(is_bidirectional_tag<std::random_access_iterator_tag>::value);
        }{
            TEST_STATIC_ASSERT(not is_random_access_tag<std::input_iterator_tag>::value);
            TEST_STATIC_ASSERT(not is_random_access_tag<std::output_iterator_tag>::value);
            TEST_STATIC_ASSERT(not is_random_access_tag<std::forward_iterator_tag>::value);
            TEST_STATIC_ASSERT(not is_random_access_tag<std::bidirectional_iterator_tag>::value);
            TEST_STATIC_ASSERT(is_random_access_tag<std::random_access_iterator_tag>::value);
        }
    }

    // iterator_tag_traits_test)
    {
        {
            TEST_STATIC_ASSERT(is_input_iterator<input_it>::value);
            TEST_STATIC_ASSERT(not is_input_iterator<output_it>::value);
            TEST_STATIC_ASSERT(is_input_iterator<forward_it>::value);
            TEST_STATIC_ASSERT(is_input_iterator<bidir_it>::value);
            TEST_STATIC_ASSERT(is_input_iterator<random_it>::value);
        }{
            TEST_STATIC_ASSERT(not is_output_iterator<input_it>::value);
            TEST_STATIC_ASSERT(is_output_iterator<output_it>::value);
            TEST_STATIC_ASSERT(not is_output_iterator<forward_it>::value);
            TEST_STATIC_ASSERT(not is_output_iterator<bidir_it>::value);
            TEST_STATIC_ASSERT(not is_output_iterator<random_it>::value);
        }{
            TEST_STATIC_ASSERT(not is_forward_iterator<input_it>::value);
            TEST_STATIC_ASSERT(not is_forward_iterator<output_it>::value);
            TEST_STATIC_ASSERT(is_forward_iterator<forward_it>::value);
            TEST_STATIC_ASSERT(is_forward_iterator<bidir_it>::value);
            TEST_STATIC_ASSERT(is_forward_iterator<random_it>::value);
        }{
            TEST_STATIC_ASSERT(not is_bidirectional_iterator<input_it>::value);
            TEST_STATIC_ASSERT(not is_bidirectional_iterator<output_it>::value);
            TEST_STATIC_ASSERT(not is_bidirectional_iterator<forward_it>::value);
            TEST_STATIC_ASSERT(is_bidirectional_iterator<bidir_it>::value);
            TEST_STATIC_ASSERT(is_bidirectional_iterator<random_it>::value);
        }{
            TEST_STATIC_ASSERT(not is_random_access_iterator<input_it>::value);
            TEST_STATIC_ASSERT(not is_random_access_iterator<output_it>::value);
            TEST_STATIC_ASSERT(not is_random_access_iterator<forward_it>::value);
            TEST_STATIC_ASSERT(not is_random_access_iterator<bidir_it>::value);
            TEST_STATIC_ASSERT(is_random_access_iterator<random_it>::value);
        }
    }

    // is_iteroperable_test)
    {
        TEST_STATIC_ASSERT(is_interoperable<convert_from_it, convert_to_it>::value);
        TEST_STATIC_ASSERT(not is_interoperable<convert_from_it, convert_to_none>::value);
    }

    // choose_iterator_traits_test)
    {
        using T = choose_iterator_traits<convert_from_it, convert_to_it>;
        using E = std::iterator_traits<convert_to_it>;
        TEST_STATIC_ASSERT(elib::aux::is_same<T, E>::value);
    }

    // choose_difference_type_test)
    {
        using T = choose_difference_type<convert_from_it, convert_to_it>;
        using E = unsigned long;
        TEST_STATIC_ASSERT(elib::aux::is_same<T, E>::value);
    }

}