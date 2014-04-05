#ifndef ELIB_MP_ALGORITHM_UPPER_BOUND_HPP
#define ELIB_MP_ALGORITHM_UPPER_BOUND_HPP

# include <elib/mp/algorithm/iter_fold_if.hpp>
# include <elib/mp/algorithm/detail/deref_lambda.hpp>
# include <elib/mp/apply_wrap.hpp>
# include <elib/mp/arg.hpp>
# include <elib/mp/sequence.hpp>
# include <elib/aux.hpp>

namespace elib 
{
  namespace mp
  {
    namespace detail
    {
      
      template <class T, class Pred>
      using upper_bound_state_op =
        if_<
            apply_wrap< detail::deref_lambda<Pred>, T, _2>
          , _2
          , _1
          >;
        
        
      template <class Seq>
      using upper_bound_pred_op =
        aux::is_same< end_t<Seq>, _1 >;
      
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