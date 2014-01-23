#ifndef ELIB_FUSE_SEQUENCE_INTRINSICS_SIZE_HPP
#define ELIB_FUSE_SEQUENCE_INTRINSICS_SIZE_HPP

# include <elib/fuse/sequence/intrinsics_fwd.hpp>
# include <elib/fuse/support.hpp>
# include <elib/aux.hpp>

namespace elib { namespace fuse
{
    namespace extension
    {
        template <class Tag>
        struct size_impl
        {
            //TODO
            template <class Seq>
            struct apply;
        };
        
        template <>
        struct size_impl<sequence_facade_tag>
        {
            template <class Seq>
            using apply = typename Seq::template size<Seq>;
        };
        
        template <> struct size_impl<elib_pair_tag>;
        template <> struct size_impl<elib_tuple_tag>;
        template <> struct size_impl<std_pair_tag>;
        template <> struct size_impl<std_tuple_tag>;
        template <> struct size_impl<std_array_tag>;
    }                                                       // namespace extension
    
    namespace result_of
    {
        template <class Seq>
        struct size
          : extension::size_impl<detail::get_tag_of_t<Seq>>
            ::template apply<Seq>
        {
            using size_application = typename
                extension::size_impl<detail::get_tag_of_t<Seq>>
                  ::template apply<Seq>::type;
                  
            static constexpr int value = size_application::value;
        };
        
        template <class Seq>
        constexpr int size<Seq>::value;
    }                                                       // namespace result_of
    
    template <class Seq>
    constexpr result_of::size_t<Seq>
    size(Seq const&)
    {
        return {};
    }
}}                                                          // namespace elib
#endif /* ELIB_FUSE_SEQUENCE_INTRINSICS_SIZE_HPP */