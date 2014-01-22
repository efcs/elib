#ifndef ELIB_FUSE_SEQUENCE_INTRINSICS_AT_HPP
#define ELIB_FUSE_SEQUENCE_INTRINSICS_AT_HPP

# include <elib/fuse/sequence/intrinsics_fwd.hpp>
# include <elib/fuse/support/support_fwd.hpp>
# include <elib/fuse/support/tags.hpp>
# include <elib/fuse/support/traits.hpp>
# include <elib/aux/integral_constant.hpp>
# include <elib/aux/type_traits.hpp>

namespace elib { namespace fuse
{
    namespace extension
    {
        template <class Tag>
        struct at_impl
        {
            template <class Seq, class N>
            struct apply;
        };
        
        template <>
        struct at_impl<sequence_facade_tag>
        {
            template <class Seq, class N>
            using apply = typename Seq::template at<Seq, N>;
        };
        
        template <> struct at_impl<elib_tuple_tag>;
        template <> struct at_impl<elib_pair_tag>;
        template <> struct at_impl<std_tuple_tag>;
        template <> struct at_impl<std_pair_tag>;
        template <> struct at_impl<std_array_tag>;
        
    }                                                       // namespace extension
    
    namespace result_of
    {
        template <class Seq, class N>
        struct at
          : extension::at_impl< detail::get_tag_of_t<Seq>>
            ::template apply<Seq, N>
        {};
        
        template <class Seq, int N>
        struct at_c
          : at<Seq, aux::int_<N>>
        {};
    }
    
    ////////////////////////////////////////////////////////////////////////////
    // fuse::at(seq)
    template <class N, class Seq>
    constexpr
        aux::lazy_disable_if_t<
            aux::is_const<Seq>
          , result_of::at<Seq, N>
        >
    at(Seq& seq)
    {
        return result_of::at<Seq, N>::call(seq);
    }
    
    template <class N, class Seq>
    constexpr result_of::at_t<Seq const, N>
    at(Seq const& seq)
    {
        return result_of::at<Seq const, N>::call(seq);
    }
    
    ////////////////////////////////////////////////////////////////////////////
    // fuse::at_c(seq)
    template <int N, class Seq>
    constexpr
        aux::lazy_disable_if_t<
            aux::is_const<Seq>
          , result_of::at_c<Seq, N>
        >
    at_c(Seq & seq)
    {
        return fuse::at<aux::int_<N>>(seq);
    }
    
    template <int N, class Seq>
    constexpr result_of::at_c_t<Seq const, N>
    at_c(Seq const& seq)
    {
        return fuse::at<aux::int_<N>>(seq);
    }
}}                                                          // namespace elib
#endif /* ELIB_FUSE_SEQUENCE_INTRINSICS_AT_HPP */