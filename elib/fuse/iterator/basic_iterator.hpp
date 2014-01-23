#ifndef ELIB_FUSE_ITERATOR_BASIC_ITERATOR_HPP
#define ELIB_FUSE_ITERATOR_BASIC_ITERATOR_HPP

# include <elib/fuse/iterator/iterator_fwd.hpp>
# include <elib/aux.hpp>

namespace elib { namespace fuse
{
    template <class Tag, class Category, class Seq, int Index>
    struct basic_iterator
      : iterator_facade<basic_iterator<Tag, Category, Seq, Index>, Category>
    {
        using index = int_<Index>;
        using seq_type = Seq;
        
        template <class It>
        using value_of = typename
            extension::value_of_impl<Tag>::template apply<It>;
        
        template <class It>
        using deref = typename
            extension::deref_impl<Tag>::template apply<It>;
        
        template <class It>
        using value_of_data = typename
            extension::value_of_data_impl<Tag>::template apply<It>;
        
        template <class It>
        using key_of = typename
            extension::key_of_impl<Tag>::template apply<It>;
            
        template <class It>
        using deref_data = typename
            extension::deref_data_impl<Tag>::template apply<It>;
            
        template <class It, class N>
        struct advance
        {
            using type = 
                basic_iterator<Tag, Category, Seq, Index + N::type::value>;
                
            static constexpr type call(It const& it)
            {
                return type(*it.seq, 0);
            }
        };
        
        template <class It>
        using next = advance<It, int_<1>>;
        
        template <class It>
        using prior = advance<It, int_<-1>>;
        
        //TODO
        template <class It1, class It2>
        struct equal_to;
        
        template <class OtherSeq>
        constexpr 
        basic_iterator(basic_iterator<Tag, Category, OtherSeq, Index> const& it) 
            noexcept : seq(it.seq) 
        {}
        
        constexpr basic_iterator(Seq& in_seq, int) noexcept
          : seq(&in_seq)
        {}
        
        template<class OtherSeq>
        basic_iterator& 
        operator=(basic_iterator<Tag, Category, OtherSeq, Index> const& it) noexcept
        {
            seq = it.seq;
            return *this;
        }
        
        Seq *seq;
    };
    
}}                                                          // namespace elib
#endif /* ELIB_FUSE_ITERATOR_BASIC_ITERATOR_HPP */