#ifndef ELIB_ITERATOR_FILTER_VIEW_HPP
#define ELIB_ITERATOR_FILTER_VIEW_HPP

# include <elib/iterator/filter_iterator.hpp>
# include <elib/aux.hpp>
# include <iterator>

namespace elib { namespace iter { inline namespace v1
{
    ////////////////////////////////////////////////////////////////////////////
    template <class Sequence, class Pred>
    class filter_view
    {
    private:
        using detected_iter  =  decltype(elib::declval<Sequence>().begin());
        using detected_citer =  decltype(elib::declval<Sequence>().cbegin());
        using detected_riter =  decltype(elib::declval<Sequence>().rbegin());
        using detected_criter = decltype(elib::declval<Sequence>().crbegin());
    public:
        using iterator       = filter_iterator<detected_iter, Pred>;
        using const_iterator = filter_iterator<detected_citer, Pred>;
        using reverse_iterator = filter_iterator<detected_riter, Pred>;
        using const_reverse_iterator  = filter_iterator<detected_criter, Pred>;
        
    public:
        explicit filter_view(Sequence & s)
          : m_seq(elib::addressof(s))
        {}
        
        filter_view(Sequence & s, Pred p) 
          : m_seq(elib::addressof(s)), m_pred(elib::move(p))
        {}
        
        filter_view(filter_view const &) = default;
        filter_view(filter_view &&) = default;
        filter_view & operator=(filter_view const &) = default;
        filter_view & operator=(filter_view &&) = default;
        
        filter_view & operator=(Sequence & s)  
        { 
            m_seq = elib::addressof(s); 
            return *this;
        }
        
        iterator begin() 
        { 
            return iterator(
                m_pred
              , m_seq->begin()
              , m_seq->end()
            ); 
        }
        
        iterator end() 
        { 
            return iterator(
                m_pred
              , m_seq->end()
              , m_seq->end()
            ); 
        }
        
        const_iterator begin() const 
        { 
            return const_iterator(
                m_pred
              , m_seq->cbegin()
              , m_seq->cend()
            ); 
        }
        
        const_iterator end() const 
        { 
            return const_iterator(
                m_pred
              , m_seq->cend()
              , m_seq->cend()
            ); 
        }
        
        const_iterator cbegin() const 
        { 
            return const_iterator(
                m_pred
              , m_seq->cbegin()
              , m_seq->cend()
            ); 
        }
        
        const_iterator cend() const 
        { 
            return const_iterator(
                m_pred
              , m_seq->cend()
              , m_seq->cend()
            ); 
        }
        
    ////////////////////////////////////////////////////////////////////////
    //                          REVERSE
    ////////////////////////////////////////////////////////////////////////
        reverse_iterator rbegin() 
        { 
            return reverse_iterator(
                m_pred
              , m_seq->rbegin()
              , m_seq->rend()
            ); 
        }
        
        reverse_iterator rend() 
        { 
            return reverse_iterator(
                m_pred
              , m_seq->rend()
              , m_seq->rend()
            ); 
        }
        
        const_reverse_iterator rbegin() const 
        { 
            return const_reverse_iterator(
                m_pred
              , m_seq->crbegin()
              , m_seq->crend()
            ); 
        }
        
        const_reverse_iterator rend() const 
        { 
            return const_reverse_iterator(
                m_pred
              , m_seq->crend()
              , m_seq->crend()
            ); 
        }
        
        const_reverse_iterator crbegin() const 
        { 
            return const_reverse_iterator(
                m_pred
              , m_seq->crbegin()
              , m_seq->crend()
            ); 
        }
        
        const_reverse_iterator crend() const 
        { 
            return const_reverse_iterator(
                m_pred
              , m_seq->crend()
              , m_seq->crend()
            ); 
        }
        
        
        void swap(filter_view & other) noexcept
        {
            using std::swap;
            swap(m_seq, other.m_seq);
            swap(m_pred, other.m_pred);
        }
        
    private:
        Sequence *m_seq;
        Pred m_pred;
    };
    
    
    template <class Seq, class Pred>
    void swap(
        filter_view<Seq, Pred> & lhs
      , filter_view<Seq, Pred> & rhs
      ) noexcept
    {
        lhs.swap(rhs);
    }
    
    
    template <class Seq, class Pred>
    auto begin(filter_view<Seq, Pred> & v) 
    ELIB_AUTO_RETURN( v.begin() )
    
    template <class Seq, class Pred>
    auto end(filter_view<Seq, Pred> & v)
    ELIB_AUTO_RETURN( v.end() )
    
    template <class Seq, class Pred>
    auto begin(filter_view<Seq, Pred> const & v) 
    ELIB_AUTO_RETURN( v.begin() )
    
    template <class Seq, class Pred>
    auto end(filter_view<Seq, Pred> const & v)
    ELIB_AUTO_RETURN( v.end() )
    
    template <class Seq, class Pred>
    auto rbegin(filter_view<Seq, Pred> & v) 
    ELIB_AUTO_RETURN( v.rbegin() )
    
    template <class Seq, class Pred>
    auto rend(filter_view<Seq, Pred> & v)
    ELIB_AUTO_RETURN( v.rend() )
    
    template <class Seq, class Pred>
    auto rbegin(filter_view<Seq, Pred> const & v) 
    ELIB_AUTO_RETURN( v.rbegin() )
    
    template <class Seq, class Pred>
    auto rend(filter_view<Seq, Pred> const & v)
    ELIB_AUTO_RETURN( v.rend() )
    
    ////////////////////////////////////////////////////////////////////////////
    template <class Sequence, class Pred>
    class reverse_filter_view
    {
    private:
        using detected_iter = decltype(elib::declval<Sequence>().rbegin());
        using detected_citer = decltype(elib::declval<Sequence>().crbegin());
    public:
        using iterator       = filter_iterator<detected_iter, Pred>;
        using const_iterator = filter_iterator<detected_citer, Pred>;
        
    public:
        explicit reverse_filter_view(Sequence & s)
          : m_seq(elib::addressof(s))
        {}
        
        reverse_filter_view(Sequence & s, Pred p) 
          : m_seq(elib::addressof(s)), m_pred(p)
        {}
        
        reverse_filter_view(reverse_filter_view const &) = default;
        reverse_filter_view(reverse_filter_view &&) = default;
        reverse_filter_view & operator=(reverse_filter_view const &) = default;
        reverse_filter_view & operator=(reverse_filter_view &&) = default;
        
        reverse_filter_view & operator=(Sequence & s)  
        { 
            m_seq = elib::addressof(s); 
        }
        
        iterator begin() 
        { 
            return iterator(
                m_pred
              , m_seq->rbegin()
              , m_seq->rend()
            ); 
        }
        
        iterator end() 
        { 
            return iterator(
                m_pred
              , m_seq->rend()
              , m_seq->rend()
            ); 
        }
        
        const_iterator begin() const 
        { 
            return const_iterator(
                m_pred
              , m_seq->rbegin()
              , m_seq->rend()
            ); 
        }
        
        const_iterator end() const 
        { 
            return const_iterator(
                m_pred
              , m_seq->rend()
              , m_seq->rend()
            ); 
        }
        
        const_iterator cbegin() const 
        { 
            return const_iterator(
                m_pred
              , m_seq->rbegin()
              , m_seq->rend()
            ); 
        }
        
        const_iterator cend() const 
        { 
            return const_iterator(
                m_pred
              , m_seq->rend()
              , m_seq->rend()
            ); 
        }
        
        void swap(reverse_filter_view & other) noexcept
        {
            using std::swap;
            swap(m_seq, other.m_seq);
            swap(m_pred, other.m_pred);
        }
        
    private:
        Sequence *m_seq;
        Pred m_pred;
    };
    
    
    template <class Seq, class Pred>
    void swap(
        reverse_filter_view<Seq, Pred> & lhs
      , reverse_filter_view<Seq, Pred> & rhs
      ) noexcept
    {
        lhs.swap(rhs);
    }
    
    
    template <class Seq, class Pred>
    auto begin(reverse_filter_view<Seq, Pred> & v) 
    ELIB_AUTO_RETURN( v.begin() )
    
    template <class Seq, class Pred>
    auto end(reverse_filter_view<Seq, Pred> & v)
    ELIB_AUTO_RETURN( v.end() )
    
    template <class Seq, class Pred>
    auto begin(reverse_filter_view<Seq, Pred> const & v) 
    ELIB_AUTO_RETURN( v.begin() )
    
    template <class Seq, class Pred>
    auto end(reverse_filter_view<Seq, Pred> const & v)
    ELIB_AUTO_RETURN( v.end() )
    
}}}                                                          // namespace elib
#endif /* ELIB_ITERATOR_FILTER_VIEW_HPP */