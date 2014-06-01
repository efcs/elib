#ifndef ELIB_EXPERIMENTAL_RANGES_NUMERIC_HPP
#define ELIB_EXPERIMENTAL_RANGES_NUMERIC_HPP

# include <elib/experimental/ranges/traits.hpp>
# include <elib/aux.hpp>
# include <numeric>

namespace elib { namespace experimental { namespace ranges { namespace numeric_adl_barrier
{
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////
    template <
        class Range, class T
      , ELIB_ENABLE_IF(is_range<Range>::value)
      >
    auto accumulate(Range && r, T init)
    ELIB_AUTO_RETURN_NOEXCEPT(std::accumulate(
        elib::adl_begin( elib::forward<Range>(r) )
      , elib::adl_end  ( elib::forward<Range>(r) )
      , init
    ))
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Range, class T, class BinaryOp
      , ELIB_ENABLE_IF(is_range<Range>::value)
      >
    auto accumulate(Range && r, T init, BinaryOp op)
    ELIB_AUTO_RETURN_NOEXCEPT(std::accumulate(
        elib::adl_begin( elib::forward<Range>(r) )
      , elib::adl_end  ( elib::forward<Range>(r) )
      , init, op
    ))
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Range1, class Range2
      , class T
      , ELIB_ENABLE_IF(is_range<Range1>::value)
      , ELIB_ENABLE_IF(is_range<Range2>::value)
      >
    auto inner_product(Range1 && r1, Range2 && r2, T init)
    ELIB_AUTO_RETURN_NOEXCEPT(std::inner_product(
        elib::adl_begin( elib::forward<Range1>(r1) )
      , elib::adl_end  ( elib::forward<Range1>(r1) )
      , elib::adl_begin( elib::forward<Range2>(r2) )
      , init
    ))
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Range1, class Range2
      , class T, class BinaryOp1, class BinaryOp2
      , ELIB_ENABLE_IF(is_range<Range1>::value)
      , ELIB_ENABLE_IF(is_range<Range2>::value)
      >
    auto inner_product(
        Range1 && r1, Range2 && r2
      , T init, BinaryOp1 op1, BinaryOp2 op2
      )
    ELIB_AUTO_RETURN_NOEXCEPT(std::inner_product(
        elib::adl_begin( elib::forward<Range1>(r1) )
      , elib::adl_end  ( elib::forward<Range1>(r1) )
      , elib::adl_begin( elib::forward<Range2>(r2) )
      , init, op1, op2
    ))
    
}}}}                                                         // namespace elib
#endif /* ELIB_EXPERIMENTAL_RANGES_NUMERIC_HPP */