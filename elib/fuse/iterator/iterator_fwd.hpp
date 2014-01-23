#ifndef ELIB_FUSE_ITERATOR_ITERATOR_FWD_HPP
#define ELIB_FUSE_ITERATOR_ITERATOR_FWD_HPP

# include <elib/fuse/support/support_fwd.hpp>
# include <elib/fuse/support/traits.hpp>
# include <elib/aux.hpp>

namespace elib { namespace fuse
{
    template <class Tag, class Category, class Seq, int Index>
    struct basic_iterator;
    
    template <
        class Derived, class Iterator
      , class Category = typename Iterator::category
    >
    struct iterator_adapter;
    
    template <class Derived, class Category>
    struct iterator_facade;
    
    namespace iterator_operators
    {
        template <class It1, class It2>
        constexpr bool operator==(It1 const&, It2 const&);
        
        template <class It1, class It2>
        constexpr bool operator!=(It1 const&, It2 const&);
    }                                           // namespace iterator_operators
    
    using iterator_operators::operator==;
    using iterator_operators::operator!=;
    
    namespace extension
    {
        template <class Tag> struct advance_impl;
        template <class Tag> struct deref_impl;
        template <class Tag> struct deref_data_impl;
        template <class Tag> struct distance_impl;
        template <class Tag> struct equal_to_impl;
        template <class Tag> struct key_of_impl;
        template <class Tag> struct next_impl;
        template <class Tag> struct prior_impl;
        template <class Tag> struct value_of_impl;
        template <class Tag> struct value_of_data_impl;
    }                                                       // namespace extension
    
    namespace result_of
    {
        template <class Iter, class N> 
        struct advance;
       
        template <class Iter, class N>
        using advance_t = typename advance<Iter, N>::type;
       
        template <class Iter, int N>
        struct advance_c;
       
        template <class Iter, int N>
        using advance_c_t = typename advance_c<Iter, N>::type;
       
        template <class Iter>
        struct deref;
       
        template <class Iter>
        using deref_t = typename deref<Iter>::type;
       
        template <class Tag> 
        struct deref_data;
       
        template <class Tag> 
        using deref_data_t = typename deref_data<Tag>::type;
       
        template <class First, class Last>
        struct distance;
        
        template <class First, class Last>
        using distance_t = typename distance<First, Last>::type;
        
        template <class T, class U>
        struct equal_to;
        
        template <class T, class U>
        using equal_to_t = typename equal_to<T, U>::type;
        
        template <class It>
        struct key_of;
        
        template <class It>
        using key_of_t = typename key_of<It>::type;
        
        template <class It>
        struct next;
        
        template <class It>
        using next_t = typename next<It>::type;
        
        template <class It>
        struct prior;
        
        template <class It>
        using prior_t = typename prior<It>::type;
        
        template <class It>
        struct value_of;
        
        template <class It>
        using value_of_t = typename value_of<It>::type;
        
        template <class It>
        struct value_of_data;
        
        template <class It>
        using value_of_data_t = typename value_of_data<It>::type;
    }                                                       // namespace result_of
    
    template <class N, class Iter>
    constexpr result_of::advance_t<Iter, N> const
    advance(Iter const& i);
    
    template <int N, class Iter>
    constexpr result_of::advance_c_t<Iter, N> const
    advance_c(Iter const& i);
    
    template <class Iter>
    constexpr result_of::deref_t<Iter>
    deref(Iter const& i);
    
    template <class Iter>
    constexpr result_of::deref_t<Iter>
    operator*(iterator_base<Iter> const& i);
    
    template <class It>
    constexpr result_of::deref_data_t<It>
    deref_data(It const& it);
    
    template <class First, class Last>
    constexpr result_of::distance_t<First, Last>
    distance(First const& f, Last const& l);
    
    template <class It>
    constexpr result_of::next_t<It> const
    next(It const& it);
    
    template <class It>
    constexpr result_of::prior_t<It> const
    prior(It const& it);
}}                                                          // namespace elib
#endif /* ELIB_FUSE_ITERATOR_ITERATOR_FWD_HPP */