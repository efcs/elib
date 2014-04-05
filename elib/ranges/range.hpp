#ifndef ELIB_RANGES_RANGE_HPP
#define ELIB_RANGES_RANGE_HPP

# include <elib/ranges/operations.hpp>
# include <elib/ranges/traits.hpp>

# include <iostream>
# include <iterator>

namespace elib { namespace ranges
{
    template< class Iterator >
    class range
    {
    public:                                            // types
        using value_type = typename std::iterator_traits<Iterator>::value_type;
        using reference = typename std::iterator_traits<Iterator>::reference;
        using difference_type = typename std::iterator_traits<Iterator>::difference_type;
        using iterator = Iterator;
        using const_iterator = Iterator;

    public:                                             // construction, assignment
        range();

        template< class Iterator2 >
        range( const Iterator2& begin, const Iterator2& end );

        template< class Range >
        range( Range&& r );

        template< class Range >
        range& operator=( Range&& r );

    public:                                             // forward range functions
        iterator        begin() const;
        iterator        end() const;
        difference_type size() const;
        bool            empty() const;

    public:                                             // convenience
        operator    unspecified_bool_type() const;
        bool        equal( const range& ) const;
        reference   front() const;
        reference   back() const;
        reference   operator[]( difference_type at ) const;
        range&      advance_begin( difference_type n );
        range&      advance_end( difference_type n );
    };

    template< class Range >
    class sub_range : public range< typename range_iterator<Range>::type >
    {
    public: 
        using base_type = range< typename range_iterator<Range>::type >;
        using iterator = typename range_iterator<Range>::type;
        using const_iterator = typename range_iterator<const Range>::type;
        using const_reference = std::iterator_traits<const_iterator>::reference;
        using base_type::value_type;
        using base_type::reference;
        using base_type::difference_type;

    public:                                             // construction, assignment
        sub_range();

        template< class Iterator >
        sub_range( const Iterator& begin, const Iterator& end );

        template< class Range2 >
        sub_range( Range2&& r );

    template< class Range2 >
        sub_range& operator=( Range2&& r );

    public:                                             // forward range functions 
        iterator        begin();
        const_iterator  begin() const;
        iterator        end();
        const_iterator  end() const;    

    public:                                             // convenience 
        reference        front();
        const_reference  front() const;
        reference        back();
        const_reference  back() const;
        reference        operator[]( difference_type at );
        const_reference  operator[]( difference_type at ) const;   
        sub_range&       advance_begin( difference_type n );
        sub_range&       advance_end( difference_type n );
    };

    // stream output
    template< class Iterator, class T, class Traits >
    std::basic_ostream<T,Traits>& 
    operator<<( std::basic_ostream<T,Traits>& Os,
                const range<Iterator>& r );

    // comparison
    template< class Iterator, class Iterator2 >
    bool operator==( const range<Iterator>& l, const range<Iterator2>& r );

    template< class Iterator, class Range >
    bool operator==( const range<Iterator>& l, const Range& r );

    template< class Iterator, class Range >
    bool operator==( const Range& l, const range<Iterator>& r );

    template< class Iterator, class Iterator2 >
    bool operator!=( const range<Iterator>& l, const range<Iterator2>& r );

    template< class Iterator, class Range >
    bool operator!=( const range<Iterator>& l, const Range& r );

    template< class Iterator, class Range >
    bool operator!=( const Range& l, const range<Iterator>& r );

    template< class Iterator, class Iterator2 >
    bool operator<( const range<Iterator>& l, const range<Iterator2>& r );

    template< class Iterator, class Range >
    bool operator<( const range<Iterator>& l, const Range& r );

    template< class Iterator, class Range >
    bool operator<( const Range& l, const range<Iterator>& r );

    template< class Range, class Range2 >
    bool operator==( const sub_range<Range>& l, const sub_range<Range2>& r );

    template< class Range, class Range2 >
    bool operator!=( const sub_range<Range>& l, const sub_range<Range2>& r )

    template< class Range, class Range2 >
    bool operator<( const sub_range<Range>& l, const sub_range<Range2>& r );

    // external construction
    template< class Iterator >
    range<Iterator>
    make_range( const Iterator& begin, const Iterator& end );
    
    template< class Range >
    range<typename range_iterator<Range>::type> 
    make_range( Range&& r );

    template< class Range >
    range<typename range_iterator<Range>::type> 
    make_range( Range&& r, typename range_difference<Range>::type advance_begin,
                           typename range_difference<Range>::type advance_end );
            
    template< class CopyableRange, class Range >      
    CopyableRange copy_range( const Range& r );

    template< class ForwardRange >
    typename range_difference<ForwardRange>::type
    distance( const ForwardRange& r );
}}                                                          // namespace elib
#endif /* ELIB_RANGES_RANGE_HPP */