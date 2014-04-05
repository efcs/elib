#ifndef ELIB_RANGES_TRAITS_HPP
#define ELIB_RANGES_TRAITS_HPP

# include <iterator>

namespace elib { namespace ranges
{
    ////////////////////////////////////////////////////////////////////////////
    template<class Range>
    struct range_iterator
    {
        using std::begin;
        using type = decltype( begin(* ((Range*)nullptr) ) );
    };
    
    
    template <class Range>
    using range_iterator_t = typename range_iterator<Range>::type;

    ////////////////////////////////////////////////////////////////////////////
    template< class BidirectionalRange >
    struct range_reverse_iterator
    {
        using type = std::reverse_iterator< range_iterator_t<BidirectionalRange> >;
    };
    
    
    template <class BidirectionalRange>
    using range_reverse_iterator_t = typename range_reverse_iterator<BidirectionalRange>::type;

    ////////////////////////////////////////////////////////////////////////////
    template< class Range >
    struct range_value
    {
        using type = typename std::iterator_traits<range_iterator_t<Range>>::value_type;
    };
    
    
    template <class Range>
    using range_value_t = typename range_value<Range>::type;

    ////////////////////////////////////////////////////////////////////////////
    template< class Range >
    struct range_reference
    {
        using type = typename std::iterator_traits<range_iterator_t<Range>>::reference;
    };
    
    
    template <class Range>
    using range_reference_t = typename range_reference<Range>::type;

    ////////////////////////////////////////////////////////////////////////////
    template< class Range >
    struct range_pointer;
    {
        using type = typename std::iterator_traits<range_iterator_t<Range>>::pointer;
    };
    
    
    template <class Range>
    using range_pointer_t = typename range_pointer<Range>::type;
    
    ////////////////////////////////////////////////////////////////////////////
    template< class Range >
    struct range_difference
    {
        using type = typename std::iterator_traits<range_iterator_t<Range>>::difference_type;
    };

    
    template <class Range>
    using range_difference_t = typename range_difference<Range>::type;
    
    ////////////////////////////////////////////////////////////////////////////
    template< class Range >
    struct range_category
    {
        using type = typename std::iterator_traits<range_iterator_t<Range>>::iterator_category;
    };
    
    
    template <class Range>
    using range_category_t = typename range_category<Range>::type;
}}                                                          // namespace elib
namespace elib
{
    using ranges::range_iterator;
    using ranges::range_iterator_t;
    using ranges::range_reverse_iterator;
    using ranges::range_reverse_iterator_t;
    using ranges::range_value;
    using ranges::range_value_t;
    using ranges::range_reference;
    using ranges::range_reference_t;
    using ranges::range_pointer;
    using ranges::range_pointer_t;
    using ranges::range_difference;
    using ranges::range_difference_t;
    using ranges::range_category;
    using ranges::range_category_t;
}                                                           // namespace elib
#endif /* ELIB_RANGES_TRAITS_HPP */