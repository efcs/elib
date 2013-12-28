#ifndef ELIB_MP_ALGORITHM_ITER_FOLDL_IF_HPP
#define ELIB_MP_ALGORITHM_ITER_FOLDL_IF_HPP

# include <elib/mp/algorithm/detail/iter_fold_if.hpp>
# include <elib/mp/algorithm/detail/iter_foldb_if.hpp>
# include <elib/mp/algorithm/detail/iter_fold_if_pred.hpp>
# include <elib/mp/algorithm/detail/reverse_begin.hpp>
# include <elib/mp/algorithm/detail/reverse_iter_op.hpp>
# include <elib/mp/algorithm/detail/identity_state_op.hpp>
# include <elib/mp/algorithm/detail/identity_iter_op.hpp>
# include <elib/mp/always.hpp>
# include <elib/mp/apply_wrap.hpp>
# include <elib/mp/if.hpp>
# include <elib/mp/iterator.hpp>
# include <elib/mp/lambda.hpp>
# include <elib/mp/logical.hpp>
# include <elib/mp/same_type.hpp>
# include <elib/mp/sequence.hpp>
# include <elib/mp/sequence_traits.hpp>

namespace elib 
{
  namespace mp
  {
  
    template <
        class Seq
      , class State
      , class F
      , class Pred = always_true
      >
    struct iter_foldl_if
      : detail::iter_fold_if<
          begin_t<Seq>
        , State
        , lambda<F>
        , lambda<next<_1>>
        , detail::iter_fold_if_pred<lambda<Pred>, end_t<Seq>>
        >
    {};
   
   
    template <
        class Seq
      , class State
      , class F
      , class Pred = always_true
      >
    using iter_foldl_if_t = typename iter_foldl_if<Seq, State, F, Pred>::type;
    
    
    namespace detail
    {
      
      template <bool IsForward, bool IsBidir>
      struct select_iter_foldr_if_impl;
      
      template <>
      struct select_iter_foldr_if_impl<true, true>
      {
        template <
            class Seq
          , class State
          , class StateOp
          , class Pred = always_true
          >
        using apply =
          detail::iter_fold_if<
              detail::reverse_begin_t<Seq>
            , State
            , lambda<StateOp>
            , detail::reverse_iter_op<begin_t<Seq>, end_t<Seq>>
            , detail::iter_fold_if_pred<lambda<Pred>, end_t<Seq>>
          >;
      };
      
      template <>
      struct select_iter_foldr_if_impl<true, false>
      {
        template <
            class Seq
          , class State
          , class StateOp
          , class Pred = always_true
          >
        using apply =
          detail::forward_iter_foldb_if<
              begin_t<Seq>
            , State
            , identity_state_op
            , lambda< next<_1> >
            , lambda< not_<same_type<end_t<Seq>, _2>> >
            , lambda< StateOp >
            , lambda<Pred>
          >;
      };
    
    }                                                       // namespace detail
    
    
    
    
    template <
        class Seq
      , class State
      , class StateOp
      , class Pred = always_true
      >
    using iter_foldr_if_t = typename 
      detail::select_iter_foldr_if_impl<
          is_forward_sequence<Seq>::value
        , is_bidirectional_sequence<Seq>::value
        >::template
      apply<
        Seq, State
      , StateOp, Pred
      >::type;
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_ALGORITHM_ITER_FOLD_IF_HPP */