#ifndef ELIB_FUSE_SEQUENCE_INTRINSICS_FRONT_HPP
#define ELIB_FUSE_SEQUENCE_INTRINSICS_FRONT_HPP

# include <elib/fuse/sequence/intrinsics_fwd.hpp>
# include <elib/fuse/sequence/intrinsics/begin.hpp>
# include <elib/fuse/iterator/deref.hpp>

namespace elib { namespace fuse
{
    namespace result_of
    {
        template <class Seq>
        struct front : result_of::deref< result_of::begin_t<Seq> > {};
    }                                                       // namespace result_of
    
    template <class Seq>
    constexpr result_of::front_t<Seq>
    front(Seq & s)
    {
        return *fuse::begin(s);
    }
    
    template <class Seq>
    constexpr result_of::front_t<Seq const> 
    front(Seq const& s)
    {
        return *fuse::begin(s);
    }
}}                                                          // namespace elib
#endif /* ELIB_FUSE_SEQUENCE_INTRINSICS_FRONT_HPP */