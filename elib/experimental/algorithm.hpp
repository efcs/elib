#ifndef ELIB_EXPERIMENTAL_ALGORITHM_HPP
#define ELIB_EXPERIMENTAL_ALGORITHM_HPP

# include <elib/aux.hpp>
# include <elib/iterator/traits.hpp>
# include <elib/ranges/algorithm.hpp>
# include <elib/ranges/traits.hpp>
# include <algorithm>
# include <utility>

namespace elib { namespace experimental { namespace algo
{
    using std::all_of;
    using std::any_of;
    using std::none_of;
    using std::for_each;
    using std::count;
    using std::count_if;
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class InputIt1, class InputIt2
      , ELIB_ENABLE_IF(iter::is_iterator<InputIt1>::value)
      , ELIB_ENABLE_IF(iter::is_iterator<InputIt2>::value)
      >
    auto mismatch(InputIt1 first1, InputIt1 last1, InputIt2 first2)
    ELIB_AUTO_RETURN( std::mismatch(first1, last1, first2) )
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class InputIt1, class InputIt2, class BinaryPred
      , ELIB_ENABLE_IF(iter::is_iterator<InputIt1>::value)
      , ELIB_ENABLE_IF(iter::is_iterator<InputIt2>::value)
      >
    auto mismatch(InputIt1 first1, InputIt1 last1, InputIt2 first2, BinaryPred p)
    ELIB_AUTO_RETURN( std::mismatch(first1, last1, first2, p) )
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class InputIt1, class InputIt2
      , ELIB_ENABLE_IF(iter::is_iterator<InputIt1>::value)
      , ELIB_ENABLE_IF(iter::is_iterator<InputIt2>::value)
      >
    auto equal(InputIt1 first1, InputIt1 last1, InputIt2 first2)
    ELIB_AUTO_RETURN( std::equal(first1, last1, first2) )
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class InputIt1, class InputIt2, class BinaryPred
      , ELIB_ENABLE_IF(iter::is_iterator<InputIt1>::value)
      , ELIB_ENABLE_IF(iter::is_iterator<InputIt2>::value)
      >
    auto equal(InputIt1 first1, InputIt1 last1, InputIt2 first2, BinaryPred p)
    ELIB_AUTO_RETURN( std::equal(first1, last1, first2, p) )
    
    ////////////////////////////////////////////////////////////////////////////
    using std::find;
    using std::find_if;
    using std::find_if_not;
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class InputIt1, class InputIt2
      , ELIB_ENABLE_IF(iter::is_iterator<InputIt1>::value)
      , ELIB_ENABLE_IF(iter::is_iterator<InputIt2>::value)
      >
    auto find_end(
        InputIt1 first1, InputIt1 last1
      , InputIt2 first2, InputIt2 last2
      )
    ELIB_AUTO_RETURN( std::find_end(first1, last1, first2, last2) )
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class InputIt1, class InputIt2, class BinaryPred
      , ELIB_ENABLE_IF(iter::is_iterator<InputIt1>::value)
      , ELIB_ENABLE_IF(iter::is_iterator<InputIt2>::value)
      >
    auto find_end(
        InputIt1 first1, InputIt1 last1
      , InputIt2 first2, InputIt2 last2
      , BinaryPred p
      )
    ELIB_AUTO_RETURN( std::find_end(first1, last1, first2, last2, p) )
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class InputIt1, class InputIt2
      , ELIB_ENABLE_IF(iter::is_iterator<InputIt1>::value)
      , ELIB_ENABLE_IF(iter::is_iterator<InputIt2>::value)
      >
    auto find_first_of(
        InputIt1 first1, InputIt1 last1
      , InputIt2 first2, InputIt2 last2
      )
    ELIB_AUTO_RETURN( std::find_first_of(first1, last1, first2, last2) )
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class InputIt1, class InputIt2, class BinaryPred
      , ELIB_ENABLE_IF(iter::is_iterator<InputIt1>::value)
      , ELIB_ENABLE_IF(iter::is_iterator<InputIt2>::value)
      >
    auto find_first_of(
        InputIt1 first1, InputIt1 last1
      , InputIt2 first2, InputIt2 last2
      , BinaryPred p
      )
    ELIB_AUTO_RETURN( std::find_first_of(first1, last1, first2, last2, p) )
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class InputIt1
      , ELIB_ENABLE_IF(iter::is_iterator<InputIt1>::value)
      >
    auto adjacent_find(
        InputIt1 first1, InputIt1 last1
      )
    ELIB_AUTO_RETURN( std::adjacent_find(first1, last1) )
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class InputIt1, class BinaryPred
      , ELIB_ENABLE_IF(iter::is_iterator<InputIt1>::value)
      >
    auto adjacent_find(
        InputIt1 first1, InputIt1 last1, BinaryPred p
      )
    ELIB_AUTO_RETURN( std::adjacent_find(first1, last1, p) )
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class InputIt1, class InputIt2
      , ELIB_ENABLE_IF(iter::is_iterator<InputIt1>::value)
      , ELIB_ENABLE_IF(iter::is_iterator<InputIt2>::value)
      >
    auto search(
        InputIt1 first1, InputIt1 last1
      , InputIt2 first2, InputIt2 last2
      )
    ELIB_AUTO_RETURN( std::search(first1, last1, first2, last2) )
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class InputIt1, class InputIt2, class BinaryPred
      , ELIB_ENABLE_IF(iter::is_iterator<InputIt1>::value)
      , ELIB_ENABLE_IF(iter::is_iterator<InputIt2>::value)
      >
    auto search(
        InputIt1 first1, InputIt1 last1
      , InputIt2 first2, InputIt2 last2
      , BinaryPred p
      )
    ELIB_AUTO_RETURN( std::search(first1, last1, first2, last2, p) )
    
    ////////////////////////////////////////////////////////////////////////////
    template<
        class Iter1
      , class Size, class T
      , ELIB_ENABLE_IF(iter::is_iterator<Iter1>::value)
      >
    auto search_n(Iter1 first1, Iter1 last1, Size s, T const & v)
    ELIB_AUTO_RETURN( std::search_n(first1, last1, s, v) )
    
    ////////////////////////////////////////////////////////////////////////////
    template<
        class Iter1
      , class Size, class T, class BinaryPred
      , ELIB_ENABLE_IF(iter::is_iterator<Iter1>::value)
      >
    auto search_n(
        Iter1 first1, Iter1 last1
      , Size s, T const & v, BinaryPred p)
    ELIB_AUTO_RETURN( std::search_n(first1, last1, s, v, p) )
    
    ////////////////////////////////////////////////////////////////////////////
    template<
        class InputIt1, class OutputIt1
      , ELIB_ENABLE_IF(iter::is_input_iterator<InputIt1>::value)
      , ELIB_ENABLE_IF(iter::is_output_iterator<OutputIt1>::value)
      >
    auto copy(InputIt1 first1, InputIt1 last1, OutputIt1 out1)
    ELIB_AUTO_RETURN( std::copy(first1, last1, out1) )
    
    ////////////////////////////////////////////////////////////////////////////
    template<
        class InputIt1, class OutputIt1, class UnaryPred
      , ELIB_ENABLE_IF(iter::is_input_iterator<InputIt1>::value)
      , ELIB_ENABLE_IF(iter::is_output_iterator<OutputIt1>::value)
      >
    auto copy_if(
        InputIt1 first1, InputIt1 last1
      , OutputIt1 out1
      , UnaryPred p
      )
    ELIB_AUTO_RETURN( std::copy_if(first1, last1, out1, p) )
    
    ////////////////////////////////////////////////////////////////////////////
    template<
        class InputIt1, class Size, class OutputIt1
      , ELIB_ENABLE_IF(iter::is_input_iterator<InputIt1>::value)
      , ELIB_ENABLE_IF(iter::is_output_iterator<OutputIt1>::value)
      >
    auto copy_n(InputIt1 first1, Size s, OutputIt1 out1)
    ELIB_AUTO_RETURN( std::copy_n(first1, s, out1) )
    
    ////////////////////////////////////////////////////////////////////////////
    using std::copy_backward;
    
    ////////////////////////////////////////////////////////////////////////////
    template<
        class InputIt1, class OutputIt1
      , ELIB_ENABLE_IF(iter::is_input_iterator<InputIt1>::value)
      , ELIB_ENABLE_IF(iter::is_output_iterator<OutputIt1>::value)
      >
    auto move(InputIt1 first1, InputIt1 last1, OutputIt1 out1)
    ELIB_AUTO_RETURN( std::move(first1, last1, out1) )
    
    ////////////////////////////////////////////////////////////////////////////
    using std::move_backward;
    using std::fill;
    using std::fill_n;
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class InIter1, class OutIter1, class UnaryOp
      , ELIB_ENABLE_IF(iter::is_input_iterator<InIter1>::value)
      , ELIB_ENABLE_IF(iter::is_output_iterator<OutIter1>::value)
      >
    auto transform(
        InIter1 first1, InIter1 last1
      , OutIter1 out
      , UnaryOp op
      )
    ELIB_AUTO_RETURN( std::transform(first1, last1, out, op) )
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class InIter1, class InIter2, class OutIter1, class UnaryOp
      , ELIB_ENABLE_IF(iter::is_input_iterator<InIter1>::value)
      , ELIB_ENABLE_IF(iter::is_input_iterator<InIter2>::value)
      , ELIB_ENABLE_IF(iter::is_output_iterator<OutIter1>::value)
      >
    auto transform(
        InIter1 first1, InIter2 last1
      , InIter2 first2
      , OutIter1 out
      , UnaryOp op
      )
    ELIB_AUTO_RETURN( std::transform(first1, last1, first2, out, op) )
    
    ////////////////////////////////////////////////////////////////////////////
    using std::generate;
    
    template <
        class OutIter1, class Size, class Generator
      , ELIB_ENABLE_IF(iter::is_output_iterator<OutIter1>::value)
      >
    auto generate_n(OutIter1 out, Size s, Generator g)
    ELIB_AUTO_RETURN( std::generate_n(out, s, g) )
    
    ////////////////////////////////////////////////////////////////////////////
    using std::remove;
    using std::remove_if;
    using std::remove_copy;
    using std::remove_copy_if;
    using std::replace;
    using std::replace_if;
    using std::replace_copy;
    using std::replace_copy_if;
    using std::swap_ranges;
    using std::iter_swap;
    using std::reverse;
    using std::reverse_copy;
    using std::rotate;
    using std::rotate_copy;
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class RandomIt
      , ELIB_ENABLE_IF(iter::is_random_access_iterator<RandomIt>::value)
      >
    auto random_shuffle(RandomIt first, RandomIt last)
    ELIB_AUTO_RETURN( std::random_shuffle(first, last) )
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class RandomIt, class RandomFunc
      , ELIB_ENABLE_IF(iter::is_random_access_iterator<RandomIt>::value)
      >
    auto random_shuffle(RandomIt first, RandomIt last, RandomFunc && r)
    ELIB_AUTO_RETURN( 
        std::random_shuffle(first, last, elib::forward<RandomFunc>(r)) 
      )
      
    ////////////////////////////////////////////////////////////////////////////
    using std::shuffle;
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class InputIt1
      , ELIB_ENABLE_IF(iter::is_iterator<InputIt1>::value)
      >
    auto unique(
        InputIt1 first1, InputIt1 last1
      )
    ELIB_AUTO_RETURN( std::unique(first1, last1) )
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class InputIt1, class BinaryPred
      , ELIB_ENABLE_IF(iter::is_iterator<InputIt1>::value)
      >
    auto unique(
        InputIt1 first1, InputIt1 last1, BinaryPred p
      )
    ELIB_AUTO_RETURN( std::unique(first1, last1, p) )
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class InputIt1, class OutputIt1
      , ELIB_ENABLE_IF(iter::is_input_iterator<InputIt1>::value)
      , ELIB_ENABLE_IF(iter::is_output_iterator<OutputIt1>::value)
      >
    auto unique_copy(
        InputIt1 first1, InputIt1 last1, OutputIt1 out
      )
    ELIB_AUTO_RETURN( std::unique_copy(first1, last1, out) )
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class InputIt1, class OutputIt1, class BinaryPred
      , ELIB_ENABLE_IF(iter::is_input_iterator<InputIt1>::value)
      , ELIB_ENABLE_IF(iter::is_output_iterator<OutputIt1>::value)
      >
    auto unique_copy(
        InputIt1 first1, InputIt1 last1, OutputIt1 out, BinaryPred p
      )
    ELIB_AUTO_RETURN( std::unique_copy(first1, last1, out, p) )
    
    ////////////////////////////////////////////////////////////////////////////
    using std::is_partitioned;
    using std::partition;
    using std::partition_copy;
    using std::stable_partition;
    using std::partition_point;
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Iter1
      , ELIB_ENABLE_IF(iter::is_forward_iterator<Iter1>::value)
      >
    auto is_sorted(Iter1 first, Iter1 last)
    ELIB_AUTO_RETURN( std::is_sorted(first, last) )
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Iter1, class Compare
      , ELIB_ENABLE_IF(iter::is_forward_iterator<Iter1>::value)
      >
    auto is_sorted(Iter1 first, Iter1 last, Compare cmp)
    ELIB_AUTO_RETURN( std::is_sorted(first, last, cmp) )
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Iter1
      , ELIB_ENABLE_IF(iter::is_forward_iterator<Iter1>::value)
      >
    auto is_sorted_until(Iter1 first, Iter1 last)
    ELIB_AUTO_RETURN( std::is_sorted_until(first, last) )
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Iter1, class Compare
      , ELIB_ENABLE_IF(iter::is_forward_iterator<Iter1>::value)
      >
    auto is_sorted_until(Iter1 first, Iter1 last, Compare cmp)
    ELIB_AUTO_RETURN( std::is_sorted_until(first, last, cmp) )
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Iter1
      , ELIB_ENABLE_IF(iter::is_random_access_iterator<Iter1>::value)
      >
    auto sort(Iter1 first, Iter1 last)
    ELIB_AUTO_RETURN( std::sort(first, last) )
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Iter1, class Compare
      , ELIB_ENABLE_IF(iter::is_random_access_iterator<Iter1>::value)
      >
    auto sort(Iter1 first, Iter1 last, Compare cmp)
    ELIB_AUTO_RETURN( std::sort(first, last, cmp) )
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Iter1
      , ELIB_ENABLE_IF(iter::is_random_access_iterator<Iter1>::value)
      >
    auto partial_sort(Iter1 first, Iter1 middle, Iter1 last)
    ELIB_AUTO_RETURN( std::partial_sort(first, middle, last) )
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Iter1, class Compare
      , ELIB_ENABLE_IF(iter::is_random_access_iterator<Iter1>::value)
      >
    auto partial_sort(Iter1 first, Iter1 middle, Iter1 last, Compare cmp)
    ELIB_AUTO_RETURN( std::partial_sort(first, middle, last, cmp) )
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Iter1, class Iter2
      , ELIB_ENABLE_IF(iter::is_input_iterator<Iter1>::value)
      , ELIB_ENABLE_IF(iter::is_random_access_iterator<Iter2>::value)
      >
    auto partial_sort_copy(
        Iter1 first, Iter1 last
      , Iter2 dfirst, Iter2 dlast
      )
    ELIB_AUTO_RETURN( std::partial_sort_copy(first, last, dfirst, dlast) )
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Iter1, class Iter2, class Compare
      , ELIB_ENABLE_IF(iter::is_input_iterator<Iter1>::value)
      , ELIB_ENABLE_IF(iter::is_random_access_iterator<Iter2>::value)
      >
    auto partial_sort_copy(
        Iter1 first, Iter1 last
      , Iter2 dfirst, Iter2 dlast
      , Compare cmp
      )
    ELIB_AUTO_RETURN( std::partial_sort_copy(first, last, dfirst, dlast, cmp) )
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Iter1
      , ELIB_ENABLE_IF(iter::is_random_access_iterator<Iter1>::value)
      >
    auto stable_sort(Iter1 first, Iter1 last)
    ELIB_AUTO_RETURN( std::stable_sort(first, last) )
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Iter1, class Compare
      , ELIB_ENABLE_IF(iter::is_random_access_iterator<Iter1>::value)
      >
    auto stable_sort(Iter1 first, Iter1 last, Compare cmp)
    ELIB_AUTO_RETURN( std::stable_sort(first, last, cmp) )
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Iter1
      , ELIB_ENABLE_IF(iter::is_random_access_iterator<Iter1>::value)
      >
    auto nth_element(Iter1 first, Iter1 nth, Iter1 last)
    ELIB_AUTO_RETURN( std::nth_element(first, nth, last) )
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Iter1, class Compare
      , ELIB_ENABLE_IF(iter::is_random_access_iterator<Iter1>::value)
      >
    auto nth_element(Iter1 first, Iter1 nth, Iter1 last, Compare cmp)
    ELIB_AUTO_RETURN( std::nth_element(first, nth, last, cmp) )
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Iter1, class T
      , ELIB_ENABLE_IF(iter::is_forward_iterator<Iter1>::value)
      >
    auto lower_bound(Iter1 first, Iter1 last, T const & v)
    ELIB_AUTO_RETURN( std::lower_bound(first, last, v) )
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Iter1, class T, class Compare
      , ELIB_ENABLE_IF(iter::is_forward_iterator<Iter1>::value)
      >
    auto lower_bound(Iter1 first, Iter1 last, T const & v, Compare cmp)
    ELIB_AUTO_RETURN( std::lower_bound(first, last, v, cmp) )
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Iter1, class T
      , ELIB_ENABLE_IF(iter::is_forward_iterator<Iter1>::value)
      >
    auto upper_bound(Iter1 first, Iter1 last, T const & v)
    ELIB_AUTO_RETURN( std::upper_bound(first, last, v) )
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Iter1, class T, class Compare
      , ELIB_ENABLE_IF(iter::is_forward_iterator<Iter1>::value)
      >
    auto upper_bound(Iter1 first, Iter1 last, T const & v, Compare cmp)
    ELIB_AUTO_RETURN( std::upper_bound(first, last, v, cmp) )
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Iter1, class T
      , ELIB_ENABLE_IF(iter::is_forward_iterator<Iter1>::value)
      >
    auto binary_search(Iter1 first, Iter1 last, T const & v)
    ELIB_AUTO_RETURN( std::binary_search(first, last, v) )
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Iter1, class T, class Compare
      , ELIB_ENABLE_IF(iter::is_forward_iterator<Iter1>::value)
      >
    auto binary_search(Iter1 first, Iter1 last, T const & v, Compare cmp)
    ELIB_AUTO_RETURN( std::binary_search(first, last, v, cmp) )
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Iter1, class T
      , ELIB_ENABLE_IF(iter::is_forward_iterator<Iter1>::value)
      >
    auto equal_range(Iter1 first, Iter1 last, T const & v)
    ELIB_AUTO_RETURN( std::equal_range(first, last, v) )
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Iter1, class T, class Compare
      , ELIB_ENABLE_IF(iter::is_forward_iterator<Iter1>::value)
      >
    auto equal_range(Iter1 first, Iter1 last, T const & v, Compare cmp)
    ELIB_AUTO_RETURN( std::equal_range(first, last, v, cmp) )
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class InputIt1, class InputIt2, class OutputIt
      , ELIB_ENABLE_IF(iter::is_input_iterator<InputIt1>::value)
      , ELIB_ENABLE_IF(iter::is_input_iterator<InputIt2>::value)
      , ELIB_ENABLE_IF(iter::is_output_iterator<OutputIt>::value)
      >
    auto merge(
        InputIt1 first1, InputIt1 last1
      , InputIt2 first2, InputIt2 last2
      , OutputIt out
      )
    ELIB_AUTO_RETURN( std::merge(first1, last1, first2, last2, out) )
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class InputIt1, class InputIt2, class OutputIt, class Compare
      , ELIB_ENABLE_IF(iter::is_input_iterator<InputIt1>::value)
      , ELIB_ENABLE_IF(iter::is_input_iterator<InputIt2>::value)
      , ELIB_ENABLE_IF(iter::is_output_iterator<OutputIt>::value)
      >
    auto merge(
        InputIt1 first1, InputIt1 last1
      , InputIt2 first2, InputIt2 last2
      , OutputIt out, Compare cmp
      )
    ELIB_AUTO_RETURN( std::merge(first1, last1, first2, last2, out, cmp) )
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Iter1
      , ELIB_ENABLE_IF(iter::is_bidirectional_iterator<Iter1>::value)
      >
    auto inplace_merge(Iter1 first, Iter1 middle, Iter1 last)
    ELIB_AUTO_RETURN( std::inplace_merge(first, middle, last) )
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Iter1, class Compare
      , ELIB_ENABLE_IF(iter::is_bidirectional_iterator<Iter1>::value)
      >
    auto inplace_merge(Iter1 first, Iter1 middle, Iter1 last, Compare cmp)
    ELIB_AUTO_RETURN( std::inplace_merge(first, middle, last, cmp) )
    
    ////////////////////////////////////////////////////////////////////////////
    template<
        class InputIt1, class InputIt2
      , ELIB_ENABLE_IF(iter::is_input_iterator<InputIt1>::value)
      , ELIB_ENABLE_IF(iter::is_input_iterator<InputIt2>::value)
      >
    auto includes(
        InputIt1 first1, InputIt1 last1
      , InputIt2 first2, InputIt2 last2
      )
    ELIB_AUTO_RETURN( std::includes(first1, last1, first2, last2) )
    
    ////////////////////////////////////////////////////////////////////////////
    template<
        class InputIt1, class InputIt2, class Compare
      , ELIB_ENABLE_IF(iter::is_input_iterator<InputIt1>::value)
      , ELIB_ENABLE_IF(iter::is_input_iterator<InputIt2>::value)
      >
    auto includes(
        InputIt1 first1, InputIt1 last1
      , InputIt2 first2, InputIt2 last2
      , Compare cmp
      )
    ELIB_AUTO_RETURN( std::includes(first1, last1, first2, last2, cmp) )
    
    ////////////////////////////////////////////////////////////////////////////
    template<
        class InputIt1, class InputIt2, class OutputIt
      , ELIB_ENABLE_IF(iter::is_input_iterator<InputIt1>::value)
      , ELIB_ENABLE_IF(iter::is_input_iterator<InputIt2>::value)
      , ELIB_ENABLE_IF(iter::is_output_iterator<OutputIt>::value)
      >
    auto set_difference(
        InputIt1 first1, InputIt1 last1
      , InputIt2 first2, InputIt2 last2
      , OutputIt out
      )
    ELIB_AUTO_RETURN( std::set_difference(first1, last1, first2, last2, out) )
    
    ////////////////////////////////////////////////////////////////////////////
    template<
        class InputIt1, class InputIt2, class OutputIt, class Compare
      , ELIB_ENABLE_IF(iter::is_input_iterator<InputIt1>::value)
      , ELIB_ENABLE_IF(iter::is_input_iterator<InputIt2>::value)
      , ELIB_ENABLE_IF(iter::is_output_iterator<OutputIt>::value)
      >
    auto set_difference(
        InputIt1 first1, InputIt1 last1
      , InputIt2 first2, InputIt2 last2
      , OutputIt out, Compare cmp
      )
    ELIB_AUTO_RETURN( std::set_difference(first1, last1, first2, last2, out, cmp) )
    
    ////////////////////////////////////////////////////////////////////////////
    template<
        class InputIt1, class InputIt2, class OutputIt
      , ELIB_ENABLE_IF(iter::is_input_iterator<InputIt1>::value)
      , ELIB_ENABLE_IF(iter::is_input_iterator<InputIt2>::value)
      , ELIB_ENABLE_IF(iter::is_output_iterator<OutputIt>::value)
      >
    auto set_symmetric_difference(
        InputIt1 first1, InputIt1 last1
      , InputIt2 first2, InputIt2 last2
      , OutputIt out
      )
    ELIB_AUTO_RETURN( std::set_symmetric_difference(first1, last1, first2, last2, out) )
    
    ////////////////////////////////////////////////////////////////////////////
    template<
        class InputIt1, class InputIt2, class OutputIt, class Compare
      , ELIB_ENABLE_IF(iter::is_input_iterator<InputIt1>::value)
      , ELIB_ENABLE_IF(iter::is_input_iterator<InputIt2>::value)
      , ELIB_ENABLE_IF(iter::is_output_iterator<OutputIt>::value)
      >
    auto set_symmetric_difference(
        InputIt1 first1, InputIt1 last1
      , InputIt2 first2, InputIt2 last2
      , OutputIt out, Compare cmp
      )
    ELIB_AUTO_RETURN( std::set_symmetric_difference(first1, last1, first2, last2, out, cmp) )
    
    ////////////////////////////////////////////////////////////////////////////
    template<
        class InputIt1, class InputIt2, class OutputIt
      , ELIB_ENABLE_IF(iter::is_input_iterator<InputIt1>::value)
      , ELIB_ENABLE_IF(iter::is_input_iterator<InputIt2>::value)
      , ELIB_ENABLE_IF(iter::is_output_iterator<OutputIt>::value)
      >
    auto set_intersection(
        InputIt1 first1, InputIt1 last1
      , InputIt2 first2, InputIt2 last2
      , OutputIt out
      )
    ELIB_AUTO_RETURN( std::set_intersection(first1, last1, first2, last2, out) )
    
    ////////////////////////////////////////////////////////////////////////////
    template<
        class InputIt1, class InputIt2, class OutputIt, class Compare
      , ELIB_ENABLE_IF(iter::is_input_iterator<InputIt1>::value)
      , ELIB_ENABLE_IF(iter::is_input_iterator<InputIt2>::value)
      , ELIB_ENABLE_IF(iter::is_output_iterator<OutputIt>::value)
      >
    auto set_intersection(
        InputIt1 first1, InputIt1 last1
      , InputIt2 first2, InputIt2 last2
      , OutputIt out, Compare cmp
      )
    ELIB_AUTO_RETURN( std::set_intersection(first1, last1, first2, last2, out, cmp) )
    
    ////////////////////////////////////////////////////////////////////////////
    template<
        class InputIt1, class InputIt2, class OutputIt
      , ELIB_ENABLE_IF(iter::is_input_iterator<InputIt1>::value)
      , ELIB_ENABLE_IF(iter::is_input_iterator<InputIt2>::value)
      , ELIB_ENABLE_IF(iter::is_output_iterator<OutputIt>::value)
      >
    auto set_union(
        InputIt1 first1, InputIt1 last1
      , InputIt2 first2, InputIt2 last2
      , OutputIt out
      )
    ELIB_AUTO_RETURN( std::set_union(first1, last1, first2, last2, out) )
    
    ////////////////////////////////////////////////////////////////////////////
    template<
        class InputIt1, class InputIt2, class OutputIt, class Compare
      , ELIB_ENABLE_IF(iter::is_input_iterator<InputIt1>::value)
      , ELIB_ENABLE_IF(iter::is_input_iterator<InputIt2>::value)
      , ELIB_ENABLE_IF(iter::is_output_iterator<OutputIt>::value)
      >
    auto set_union(
        InputIt1 first1, InputIt1 last1
      , InputIt2 first2, InputIt2 last2
      , OutputIt out, Compare cmp
      )
    ELIB_AUTO_RETURN( std::set_union(first1, last1, first2, last2, out, cmp) )
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Iter1
      , ELIB_ENABLE_IF(iter::is_random_access_iterator<Iter1>::value)
      >
    auto is_heap(Iter1 first, Iter1 last)
    ELIB_AUTO_RETURN( std::is_heap(first, last) )
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Iter1, class Compare
      , ELIB_ENABLE_IF(iter::is_random_access_iterator<Iter1>::value)
      >
    auto is_heap(Iter1 first, Iter1 last, Compare cmp)
    ELIB_AUTO_RETURN( std::is_heap(first, last, cmp) )
    
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Iter1
      , ELIB_ENABLE_IF(iter::is_random_access_iterator<Iter1>::value)
      >
    auto is_heap_until(Iter1 first, Iter1 last)
    ELIB_AUTO_RETURN( std::is_heap_until(first, last) )
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Iter1, class Compare
      , ELIB_ENABLE_IF(iter::is_random_access_iterator<Iter1>::value)
      >
    auto is_heap_until(Iter1 first, Iter1 last, Compare cmp)
    ELIB_AUTO_RETURN( std::is_heap_until(first, last, cmp) )
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Iter1
      , ELIB_ENABLE_IF(iter::is_random_access_iterator<Iter1>::value)
      >
    auto make_heap(Iter1 first, Iter1 last)
    ELIB_AUTO_RETURN( std::make_heap(first, last) )
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Iter1, class Compare
      , ELIB_ENABLE_IF(iter::is_random_access_iterator<Iter1>::value)
      >
    auto make_heap(Iter1 first, Iter1 last, Compare cmp)
    ELIB_AUTO_RETURN( std::make_heap(first, last, cmp) )
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Iter1
      , ELIB_ENABLE_IF(iter::is_random_access_iterator<Iter1>::value)
      >
    auto push_heap(Iter1 first, Iter1 last)
    ELIB_AUTO_RETURN( std::push_heap(first, last) )
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Iter1, class Compare
      , ELIB_ENABLE_IF(iter::is_random_access_iterator<Iter1>::value)
      >
    auto push_heap(Iter1 first, Iter1 last, Compare cmp)
    ELIB_AUTO_RETURN( std::push_heap(first, last, cmp) )
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Iter1
      , ELIB_ENABLE_IF(iter::is_random_access_iterator<Iter1>::value)
      >
    auto pop_heap(Iter1 first, Iter1 last)
    ELIB_AUTO_RETURN( std::pop_heap(first, last) )
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Iter1, class Compare
      , ELIB_ENABLE_IF(iter::is_random_access_iterator<Iter1>::value)
      >
    auto pop_heap(Iter1 first, Iter1 last, Compare cmp)
    ELIB_AUTO_RETURN( std::pop_heap(first, last, cmp) )
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Iter1
      , ELIB_ENABLE_IF(iter::is_random_access_iterator<Iter1>::value)
      >
    auto sort_heap(Iter1 first, Iter1 last)
    ELIB_AUTO_RETURN( std::sort_heap(first, last) )
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Iter1, class Compare
      , ELIB_ENABLE_IF(iter::is_random_access_iterator<Iter1>::value)
      >
    auto sort_heap(Iter1 first, Iter1 last, Compare cmp)
    ELIB_AUTO_RETURN( std::sort_heap(first, last, cmp) )
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Iter1
      , ELIB_ENABLE_IF(iter::is_forward_iterator<Iter1>::value)
      >
    auto min_element(Iter1 first, Iter1 last)
    ELIB_AUTO_RETURN( std::min_element(first, last) )
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Iter1, class Compare
      , ELIB_ENABLE_IF(iter::is_forward_iterator<Iter1>::value)
      >
    auto min_element(Iter1 first, Iter1 last, Compare cmp)
    ELIB_AUTO_RETURN( std::min_element(first, last, cmp) )
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Iter1
      , ELIB_ENABLE_IF(iter::is_forward_iterator<Iter1>::value)
      >
    auto max_element(Iter1 first, Iter1 last)
    ELIB_AUTO_RETURN( std::max_element(first, last) )
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Iter1, class Compare
      , ELIB_ENABLE_IF(iter::is_forward_iterator<Iter1>::value)
      >
    auto max_element(Iter1 first, Iter1 last, Compare cmp)
    ELIB_AUTO_RETURN( std::max_element(first, last, cmp) )
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Iter1
      , ELIB_ENABLE_IF(iter::is_forward_iterator<Iter1>::value)
      >
    auto minmax_element(Iter1 first, Iter1 last)
    ELIB_AUTO_RETURN( std::minmax_element(first, last) )
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Iter1, class Compare
      , ELIB_ENABLE_IF(iter::is_forward_iterator<Iter1>::value)
      >
    auto minmax_element(Iter1 first, Iter1 last, Compare cmp)
    ELIB_AUTO_RETURN( std::minmax_element(first, last, cmp) )
    
    ///////////////////////////////////////////////////////////////////////////
    template <
        class InputIt1, class InputIt2
      , ELIB_ENABLE_IF(iter::is_input_iterator<InputIt1>::value)
      , ELIB_ENABLE_IF(iter::is_input_iterator<InputIt2>::value)
      >
    auto lexicographical_compare(
        InputIt1 first1, InputIt1 last1
      , InputIt2 first2, InputIt2 last2
      )
    ELIB_AUTO_RETURN( std::lexicographical_compare(first1, last1, first2, last2) )
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class InputIt1, class InputIt2, class Compare
      , ELIB_ENABLE_IF(iter::is_input_iterator<InputIt1>::value)
      , ELIB_ENABLE_IF(iter::is_input_iterator<InputIt2>::value)
      >
    auto lexicographical_compare(
        InputIt1 first1, InputIt1 last1
      , InputIt2 first2, InputIt2 last2
      , Compare cmp
      )
    ELIB_AUTO_RETURN( std::lexicographical_compare(first1, last1, first2, last2, cmp) )
    
    ///////////////////////////////////////////////////////////////////////////
    template <
        class ForwardIt1, class ForwardIt2
      , ELIB_ENABLE_IF(iter::is_forward_iterator<ForwardIt1>::value)
      , ELIB_ENABLE_IF(iter::is_forward_iterator<ForwardIt2>::value)
      >
    auto is_permutation(
        ForwardIt1 first1, ForwardIt1 last1
      , ForwardIt2 first2
      )
    ELIB_AUTO_RETURN( std::is_permutation(first1, last1, first2) )
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class ForwardIt1, class ForwardIt2, class Compare
      , ELIB_ENABLE_IF(iter::is_forward_iterator<ForwardIt1>::value)
      , ELIB_ENABLE_IF(iter::is_forward_iterator<ForwardIt2>::value)
      >
    auto is_permutation(
        ForwardIt1 first1, ForwardIt1 last1
      , ForwardIt2 first2
      , Compare cmp
      )
    ELIB_AUTO_RETURN( std::is_permutation(first1, last1, first2, cmp) )
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Iter1
      , ELIB_ENABLE_IF(iter::is_bidirectional_iterator<Iter1>::value)
      >
    auto next_permutation(Iter1 first, Iter1 last)
    ELIB_AUTO_RETURN( std::next_permutation(first, last) )
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Iter1, class Compare
      , ELIB_ENABLE_IF(iter::is_bidirectional_iterator<Iter1>::value)
      >
    auto next_permutation(Iter1 first, Iter1 last, Compare cmp)
    ELIB_AUTO_RETURN( std::next_permutation(first, last, cmp) )
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Iter1
      , ELIB_ENABLE_IF(iter::is_bidirectional_iterator<Iter1>::value)
      >
    auto prev_permutation(Iter1 first, Iter1 last)
    ELIB_AUTO_RETURN( std::prev_permutation(first, last) )
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Iter1, class Compare
      , ELIB_ENABLE_IF(iter::is_bidirectional_iterator<Iter1>::value)
      >
    auto prev_permutation(Iter1 first, Iter1 last, Compare cmp)
    ELIB_AUTO_RETURN( std::prev_permutation(first, last, cmp) )
    
}}}                                                          // namespace elib
namespace elib { namespace experimental
{
    using algo::all_of;
    using algo::any_of;
    using algo::none_of;
    using algo::for_each;
    using algo::count;
    using algo::count_if;
    using algo::mismatch;
    using algo::equal;
    using algo::find;
    using algo::find_if;
    using algo::find_if_not;
    using algo::find_end;
    using algo::find_first_of;
    using algo::adjacent_find;
    using algo::search;
    using algo::search_n;
    
    using algo::copy;
    using algo::copy_if;
    using algo::copy_n;
    using algo::copy_backward;
    using algo::move;
    using algo::move_backward;
    using algo::fill;
    using algo::fill_n;
    using algo::transform;
    using algo::generate;
    using algo::generate_n;
    using algo::remove;
    using algo::remove_if;
    using algo::remove_copy;
    using algo::remove_copy_if;
    using algo::replace;
    using algo::replace_if;
    using algo::replace_copy;
    using algo::replace_copy_if;
    using algo::swap_ranges;
    using algo::iter_swap;
    using algo::reverse;
    using algo::reverse_copy;
    using algo::rotate;
    using algo::rotate_copy;
    using algo::random_shuffle;
    using algo::shuffle;
    using algo::unique;
    using algo::unique_copy;
    
    using algo::is_partitioned;
    using algo::partition;
    using algo::partition_copy;
    using algo::stable_partition;
    using algo::partition_point;
    
    using algo::is_sorted;
    using algo::is_sorted_until;
    using algo::sort;
    using algo::partial_sort;
    using algo::partial_sort_copy;
    using algo::stable_sort;
    using algo::nth_element;
    
    using algo::lower_bound;
    using algo::upper_bound;
    using algo::binary_search;
    using algo::equal_range;
    
    using algo::merge;
    using algo::inplace_merge;
    using algo::includes;
    using algo::set_difference;
    using algo::set_symmetric_difference;
    using algo::set_intersection;
    using algo::set_union;
    
    using algo::is_heap;
    using algo::is_heap_until;
    using algo::make_heap;
    using algo::push_heap;
    using algo::pop_heap;
    using algo::sort_heap;
    
    using algo::min_element;
    using algo::max_element;
    using algo::minmax_element;
    using algo::lexicographical_compare;
    using algo::is_permutation;
    using algo::next_permutation;
    using algo::prev_permutation;
}}                                                          // namespace elib
#endif /* ELIB_ALGORITHM_HPP */