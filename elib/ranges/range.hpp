#ifndef ELIB_RANGES_RANGE_HPP
#define ELIB_RANGES_RANGE_HPP

# include <elib/ranges/traits.hpp>
# include <elib/aux.hpp>
# include <elib/iter/algorithm.hpp>
# include <elib/iter/traits.hpp>
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
    public:
        // types
        using iterator_category = typename 
        std::iterator_traits<Iterator>::iterator_category;
        
        using value_type = typename 
        std::iterator_traits<Iterator>::value_type;
        
        using reference = typename
        std::iterator_traits<Iterator>::reference;
        
        using pointer = typename
        std::iterator_traits<Iterator>::pointer;
        
        using difference_type = typename
        std::iterator_traits<Iterator>::difference_type;
        
    public:
        // constructors
        range() = default;
        
        constexpr range(Iterator xbegin, Iterator xend)
          : m_begin(xbegin), m_end(xend)
        {}
        
        template<
            class R
          , ELIB_ENABLE_IF(not aux::is_pointer<R>::value)
          , ELIB_ENABLE_IF(is_range<R>::value)
          , ELIB_ENABLE_IF(aux::is_convertible<aux::begin_result_t<R>, Iterator>::value)
          >
        constexpr range(R && r)
          : m_begin( adl_begin(elib::forward<R>(r)) )
          , m_end  ( adl_end  (elib::forward<R>(r)) )
        {}
        
        //template<typename R>
        //constexpr range(R && r);

        ////////////////////////////////////////////////////////////////////////
        constexpr Iterator begin() const
        { return m_begin; }
        
        constexpr Iterator end() const
        { return m_end; }

        ////////////////////////////////////////////////////////////////////////
        constexpr reference front() const
        {
            return *begin();
        }
        
        ////////////////////////////////////////////////////////////////////////
        constexpr reference back() const
        {
            return *std::prev(end());
            static_assert(
                iter::is_bidirectional_tag<iterator_category>::value
              , "Must be convertible to bidirectional_iterator_tag"
            );
        }
        
        ////////////////////////////////////////////////////////////////////////
        constexpr reference operator[](difference_type index) const
        {
            return (index >= 0 ? begin() : end())[index];
            static_assert(
                iter::is_random_access_tag<iterator_category>::value
              , "Must be convertible to random_access_iterator_tag"
            );
        }

        ////////////////////////////////////////////////////////////////////////
        constexpr bool empty() const
        { return begin() == end(); }
        
        ////////////////////////////////////////////////////////////////////////
        constexpr difference_type size() const
        { return iter::size(begin(), end(), iterator_category()); }

        ////////////////////////////////////////////////////////////////////////
        void pop_front()
        {
            ELIB_ASSERT(!empty());
            ++m_begin;
        }
        
        void pop_front(difference_type n)
        {
            ELIB_ASSERT(size() <= n);
            std::advance(m_begin, n);
        }
        
        void pop_front_upto(difference_type n)
        {
            iter::advance_upto(
                m_begin
              , std::max((difference_type)0, n)
              , m_end
              , iterator_category()
            );
        }

        ////////////////////////////////////////////////////////////////////////
        void pop_back()
        {
            --m_end;
            static_assert(
               iter::is_bidirectional_tag<iterator_category>::value
              , "Must be bidirectional_iterator_tag"
            );
        }
        
        
        void pop_back(difference_type n)
        {
            std::advance(m_end, -n);
            static_assert(
                iter::is_bidirectional_tag<iterator_category>::value
              , "Must be bidirectional iterator"
            );
        }
        
        void pop_back_upto(difference_type n)
        {
            iter::advance_upto(
                m_end
              , -std::max((difference_type)0, n)
              , m_begin
              , iterator_category()
            );
            static_assert(
                iter::is_bidirectional_tag<iterator_category>::value
              , "Must be bidirectional iterator"
            );
        }

        ////////////////////////////////////////////////////////////////////////
        std::pair<range, range> split(difference_type index) const
        {
            if (index >= 0) {
                range second = *this;
                second.pop_front_upto(index);
                return std::make_pair(
                    range(begin(), second.begin())
                  , second
                );
            }
            else {
                return m_dispatch_split_neg(index, iterator_category{});
            }
            
            static_assert(
                iter::is_forward_tag<iterator_category>::value
              , " must be forward iterator"
            );
        }
        
        ////////////////////////////////////////////////////////////////////////
        range slice(difference_type start, difference_type stop) const
        {
            return m_dispatch_slice(start, stop, iterator_category{});
            static_assert(
                iter::is_forward_tag<iterator_category>::type
              , "Must be forward iterator"
            );
        }
        
        range slice(difference_type start) const
        {
            return split(start).second;
            static_assert(
                iter::is_forward_tag<iterator_category>::type
              , "Must be forward iterator"
            );
        }

    private:
        
        ////////////////////////////////////////////////////////////////////////
        std::pair<range, range> m_dispatch_split_neg(
            difference_type n
          , std::forward_iterator_tag
          ) const
        {
            ELIB_ASSERT(n <= 0);
            return split(std::max<difference_type>(0, size() + n));
        }
        
        std::pair<range, range> m_dispatch_split_neg(
            difference_type n
          , std::bidirectional_iterator_tag
          ) const
        {
            ELIB_ASSERT(n <= 0);
            range first = *this;
            first.pop_back_upto(-n);
            return std::make_pair(first, range(first.end(), end()));
        }
        
        ////////////////////////////////////////////////////////////////////////
        range m_dispatch_slice(
            difference_type start, difference_type stop
          , std::forward_iterator_tag
          ) const;
        
        range m_dispatch_slice(
            difference_type start, difference_type stop
          , std::bidirectional_iterator_tag
          ) const;
          
        range m_dispatch_slice(
            difference_type start, difference_type stop
          , std::random_access_iterator_tag
          ) const;
        
    private:
        Iterator m_begin, m_end;
    };

    ////////////////////////////////////////////////////////////////////////////
    template<class Iterator>
    constexpr range<Iterator> make_range(Iterator begin, Iterator end)
    {
        return range<Iterator>(elib::move(begin), elib::move(end));
    }
    
    ////////////////////////////////////////////////////////////////////////////
    template<
        class Range
      , ELIB_ENABLE_IF(is_range<Range>::value)
      >
    constexpr auto make_range(Range && r)
        -> range<decltype( elib::adl_begin(declval<Range>()) )>
    {
        using iter_type = decltype( elib::adl_begin(declval<Range>()) );
        return range<iter_type>( elib::forward<Range>(r) );
    }
    
    ////////////////////////////////////////////////////////////////////////////
    template<
        class Range
      , ELIB_ENABLE_IF(is_contigious_range<Range>::value)
      , ELIB_ENABLE_IF(aux::is_pointer<
          decltype(&*adl_begin(declval<Range>()))
          >::value
        )
      >
    constexpr auto make_ptr_range(Range && r) 
      -> range< decltype(&*elib::adl_begin(declval<Range>())) >
    {
        return range<decltype(&*elib::adl_begin(declval<Range>()))>(
            elib::forward<Range>(r)
          );
    }

}}                                                          // namespace elib
namespace elib
{
    using ranges::range;
    using ranges::make_range;
    using ranges::make_ptr_range;
}                                                           // namespace elib
#endif /* ELIB_RANGES_RANGE_HPP */