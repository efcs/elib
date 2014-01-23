#ifndef ELIB_FUSE_ITERATOR_KEY_OF_HPP
#define ELIB_FUSE_ITERATOR_KEY_OF_HPP

# include <elib/fuse/iterator/iterator_fwd.hpp>
# include <elib/fuse/support/tags.hpp>
# include <elib/fuse/support/traits.hpp>

namespace elib { namespace fuse
{
    namespace extension
    {
        template <class> struct key_of_impl;
        
        template <> 
        struct key_of_impl<iterator_facade_tag>
        {
            template <class It>
            using apply = typename It::template key_of<It>;
        };
    }                                                       // namespace extension
    
    namespace result_of
    {
        template <class It>
        struct key_of 
          : extension::key_of_impl<detail::get_tag_of_t<It>>
            ::template apply<It>
        {};
    }                                                       // namespace result_of
}}                                                          // namespace elib
#endif /* ELIB_FUSE_ITERATOR_KEY_OF_HPP */