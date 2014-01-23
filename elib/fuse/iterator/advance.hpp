#ifndef ELIB_FUSE_ITERATOR_ADVANCE_HPP
#define ELIB_FUSE_ITERATOR_ADVANCE_HPP

# include <elib/fuse/iterator/iterator_fwd.hpp>
# include <elib/fuse/support/tags.hpp>
# include <elib/fuse/support/traits.hpp>
# include <elib/aux.hpp>

namespace elib { namespace fuse
{
    namespace extension
    {
        template <class Tag>
        struct advance_impl
        {
            //TODO
            template <class It, class N>
            struct apply;
        };
        
        template <>
        struct advance_impl<iterator_facade_tag>
        {
            template <class It, class N>
            using apply = typename It::template advance<It, N>;
        };
        
        template<> struct advance_impl<elib_pair_iterator_tag>;
        template<> struct advance_impl<elib_tuple_iterator_tag>;
        template<> struct advance_impl<std_pair_iterator_tag>;
        template<> struct advance_impl<std_tuple_iterator_tag>;
        template<> struct advance_impl<std_array_iterator_tag>;
    }                                                       // namespace extension
    
    namespace result_of
    {
        template <class It, class N>
        struct advance
          : extension::advance_impl< detail::get_tag_of_t<It> >
            ::template apply<It, N>
        {};
        
        template <class It, int N>
        struct advance_c
          : extension::advance_impl< detail::get_tag_of_t<It> >
            ::template apply<It, aux::int_<N>>
        {};
    }
    
    template <class N, class It>
    constexpr result_of::advance_t<It, N> const
    advance(It const& it)
    {
        return result_of::advance<It, N>::call(it);
    }
    
    template <int N, class It>
    constexpr result_of::advance_c_t<It, N> const
    advance_c(It const& it)
    {
        return result_of::advance_c<It, N>::call(it);
    }
}}                                                           // namespace elib
#endif /* ELIB_FUSE_ITERATOR_ADVANCE_HPP */