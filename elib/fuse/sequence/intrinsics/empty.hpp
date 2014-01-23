#ifndef ELIB_FUSE_SEQUENCE_INTRINSICS_EMPTY_HPP
# define ELIB_FUSE_SEQUENCE_INTRINSICS_EMPTY_HPP

# include <elib/fuse/sequence/intrinsics_fwd.hpp>
# include <elib/fuse/support.hpp>
# include <elib/aux.hpp>

namespace elib { namespace fuse
{
    namespace extension
    {
        template <class Tag>
        struct empty_impl
        {
            template <class Seq>
            using apply = bool_<result_of::size<Seq>::value == 0>;
        };
        
        template <>
        struct empty_impl<sequence_facade_tag>
        {
            template <class Seq>
            using apply = typename Seq::template empty<Seq>;
        };
    }                                                       // namespace extension
    
    namespace result_of
    {
        template <class Seq>
        struct empty
          : extension::empty_impl<detail::get_tag_of_t<Seq>>
            ::template apply<Seq>
        {};
    }                                                       // namespace result_of
    
    template <class Seq>
    constexpr result_of::empty_t<Seq>
    empty(Seq const&)
    {
        return {};
    }
}}                                                          // namespace elib
#endif /* ELIB_FUSE_SEQUENCE_INTRINSICS_EMPTY_HPP */