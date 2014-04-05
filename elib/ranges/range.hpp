#ifndef ELIB_RANGES_RANGE_HPP
#define ELIB_RANGES_RANGE_HPP

# include <elib/ranges/begin_end.hpp>
# include <elib/ranges/operations.hpp>
# include <elib/ranges/traits.hpp>
# include <elib/aux.hpp>
# include <algorithm>
# include <iostream>
# include <iterator>
# include <utility>

namespace elib { namespace ranges
{
    ////////////////////////////////////////////////////////////////////////////
    template<class Iterator>
    class range
    {
    public:                                            // types
        using value_type = typename std::iterator_traits<Iterator>::value_type;
        using reference = typename std::iterator_traits<Iterator>::reference;
        using difference_type = typename std::iterator_traits<Iterator>::difference_type;
        using iterator = Iterator;
        using const_iterator = Iterator;

    public:                                             // construction, assignment
        range() = default;

        template< class Iterator2 >
        range(Iterator2 const & xbegin, Iterator2 const & xend)
          : m_iters(xbegin, xend)
        {}

        template< class Range >
        range(Range && r)
          : m_iters(
              ranges::begin(elib::forward<Range>(r))
            , ranges::end(elib::forward<Range>(r))
            )
        {}

        template< class Range >
        range& operator=( Range && r )
        {
            m_iters = {
                ranges::begin(elib::forward<Range>(r))
              , ranges::end(elib::forward<Range>(r))
            };
        }

    public:                                             // forward range functions
        Iterator begin() const
        { return m_iters.first; }
        
        Iterator end() const
        { return m_iters.second; }
        
        difference_type size() const
        { return m_iters.second - m_iters.first; }
        
        bool empty() const
        { return size() == 0; }

    public:                                             // convenience
        explicit operator bool() const
        { return empty(); }
        
        bool equal(range const & other) const
        { return begin() == other.begin() && end() == other.end(); }
        
        reference front() const
        { return *begin(); }
        
        reference back() const
        { return *--end(); }
        
        reference operator[]( difference_type at ) const
        {
            ELIB_ASSERT( 0 <= at && at <= size() );
            return *(begin() + at);
        }
        
        range & advance_begin( difference_type n )
        {
            m_iters.first = std::advance(m_iters.first, n);
            return *this;
        }
        
        range & advance_end( difference_type n )
        {
            m_iters.second = std::advance(m_iters.second, n);
            return *this;
        }

    private:
        std::pair<iterator, iterator> m_iters;
    };

    ////////////////////////////////////////////////////////////////////////////
    template< class Range >
    class sub_range : public range< typename range_iterator<Range>::type >
    {
    public: 
        using base_type = range< typename range_iterator<Range>::type >;
        using iterator = typename range_iterator<Range>::type;
        using const_iterator = typename range_iterator<const Range>::type;
        using const_reference = typename std::iterator_traits<const_iterator>::reference;
        using value_type = typename base_type::value_type;
        using reference = typename base_type::reference;
        using difference_type = typename base_type::difference_type;

    public:                                         // construction, assignment
        sub_range() = default;

        template< class Iterator >
        sub_range(Iterator const & xbegin, Iterator const & xend)
          : base_type(xbegin, xend)
        {}

        template< class Range2 >
        sub_range(Range2 && r)
          : base_type( elib::forward<Range2>(r) )
        {}

        template< class Range2 >
        sub_range & operator=(Range2 && r)
        {
            base_type::operator=(elib::forward<Range2>(r));
            return *this;;
        }

    public:                                          // forward range functions 
        iterator begin()
        { return base_type::begin();}
        
        const_iterator begin() const
        { return base_type::begin(); }
        
        iterator end()
        { return base_type::end(); }
        
        const_iterator  end() const
        { return base_type::end(); }

    public:                                             // convenience 
        reference front()
        { return base_type::front(); }
        
        const_reference  front() const
        { return base_type::front(); }
        
        reference back()
        { return base_type::back(); }
        
        const_reference back() const
        { return base_type::back(); }
        
        reference operator[](difference_type at)
        { return base_type::operator[](at); }
        
        const_reference operator[](difference_type at) const
        { return base_type::operator[](at); }
        
        sub_range & advance_begin( difference_type n )
        { 
            base_type::advance_begin(n);
            return *this;
        }
        
        sub_range & advance_end( difference_type n )
        {
            base_type::advance_end(n);
            return *this;
        }
    };                                                      // class sub_range

    ////////////////////////////////////////////////////////////////////////////
    // stream output
    template< class Iterator, class T, class Traits >
    std::basic_ostream<T,Traits>& 
    operator<<(
        std::basic_ostream<T,Traits> & out
      , range<Iterator> const & r
      )
    {
        using out_iter = std::ostream_iterator<
            typename std::iterator_traits<Iterator>::value_type, T, Traits
          >;
        
        std::copy(
            r.begin(), r.end()
          , out_iter(out)
        ); 
        
        return out;
    }

    ////////////////////////////////////////////////////////////////////////////
    // comparison
    template< class Iterator, class Iterator2 >
    bool operator==(range<Iterator> const & lhs, range<Iterator2> const & rhs)
    {
        return std::equal(
            ranges::begin(lhs), ranges::end(lhs)
          , ranges::begin(rhs)
        );
    }

    template< class Iterator, class Range >
    bool operator==(range<Iterator> const & lhs, Range const & rhs)
    {
        return std::equal(
            ranges::begin(lhs), ranges::end(lhs)
          , ranges::begin(rhs)
        );
    }

    template< class Iterator, class Range >
    bool operator==(Range const & lhs, range<Iterator> const & rhs)
    {
        return std::equal(
            ranges::begin(lhs), ranges::end(lhs)
          , ranges::begin(rhs)
        );
    }

    ////////////////////////////////////////////////////////////////////////////
    template< class Iterator, class Iterator2 >
    bool operator!=(range<Iterator> const & lhs, range<Iterator2> const & rhs)
    {
        return !(lhs == rhs);
    }

    template< class Iterator, class Range >
    bool operator!=(range<Iterator> const & lhs, Range const & rhs)
    {
        return !(lhs == rhs);
    }

    template< class Iterator, class Range >
    bool operator!=(Range const & lhs, range<Iterator> const & rhs)
    {
        return !(lhs == rhs);
    }

    ////////////////////////////////////////////////////////////////////////////
    template< class Iterator, class Iterator2 >
    bool operator<(range<Iterator> const & lhs, range<Iterator2> const & rhs)
    {
        return std::lexicographical_compare(
            ranges::begin(lhs), ranges::end(lhs)
          , ranges::begin(rhs), ranges::end(rhs)
          );
    }

    template< class Iterator, class Range >
    bool operator<(range<Iterator> const & lhs, Range const & rhs)
    {
        return std::lexicographical_compare(
            ranges::begin(lhs), ranges::end(lhs)
          , ranges::begin(rhs), ranges::end(rhs)
          );
    }

    template< class Iterator, class Range >
    bool operator<(Range const & lhs, range<Iterator> const & rhs)
    {
        return std::lexicographical_compare(
            ranges::begin(lhs), ranges::end(lhs)
          , ranges::begin(rhs), ranges::end(rhs)
          );
    }

    ////////////////////////////////////////////////////////////////////////////
    template< class Range, class Range2 >
    bool operator==(sub_range<Range> const & lhs, sub_range<Range2> const & rhs)
    {
        using lhs_base = typename sub_range<Range>::base_type const &;
        using rhs_base = typename sub_range<Range2>::base_type const &;
        return static_cast<lhs_base>(lhs) == static_cast<rhs_base>(rhs);
    }

    ////////////////////////////////////////////////////////////////////////////
    template< class Range, class Range2 >
    bool operator!=(sub_range<Range> const & lhs, sub_range<Range2> const & rhs)
    {
        using lhs_base = typename sub_range<Range>::base_type const &;
        using rhs_base = typename sub_range<Range2>::base_type const &;
        return static_cast<lhs_base>(lhs) != static_cast<rhs_base>(rhs);
    }

    ////////////////////////////////////////////////////////////////////////////
    template< class Range, class Range2 >
    bool operator<(sub_range<Range> const & lhs, sub_range<Range2> const & rhs)
    {
        using lhs_base = typename sub_range<Range>::base_type const &;
        using rhs_base = typename sub_range<Range2>::base_type const &;
        return static_cast<lhs_base>(lhs) < static_cast<rhs_base>(rhs);
    }

    ////////////////////////////////////////////////////////////////////////////
    // external construction
    template< class Iterator >
    range<Iterator>
    make_range(Iterator const & begin, Iterator const & end)
    {
        return range<Iterator>(begin, end);
    }
    
    template< class Range >
    range<range_iterator_t<Range>> 
    make_range(Range && r)
    {
        return range<range_iterator_t<Range>>(elib::forward<Range>(r));
    }

    template< class Range >
    range<range_iterator_t<Range>> 
    make_range(
        Range && r
      , range_difference_t<Range> advance_begin
      , range_difference_t<Range> advance_end 
      )
    {
        range<range_iterator_t<Range>> tmp(elib::forward<Range>(r));
        tmp.advance_begin(advance_begin);
        tmp.advance_end(advance_end);
        return tmp;
    }
}}                                                          // namespace elib
namespace elib
{
    using ranges::range;
    using ranges::sub_range;
    using ranges::make_range;
}                                                           // namespace elib
#endif /* ELIB_RANGES_RANGE_HPP */