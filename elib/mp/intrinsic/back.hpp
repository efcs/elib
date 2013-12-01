#ifndef ELIB_MP_INTRINSIC_BACK_HPP
#define ELIB_MP_INTRINSIC_BACK_HPP

# include <elib/mp/intrinsic/intrinsic_fwd.hpp>
# include <elib/mp/intrinsic/sequence_tag.hpp>
# include <elib/mp/intrinsic/begin_end.hpp>
# include <elib/mp/next_prior.hpp>
# include <elib/mp/deref.hpp>

namespace elib
{
  namespace mp
  {
  //-------------------------------- back -----------------------------------// 
    
    template <class Seq>
    struct back
      : detail::back_impl<sequence_tag_t<Seq>> 
          ::template apply<Seq>
    {};
     
     
    template <class Seq>
    using back_t = typename back<Seq>::type;
    
    
    namespace detail
    {
     
    //-------------------------------- back_impl ----------------------------// 
      template <class Tag>
      struct back_impl
      {
        template <class Seq>
        struct apply
        {
          using last_ = prior_t< end_t<Seq> >;
          using type = deref_t<last_>;
        };                                                  
      };                                                    
      
    }                                                       // namespace detail
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_INTRINSIC_BACK_HPP */