#ifndef ELIB_FUSE_SEQUENCE_INTRINSICS_VALUE_AT_KEY_HPP
#define ELIB_FUSE_SEQUENCE_INTRINSICS_VALUE_AT_KEY_HPP

# include <elib/fuse/sequence/intrinsics_fwd.hpp>
# include <elib/fuse/support.hpp>

namespace elib { namespace fuse
{
    namespace extension
    {
        template <class Tag>
        struct value_at_key_impl
        {
            //TODO
            template <class Seq, class N>
            struct apply;
        };
        
        template <>
        struct value_at_key_impl<sequence_facade_tag>
        {
            template <class Seq, class N>
            using apply = typename Seq::template value_at_key<Seq, N>;
        };
        
        template <> struct value_at_key_impl<elib_pair_tag>;
        template <> struct value_at_key_impl<elib_tuple_tag>;
        template <> struct value_at_key_impl<std_pair_tag>;
        template <> struct value_at_key_impl<std_tuple_tag>;
        template <> struct value_at_key_impl<std_array_tag>;
    }                                                       // namespace extension
    
    namespace result_of
    {
        template <class Seq, class N>
        struct value_at_key
          : extension::value_at_key_impl< detail::get_tag_of_t<Seq> >
            ::template apply<Seq, N>
        {};
    }                                                       // namespace result_of
}}                                                          // namespace elib
#endif /* ELIB_FUSE_SEQUENCE_INTRINSICS_VALUE_AT_KEY_HPP */