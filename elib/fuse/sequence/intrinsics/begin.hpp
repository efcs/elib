#ifndef ELIB_FUSE_SEQUENCE_INTRINSICS_BEGIN_HPP
#define ELIB_FUSE_SEQUENCE_INTRINSICS_BEGIN_HPP

# include <elib/fuse/sequence/intrinsics_fwd.hpp>
# include <elib/fuse/support/tags.hpp>
# include <elib/fuse/support/traits.hpp>
# include <elib/aux/if.hpp>
# include <elib/aux/type_traits.hpp>

namespace elib { namespace fuse
{
    namespace extension
    {
        template <class Tag>
        struct begin_impl
        {
            template <class Seq>
            struct apply;
        };
        
        template <>
        struct begin_impl<sequence_facade_tag>
        {
            template <class Seq>
            using apply = typename Seq::template begin<Seq>;
        };
        
        template <> struct begin_impl<elib_tuple_tag>;
        template <> struct begin_impl<elib_pair_tag>;
        template <> struct begin_impl<std_tuple_tag>;
        template <> struct begin_impl<std_pair_tag>;
        template <> struct begin_impl<std_array_tag>;
    }                                                       // namespace extension
    
    namespace result_of
    {
        template <class Seq>
        struct begin
          : extension::begin_impl< detail::get_tag_of_t<Seq> >
                ::template apply<Seq>
        {};
    }                                                       // namespace result_of
    
    template <class Seq>
    constexpr
        aux::lazy_enable_if_t<
            traits::is_sequence<Seq>
          , result_of::begin<Seq>
        > const
    begin(Seq & seq)
    {
        return result_of::begin<Seq>::call(seq);
    }
    
    template <class Seq>
    constexpr
        aux::lazy_enable_if_t<
            traits::is_sequence<Seq>
          , result_of::begin<Seq const>
        > const
    begin(Seq const& seq)
    {
        return result_of::begin<Seq const>::call(seq);
    }
}}                                                          // namespace elib
#endif /* ELIB_FUSE_SEQUENCE_INTRINSICS_BEGIN_HPP */