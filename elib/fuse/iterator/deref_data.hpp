#ifndef ELIB_FUSE_ITERATOR_DEREF_DATA_HPP
#define ELIB_FUSE_ITERATOR_DEREF_DATA_HPP

# include <elib/fuse/iterator/iterator_fwd.hpp>
# include <elib/fuse/support/tags.hpp>
# include <elib/fuse/support/traits.hpp>

namespace elib { namespace fuse
{
    namespace extension
    {
        template <class>
        struct deref_data_impl;
        
        template <>
        struct deref_data_impl
        {
            template <class It>
            using apply = typename It::template deref_data<It>;
        };
    }                                                       // namespace extension
    
    namespace result_of
    {
        template <class It>
        struct deref_data
          : extension::deref_data_impl< traits::tag_of_t<It> >
            ::template apply<It>
        {};
    }                                                       // namespace result_of
    
    template <class It>
    constexpr result_of::deref_data_t<It>
    deref_data(It const& it)
    {
        return result_of::deref_data<It>::call(it);
    }
}}                                                          // namespace elib
#endif /* ELIB_FUSE_ITERATOR_DEREF_DATA_HPP */