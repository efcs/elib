#ifndef ELIB_MP_ALGORITHM_MAX_ELEMENT_HPP
#define ELIB_MP_ALGORITHM_MAX_ELEMENT_HPP

# include <elib/mp/algorithm/iter_fold.hpp>
# include <elib/mp/algorithm/detail/deref_lambda.hpp>
# include <elib/mp/arg.hpp>
# include <elib/mp/comparison.hpp>
# include <elib/mp/if.hpp>
# include <elib/mp/sequence.hpp>

namespace elib 
{
  namespace mp
  {
    
    template <
        class Seq
      , class Pred = greater<_1, _2>
      >
    struct max_element 
      : iter_foldl<
          begin_t<Seq>
        , begin_t<Seq>
        , if_< detail::binary_deref_lambda<Pred>
            , _1
            , _2
          >
        >
    {};
    
    
    template < class Seq, class Pred = greater<_1, _2> >
    using max_element_t = typename max_element<Seq, Pred>::type;
    
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_ALGORITHM_MAX_ELEMENT_HPP */