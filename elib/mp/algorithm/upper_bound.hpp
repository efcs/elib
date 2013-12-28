#ifndef ELIB_MP_ALGORITHM_UPPER_BOUND_HPP
#define ELIB_MP_ALGORITHM_UPPER_BOUND_HPP

# include <elib/mp/algorithm/iter_fold_if.hpp>
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
      using upper_bound_state_op =
        if_<
            apply_wrap< deref_wrapper<lambda<Pred>>, T, _2>
          , _2
          , _1
          >;
        
      template <class Seq>
      using upper_bound_pred_op =
        same_type< end_t<Seq>, _1 >;
      
    }                                                       // namespace detail
    
    template <
        class Seq
      , class T
      , class Pred = less<_1, _2>
      >
    struct upper_bound
      : iter_foldl_if<
          Seq
        , end_t<Seq>
        , detail::upper_bound_state_op<T, Pred>
        , detail::upper_bound_pred_op<Seq>
        >
    {};
    
    
    template<
        class Seq
      , class T
      , class Pred = less<_1, _2>
      >
    using upper_bound_t = typename upper_bound<Seq, T, Pred>::type;
    
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_ALGORITHM_UPPER_BOUND_HPP */