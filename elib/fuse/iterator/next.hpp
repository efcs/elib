#ifndef ELIB_FUSE_ITERATOR_NEXT_HPP
#define ELIB_FUSE_ITERATOR_NEXT_HPP

# include <elib/fuse/iterator/iterator_fwd.hpp>
# include <elib/fuse/support/tags.hpp>
# include <elib/fuse/support/traits.hpp>

namespace elib { namespace fuse
{
    namespace extension
    {
        template <class Tag>
        struct next_impl
        {
            template <class Iter>
            struct apply;
        };
        
        template <>
        struct next_impl<iterator_facade_tag>
        {
            template <class It>
            using apply = typename It::template next<It>;
        };
        
        template <> struct next_impl<elib_pair_iterator_tag>;
        template <> struct next_impl<elib_tuple_iterator_tag>;
        template <> struct next_impl<std_pair_iterator_tag>;
        template <> struct next_impl<std_tuple_iterator_tag>;
        template <> struct next_impl<std_array_iterator_tag>;
    }                                                       // namespace extension
    
    namespace result_of
    {
        template <class It>
        struct next
            : extension::next_impl< detail::get_tag_of_t<It> >
              ::template apply<It>
        {};
    }
    
    template <class It>
    constexpr result_of::next_t<It> const
    next(It const& it)
    {
        return result_of::next<It>::call(it);
    }
    
}}                                                          // namespace elib
#endif /* ELIB_FUSE_ITERATOR_NEXT_HPP */