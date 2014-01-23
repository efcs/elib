#ifndef ELIB_FUSE_ITERATOR_ITERATOR_ADAPTER_HPP
#define ELIB_FUSE_ITERATOR_ITERATOR_ADAPTER_HPP

# include <elib/fuse/iterator/iterator_fwd.hpp>
# include <elib/fuse/iterator/iterator_facade.hpp>
# include <elib/aux.hpp>

namespace elib { namespace fuse
{
    template <
        class Derived, class Iterator
      , class Category /* = typename Iterator::category */
    >
    struct iterator_adapter
      : iterator_facade<Derived, Category>
    {
        using iterator_base_type = aux::remove_const_t<Iterator>;
        
        iterator_base_type iterator_base;
        
        constexpr 
        iterator_adapter(iterator_base_type const& iter_base)
          : iterator_base(iter_base)
        {}
        
        template <class It1, class It2>
        struct equal_to
          : result_of::equal_to<
              typename It1::iterator_base_type
            , typename It2::iterator_base_type
          >
        {};
        
        template <class It, class N>
        struct advance
        {
            using type = typename 
                Derived::template make<
                    result_of::advance_t<
                        typename It::iterator_base_type, N
                    >
                >::type;
                
            static constexpr type call(It const& it)
            {
                return type(fuse::advance<N>(it.iterator_base));
            }
        };
        
        template <class First, class Last>
        using distance =
            result_of::distance<
                typename First::iterator_base_type
              , typename Last::iterator_base_type
            >;
            
        template <class It>
        using value_of = result_of::value_of<typename It::iterator_base_type>;
        
        template <class It>
        struct deref
        {
            using type = result_of::deref_t< typename It::iterator_base_type >;
            
            static constexpr type call(It const& it)
            {
                return fuse::deref(it.iterator_base);
            }
        };
        
        template <class It>
        struct next
        {
            using type = typename 
                Derived::template make<
                    result_of::next_t<typename It::iterator_base_type>
                >::type;
                
            static constexpr type call(It const& it)
            {
                return type(fuse::next(it.iterator_base));
            }
        };
        
        template <class It>
        struct prior
        {
            using type = typename
                Derived::template make<
                    result_of::prior_t<typename It::iterator_base_type>
                >::type;
                
            static constexpr type call(It const& it)
            {
                return type(fuse::prior(it.iterator_base));
            }
        };
    };
}}                                                          // namespace elib
#endif /* ELIB_FUSE_ITERATOR_ITERATOR_ADAPTER_HPP */