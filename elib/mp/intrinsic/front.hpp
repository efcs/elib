#ifndef ELIB_MP_INTRINSIC_FRONT_HPP
#define ELIB_MP_INTRINSIC_FRONT_HPP

# include <elib/mp/intrinsic/intrinsic_fwd.hpp>
# include <elib/mp/intrinsic/sequence_tag.hpp>
# include <elib/mp/intrinsic/begin_end.hpp>
# include <elib/mp/iterator/deref.hpp>

namespace elib
{
  namespace mp
  {
  //-------------------------------- front ----------------------------------// 
    
    template <class Seq>
    struct front
      : detail::front_impl<sequence_tag_t<Seq>>
          ::template apply<Seq>
    {};
    
    
    template <class Seq>
    using front_t = typename front<Seq>::type;
    
    
    namespace detail
    {
    //-------------------------------- front_impl ---------------------------// 
      
      // Default impl
      template <class Tag>
      struct front_impl
      {
        
        template <class Seq>
        struct apply
        { using type = deref_t< begin_t<Seq> >; };
        
      };

    }                                                       // namespace detail
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_INTRINSIC_FRONT_HPP */