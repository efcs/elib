#ifndef ELIB_ITER_ITERATOR_FACADE_HPP
#define ELIB_ITER_ITERATOR_FACADE_HPP

# include <elib/iter/iterator_traits.hpp>
# include <elib/aux.hpp>
# include <iterator>
# include <cstddef>

namespace elib { namespace iter
{
    template<
        class Derived
      , class Value
      , class Catagory
      , class Reference = Value &
      , class Difference = std::ptrdiff_t
    >
    class iterator_facade;
    
# define ELIB_ITER_ITERATOR_ACCESS_OP(Prefix, Return, Op) \
    template <                                             \
        class D1, class V1, class C1, class R1, class Di1  \
      , class D2, class V2, class C2, class R2, class Di2  \
    >                                                      \
    Prefix Return operator Op (                            \
        iterator_facade<D1, V1, C1, R1, Di1> const & lhs   \
      , iterator_facade<D2, V2, C2, R2, Di2> const & rhs   \
    )
# 
    class iterator_access
    {
    private:
        template <class, class, class, class, class>
        friend class iterator_facade;
        
        ELIB_ITER_ITERATOR_ACCESS_OP(friend, bool, == );
        ELIB_ITER_ITERATOR_ACCESS_OP(friend, bool, != );
        ELIB_ITER_ITERATOR_ACCESS_OP(friend, bool, <  );
        ELIB_ITER_ITERATOR_ACCESS_OP(friend, bool, <= );
        ELIB_ITER_ITERATOR_ACCESS_OP(friend, bool, >  );
        ELIB_ITER_ITERATOR_ACCESS_OP(friend, bool, >= );
        
    private:
        template <class Facade>
        static auto dereference(Facade const & f)
        ELIB_AUTO_RETURN_NOEXCEPT( f.dereference() )
        
        template <class Facade>
        static auto increment(Facade & f)
        ELIB_AUTO_RETURN_NOEXCEPT( f.increment() )
        
        template <class Facade>
        static auto decrement(Facade & f)
        ELIB_AUTO_RETURN_NOEXCEPT( f.decrement() )
        
        template <class Facade1, class Facade2>
        static auto equal(Facade1 const & f1, Facade2 const & f2, elib::true_)
        ELIB_AUTO_RETURN_NOEXCEPT( f1.equal(f2) )
        
        template <class Facade1, class Facade2>
        static auto equal(Facade1 const & f1, Facade2 const & f2, elib::false_)
        ELIB_AUTO_RETURN_NOEXCEPT( f2.equal(f1) )
        
        template <class Facade, class Diff>
        static auto advance(Facade & f, Diff && d)
        ELIB_AUTO_RETURN_NOEXCEPT( f.advance(static_cast<Diff &&>(d)) )
        
        template <class Facade1, class Facade2>
        static auto distance_from(
            Facade1 const & f1, Facade2 const & f2
          , elib::true_
        )
        ELIB_AUTO_RETURN_NOEXCEPT( -f1.distance_to(f2) )
        
        template <class Facade1, class Facade2>
        static auto distance_from(
            Facade1 const & f1, Facade2 const & f2
          , elib::false_
        )
        ELIB_AUTO_RETURN_NOEXCEPT( f2.distance_to(f1) )
        
        template <class Derived, class V, class C, class R, class D>
        static auto derived(iterator_facade<Derived, V, C, R, D> & f) 
        ELIB_AUTO_RETURN_NOEXCEPT( static_cast<Derived &>(f) )
        
        template <class Derived, class V, class C, class R, class D>
        static auto derived(iterator_facade<Derived, V, C, R, D> const & f) 
        ELIB_AUTO_RETURN_NOEXCEPT( static_cast<Derived const &>(f) )
        
    private:
        iterator_access() = delete;
    };
# undef ELIB_ITER_ITERATOR_ACCESS_OP


    template<
        class Derived
      , class ValueType
      , class Catagory
      , class Reference
      , class Difference
    >
    class iterator_facade
    {
    public:
        using iterator_catagory = Catagory;
        using value_type = aux::remove_const_t<ValueType>;
        using reference = Reference;
        using pointer = value_type *;
        using difference_type = Difference;
        
    public:
        auto operator*() const 
        ELIB_AUTO_RETURN(
            iterator_access::dereference( this->derived() )
        )
        
        auto operator->() const
        ELIB_AUTO_RETURN(elib::addressof(
            iterator_access::dereference( this->derived() )
        ))
        
        auto operator[](difference_type d) const
        ELIB_AUTO_RETURN( *(this->derived() + d) )
        
        Derived & operator++()
        {
            iterator_access::increment( derived() );
            return derived();
        }
        
        Derived operator++(int)
        {
            Derived cp(derived());
            iterator_access::increment( derived() );
            return cp;
        }
        
        Derived & operator--()
        {
            iterator_access::decrement( derived() );
            return derived();
        }
        
        Derived operator--(int)
        {
            Derived cp( derived() );
            iterator_access::decrement( derived() );
            return cp;
        }
        
        Derived & operator+=(difference_type n)
        {
            iterator_access::advance(derived(), n);
            return derived();
        }
        
        Derived & operator-=(difference_type n)
        {
            iterator_access::advance(derived(), -n);
            return derived();
        }
        
        Derived operator-(difference_type n) const
        {
            Derived cp( derived() );
            cp -= n;
            return cp;
        }
        
    private:
        Derived & derived() noexcept 
        { return static_cast<Derived &>(*this); }
        
        Derived const & derived() const noexcept
        { return static_cast<Derived const &>(*this); }
    };
    
    ////////////////////////////////////////////////////////////////////////////
    template <                                             
        class D1, class V1, class C1, class R1, class Di1  
      , class D2, class V2, class C2, class R2, class Di2 
      , ELIB_ENABLE_IF( is_interoperable<D1, D2>::value )
    >                                                      
    bool operator==(                            
        iterator_facade<D1, V1, C1, R1, Di1> const & lhs   
      , iterator_facade<D2, V2, C2, R2, Di2> const & rhs   
    )
    {
        return 
        iterator_access::equal(
            static_cast<D1 const &>(lhs), static_cast<D2 const &>(rhs)
          , typename aux::is_convertible<D2, D1>::type{}
        );
    }
    
    ////////////////////////////////////////////////////////////////////////////
    template <                                             
        class D1, class V1, class C1, class R1, class Di1  
      , class D2, class V2, class C2, class R2, class Di2 
      , ELIB_ENABLE_IF( is_interoperable<D1, D2>::value )
    >                                                      
    bool operator!=(                            
        iterator_facade<D1, V1, C1, R1, Di1> const & lhs   
      , iterator_facade<D2, V2, C2, R2, Di2> const & rhs   
    )
    {
        return 
        not iterator_access::equal(
            static_cast<D1 const &>(lhs), static_cast<D2 const &>(rhs)
          , typename aux::is_convertible<D2, D1>::type{}
        );
    }
    
    ////////////////////////////////////////////////////////////////////////////
    template <                                             
        class D1, class V1, class C1, class R1, class Di1  
      , class D2, class V2, class C2, class R2, class Di2 
      , ELIB_ENABLE_IF( is_interoperable<D1, D2>::value )
    >                                                      
    bool operator<(                            
        iterator_facade<D1, V1, C1, R1, Di1> const & lhs   
      , iterator_facade<D2, V2, C2, R2, Di2> const & rhs   
    )
    {
        return 
        iterator_access::distance_from(
            static_cast<D1 const &>(lhs), static_cast<D2 const &>(rhs)
          , typename aux::is_convertible<D2, D1>::type{}
        ) < 0;
    }
    
    ////////////////////////////////////////////////////////////////////////////
    template <                                             
        class D1, class V1, class C1, class R1, class Di1  
      , class D2, class V2, class C2, class R2, class Di2
      , ELIB_ENABLE_IF( is_interoperable<D1, D2>::value )
    >                                                      
    bool operator<=(                            
        iterator_facade<D1, V1, C1, R1, Di1> const & lhs   
      , iterator_facade<D2, V2, C2, R2, Di2> const & rhs 
    )
    {
        return 
        iterator_access::distance_from(
            static_cast<D1 const &>(lhs), static_cast<D2 const &>(rhs)
          , typename aux::is_convertible<D2, D1>::type{}
        ) <= 0;
    }
    
    ////////////////////////////////////////////////////////////////////////////
    template <                                             
        class D1, class V1, class C1, class R1, class Di1  
      , class D2, class V2, class C2, class R2, class Di2 
      , ELIB_ENABLE_IF( is_interoperable<D1, D2>::value )
    >                                                      
    bool operator>(                            
        iterator_facade<D1, V1, C1, R1, Di1> const & lhs   
      , iterator_facade<D2, V2, C2, R2, Di2> const & rhs   
    )
    {
        return 
        iterator_access::distance_from(
            static_cast<D1 const &>(lhs), static_cast<D2 const &>(rhs)
          , typename aux::is_convertible<D2, D1>::type{}
        ) > 0;
    }
    
    ////////////////////////////////////////////////////////////////////////////
    template <                                             
        class D1, class V1, class C1, class R1, class Di1  
      , class D2, class V2, class C2, class R2, class Di2 
      , ELIB_ENABLE_IF( is_interoperable<D1, D2>::value )
    >                                                      
    bool operator>=(                            
        iterator_facade<D1, V1, C1, R1, Di1> const & lhs   
      , iterator_facade<D2, V2, C2, R2, Di2> const & rhs   
    )
    {
        return 
        iterator_access::distance_from(
            static_cast<D1 const &>(lhs), static_cast<D2 const &>(rhs)
          , typename aux::is_convertible<D2, D1>::type{}
        ) >= 0;
    }
}}                                                          // namespace elib
#endif /* ELIB_ITER_ITERATOR_FACADE_HPP */