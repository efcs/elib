#ifndef ELIB_RANGES_OPERATIONS_HPP
#define ELIB_RANGES_OPERATIONS_HPP

# include <elib/ranges/traits.hpp>
# include <elib/aux/convert.hpp>
# include <utility>
# include <cstddef>

namespace elib { namespace ranges
{
    template <class Range>
    auto range_begin(Range && r) -> decltype( r.begin() )
    {
        return r.begin();
    }
    
    template <class Iterator>
    Iterator range_begin(std::pair<Iterator, Iterator> const & p)
    {
        return p.first;
    }
    
    template <class T, std::size_t N>
    T* range_begin(T (&array)[N] )
    {
        return array;
    }
    
    template <class Range>
    auto range_end(Range && r) -> decltype( r.end() )
    {
        return r.end();
    }
    
    template <class Iterator>
    Iterator range_end(std::pair<Iterator, Iterator> const & p)
    {
        return p.second;
    }
    
    template <class T, std::size_t N>
    T* range_end(T (&array)[N] )
    {
        return array + N;
    }
    
    template< class RandomAccessRange >
    typename range_difference<RandomAccessRange>::type 
    size(RandomAccessRange const & r)
    {
        return std::end(r) - std::begin(r);
    }
    
    template< class Range >
    bool empty(Range const & r)
    {
        return (ranges::size(r) == 0);;
    }

    template< class BidirectionalRange >
    typename range_reverse_iterator<BidirectionalRange>::type 
    rbegin(BidirectionalRange && r )
    {
        return elib::convert(std::end(r));
    }

    template< class BidirectionalRange >
    typename range_reverse_iterator<BidirectionalRange>::type
    rend(BidirectionalRange && r)
    {
        return elib::convert(std::begin(r));
    }

    template< class Range >
    typename range_iterator<const Range>::type 
    const_begin(Range const & r)
    {
        return std::begin(r);
    }

    template< class Range >
    typename range_iterator<const Range>::type 
    const_end(Range const & r)
    {
        return std::end(r);
    }

    template< class BidirectionalRange >
    typename range_reverse_iterator<const BidirectionalRange>::type 
    const_rbegin( const BidirectionalRange& r );

    template< class BidirectionalRange >
    typename range_reverse_iterator<const BidirectionalRange>::type 
    const_rend( const BidirectionalRange& r );
    
}}                                                          // namespace elib
#endif /* ELIB_RANGES_OPERATIONS_HPP */