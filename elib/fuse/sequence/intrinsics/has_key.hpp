#ifndef ELIB_FUSE_SEQUENCE_INTRINSICS_HAS_KEY_HPP
#define ELIB_FUSE_SEQUENCE_INTRINSICS_HAS_KEY_HPP

# include <elib/fuse/sequence/intrinsics_fwd.hpp>
# include <elib/fuse/iterator/equal_to.hpp>
# include <elib/fuse/support.hpp>
# include <elib/aux.hpp>

namespace elib { namespace fuse
{
    namespace extension
    {
        template <class Tag>
        struct has_key_impl
        {
            //TODO
            template <class Seq, class Key>
            struct apply;
        };
        
        template <>
        struct has_key_impl<sequence_facade_tag>
        {
            template <class Seq, class Key>
            using apply = typename Seq::template has_key<Seq, Key>;
        };
        
        template <> struct has_key_impl<elib_pair_tag>;
        template <> struct has_key_impl<elib_tuple_tag>;
        template <> struct has_key_impl<std_pair_tag>;
        template <> struct has_key_impl<std_tuple_tag>;
        template <> struct has_key_impl<std_array_tag>;
    }                                                       // namespace extension
    
    namespace result_of
    {
        template <class Seq, class Key>
        struct has_key 
          : extension::has_key_impl< detail::get_tag_of_t<Seq> >
            ::template apply<Seq, Key>
        {};
    }
    
    template <class Key, class Seq>
    constexpr result_of::has_key_t<Seq, Key>
    has_key(Seq const&)
    {
        return {};
    }
}}                                                          // namespace elib
#endif /* ELIB_FUSE_SEQUENCE_INTRINSICS_HAS_KEY_HPP */