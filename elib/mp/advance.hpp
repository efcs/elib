#ifndef ELIB_MP_ADVANCE_HPP
#define ELIB_MP_ADVANCE_HPP

# include <elib/mp/iterator_fwd.hpp>
# include <elib/mp/next_prior.hpp>
# include <elib/mp/intrinsic/sequence_tag.hpp>
# include <elib/mp/apply_wrap.hpp>
# include <elib/mp/comparison.hpp>
# include <elib/mp/arithmetic.hpp>
# include <elib/mp/if.hpp>
# include <elib/mp/integral_constant.hpp>

namespace elib
{
  namespace mp
  {
  //-------------------------------- advance --------------------------------//
  
    template <class Iter, class N>
    struct advance 
      : detail::advance_impl< sequence_tag_t<Iter> > 
          ::template apply<Iter, N>
    {};
          
          
    template <class Iter, class N>
    using advance_t = typename advance<Iter, N>::type;
    
    
    namespace detail
    {
      
    //-------------------------------- advance_forward ----------------------// 
      template <long Offset>
      struct advance_forward
      {
        template <class Iter>
        struct apply 
          : apply_wrap<advance_forward<Offset-1>, next_t<Iter>>
        {};
      };
      
      template <>
      struct advance_forward<0>
      {
        template <class Iter>
        struct apply
        {
          using type = Iter;
        };
      };
      
    //-------------------------------- advance_back -------------------------// 

      template <long Offset>
      struct advance_back
      {
        template <class Iter>
        struct apply 
          : apply_wrap<advance_back<Offset-1>, prior_t<Iter>>
        {};
      };
      
      template <>
      struct advance_back<0>
      {
        template <class Iter>
        struct apply
        {
          using type = Iter;
        };
      };
      
    //-------------------------------- advance_impl -------------------------// 
      
      template <class Tag>
      struct advance_impl
      {
        template <class Iter, class N>
        struct apply
        {
          using is_negative = less<N, long_<0>>;
          
          using off = if_t<is_negative, negate<N>, N>;
          using op = if_t<is_negative
                        , advance_back<off::value>
                        , advance_forward<off::value> 
                      >;
                    
          using type = apply_wrap_t<op, Iter>;
        };
      };

    }                                                       // namespace detail
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_ADVANCE_HPP */