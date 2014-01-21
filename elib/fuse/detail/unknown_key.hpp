#ifndef ELIB_FUSE_DETAIL_UNKNOWN_KEY_HPP
#define ELIB_FUSE_DETAIL_UNKNOWN_KEY_HPP

namespace elib { namespace fuse
{
    namespace detail
    {
        template <int I>
        struct unknown_key
        {
            static constexpr int value = I;
        };
        
        template <int I>
        constexpr int unknown_key<I>::value;
    }                                                       // namespace detail
}}                                                          // namespace elib
#endif /* ELIB_FUSE_DETAIL_UNKNOWN_KEY_HPP */