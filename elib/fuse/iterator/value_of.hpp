#ifndef ELIB_FUSE_ITERATOR_VALUE_OF_HPP
#define ELIB_FUSE_ITERATOR_VALUE_OF_HPP

# include <elib/fuse/iterator/iterator_fwd.hpp>
# include <elib/fuse/support/tags.hpp>
# include <elib/fuse/support/traits.hpp>

namespace elib { namespace fuse
{
    namespace extension
    {
        template <class Tag>
        struct value_of_impl
        {
            template <class It>
            struct apply;
        };
        
        template <>
        struct value_of_impl<iterator_facade_tag>
        {
            template <class It>
            using apply = typename It::template value_of<It>;
        };
        
        template <> struct value_of_impl<elib_pair_iterator_tag>;
        template <> struct value_of_impl<elib_tuple_iterator_tag>;
        template <> struct value_of_impl<std_pair_iterator_tag>;
        template <> struct value_of_impl<std_tuple_iterator_tag>;
        template <> struct value_of_impl<std_array_iterator_tag>;
    }                                                       // namespace extension
    
    namespace result_of
    {
        template <class It>
        struct value_of
          : extension::value_of_impl< detail::get_tag_of_t<It> >
            ::template apply<It>
        {};
    }                                                       // namespace result_of
}}                                                          // namespace elib
#endif /* ELIB_FUSE_ITERATOR_VALUE_OF_HPP */