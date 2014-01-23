#ifndef ELIB_FUSE_ITERATOR_PRIOR_HPP
# define ELIB_FUSE_ITERATOR_PRIOR_HPP

# include <elib/fuse/iterator/iterator_fwd.hpp>
# include <elib/fuse/support/tags.hpp>
# include <elib/fuse/support/traits.hpp>

namespace elib { namespace fuse
{
    namespace extension
    {
        template <class Tag>
        struct prior_impl
        {
            template <class It>
            struct apply;
        };
        
        template <>
        struct prior_impl<iterator_facade_tag>
        {
            template <class It>
            using apply = typename It::template prior<It>;
        };
        
        template <> struct prior_impl<elib_pair_iterator_tag>;
        template <> struct prior_impl<elib_tuple_iterator_tag>;
        template <> struct prior_impl<std_pair_iterator_tag>;
        template <> struct prior_impl<std_tuple_iterator_tag>;
        template <> struct prior_impl<std_array_iterator_tag>;
    }                                                       // namespace extension
    
    namespace result_of
    {
        template <class It>
        struct prior
          : extension::prior_impl< detail::get_tag_of_t<It> >
            ::template apply<It>
        {};
    }                                                       // namespace result_of
    
    template <class It>
    constexpr result_of::prior_t<It> const
    prior(It const& it)
    {
        return result_of::prior<It>::call(it);
    }
}}                                                          // namespace elib
#endif /* ELIB_FUSE_ITERATOR_PRIOR_HPP */