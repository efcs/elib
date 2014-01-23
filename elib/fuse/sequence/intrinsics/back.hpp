#ifndef ELIB_FUSE_SEQUENCE_INTRINSICS_BACK_HPP
#define ELIB_FUSE_SEQUENCE_INTRINSICS_BACK_HPP

# include <elib/fuse/sequence/intrinsics_fwd.hpp>
# include <elib/fuse/sequence/intrinsics/end.hpp>
# include <elib/fuse/iterator/deref.hpp>
# include <elib/fuse/iterator/prior.hpp>

namespace elib { namespace fuse
{
    namespace result_of
    {
        template <class Seq>
        struct back 
          : result_of::deref< 
              result_of::prior_t< result_of::end_t<Seq> >
            >
        {};
    }                                                       // namespace result_of
    
    template <class Seq>
    constexpr result_of::back_t<Seq>
    back(Seq & s)
    {
        return *fuse::prior(fuse::end(s));
    }
    
    template <class Seq>
    constexpr result_of::back_t<Seq const>
    back(Seq const& s)
    {
        return *fuse::prior(fuse::end(s));
    }
    
}}                                                          // namespace elib
#endif /* ELIB_FUSE_SEQUENCE_INTRINSICS_BACK_HPP */