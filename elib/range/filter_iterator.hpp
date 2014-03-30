#ifndef ELIB_RANGE_FILTER_ITERATOR_HPP
#define ELIB_RANGE_FILTER_ITERATOR_HPP

# include <elib/aux.hpp>
# include <iterator>

namespace elib { namespace range
{
    ////////////////////////////////////////////////////////////////////////////
    template<class Iterator, class Pred>
    class filter_iterator
    {
    private:
        using self = filter_iterator;
        using Traits = std::iterator_traits<Iterator>;
    public:
        using value_type = typename Traits::value_type;
        using reference = typename Traits::reference;
        using pointer = typename Traits::pointer;
        using difference_type = typename Traits::difference_type;
        using iterator_category = std::forward_iterator_tag;
        
    public:

        filter_iterator(Pred p, Iterator b, Iterator e = Iterator())
          : m_pred(p), m_pos(b), m_end(e)
        {
            satify_pred();
        }
        
        ELIB_DEFAULT_COPY_MOVE(filter_iterator);
        
        bool operator==(self const & other) const { return m_pos == other.m_pos; }
        bool operator!=(self const & other) const { return m_pos != other.m_pos; }
        
        reference operator*()  const { return *m_pos; }
        pointer   operator->() const { return m_pos.operator->(); }
        
        self & operator++() { increment(); return *this; }
        
        Iterator position() { return m_pos; }
        
    private:
        void increment() { ++m_pos; satify_pred(); }
        
        void satify_pred() 
        { 
            while (m_pos != m_end && !m_pred(*m_pos))
                ++m_pos; 
        }
        
    private:
        Pred m_pred;
        Iterator m_pos;
        Iterator m_end;
    };
}}                                                          // namespace elib
#endif /* ELIB_RANGE_FILTER_ITERATOR_HPP */