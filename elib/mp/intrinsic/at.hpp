#ifndef ELIB_MP_INTRINSIC_AT_HPP
#define ELIB_MP_INTRINSIC_AT_HPP

# include <elib/mp/intrinsic/intrinsic_fwd.hpp>
# include <elib/mp/intrinsic/sequence_tag.hpp>
# include <elib/mp/intrinsic/begin_end.hpp>
# include <elib/mp/iterator/advance.hpp>
# include <elib/mp/types/long.hpp>

namespace elib
{
  namespace mp
  { 
  //-------------------------------- at -------------------------------------//
  
    template <class Seq, class N>
    struct at 
      : detail::at_impl< sequence_tag_t<Seq> >
          ::template apply<Seq, N>
    {};
    
    
    template <class Seq, class N>
    using at_t = typename at<Seq, N>::type;
    
  //-------------------------------- at_c -----------------------------------// 
    
    template <class Seq, long N>
    struct at_c 
      : detail::at_impl< sequence_tag_t<Seq> >
        ::template apply<Seq, long_<N>>
    {};
    
    
    template <class Seq, long N>
    using at_c_t = typename at_c<Seq, N>::type;
    
    
    namespace detail
    {
    //-------------------------------- at_impl ------------------------------// 
    
      template <class Tag>
      struct at_impl
      {
        template <class Seq, class N>
        struct apply 
          : advance< begin_t<Seq>, N >
        {};
      };
      
    }                                                       // namespace detail
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_INTRINSIC_AT_HPP */