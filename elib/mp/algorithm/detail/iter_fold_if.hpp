#ifndef ELIB_MP_ALGORITHM_DETAIL_ITER_FOLD_IF_HPP
#define ELIB_MP_ALGORITHM_DETAIL_ITER_FOLD_IF_HPP

# include <elib/mp/apply_wrap.hpp>
# include <elib/mp/identity.hpp>

namespace elib 
{
  namespace mp
  {
    namespace detail
    {
      
      
      template < bool DoStep >
      struct iter_fold_if_impl;
      
      
      template <>
      struct iter_fold_if_impl<false>
      {
        template <
            class Iter, class State
          , class NextIter, class NextState
          , class StateOp, class IterOp
          , class Pred
          >
        struct apply
        {
          using state = State;
          using iterator = Iter;
          using type = state;
        };
      };
      
      
      template <>
      struct iter_fold_if_impl<true>
      {
        template <
            class Iter, class State
          , class NextIter, class NextState
          , class StateOp, class IterOp
          , class Pred
          >
        using apply = typename
          iter_fold_if_impl<
            apply_wrap_t<
                Pred
              , typename NextState::type
              , typename NextIter::type
              >::value
          >::template 
          apply<
              typename NextIter::type
            , typename NextState::type
            , apply_wrap<IterOp, typename NextIter::type>
            , apply_wrap<StateOp, typename NextState::type, typename NextIter::type>
            , StateOp, IterOp, Pred
          >;
      };
      
      template <
          class Iter
        , class State
        , class StateOp
        , class IterOp
        , class Pred
        >
      using iter_fold_if = typename
        iter_fold_if_impl<
            apply_wrap_t<Pred, State, Iter>::value
        >::template 
        apply<
            Iter
          , State
          , apply_wrap<IterOp, Iter>
          , apply_wrap<StateOp, State, Iter>
          , StateOp
          , IterOp
          , Pred
          >;
      
      
    }                                                       // namespace detail
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_ALGORITHM_DETAIL_ITER_FOLD_IF_HPP */
