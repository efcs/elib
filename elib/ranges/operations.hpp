#ifndef ELIB_RANGES_OPERATIONS_HPP
#define ELIB_RANGES_OPERATIONS_HPP

# include <elib/ranges/begin_end.hpp>
# include <elib/ranges/traits.hpp>
# include <elib/aux/convert.hpp>
# include <iterator>
# include <utility>
# include <cstddef>

namespace elib { namespace ranges
{
    template< class RandomAccessRange >
    range_difference_t<RandomAccessRange> 
    size(RandomAccessRange const & r)
    {
        return ranges::end(r) - ranges::begin(r);
    }
    
    template< class Range >
    bool empty(Range const & r)
    {
        return (ranges::size(r) == 0);;
    }

    template< class BidirectionalRange >
    range_reverse_iterator_t<BidirectionalRange>
    rbegin(BidirectionalRange && r)
    {
        return elib::convert(ranges::end(r));
    }

    template< class BidirectionalRange >
    range_reverse_iterator_t<BidirectionalRange>
    rend(BidirectionalRange && r)
    {
        return elib::convert(ranges::begin(r));
    }

    template< class Range >
    range_iterator_t<const Range> 
    const_begin(Range const & r)
    {
        return ranges::begin(r);
    }

    template< class Range >
    range_iterator_t<const Range>
    const_end(Range const & r)
    {
        return ranges::end(r);
    }

    template< class BidirectionalRange >
    range_reverse_iterator_t<const BidirectionalRange> 
    const_rbegin(BidirectionalRange const & r)
    {
        return ranges::rbegin(r);
    }

    template< class BidirectionalRange >
    range_reverse_iterator_t<const BidirectionalRange>
    const_rend(BidirectionalRange const & r)
    {
        return ranges::rend(r);
    }
    
    template< class CopyableRange, class Range >      
    CopyableRange copy_range(Range const & r)
    {
        return CopyableRange(ranges::begin(r), ranges::end(r));
    }

    template< class ForwardRange >
    typename range_difference<ForwardRange>::type
    distance(ForwardRange const & r)
    {
        return std::distance(ranges::begin(r), ranges::end(r));
    }
    
}}                                                          // namespace elib
namespace elib
{
    using ranges::size;
    using ranges::empty;
    using ranges::rbegin;
    using ranges::rend;
    using ranges::const_begin;
    using ranges::const_end;
    using ranges::const_rbegin;
    using ranges::const_rend;
    using ranges::copy_range;
    using ranges::distance;
}                                                           // namespace elib
#endif /* ELIB_RANGES_OPERATIONS_HPP */