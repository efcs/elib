#ifndef ELIB_MP_ALGORITHM_LOWER_BOUND_HPP
#define ELIB_MP_ALGORITHM_LOWER_BOUND_HPP

# include <elib/mp/algorithm/iter_foldl_if.hpp>
# include <elib/mp/algorithm/deref_wrapper.hpp>
# include <elib/mp/apply_wrap.hpp>
# include <elib/mp/arg.hpp>
# include <elib/mp/if.hpp>
# include <elib/mp/iterator.hpp>
# include <elib/mp/lambda.hpp>
# include <elib/mp/logical.hpp>
# include <elib/mp/pair.hpp>
# include <elib/mp/protect.hpp>
# include <elib/mp/sequence.hpp>
# include <elib/mp/same_type.hpp>

namespace elib 
{
  namespace mp
  {
    namespace detail
    {
      
      template <class T, class Pred>
      using lower_bound_state_op =
        if_<
            apply_wrap< first_deref_wrapper<lambda<Pred>>, _2, T>
          , _1
          , _2
          >;
        
        
      template <class Seq>
      using lower_bound_pred_op = same_type< end_t<Seq>, _1>;
    }                                                       // namespace detail
      
      
    template <
        class Seq
      , class T
      , class Pred = less<_1, _2>
      >
    struct lower_bound
      : iter_foldl_if<
            Seq
          , end_t<Seq>
          , detail::lower_bound_state_op<T, Pred>
          , detail::lower_bound_pred_op<Seq>
          >
    {};

    
    template <
        class Seq
      , class T
      , class Pred = less<_1, _2>
      >
    using lower_bound_t = typename lower_bound<Seq, T, Pred>::type;
    
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_ALGORITHM_LOWER_BOUND_HPP */