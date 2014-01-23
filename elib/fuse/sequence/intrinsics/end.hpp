#ifndef ELIB_FUSE_SEQUENCE_INTRINSICS_END_HPP
#define ELIB_FUSE_SEQUENCE_INTRINSICS_END_HPP

# include <elib/fuse/sequence/intrinsics_fwd.hpp>

namespace elib { namespace fuse
{
    namespace extension
    {
        template <class Tag>
        struct end_impl
        {
            template <class Seq>
            struct apply;
        };
        
        template <>
        struct end_impl<sequence_facade_tag>
        {
            template <class Seq>
            using apply = typename Seq::template end<Seq>;
        };
        
        template <> struct end_impl<elib_tuple_tag>;
        template <> struct end_impl<elib_pair_tag>;
        template <> struct end_impl<std_tuple_tag>;
        template <> struct end_impl<std_pair_tag>;
        template <> struct end_impl<std_array_tag>;
    }                                                       // namespace extension
    
    namespace result_of
    {
        template <class Seq>
        struct end
          : extension::end_impl< detail::get_tag_of_t<Seq> >
              ::template apply<Seq>
        {};
    }                                                       // namespace result_of
    
    template <class Seq>
    constexpr
        lazy_enable_if_t<
            traits::is_sequence<Seq>
          , result_of::end<Seq>
        > const
    end(Seq & seq)
    {
        return result_of::end<Seq>::call(seq);
    }
    
    template <class Seq>
    constexpr
        lazy_enable_if_t<
            traits::is_sequence<Seq>
          , result_of::end<Seq const>
        > const
    end(Seq const& seq)
    {
        return result_of::end<Seq const>::call(seq);
    }
}}                                                          // namespace elib
#endif /* ELIB_FUSE_SEQUENCE_INTRINSICS_END_HPP */