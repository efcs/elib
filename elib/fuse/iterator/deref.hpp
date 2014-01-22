#ifndef ELIB_FUSE_ITERATOR_DEREF_HPP
#define ELIB_FUSE_ITERATOR_DEREF_HPP

# include <elib/fuse/iterator/iterator_fwd.hpp>
# include <elib/fuse/support/iterator_base.hpp>
# include <elib/fuse/support/tags.hpp>
# include <elib/fuse/support/traits.hpp>

namespace elib { namespace fuse
{
    namespace extension
    {
        template <class Tag>
        struct deref_impl
        {
            template <class It>
            struct apply;
        };
        
        template <>
        struct deref_impl<iterator_facade_tag>
        {
            template <class It>
            using apply = typename It::template deref<It>;
        };
        
        template<> struct deref_impl<elib_pair_iterator_tag>;
        template<> struct deref_impl<elib_tuple_iterator_tag>;
        template<> struct deref_impl<std_pair_iterator_tag>;
        template<> struct deref_impl<std_tuple_iterator_tag>;
        template<> struct deref_impl<std_array_iterator_tag>;
    }                                                       // namespace extension
    
    namespace result_of
    {
        template <class It>
        struct deref 
          : extension::deref_impl< detail::get_tag_of_t<It> >
            ::template apply<It>
        {};
    }                                                       // namespace result_of
    
    template <class It>
    constexpr result_of::deref_t<It>
    deref(It const& it)
    {
        return result_of::deref<It>::call(it);
    }
    
    template <class It>
    constexpr result_of::deref_t<It>
    operator*(iterator_base<It> const& it)
    {
        return fuse::deref(it.cast());
    }
}}                                                          // namespace elib
#endif /* ELIB_FUSE_ITERATOR_DEREF_HPP */