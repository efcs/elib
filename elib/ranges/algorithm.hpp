#ifndef ELIB_RANGES_ALGORITHM_HPP
#define ELIB_RANGES_ALGORITHM_HPP

# include <elib/ranges/traits.hpp>
# include <elib/aux.hpp>
# include <elib/config.hpp>

# include <algorithm>

namespace elib { namespace ranges { namespace algorithm_adl_barrier
{
////////////////////////////////////////////////////////////////////////////////
//                        all_of, any_of, none_of
////////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////
    template <
        class Range, class UnaryPred
      , ELIB_ENABLE_IF(is_range<Range>::value)
      >
    auto all_of(Range && r, UnaryPred p)
    ELIB_AUTO_RETURN_NOEXCEPT(std::all_of(
        elib::adl_begin(elib::forward<Range>(r))
      , elib::adl_end(  elib::forward<Range>(r))
      , p
    ))
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Range, class UnaryPred
      , ELIB_ENABLE_IF(is_range<Range>::value)
      >
    auto any_of(Range && r, UnaryPred p)
    ELIB_AUTO_RETURN_NOEXCEPT(std::any_of(
        elib::adl_begin( elib::forward<Range>(r) )
      , elib::adl_end  ( elib::forward<Range>(r) )
      , p
    ))
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Range, class UnaryPred
      , ELIB_ENABLE_IF(is_range<Range>::value)
      >
    auto none_of(Range && r, UnaryPred p)
    ELIB_AUTO_RETURN_NOEXCEPT(std::none_of(
        elib::adl_begin( elib::forward<Range>(r) )
      , elib::adl_end  ( elib::forward<Range>(r) )
      , p
    ))
    
////////////////////////////////////////////////////////////////////////////////
//                              for_each
////////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////
    template <
        class Range, class UnaryFunc
      , ELIB_ENABLE_IF(is_range<Range>::value)
      >
    auto for_each(Range && r, UnaryFunc p)
    ELIB_AUTO_RETURN_NOEXCEPT(std::for_each(
        elib::adl_begin( elib::forward<Range>(r) )
      , elib::adl_end  ( elib::forward<Range>(r) )
      , p
    ))
    
////////////////////////////////////////////////////////////////////////////////
//                          count, count_if
////////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////
    template <
        class Range, class T
      , ELIB_ENABLE_IF(is_range<Range>::value)
      >
    auto count(Range && r, T const & v)
    ELIB_AUTO_RETURN_NOEXCEPT(std::count(
        elib::adl_begin( elib::forward<Range>(r) )
      , elib::adl_end  ( elib::forward<Range>(r) )
      , v
    ))
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Range, class UnaryPred
      , ELIB_ENABLE_IF(is_range<Range>::value)
      >
    auto count_if(Range && r, UnaryPred p)
    ELIB_AUTO_RETURN_NOEXCEPT(std::count_if(
        elib::adl_begin( elib::forward<Range>(r) )
      , elib::adl_end  ( elib::forward<Range>(r) )
      , p
    ))
    
////////////////////////////////////////////////////////////////////////////////
//                               mismatch
////////////////////////////////////////////////////////////////////////////////

# if ! defined(ELIB_CONFIG_CXX14)
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Range1, class Range2
      , ELIB_ENABLE_IF(is_range<Range1>::value)
      , ELIB_ENABLE_IF(is_range<Range2>::value)
      >
    auto mismatch(Range1 && r1, Range2 && r2)
    ELIB_AUTO_RETURN_NOEXCEPT(std::mismatch(
        elib::adl_begin( elib::forward<Range1>(r1) )
      , elib::adl_end  ( elib::forward<Range1>(r1) )
      , elib::adl_begin( elib::forward<Range2>(r2) )
    ))
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Range1, class Range2
      , class BinaryPred
      , ELIB_ENABLE_IF(is_range<Range1>::value)
      , ELIB_ENABLE_IF(is_range<Range2>::value)
      >
    auto mismatch(Range1 && r1, Range2 && r2, BinaryPred p)
    ELIB_AUTO_RETURN_NOEXCEPT(std::mismatch(
        elib::adl_begin( elib::forward<Range1>(r1) )
      , elib::adl_end  ( elib::forward<Range1>(r1) )
      , elib::adl_begin( elib::forward<Range2>(r2) )
      , p
    ))
# else /* ELIB_CONFIG_CXX14 */
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Range1, class Range2
      , ELIB_ENABLE_IF(is_range<Range1>::value)
      , ELIB_ENABLE_IF(is_range<Range2>::value)
      >
    auto mismatch(Range1 && r1, Range2 && r2)
    ELIB_AUTO_RETURN_NOEXCEPT(std::mismatch(
        elib::adl_begin( elib::forward<Range1>(r1) )
      , elib::adl_end  ( elib::forward<Range1>(r1) )
      , elib::adl_begin( elib::forward<Range2>(r2) )
      , elib::adl_end  ( elib::forward<Range2>(r2) )
    ))
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Range1, class Range2
      , class BinaryPred
      , ELIB_ENABLE_IF(is_range<Range1>::value)
      , ELIB_ENABLE_IF(is_range<Range2>::value)
      >
    auto mismatch(Range1 && r1, Range2 && r2, BinaryPred p)
    ELIB_AUTO_RETURN_NOEXCEPT(std::mismatch(
        elib::adl_begin( elib::forward<Range1>(r1) )
      , elib::adl_end  ( elib::forward<Range1>(r1) )
      , elib::adl_begin( elib::forward<Range2>(r2) )
      , elib::adl_end  ( elib::forward<Range2>(r2) )
      , p
    ))
# endif /* ELIB_CONFIG_CXX14 */
    
////////////////////////////////////////////////////////////////////////////////
//                              equal
////////////////////////////////////////////////////////////////////////////////

# if ! defined(ELIB_CONFIG_CXX14)
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Range1, class Range2
      , ELIB_ENABLE_IF(is_range<Range1>::value)
      , ELIB_ENABLE_IF(is_range<Range2>::value)
      >
    auto equal(Range1 && r1, Range2 && r2)
    ELIB_AUTO_RETURN_NOEXCEPT(std::equal(
        elib::adl_begin( elib::forward<Range1>(r1) )
      , elib::adl_end  ( elib::forward<Range1>(r1) )
      , elib::adl_begin( elib::forward<Range2>(r2) )
    ))
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Range1, class Range2
      , class BinaryPred
      , ELIB_ENABLE_IF(is_range<Range1>::value)
      , ELIB_ENABLE_IF(is_range<Range2>::value)
      >
    auto equal(Range1 && r1, Range2 && r2, BinaryPred p)
    ELIB_AUTO_RETURN_NOEXCEPT(std::equal(
        elib::adl_begin( elib::forward<Range1>(r1) )
      , elib::adl_end  ( elib::forward<Range1>(r1) )
      , elib::adl_begin( elib::forward<Range2>(r2) )
      , p
    ))
# else /* ELIB_CONFIG_CXX14 */
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Range1, class Range2
      , ELIB_ENABLE_IF(is_range<Range1>::value)
      , ELIB_ENABLE_IF(is_range<Range2>::value)
      >
    auto equal(Range1 && r1, Range2 && r2)
    ELIB_AUTO_RETURN_NOEXCEPT(std::equal(
        elib::adl_begin( elib::forward<Range1>(r1) )
      , elib::adl_end  ( elib::forward<Range1>(r1) )
      , elib::adl_begin( elib::forward<Range2>(r2) )
      , elib::adl_end  ( elib::forward<Range2>(r2) )
    ))
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Range1, class Range2
      , class BinaryPred
      , ELIB_ENABLE_IF(is_range<Range1>::value)
      , ELIB_ENABLE_IF(is_range<Range2>::value)
      >
    auto equal(Range1 && r1, Range2 && r2, BinaryPred p)
    ELIB_AUTO_RETURN_NOEXCEPT(std::equal(
        elib::adl_begin( elib::forward<Range1>(r1) )
      , elib::adl_end  ( elib::forward<Range1>(r1) )
      , elib::adl_begin( elib::forward<Range2>(r2) )
      , elib::adl_end  ( elib::forward<Range2>(r2) )
      , p
    ))
# endif /* ELIB_CONFIG_CXX14 */
    
////////////////////////////////////////////////////////////////////////////////
//                      find, find_if, find_if_not
////////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////
    template <
        class Range, class T
      , ELIB_ENABLE_IF(is_range<Range>::value)
      >
    auto find(Range && r, T const & v)
    ELIB_AUTO_RETURN_NOEXCEPT(std::find(
        elib::adl_begin( elib::forward<Range>(r) )
      , elib::adl_end  ( elib::forward<Range>(r) )
      , v
    ))
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Range, class UnaryPred
      , ELIB_ENABLE_IF(is_range<Range>::value)
      >
    auto find_if(Range && r, UnaryPred p)
    ELIB_AUTO_RETURN_NOEXCEPT(std::find_if(
        elib::adl_begin( elib::forward<Range>(r) )
      , elib::adl_end  ( elib::forward<Range>(r) )
      , p
    ))
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Range, class UnaryPred
      , ELIB_ENABLE_IF(is_range<Range>::value)
      >
    auto find_if_not(Range && r, UnaryPred p)
    ELIB_AUTO_RETURN_NOEXCEPT(std::find_if_not(
        elib::adl_begin( elib::forward<Range>(r) )
      , elib::adl_end  ( elib::forward<Range>(r) )
      , p
    ))
    
////////////////////////////////////////////////////////////////////////////////
//                              find_end
////////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////
    template <
        class Range1, class Range2
      , ELIB_ENABLE_IF(is_range<Range1>::value)
      , ELIB_ENABLE_IF(is_range<Range2>::value)
      >
    auto find_end(Range1 && r1, Range2 && r2)
    ELIB_AUTO_RETURN_NOEXCEPT(std::find_end(
        elib::adl_begin( elib::forward<Range1>(r1) )
      , elib::adl_end  ( elib::forward<Range1>(r1) )
      , elib::adl_begin( elib::forward<Range2>(r2) )
      , elib::adl_end  ( elib::forward<Range2>(r2) )
    ))
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Range1, class Range2
      , class BinaryPred
      , ELIB_ENABLE_IF(is_range<Range1>::value)
      , ELIB_ENABLE_IF(is_range<Range2>::value)
      >
    auto find_end(Range1 && r1, Range2 && r2, BinaryPred p)
    ELIB_AUTO_RETURN_NOEXCEPT(std::find_end(
        elib::adl_begin( elib::forward<Range1>(r1) )
      , elib::adl_end  ( elib::forward<Range1>(r1) )
      , elib::adl_begin( elib::forward<Range2>(r2) )
      , elib::adl_end  ( elib::forward<Range2>(r2) )
      , p
    ))
    
////////////////////////////////////////////////////////////////////////////////
//                           find_first_of
////////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////
    template <
        class Range1, class Range2
      , ELIB_ENABLE_IF(is_range<Range1>::value)
      , ELIB_ENABLE_IF(is_range<Range2>::value)
      >
    auto find_first_of(Range1 && r1, Range2 && r2)
    ELIB_AUTO_RETURN_NOEXCEPT(std::find_first_of(
        elib::adl_begin( elib::forward<Range1>(r1) )
      , elib::adl_end  ( elib::forward<Range1>(r1) )
      , elib::adl_begin( elib::forward<Range2>(r2) )
      , elib::adl_end  ( elib::forward<Range2>(r2) )
    ))
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Range1, class Range2
      , class BinaryPred
      , ELIB_ENABLE_IF(is_range<Range1>::value)
      , ELIB_ENABLE_IF(is_range<Range2>::value)
      >
    auto find_first_of(Range1 && r1, Range2 && r2, BinaryPred p)
    ELIB_AUTO_RETURN_NOEXCEPT(std::find_first_of(
        elib::adl_begin( elib::forward<Range1>(r1) )
      , elib::adl_end  ( elib::forward<Range1>(r1) )
      , elib::adl_begin( elib::forward<Range2>(r2) )
      , elib::adl_end  ( elib::forward<Range2>(r2) )
      , p
    ))
    
////////////////////////////////////////////////////////////////////////////////
//                          adjacent_find
////////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////
    template <
        class Range
      , ELIB_ENABLE_IF(is_range<Range>::value)
      >
    auto adjacent_find(Range && r)
    ELIB_AUTO_RETURN_NOEXCEPT(std::adjacent_find(
        elib::adl_begin(elib::forward<Range>(r))
      , elib::adl_end(  elib::forward<Range>(r))
    ))
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Range, class BinaryPred
      , ELIB_ENABLE_IF(is_range<Range>::value)
      >
    auto adjacent_find(Range && r, BinaryPred p)
    ELIB_AUTO_RETURN_NOEXCEPT(std::adjacent_find(
        elib::adl_begin(elib::forward<Range>(r))
      , elib::adl_end(  elib::forward<Range>(r))
      , p
    ))
    
////////////////////////////////////////////////////////////////////////////////
//                         search, search_n
////////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////
    template <
        class Range1, class Range2
      , ELIB_ENABLE_IF(is_range<Range1>::value)
      , ELIB_ENABLE_IF(is_range<Range2>::value)
      >
    auto search(Range1 && r1, Range2 && r2)
    ELIB_AUTO_RETURN_NOEXCEPT(std::search(
        elib::adl_begin( elib::forward<Range1>(r1) )
      , elib::adl_end  ( elib::forward<Range1>(r1) )
      , elib::adl_begin( elib::forward<Range2>(r2) )
      , elib::adl_end  ( elib::forward<Range2>(r2) )
    ))
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Range1, class Range2
      , class BinaryPred
      , ELIB_ENABLE_IF(is_range<Range1>::value)
      , ELIB_ENABLE_IF(is_range<Range2>::value)
      >
    auto search(Range1 && r1, Range2 && r2, BinaryPred p)
    ELIB_AUTO_RETURN_NOEXCEPT(std::search(
        elib::adl_begin( elib::forward<Range1>(r1) )
      , elib::adl_end  ( elib::forward<Range1>(r1) )
      , elib::adl_begin( elib::forward<Range2>(r2) )
      , elib::adl_end  ( elib::forward<Range2>(r2) )
      , p
    ))
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Range, class Size, class T
      , ELIB_ENABLE_IF(is_range<Range>::value)
      >
    auto search_n( Range && r, Size count,  T const & v)
    ELIB_AUTO_RETURN_NOEXCEPT(std::search_n(
        elib::adl_begin( elib::forward<Range>(r) )
      , elib::adl_end  ( elib::forward<Range>(r) )
      , count, v
    ))
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Range, class Size
      , class T, class BinaryPred
      , ELIB_ENABLE_IF(is_range<Range>::value)
      >
    auto search_n( Range && r,  Size count, T const & v, BinaryPred p)
    ELIB_AUTO_RETURN_NOEXCEPT(std::search_n(
        elib::adl_begin( elib::forward<Range>(r) )
      , elib::adl_end  ( elib::forward<Range>(r) )
      , count, v, p
    ))
    
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////
    template <
        class Range, class OutIt
      , ELIB_ENABLE_IF(is_range<Range>::value)
      >
    auto copy(Range && r, OutIt out)
    ELIB_AUTO_RETURN_NOEXCEPT(std::copy(
        elib::adl_begin( elib::forward<Range>(r) )
      , elib::adl_end  ( elib::forward<Range>(r) )
      , out
    ))
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Range, class OutIt, class UnaryPred
      , ELIB_ENABLE_IF(is_range<Range>::value)
      >
    auto copy_if(Range && r, OutIt out, UnaryPred p)
    ELIB_AUTO_RETURN_NOEXCEPT(std::copy_if(
        elib::adl_begin( elib::forward<Range>(r) )
      , elib::adl_end  ( elib::forward<Range>(r) )
      , out, p
    ))
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Range, class Size, class OutIt
      , ELIB_ENABLE_IF(is_range<Range>::value)
      >
    auto copy_n(Range && r, Size n, OutIt out)
    ELIB_AUTO_RETURN_NOEXCEPT(std::copy_n(
        elib::adl_begin( elib::forward<Range>(r) )
      , n, out
    ))

    ////////////////////////////////////////////////////////////////////////////
    template <
        class Range, class OutIt
      , ELIB_ENABLE_IF(is_range<Range>::value)
      >
    auto copy_backward(Range && r, OutIt out)
    ELIB_AUTO_RETURN_NOEXCEPT(std::copy_backward(
        elib::adl_begin( elib::forward<Range>(r) )
      , elib::adl_end  ( elib::forward<Range>(r) )
      , out
    ))
    
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////
    template <
        class Range, class OutIt
      , ELIB_ENABLE_IF(is_range<Range>::value)
      >
    auto move(Range && r, OutIt out)
    ELIB_AUTO_RETURN_NOEXCEPT(std::move(
        elib::adl_begin( elib::forward<Range>(r) )
      , elib::adl_end  ( elib::forward<Range>(r) )
      , out
    ))
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Range, class OutIt
      , ELIB_ENABLE_IF(is_range<Range>::value)
      >
    auto move_backward(Range && r, OutIt out)
    ELIB_AUTO_RETURN_NOEXCEPT(std::move_backward(
        elib::adl_begin( elib::forward<Range>(r) )
      , elib::adl_end  ( elib::forward<Range>(r) )
      , out
    ))
    
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////
    template <
        class Range, class T
      , ELIB_ENABLE_IF(is_range<Range>::value)
      >
    auto fill(Range && r, T const & v)
    ELIB_AUTO_RETURN_NOEXCEPT(std::fill(
        elib::adl_begin( elib::forward<Range>(r) )
      , elib::adl_end  ( elib::forward<Range>(r) )
      , v
    ))
    
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////
    template <
        class Range, class OutIt, class UnaryOp
      , ELIB_ENABLE_IF(is_range<Range>::value)
      >
    auto transform(Range && r, OutIt out, UnaryOp op)
    ELIB_AUTO_RETURN_NOEXCEPT(std::transform(
        elib::adl_begin( elib::forward<Range>(r) )
      , elib::adl_end  ( elib::forward<Range>(r) )
      , out, op
    ))
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Range1, class Range2, class OutIt, class BinaryOp
      , ELIB_ENABLE_IF(is_range<Range1>::value)
      , ELIB_ENABLE_IF(is_range<Range2>::value)
      >
    auto transform(Range1 && r1, Range2 && r2, OutIt out, BinaryOp op)
    ELIB_AUTO_RETURN_NOEXCEPT(std::transform(
        elib::adl_begin( elib::forward<Range1>(r1) )
      , elib::adl_end  ( elib::forward<Range1>(r1) )
      , elib::adl_begin( elib::forward<Range2>(r2) )
      , out, op
    ))
    
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////
    template <
        class Range, class Generator
      , ELIB_ENABLE_IF(is_range<Range>::value)
      >
    auto generate(Range && r, Generator g)
    ELIB_AUTO_RETURN_NOEXCEPT(std::generate(
        elib::adl_begin( elib::forward<Range>(r) )
      , elib::adl_end  ( elib::forward<Range>(r) )
      , g
    ))
    
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////
    template <
        class Range, class T
      , ELIB_ENABLE_IF(is_range<Range>::value)
      >
    auto remove(Range && r, T const & v)
    ELIB_AUTO_RETURN_NOEXCEPT(std::remove(
        elib::adl_begin( elib::forward<Range>(r) )
      , elib::adl_end  ( elib::forward<Range>(r) )
      , v
    ))
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Range, class UnaryPred
      , ELIB_ENABLE_IF(is_range<Range>::value)
      >
    auto remove_if(Range && r, UnaryPred p)
    ELIB_AUTO_RETURN_NOEXCEPT(std::remove_if(
        elib::adl_begin( elib::forward<Range>(r) )
      , elib::adl_end  ( elib::forward<Range>(r) )
      , p
    ))
    
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////
    template <
        class Range, class OutIt, class T
      , ELIB_ENABLE_IF(is_range<Range>::value)
      >
    auto remove_copy(Range && r, OutIt out, T const & v)
    ELIB_AUTO_RETURN_NOEXCEPT(std::remove_copy(
        elib::adl_begin( elib::forward<Range>(r) )
      , elib::adl_end  ( elib::forward<Range>(r) )
      , out, v
    ))
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Range, class OutIt, class UnaryPred
      , ELIB_ENABLE_IF(is_range<Range>::value)
      >
    auto remove_copy_if(Range && r, OutIt out, UnaryPred p)
    ELIB_AUTO_RETURN_NOEXCEPT(std::remove_copy_if(
        elib::adl_begin( elib::forward<Range>(r) )
      , elib::adl_end  ( elib::forward<Range>(r) )
      , out, p
    ))
    
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////
    template <
        class Range, class T
      , ELIB_ENABLE_IF(is_range<Range>::value)
      >
    auto replace(Range && r, T const & old_v, T const & new_v)
    ELIB_AUTO_RETURN_NOEXCEPT(std::replace(
        elib::adl_begin( elib::forward<Range>(r) )
      , elib::adl_end  ( elib::forward<Range>(r) )
      , old_v, new_v
    ))
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Range, class UnaryPred, class T
      , ELIB_ENABLE_IF(is_range<Range>::value)
      >
    auto replace_if(Range && r, UnaryPred p, T const & new_v)
    ELIB_AUTO_RETURN_NOEXCEPT(std::replace_if(
        elib::adl_begin( elib::forward<Range>(r) )
      , elib::adl_end  ( elib::forward<Range>(r) )
      , p, new_v
    ))
    
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////
    template <
        class Range, class OutIt, class T
      , ELIB_ENABLE_IF(is_range<Range>::value)
      >
    auto replace_copy(Range && r, OutIt out, T const & old_v, T const & new_v)
    ELIB_AUTO_RETURN_NOEXCEPT(std::replace_copy(
        elib::adl_begin( elib::forward<Range>(r) )
      , elib::adl_end  ( elib::forward<Range>(r) )
      , out, old_v, new_v
    ))
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Range, class OutIt, class UnaryPred, class T
      , ELIB_ENABLE_IF(is_range<Range>::value)
      >
    auto replace_copy_if(Range && r, OutIt out, UnaryPred p, T const & new_v)
    ELIB_AUTO_RETURN_NOEXCEPT(std::replace_copy_if(
        elib::adl_begin( elib::forward<Range>(r) )
      , elib::adl_end  ( elib::forward<Range>(r) )
      , out, p, new_v
    ))
    
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////
    template <
        class Range1, class Range2
      , ELIB_ENABLE_IF(is_range<Range1>::value)
      , ELIB_ENABLE_IF(is_range<Range2>::value)
      >
    auto swap_ranges(Range1 && r1, Range2 && r2)
    ELIB_AUTO_RETURN_NOEXCEPT(std::swap_ranges(
        elib::adl_begin( elib::forward<Range1>(r1) )
      , elib::adl_end  ( elib::forward<Range1>(r1) )
      , elib::adl_begin( elib::forward<Range2>(r2) )
    ))
    
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////
    template <
        class Range
      , ELIB_ENABLE_IF(is_range<Range>::value)
      >
    auto reverse(Range && r)
    ELIB_AUTO_RETURN_NOEXCEPT(std::reverse(
        elib::adl_begin( elib::forward<Range>(r) )
      , elib::adl_end  ( elib::forward<Range>(r) )
    ))
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Range, class OutIt
      , ELIB_ENABLE_IF(is_range<Range>::value)
      >
    auto reverse_copy(Range && r, OutIt out)
    ELIB_AUTO_RETURN_NOEXCEPT(std::reverse_copy(
        elib::adl_begin( elib::forward<Range>(r) )
      , elib::adl_end  ( elib::forward<Range>(r) )
      , out
    ))
    
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////
    template <
        class Range, class ForwardIt
      , ELIB_ENABLE_IF(is_range<Range>::value)
      >
    auto rotate(Range && r, ForwardIt pos)
    ELIB_AUTO_RETURN_NOEXCEPT(std::rotate(
        elib::adl_begin( elib::forward<Range>(r) )
      , elib::adl_end  ( elib::forward<Range>(r) )
      , pos
    ))
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Range, class ForwardIt, class OutIt
      , ELIB_ENABLE_IF(is_range<Range>::value)
      >
    auto rotate_copy(Range && r, ForwardIt pos, OutIt out)
    ELIB_AUTO_RETURN_NOEXCEPT(std::rotate_copy(
        elib::adl_begin( elib::forward<Range>(r) )
      , elib::adl_end  ( elib::forward<Range>(r) )
      , pos, out
    ))
    
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////
    template <
        class Range
      , ELIB_ENABLE_IF(is_range<Range>::value)
      >
    auto random_shuffle(Range && r)
    ELIB_AUTO_RETURN_NOEXCEPT(std::random_shuffle(
        elib::adl_begin( elib::forward<Range>(r) )
      , elib::adl_end  ( elib::forward<Range>(r) )
    ))
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Range, class RandFunc
      , ELIB_ENABLE_IF(is_range<Range>::value)
      >
    auto random_shuffle(Range && r, RandFunc && fn)
    ELIB_AUTO_RETURN_NOEXCEPT(std::random_shuffle(
        elib::adl_begin( elib::forward<Range>(r) )
      , elib::adl_end  ( elib::forward<Range>(r) )
      , elib::forward<RandFunc>(fn)
    ))
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Range, class RandFunc
      , ELIB_ENABLE_IF(is_range<Range>::value)
      >
    auto shuffle(Range && r, RandFunc && fn)
    ELIB_AUTO_RETURN_NOEXCEPT(std::shuffle(
        elib::adl_begin( elib::forward<Range>(r) )
      , elib::adl_end  ( elib::forward<Range>(r) )
      , elib::forward<RandFunc>(fn)
    ))
    
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////
    template <
        class Range
      , ELIB_ENABLE_IF(is_range<Range>::value)
      >
    auto unique(Range && r)
    ELIB_AUTO_RETURN_NOEXCEPT(std::unique(
        elib::adl_begin( elib::forward<Range>(r) )
      , elib::adl_end  ( elib::forward<Range>(r) )
    ))
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Range, class BinaryPred
      , ELIB_ENABLE_IF(is_range<Range>::value)
      >
    auto unique(Range && r, BinaryPred p)
    ELIB_AUTO_RETURN_NOEXCEPT(std::unique(
        elib::adl_begin( elib::forward<Range>(r) )
      , elib::adl_end  ( elib::forward<Range>(r) )
      , p
    ))
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Range, class OutputIt
      , ELIB_ENABLE_IF(is_range<Range>::value)
      >
    auto unique_copy(Range && r, OutputIt out)
    ELIB_AUTO_RETURN_NOEXCEPT(std::unique_copy(
        elib::adl_begin( elib::forward<Range>(r) )
      , elib::adl_end  ( elib::forward<Range>(r) )
      , out
    ))
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Range, class OutputIt, class BinaryPred
      , ELIB_ENABLE_IF(is_range<Range>::value)
      >
    auto unique_copy(Range && r, OutputIt out, BinaryPred p)
    ELIB_AUTO_RETURN_NOEXCEPT(std::unique_copy(
        elib::adl_begin( elib::forward<Range>(r) )
      , elib::adl_end  ( elib::forward<Range>(r) )
      , out, p
    ))
    
////////////////////////////////////////////////////////////////////////////////
//  is_partitioned, partition, parition_copy, stable_partition, parition_point
////////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////
    template <
        class Range
      , ELIB_ENABLE_IF(is_range<Range>::value)
      >
    auto is_partitioned(Range && r)
    ELIB_AUTO_RETURN_NOEXCEPT(std::is_partitioned(
        elib::adl_begin( elib::forward<Range>(r) )
      , elib::adl_end  ( elib::forward<Range>(r) )
    ))
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Range, class Compare
      , ELIB_ENABLE_IF(is_range<Range>::value)
      >
    auto is_partitioned(Range && r, Compare cmp)
    ELIB_AUTO_RETURN_NOEXCEPT(std::is_partitioned(
        elib::adl_begin( elib::forward<Range>(r) )
      , elib::adl_end  ( elib::forward<Range>(r) )
      , cmp
    ))
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Range
      , ELIB_ENABLE_IF(is_range<Range>::value)
      >
    auto partition(Range && r)
    ELIB_AUTO_RETURN_NOEXCEPT(std::partition(
        elib::adl_begin( elib::forward<Range>(r) )
      , elib::adl_end  ( elib::forward<Range>(r) )
    ))
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Range, class Compare
      , ELIB_ENABLE_IF(is_range<Range>::value)
      >
    auto partition(Range && r, Compare cmp)
    ELIB_AUTO_RETURN_NOEXCEPT(std::partition(
        elib::adl_begin( elib::forward<Range>(r) )
      , elib::adl_end  ( elib::forward<Range>(r) )
      , cmp
    ))
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Range, class OutputIt1, class OutputIt2
      , ELIB_ENABLE_IF(is_range<Range>::value)
      >
    auto partition_copy(Range && r, OutputIt1 out1, OutputIt2 out2)
    ELIB_AUTO_RETURN_NOEXCEPT(std::partition_copy(
        elib::adl_begin( elib::forward<Range>(r) )
      , elib::adl_end  ( elib::forward<Range>(r) )
      , out1, out2
    ))
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Range, class OutputIt1, class OutputIt2
      , class UnaryPred
      , ELIB_ENABLE_IF(is_range<Range>::value)
      >
    auto partition_copy(Range && r, OutputIt1 out1, OutputIt2 out2, UnaryPred p)
    ELIB_AUTO_RETURN_NOEXCEPT(std::partition_copy(
        elib::adl_begin( elib::forward<Range>(r) )
      , elib::adl_end  ( elib::forward<Range>(r) )
      , out1, out2, p
    ))
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Range
      , ELIB_ENABLE_IF(is_range<Range>::value)
      >
    auto stable_partition(Range && r)
    ELIB_AUTO_RETURN_NOEXCEPT(std::stable_partition(
        elib::adl_begin( elib::forward<Range>(r) )
      , elib::adl_end  ( elib::forward<Range>(r) )
    ))
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Range, class Compare
      , ELIB_ENABLE_IF(is_range<Range>::value)
      >
    auto stable_partition(Range && r, Compare cmp)
    ELIB_AUTO_RETURN_NOEXCEPT(std::stable_partition(
        elib::adl_begin( elib::forward<Range>(r) )
      , elib::adl_end  ( elib::forward<Range>(r) )
      , cmp
    ))
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Range, class UnaryPred
      , ELIB_ENABLE_IF(is_range<Range>::value)
      >
    auto partition_point(Range && r, UnaryPred p)
    ELIB_AUTO_RETURN_NOEXCEPT(std::partition_point(
        elib::adl_begin( elib::forward<Range>(r) )
      , elib::adl_end  ( elib::forward<Range>(r) )
      , p
    ))
    
    
////////////////////////////////////////////////////////////////////////////////
//       is_sorted, is_sorted_until, sort, stable_sort, nth_element
////////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////
    template <
        class Range
      , ELIB_ENABLE_IF(is_range<Range>::value)
      >
    auto is_sorted(Range && r)
    ELIB_AUTO_RETURN_NOEXCEPT(std::is_sorted(
        elib::adl_begin( elib::forward<Range>(r) )
      , elib::adl_end  ( elib::forward<Range>(r) )
    ))
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Range, class Compare
      , ELIB_ENABLE_IF(is_range<Range>::value)
      >
    auto is_sorted(Range && r, Compare cmp)
    ELIB_AUTO_RETURN_NOEXCEPT(std::is_sorted(
        elib::adl_begin( elib::forward<Range>(r) )
      , elib::adl_end  ( elib::forward<Range>(r) )
      , cmp
    ))
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Range
      , ELIB_ENABLE_IF(is_range<Range>::value)
      >
    auto is_sorted_until(Range && r)
    ELIB_AUTO_RETURN_NOEXCEPT(std::is_sorted_until(
        elib::adl_begin( elib::forward<Range>(r) )
      , elib::adl_end  ( elib::forward<Range>(r) )
    ))
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Range, class Compare
      , ELIB_ENABLE_IF(is_range<Range>::value)
      >
    auto is_sorted_until(Range && r, Compare cmp)
    ELIB_AUTO_RETURN_NOEXCEPT(std::is_sorted_until(
        elib::adl_begin( elib::forward<Range>(r) )
      , elib::adl_end  ( elib::forward<Range>(r) )
      , cmp
    ))
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Range
      , ELIB_ENABLE_IF(is_range<Range>::value)
      >
    auto sort(Range && r)
    ELIB_AUTO_RETURN_NOEXCEPT(std::sort(
        elib::adl_begin( elib::forward<Range>(r) )
      , elib::adl_end  ( elib::forward<Range>(r) )
    ))
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Range, class Compare
      , ELIB_ENABLE_IF(is_range<Range>::value)
      >
    auto sort(Range && r, Compare cmp)
    ELIB_AUTO_RETURN_NOEXCEPT(std::sort(
        elib::adl_begin( elib::forward<Range>(r) )
      , elib::adl_end  ( elib::forward<Range>(r) )
      , cmp
    ))
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Range, class RandIt
      , ELIB_ENABLE_IF(is_range<Range>::value)
      >
    auto partial_sort(Range && r, RandIt pivot)
    ELIB_AUTO_RETURN_NOEXCEPT(std::partial_sort(
        elib::adl_begin( elib::forward<Range>(r) )
      , pivot
      , elib::adl_end  ( elib::forward<Range>(r) )
    ))
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Range, class RandIt, class Compare
      , ELIB_ENABLE_IF(is_range<Range>::value)
      >
    auto partial_sort(Range && r, RandIt pivot, Compare cmp)
    ELIB_AUTO_RETURN_NOEXCEPT(std::partial_sort(
        elib::adl_begin( elib::forward<Range>(r) )
      , pivot
      , elib::adl_end  ( elib::forward<Range>(r) )
      , cmp
    ))
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Range, class RandIt
      , ELIB_ENABLE_IF(is_range<Range>::value)
      >
    auto partial_sort_copy(Range && r, RandIt dfirst, RandIt dlast)
    ELIB_AUTO_RETURN_NOEXCEPT(std::partial_sort_copy(
        elib::adl_begin( elib::forward<Range>(r) )
      , elib::adl_end  ( elib::forward<Range>(r) )
      , dfirst, dlast
    ))
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Range, class RandIt, class Compare
      , ELIB_ENABLE_IF(is_range<Range>::value)
      >
    auto partial_sort_copy(Range && r, RandIt dfirst, RandIt dlast, Compare cmp)
    ELIB_AUTO_RETURN_NOEXCEPT(std::partial_sort_copy(
        elib::adl_begin( elib::forward<Range>(r) )
      , elib::adl_end  ( elib::forward<Range>(r) )
      , dfirst, dlast, cmp
    ))
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Range
      , ELIB_ENABLE_IF(is_range<Range>::value)
      >
    auto stable_sort(Range && r)
    ELIB_AUTO_RETURN_NOEXCEPT(std::stable_sort(
        elib::adl_begin( elib::forward<Range>(r) )
      , elib::adl_end  ( elib::forward<Range>(r) )
    ))
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Range, class Compare
      , ELIB_ENABLE_IF(is_range<Range>::value)
      >
    auto stable_sort(Range && r, Compare cmp)
    ELIB_AUTO_RETURN_NOEXCEPT(std::stable_sort(
        elib::adl_begin( elib::forward<Range>(r) )
      , elib::adl_end  ( elib::forward<Range>(r) )
      , cmp
    ))
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Range, class RandIt
      , ELIB_ENABLE_IF(is_range<Range>::value)
      >
    auto nth_element(Range && r, RandIt pivot)
    ELIB_AUTO_RETURN_NOEXCEPT(std::nth_element(
        elib::adl_begin( elib::forward<Range>(r) )
      , pivot
      , elib::adl_end  ( elib::forward<Range>(r) )
    ))
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Range, class RandIt, class Compare
      , ELIB_ENABLE_IF(is_range<Range>::value)
      >
    auto nth_element(Range && r, RandIt pivot, Compare cmp)
    ELIB_AUTO_RETURN_NOEXCEPT(std::nth_element(
        elib::adl_begin( elib::forward<Range>(r) )
      , pivot
      , elib::adl_end  ( elib::forward<Range>(r) )
      , cmp
    ))
    
////////////////////////////////////////////////////////////////////////////////
//                        lower_bound, upper_bound    
////////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////
    template <
        class Range, class T
      , ELIB_ENABLE_IF(is_range<Range>::value)
      >
    auto lower_bound( Range && r, T const & v)
    ELIB_AUTO_RETURN_NOEXCEPT(std::lower_bound(
        elib::adl_begin( elib::forward<Range>(r) )
      , elib::adl_end  ( elib::forward<Range>(r) )
      , v
    ))
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Range, class T, class Compare
      , ELIB_ENABLE_IF(is_range<Range>::value)
      >
    auto lower_bound( Range && r, T const & v, Compare cmp)
    ELIB_AUTO_RETURN_NOEXCEPT(std::lower_bound(
        elib::adl_begin( elib::forward<Range>(r) )
      , elib::adl_end  ( elib::forward<Range>(r) )
      , v, cmp
    ))
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Range, class T
      , ELIB_ENABLE_IF(is_range<Range>::value)
      >
    auto upper_bound( Range && r, T const & v)
    ELIB_AUTO_RETURN_NOEXCEPT(std::upper_bound(
        elib::adl_begin( elib::forward<Range>(r) )
      , elib::adl_end  ( elib::forward<Range>(r) )
      , v
    ))
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Range, class T, class Compare
      , ELIB_ENABLE_IF(is_range<Range>::value)
      >
    auto upper_bound( Range && r, T const & v, Compare cmp)
    ELIB_AUTO_RETURN_NOEXCEPT(std::upper_bound(
        elib::adl_begin( elib::forward<Range>(r) )
      , elib::adl_end  ( elib::forward<Range>(r) )
      , v, cmp
    ))
    
////////////////////////////////////////////////////////////////////////////////
//                           binary_search
////////////////////////////////////////////////////////////////////////////////
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Range, class T
      , ELIB_ENABLE_IF(is_range<Range>::value)
      >
    auto binary_search( Range && r, T const & v)
    ELIB_AUTO_RETURN_NOEXCEPT(std::binary_search(
        elib::adl_begin( elib::forward<Range>(r) )
      , elib::adl_end  ( elib::forward<Range>(r) )
      , v
    ))
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Range, class T, class Compare
      , ELIB_ENABLE_IF(is_range<Range>::value)
      >
    auto binary_search( Range && r, T const & v, Compare cmp)
    ELIB_AUTO_RETURN_NOEXCEPT(std::binary_search(
        elib::adl_begin( elib::forward<Range>(r) )
      , elib::adl_end  ( elib::forward<Range>(r) )
      , v, cmp
    ))
    
////////////////////////////////////////////////////////////////////////////////
//                            equal_range   
////////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////
    template <
        class Range, class T
      , ELIB_ENABLE_IF(is_range<Range>::value)
      >
    auto equal_range( Range && r, T const & v)
    ELIB_AUTO_RETURN_NOEXCEPT(std::equal_range(
        elib::adl_begin( elib::forward<Range>(r) )
      , elib::adl_end  ( elib::forward<Range>(r) )
      , v
    ))
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Range, class T, class Compare
      , ELIB_ENABLE_IF(is_range<Range>::value)
      >
    auto equal_range( Range && r, T const & v, Compare cmp)
    ELIB_AUTO_RETURN_NOEXCEPT(std::equal_range(
        elib::adl_begin( elib::forward<Range>(r) )
      , elib::adl_end  ( elib::forward<Range>(r) )
      , v, cmp
    ))
    
////////////////////////////////////////////////////////////////////////////////
//                            merge  
////////////////////////////////////////////////////////////////////////////////
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Range1, class Range2, class OutIt
      , ELIB_ENABLE_IF(is_range<Range1>::value)
      , ELIB_ENABLE_IF(is_range<Range2>::value)
      >
    auto merge(Range1 && r1, Range2 && r2, OutIt out)
    ELIB_AUTO_RETURN_NOEXCEPT(std::merge(
        elib::adl_begin( elib::forward<Range1>(r1) )
      , elib::adl_end  ( elib::forward<Range1>(r1) )
      , elib::adl_begin( elib::forward<Range2>(r2) )
      , elib::adl_end  ( elib::forward<Range2>(r2) )
      , out
    ))
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Range1, class Range2, class OutIt, class Compare
      , ELIB_ENABLE_IF(is_range<Range1>::value)
      , ELIB_ENABLE_IF(is_range<Range2>::value)
      >
    auto merge(Range1 && r1, Range2 && r2, OutIt out, Compare cmp)
    ELIB_AUTO_RETURN_NOEXCEPT(std::merge(
        elib::adl_begin( elib::forward<Range1>(r1) )
      , elib::adl_end  ( elib::forward<Range1>(r1) )
      , elib::adl_begin( elib::forward<Range2>(r2) )
      , elib::adl_end  ( elib::forward<Range2>(r2) )
      , out, cmp
    ))
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Range, class RangeIt
      , ELIB_ENABLE_IF(is_range<Range>::value)
      >
    auto inplace_merge(Range && r, RangeIt pivot)
    ELIB_AUTO_RETURN_NOEXCEPT(std::inplace_merge(
        elib::adl_begin( elib::forward<Range>(r) )
      , pivot
      , elib::adl_end  ( elib::forward<Range>(r) )
    ))
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Range, class RangeIt, class Compare
      , ELIB_ENABLE_IF(is_range<Range>::value)
      >
    auto inplace_merge(Range && r, RangeIt pivot, Compare cmp)
    ELIB_AUTO_RETURN_NOEXCEPT(std::inplace_merge(
        elib::adl_begin( elib::forward<Range>(r) )
      , pivot
      , elib::adl_end  ( elib::forward<Range>(r) )
      , cmp
    ))
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Range1, class Range2
      , ELIB_ENABLE_IF(is_range<Range1>::value)
      , ELIB_ENABLE_IF(is_range<Range2>::value)
      >
    auto includes(Range1 && r1, Range2 && r2)
    ELIB_AUTO_RETURN_NOEXCEPT(std::includes(
        elib::adl_begin( elib::forward<Range1>(r1) )
      , elib::adl_end  ( elib::forward<Range1>(r1) )
      , elib::adl_begin( elib::forward<Range2>(r2) )
      , elib::adl_end  ( elib::forward<Range2>(r2) )
    ))
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Range1, class Range2, class Compare
      , ELIB_ENABLE_IF(is_range<Range1>::value)
      , ELIB_ENABLE_IF(is_range<Range2>::value)
      >
    auto includes(Range1 && r1, Range2 && r2, Compare cmp)
    ELIB_AUTO_RETURN_NOEXCEPT(std::includes(
        elib::adl_begin( elib::forward<Range1>(r1) )
      , elib::adl_end  ( elib::forward<Range1>(r1) )
      , elib::adl_begin( elib::forward<Range2>(r2) )
      , elib::adl_end  ( elib::forward<Range2>(r2) )
      , cmp
    ))
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Range1, class Range2, class OutIt
      , ELIB_ENABLE_IF(is_range<Range1>::value)
      , ELIB_ENABLE_IF(is_range<Range2>::value)
      >
    auto set_difference(Range1 && r1, Range2 && r2, OutIt out)
    ELIB_AUTO_RETURN_NOEXCEPT(std::set_difference(
        elib::adl_begin( elib::forward<Range1>(r1) )
      , elib::adl_end  ( elib::forward<Range1>(r1) )
      , elib::adl_begin( elib::forward<Range2>(r2) )
      , elib::adl_end  ( elib::forward<Range2>(r2) )
      , out
    ))
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Range1, class Range2, class OutIt, class Compare
      , ELIB_ENABLE_IF(is_range<Range1>::value)
      , ELIB_ENABLE_IF(is_range<Range2>::value)
      >
    auto set_difference(Range1 && r1, Range2 && r2, OutIt out, Compare cmp)
    ELIB_AUTO_RETURN_NOEXCEPT(std::set_difference(
        elib::adl_begin( elib::forward<Range1>(r1) )
      , elib::adl_end  ( elib::forward<Range1>(r1) )
      , elib::adl_begin( elib::forward<Range2>(r2) )
      , elib::adl_end  ( elib::forward<Range2>(r2) )
      , out, cmp
    ))
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Range1, class Range2, class OutIt
      , ELIB_ENABLE_IF(is_range<Range1>::value)
      , ELIB_ENABLE_IF(is_range<Range2>::value)
      >
    auto set_symmetric_difference(Range1 && r1, Range2 && r2, OutIt out)
    ELIB_AUTO_RETURN_NOEXCEPT(std::set_symmetric_difference(
        elib::adl_begin( elib::forward<Range1>(r1) )
      , elib::adl_end  ( elib::forward<Range1>(r1) )
      , elib::adl_begin( elib::forward<Range2>(r2) )
      , elib::adl_end  ( elib::forward<Range2>(r2) )
      , out
    ))
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Range1, class Range2, class OutIt, class Compare
      , ELIB_ENABLE_IF(is_range<Range1>::value)
      , ELIB_ENABLE_IF(is_range<Range2>::value)
      >
    auto set_symmetric_difference(Range1 && r1, Range2 && r2, OutIt out, Compare cmp)
    ELIB_AUTO_RETURN_NOEXCEPT(std::set_symmetric_difference(
        elib::adl_begin( elib::forward<Range1>(r1) )
      , elib::adl_end  ( elib::forward<Range1>(r1) )
      , elib::adl_begin( elib::forward<Range2>(r2) )
      , elib::adl_end  ( elib::forward<Range2>(r2) )
      , out, cmp
    ))
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Range1, class Range2, class OutIt
      , ELIB_ENABLE_IF(is_range<Range1>::value)
      , ELIB_ENABLE_IF(is_range<Range2>::value)
      >
    auto set_intersection(Range1 && r1, Range2 && r2, OutIt out)
    ELIB_AUTO_RETURN_NOEXCEPT(std::set_intersection(
        elib::adl_begin( elib::forward<Range1>(r1) )
      , elib::adl_end  ( elib::forward<Range1>(r1) )
      , elib::adl_begin( elib::forward<Range2>(r2) )
      , elib::adl_end  ( elib::forward<Range2>(r2) )
      , out
    ))
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Range1, class Range2, class OutIt, class Compare
      , ELIB_ENABLE_IF(is_range<Range1>::value)
      , ELIB_ENABLE_IF(is_range<Range2>::value)
      >
    auto set_intersection(Range1 && r1, Range2 && r2, OutIt out, Compare cmp)
    ELIB_AUTO_RETURN_NOEXCEPT(std::set_intersection(
        elib::adl_begin( elib::forward<Range1>(r1) )
      , elib::adl_end  ( elib::forward<Range1>(r1) )
      , elib::adl_begin( elib::forward<Range2>(r2) )
      , elib::adl_end  ( elib::forward<Range2>(r2) )
      , out, cmp
    ))
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Range1, class Range2, class OutIt
      , ELIB_ENABLE_IF(is_range<Range1>::value)
      , ELIB_ENABLE_IF(is_range<Range2>::value)
      >
    auto set_union(Range1 && r1, Range2 && r2, OutIt out)
    ELIB_AUTO_RETURN_NOEXCEPT(std::set_union(
        elib::adl_begin( elib::forward<Range1>(r1) )
      , elib::adl_end  ( elib::forward<Range1>(r1) )
      , elib::adl_begin( elib::forward<Range2>(r2) )
      , elib::adl_end  ( elib::forward<Range2>(r2) )
      , out
    ))
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Range1, class Range2, class OutIt, class Compare
      , ELIB_ENABLE_IF(is_range<Range1>::value)
      , ELIB_ENABLE_IF(is_range<Range2>::value)
      >
    auto set_union(Range1 && r1, Range2 && r2, OutIt out, Compare cmp)
    ELIB_AUTO_RETURN_NOEXCEPT(std::set_union(
        elib::adl_begin( elib::forward<Range1>(r1) )
      , elib::adl_end  ( elib::forward<Range1>(r1) )
      , elib::adl_begin( elib::forward<Range2>(r2) )
      , elib::adl_end  ( elib::forward<Range2>(r2) )
      , out, cmp
    ))
    
////////////////////////////////////////////////////////////////////////////////
//           is_heap, make_heap, push_heap, pop_heap, sort_heap
////////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////
    template <
        class Range
      , ELIB_ENABLE_IF(is_range<Range>::value)
      >
    auto is_heap(Range && r)
    ELIB_AUTO_RETURN_NOEXCEPT(std::is_heap(
        elib::adl_begin( elib::forward<Range>(r) )
      , elib::adl_end  ( elib::forward<Range>(r) )
    ))
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Range, class Compare
      , ELIB_ENABLE_IF(is_range<Range>::value)
      >
    auto is_heap(Range && r, Compare cmp)
    ELIB_AUTO_RETURN_NOEXCEPT(std::is_heap(
        elib::adl_begin( elib::forward<Range>(r) )
      , elib::adl_end  ( elib::forward<Range>(r) )
      , cmp
    ))
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Range
      , ELIB_ENABLE_IF(is_range<Range>::value)
      >
    auto is_heap_until(Range && r)
    ELIB_AUTO_RETURN_NOEXCEPT(std::is_heap_until(
        elib::adl_begin( elib::forward<Range>(r) )
      , elib::adl_end  ( elib::forward<Range>(r) )
    ))
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Range, class Compare
      , ELIB_ENABLE_IF(is_range<Range>::value)
      >
    auto is_heap_until(Range && r, Compare cmp)
    ELIB_AUTO_RETURN_NOEXCEPT(std::is_heap_until(
        elib::adl_begin( elib::forward<Range>(r) )
      , elib::adl_end  ( elib::forward<Range>(r) )
      , cmp
    ))
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Range
      , ELIB_ENABLE_IF(is_range<Range>::value)
      >
    auto make_heap(Range && r)
    ELIB_AUTO_RETURN_NOEXCEPT(std::make_heap(
        elib::adl_begin( elib::forward<Range>(r) )
      , elib::adl_end  ( elib::forward<Range>(r) )
    ))
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Range, class Compare
      , ELIB_ENABLE_IF(is_range<Range>::value)
      >
    auto make_heap(Range && r, Compare cmp)
    ELIB_AUTO_RETURN_NOEXCEPT(std::make_heap(
        elib::adl_begin( elib::forward<Range>(r) )
      , elib::adl_end  ( elib::forward<Range>(r) )
      , cmp
    ))

    ////////////////////////////////////////////////////////////////////////////
    template <
        class Range
      , ELIB_ENABLE_IF(is_range<Range>::value)
      >
    auto push_heap(Range && r)
    ELIB_AUTO_RETURN_NOEXCEPT(std::push_heap(
        elib::adl_begin( elib::forward<Range>(r) )
      , elib::adl_end  ( elib::forward<Range>(r) )
    ))
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Range, class Compare
      , ELIB_ENABLE_IF(is_range<Range>::value)
      >
    auto push_heap(Range && r, Compare cmp)
    ELIB_AUTO_RETURN_NOEXCEPT(std::push_heap(
        elib::adl_begin( elib::forward<Range>(r) )
      , elib::adl_end  ( elib::forward<Range>(r) )
      , cmp
    ))
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Range
      , ELIB_ENABLE_IF(is_range<Range>::value)
      >
    auto pop_heap(Range && r)
    ELIB_AUTO_RETURN_NOEXCEPT(std::pop_heap(
        elib::adl_begin( elib::forward<Range>(r) )
      , elib::adl_end  ( elib::forward<Range>(r) )
    ))
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Range, class Compare
      , ELIB_ENABLE_IF(is_range<Range>::value)
      >
    auto pop_heap(Range && r, Compare cmp)
    ELIB_AUTO_RETURN_NOEXCEPT(std::pop_heap(
        elib::adl_begin( elib::forward<Range>(r) )
      , elib::adl_end  ( elib::forward<Range>(r) )
      , cmp
    ))
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Range
      , ELIB_ENABLE_IF(is_range<Range>::value)
      >
    auto sort_heap(Range && r)
    ELIB_AUTO_RETURN_NOEXCEPT(std::sort_heap(
        elib::adl_begin( elib::forward<Range>(r) )
      , elib::adl_end  ( elib::forward<Range>(r) )
    ))
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Range, class Compare
      , ELIB_ENABLE_IF(is_range<Range>::value)
      >
    auto sort_heap(Range && r, Compare cmp)
    ELIB_AUTO_RETURN_NOEXCEPT(std::sort_heap(
        elib::adl_begin( elib::forward<Range>(r) )
      , elib::adl_end  ( elib::forward<Range>(r) )
      , cmp
    ))
    
////////////////////////////////////////////////////////////////////////////////
//              max_element, min_element, minmax_element
////////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////
    template <
        class Range
      , ELIB_ENABLE_IF(is_range<Range>::value)
      >
    auto max_element(Range && r)
    ELIB_AUTO_RETURN_NOEXCEPT(std::max_element(
        elib::adl_begin( elib::forward<Range>(r) )
      , elib::adl_end  ( elib::forward<Range>(r) )
    ))
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Range, class Compare
      , ELIB_ENABLE_IF(is_range<Range>::value)
      >
    auto max_element(Range && r, Compare cmp)
    ELIB_AUTO_RETURN_NOEXCEPT(std::max_element(
        elib::adl_begin( elib::forward<Range>(r) )
      , elib::adl_end  ( elib::forward<Range>(r) )
      , cmp
    ))
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Range
      , ELIB_ENABLE_IF(is_range<Range>::value)
      >
    auto min_element(Range && r)
    ELIB_AUTO_RETURN_NOEXCEPT(std::min_element(
        elib::adl_begin( elib::forward<Range>(r) )
      , elib::adl_end  ( elib::forward<Range>(r) )
    ))
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Range, class Compare
      , ELIB_ENABLE_IF(is_range<Range>::value)
      >
    auto min_element(Range && r, Compare cmp)
    ELIB_AUTO_RETURN_NOEXCEPT(std::min_element(
        elib::adl_begin( elib::forward<Range>(r) )
      , elib::adl_end  ( elib::forward<Range>(r) )
      , cmp
    ))

    ////////////////////////////////////////////////////////////////////////////
    template <
        class Range
      , ELIB_ENABLE_IF(is_range<Range>::value)
      >
    auto minmax_element(Range && r)
    ELIB_AUTO_RETURN_NOEXCEPT(std::minmax_element(
        elib::adl_begin( elib::forward<Range>(r) )
      , elib::adl_end  ( elib::forward<Range>(r) )
    ))
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Range, class Compare
      , ELIB_ENABLE_IF(is_range<Range>::value)
      >
    auto minmax_element(Range && r, Compare cmp)
    ELIB_AUTO_RETURN_NOEXCEPT(std::minmax_element(
        elib::adl_begin( elib::forward<Range>(r) )
      , elib::adl_end  ( elib::forward<Range>(r) )
      , cmp
    ))
    
////////////////////////////////////////////////////////////////////////////////
//                        lexicographical_compare
////////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////
    template <
        class Range1, class Range2
      , ELIB_ENABLE_IF(is_range<Range1>::value)
      , ELIB_ENABLE_IF(is_range<Range2>::value)
      >
    auto lexicographical_compare(Range1 && r1, Range2 && r2)
    ELIB_AUTO_RETURN_NOEXCEPT(std::lexicographical_compare(
        elib::adl_begin( elib::forward<Range1>(r1) )
      , elib::adl_end  ( elib::forward<Range1>(r1) )
      , elib::adl_begin( elib::forward<Range2>(r2) )
      , elib::adl_end  ( elib::forward<Range2>(r2) )
    ))
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Range1, class Range2
      , class Compare
      , ELIB_ENABLE_IF(is_range<Range1>::value)
      , ELIB_ENABLE_IF(is_range<Range2>::value)
      >
    auto lexicographical_compare(Range1 && r1, Range2 && r2, Compare cmp)
    ELIB_AUTO_RETURN_NOEXCEPT(std::lexicographical_compare(
        elib::adl_begin( elib::forward<Range1>(r1) )
      , elib::adl_end  ( elib::forward<Range1>(r1) )
      , elib::adl_begin( elib::forward<Range2>(r2) )
      , elib::adl_end  ( elib::forward<Range2>(r2) )
      , cmp
    ))
    
////////////////////////////////////////////////////////////////////////////////
//           is_permutation, next_permutation, prev_permutation  
////////////////////////////////////////////////////////////////////////////////
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Range1, class Range2
      , ELIB_ENABLE_IF(is_range<Range1>::value)
      , ELIB_ENABLE_IF(is_range<Range2>::value)
      >
    auto is_permutation(Range1 && r1, Range2 && r2)
    ELIB_AUTO_RETURN_NOEXCEPT(std::is_permutation(
        elib::adl_begin( elib::forward<Range1>(r1) )
      , elib::adl_end  ( elib::forward<Range1>(r1) )
      , elib::adl_begin( elib::forward<Range2>(r2) )
    ))
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Range1, class Range2
      , class BinaryPred
      , ELIB_ENABLE_IF(is_range<Range1>::value)
      , ELIB_ENABLE_IF(is_range<Range2>::value)
      >
    auto is_permutation(Range1 && r1, Range2 && r2, BinaryPred p)
    ELIB_AUTO_RETURN_NOEXCEPT(std::is_permutation(
        elib::adl_begin( elib::forward<Range1>(r1) )
      , elib::adl_end  ( elib::forward<Range1>(r1) )
      , elib::adl_begin( elib::forward<Range2>(r2) )
      , p
    ))
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Range
      , ELIB_ENABLE_IF(is_range<Range>::value)
      >
    auto next_permutation(Range && r)
    ELIB_AUTO_RETURN_NOEXCEPT(std::next_permutation(
        elib::adl_begin( elib::forward<Range>(r) )
      , elib::adl_end  ( elib::forward<Range>(r) )
    ))
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Range, class Compare
      , ELIB_ENABLE_IF(is_range<Range>::value)
      >
    auto next_permutation(Range && r, Compare cmp)
    ELIB_AUTO_RETURN_NOEXCEPT(std::next_permutation(
        elib::adl_begin( elib::forward<Range>(r) )
      , elib::adl_end  ( elib::forward<Range>(r) )
      , cmp
    ))
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Range
      , ELIB_ENABLE_IF(is_range<Range>::value)
      >
    auto prev_permutation(Range && r)
    ELIB_AUTO_RETURN_NOEXCEPT(std::prev_permutation(
        elib::adl_begin( elib::forward<Range>(r) )
      , elib::adl_end  ( elib::forward<Range>(r) )
    ))
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Range, class Compare
      , ELIB_ENABLE_IF(is_range<Range>::value)
      >
    auto prev_permutation(Range && r, Compare cmp)
    ELIB_AUTO_RETURN_NOEXCEPT(std::prev_permutation(
        elib::adl_begin( elib::forward<Range>(r) )
      , elib::adl_end  ( elib::forward<Range>(r) )
      , cmp
    ))
    
}}}                                                          // namespace elib
namespace elib
{
    namespace ranges { using namespace algorithm_adl_barrier; }
    
    using ranges::all_of;
    using ranges::any_of;
    using ranges::none_of;
    using ranges::for_each;
    using ranges::count;
    using ranges::count_if;
    using ranges::mismatch;
    using ranges::equal;
    using ranges::find;
    using ranges::find_if;
    using ranges::find_if_not;
    using ranges::find_end;
    using ranges::find_first_of;
    using ranges::adjacent_find;
    using ranges::search;
    using ranges::search_n;
    
    using ranges::copy;
    using ranges::copy_if;
    using ranges::copy_n;
    using ranges::copy_backward;
    using ranges::move;
    using ranges::move_backward;
    using ranges::fill;
    using ranges::transform;
    using ranges::generate;
    using ranges::remove;
    using ranges::remove_if;
    using ranges::remove_copy;
    using ranges::remove_copy_if;
    using ranges::replace;
    using ranges::replace_if;
    using ranges::replace_copy_if;
    using ranges::swap_ranges;
    using ranges::reverse;
    using ranges::reverse_copy;
    using ranges::rotate;
    using ranges::rotate_copy;
    using ranges::random_shuffle;
    using ranges::shuffle;
    using ranges::unique;
    using ranges::unique_copy;
    
    using ranges::is_partitioned;
    using ranges::partition;
    using ranges::partition_copy;
    using ranges::stable_partition;
    using ranges::partition_point;
    
    using ranges::is_sorted;
    using ranges::is_sorted_until;
    using ranges::sort;
    using ranges::partial_sort;
    using ranges::partial_sort_copy;
    using ranges::stable_sort;
    using ranges::nth_element;
    
    using ranges::lower_bound;
    using ranges::upper_bound;
    using ranges::binary_search;
    using ranges::equal_range;
    
    using ranges::merge;
    using ranges::inplace_merge;
    using ranges::includes;
    using ranges::set_difference;
    using ranges::set_symmetric_difference;
    using ranges::set_intersection;
    using ranges::set_union;
    
    using ranges::is_heap;
    using ranges::is_heap_until;
    using ranges::make_heap;
    using ranges::push_heap;
    using ranges::pop_heap;
    using ranges::sort_heap;
    
    using ranges::max_element;
    using ranges::min_element;
    using ranges::minmax_element;
    using ranges::lexicographical_compare;
    using ranges::is_permutation;
    using ranges::next_permutation;
    using ranges::prev_permutation;
    
}                                                           // namespace elib
#endif /* ELIB_RANGES_ALGORITHM_HPP */