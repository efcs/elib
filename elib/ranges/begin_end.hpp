#ifndef ELIB_RANGES_BEGIN_END_HPP
#define ELIB_RANGES_BEGIN_END_HPP

# include <elib/aux/forward.hpp>
# include <utility>
# include <cstddef>

namespace elib { namespace ranges
{
    ////////////////////////////////////////////////////////////////////////////
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
    auto begin(Range && r) -> 
        decltype( range_begin(elib::forward<Range>(r)) )
    {
        return range_begin(elib::forward<Range>(r));
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
    
    template <class Range>
    auto end(Range && r) -> 
        decltype( range_end(elib::forward<Range>(r)) )
    {
        return range_end(elib::forward<Range>(r));
    }
}}                                                          // namespace elib
namespace elib
{
    using ranges::range_begin;
    using ranges::begin;
    using ranges::range_end;
    using ranges::end;
}                                                           // namespace elib
#endif /* ELIB_RANGES_BEGIN_END_HPP */  