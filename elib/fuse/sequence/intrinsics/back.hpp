#ifndef ELIB_FUSE_SEQUENCE_INTRINSICS_BACK_HPP
#define ELIB_FUSE_SEQUENCE_INTRINSICS_BACK_HPP

# include <elib/fuse/sequence/intrinsics_fwd.hpp>
# include <elib/fuse/support/tags.hpp>
# include <elib/fuse/support/traits.hpp>
# include <elib/aux.hpp>

namespace elib { namespace fuse
{
    namespace extension
    {
        template <class Tag>
        struct back_impl
        {
            template <class Seq>
            struct apply;
        };
    }                                                       // namespace extension
}}                                                          // namespace elib
#endif /* ELIB_FUSE_SEQUENCE_INTRINSICS_BACK_HPP */