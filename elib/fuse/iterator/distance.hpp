#ifndef ELIB_FUSE_ITERATOR_DISTANCE_HPP
#define ELIB_FUSE_ITERATOR_DISTANCE_HPP

# include <elib/fuse/iterator/iterator_fwd.hpp>
# include <elib/fuse/support/tags.hpp>
# include <elib/fuse/support/traits.hpp>
# include <elib/aux.hpp>

namespace elib { namespace fuse
{
    namespace extension
    {
        template <class Tag>
        struct distance_impl
        {
            //TODO
            template <class First, class Last>
            struct apply;
        };
        
        template <>
        struct distance_impl<iterator_facade_tag>
        {
            template <class First, class Last>
            using apply = typename First::template distance<First, Last>;
        };
        
        template <> struct distance_impl<elib_pair_iterator_tag>;
        template <> struct distance_impl<elib_tuple_iterator_tag>;
        template <> struct distance_impl<std_pair_iterator_tag>;
        template <> struct distance_impl<std_tuple_iterator_tag>;
        template <> struct distance_impl<std_array_iterator_tag>;
    }                                                       // namespace extension
    
    namespace result_of
    {
        template <class First, class Last>
        struct distance
          : extension::distance_impl< detail::get_tag_of_t<First> >
                ::template apply<First, Last>
        {
            using distance_application = typename
                extension::distance_impl< 
                    detail::get_tag_of_t<First> >
                ::template apply<First, Last>::type;
                
            static constexpr int value = distance_application::value;
        };
        
        template <class First, class Last>
        constexpr int distance<First, Last>::value;
    }                                                       // namespace result_of
    
    template <class First, class Last>
    constexpr result_of::distance_t<First, Last>
    distance(First const& f, Last const& l)
    {
        return result_of::distance<First, Last>::call(f, l);
    }
}}                                                          // namespace elib
#endif /* ELIB_FUSE_ITERATOR_DISTANCE_HPP */