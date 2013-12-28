#ifndef ELIB_MP_ALGORITHM_DETAIL_ITER_FOLDB_IF_HPP
#define ELIB_MP_ALGORITHM_DETAIL_ITER_FOLDB_IF_HPP

# include <elib/mp/algorithm/detail/identity_iter_op.hpp>
# include <elib/mp/apply_wrap.hpp>
# include <elib/mp/if.hpp>
# include <elib/mp/logical.hpp>
# include <elib/mp/detail/integral_constant.hpp>

namespace elib 
{
  namespace mp
  {
    namespace detail
    {
      namespace iter_foldb_if_detail
      {
       
        template <class Iter, class State>
        struct null_step
        {
          using iterator = Iter;
          using state = State;
        };
       
       
        template <bool TakeStep>
        struct iter_take_step_impl;
        
        
        template<>
        struct iter_take_step_impl<true>
        {
          template<
              class Iter
            , class State
            , class StateOp
            , class IterOp
            >
          struct apply
          {
            using iterator = apply_wrap_t<IterOp, Iter>;
            using state = apply_wrap_t<StateOp, State, Iter>;
          };
        };
        
        
        template <>
        struct iter_take_step_impl<false>
        {
          template <
              class Iter
            , class State
            , class StateOp
            , class IterOp
            >
          struct apply
          {
            using iterator = Iter;
            using state = State;
          };
        };
        

        template <class Iter, class State, class StateOp, class IterOp, class Pred>
        using take_step = typename
          iter_take_step_impl<
              apply_wrap_t<Pred, State, Iter>::value
            >::template
            apply<
                Iter
              , State
              , StateOp
              , IterOp
              >;
              
              
        template <class Step, class StateOp, class IterOp, class Pred>
        using take_next_step = 
          take_step<
              typename Step::iterator
            , typename Step::state
            , StateOp
            , IterOp
            , Pred
            >;
        
        
        template <
            class FStep,  class FPred 
          , class BStep,  class StateOp
          , class IterOp, class BPred
        >
        using forward_iter_take_backward_step = typename 
          iter_take_step_impl<
            and_<
                apply_wrap<
                    FPred
                  , typename FStep::state
                  , typename FStep::iterator
                  >
              , apply_wrap<
                    BPred
                  , typename BStep::state
                  , typename FStep::iterator
                  >
              >::value
            >::template
            apply<
                typename FStep::iterator
              , typename BStep::state
              , StateOp
              , IterOp
            >;
        
        
        template <
            class FStep,  class FPred 
          , class BStep,  class StateOp
          , class IterOp, class BPred
        >
        using bidirectional_iter_take_backward_step = typename
          iter_take_step_impl<
              and_<
                apply_wrap<
                    FPred
                  , typename FStep::state
                  , typename FStep::iterator
                  >
              , apply_wrap<
                    BPred
                  , typename BStep::state
                  , typename BStep::iterator
                  >
              >::value
            >::template
            apply<
                typename BStep::iterator
              , typename BStep::state
              , StateOp
              , IterOp
            >;
        

        template <
            class Iter, class State
          , class FOp, class FIterOp, class FPred
          , class BOp, class BIterOp, class BPred
          , template <class ...> class BackwardStep
          >
        struct iter_foldb_if_impl
        {
          using fstep0 = null_step<Iter, State>;
          using fstep1 = take_next_step<fstep0, FOp, FIterOp, FPred>;
          using fstep2 = take_next_step<fstep1, FOp, FIterOp, FPred>;
          using fstep3 = take_next_step<fstep2, FOp, FIterOp, FPred>;
          using fstep4 = take_next_step<fstep3, FOp, FIterOp, FPred>;
          using fstep5 = take_next_step<fstep4, FOp, FIterOp, FPred>;
          
          using rest_ = 
            if_t<
                apply_wrap_t<
                    FPred
                  , typename fstep4::state
                  , typename fstep4::iterator
                  >
              , iter_foldb_if_impl<
                    typename fstep5::iterator
                  , typename fstep5::state
                  , FOp, FIterOp, FPred
                  , BOp, BIterOp, BPred
                  , BackwardStep
                  >
              , fstep4
            >;
          
   
          using bstep4 = BackwardStep<fstep4, FPred, rest_,  BOp, BIterOp, BPred>;
          using bstep3 = BackwardStep<fstep3, FPred, bstep4, BOp, BIterOp, BPred>;
          using bstep2 = BackwardStep<fstep2, FPred, bstep3, BOp, BIterOp, BPred>;
          using bstep1 = BackwardStep<fstep1, FPred, bstep2, BOp, BIterOp, BPred>;
          using bstep0 = BackwardStep<fstep0, FPred, bstep1, BOp, BIterOp, BPred>;
          
          using iterator = typename bstep0::iterator;
          using state = typename bstep0::state;
          using type = state;
        };
        
      }                                // namespace iter_fold_if_detail
      
      
      template <
          class Iter, class State
        , class FOp, class FIterOp, class FPred
        , class BOp, class BPred
        >
      using forward_iter_foldb_if = 
        iter_foldb_if_detail::iter_foldb_if_impl<
            Iter, State
          , FOp, FIterOp, FPred
          , BOp, identity_iter_op, BPred
          , iter_foldb_if_detail::forward_iter_take_backward_step
          >;
      
      
      template <
          class Iter, class State
        , class FOp, class FIterOp, class FPred
        , class BOp, class BIterOp, class BPred
        >
      using bidirectional_iter_foldb_if =
        iter_foldb_if_detail::iter_foldb_if_impl<
            Iter, State
          , FOp, FIterOp, FPred
          , BOp, BIterOp, BPred
          , iter_foldb_if_detail::bidirectional_iter_take_backward_step
          >;
      
    }                                                       // namespace detail
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_ALGORITHM_DETAIL_ITER_FOLDB_IF_HPP */