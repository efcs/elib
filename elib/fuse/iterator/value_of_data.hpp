#ifndef ELIB_FUSE_ITERATOR_VALUE_OF_DATA_HPP
# define ELIB_FUSE_ITERATOR_VALUE_OF_DATA_HPP

# include <elib/fuse/iterator/iterator_fwd.hpp>
# include <elib/fuse/support/tags.hpp>
# include <elib/fuse/support/traits.hpp>

namespace elib { namespace fuse
{
    namespace extension
    {
        template <class> struct value_of_data_impl;
        
        template <>
        struct value_of_data_impl<iterator_facade_tag>
        {
            template <class It>
            using apply = typename It::template value_of_data<It>;
        };
    }                                                       // namespace extension
    
    namespace result_of
    {
        template <class It>
        struct value_of_data
          : extension::value_of_data_impl< traits::tag_of_t<It> >
            ::template apply<It>
        {};
    }                                                       // namespace result_of
}}                                                          // namespace elib
#endif /* ELIB_FUSE_ITERATOR_VALUE_OF_DATA_HPP */