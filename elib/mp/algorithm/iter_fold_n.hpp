#ifndef ELIB_MP_ALGORITHM_ITER_FOLD_N_HPP
#define ELIB_MP_ALGORITHM_ITER_FOLD_N_HPP

# include <elib/mp/algorithm/detail/iter_fold_n.hpp>
# include <elib/mp/algorithm/detail/iter_foldb_if.hpp>
# include <elib/mp/algorithm/detail/reverse_begin.hpp>
# include <elib/mp/apply_wrap.hpp>
# include <elib/mp/arg.hpp>
# include <elib/mp/comparison.hpp>
# include <elib/mp/iterator.hpp>
# include <elib/mp/integral_constant.hpp>
# include <elib/mp/pair.hpp>
# include <elib/mp/lambda.hpp>
# include <elib/mp/sequence.hpp>
# include <cstddef>

namespace elib 
{
  namespace mp
  {
    
    template <
        class Seq
      , class State
      , class StateOp
      , std::size_t N = sequence_size_t<Seq>::value
      >
    struct iter_foldl_n
      : detail::iter_fold_n<
          begin_t<Seq>
        , State
        , lambda<StateOp>
        , lambda< next<_1> >
        , N
        >
    {};
    
    
    template <
        class Seq
      , class State
      , class StateOp
      , std::size_t N = sequence_size_t<Seq>::value
      >
    using iter_foldl_n_t = typename iter_foldl_n<Seq, State, StateOp, N>::type;
    
    
    namespace detail
    {
      
      template <class StateOp>
      struct iter_foldr_n_state_op_impl
      {
        template <class State, class Iter>
        struct apply 
        {
          
          using first_ = first_t<State>;
          using second_ = second_t<State>;
          
          using type = pair<
            apply_wrap_t< lambda<StateOp>, first_, Iter>
          , apply_wrap_t< 
                lambda< prior<_1> >
              , second_
              , Iter
              >
          >;
        };
      };
      
      template <class StateOp>
      using iter_foldr_n_pair_first_lambda = 
        protect< iter_foldr_n_state_op_impl<StateOp> >;
      
      
      struct iter_foldr_n_pred
      {
        template <class State, class Iter>
        using apply = 
          greater< second_t<State>, size_type<0> >;
      };
      
      
      template <bool IsBidir>
      struct select_iter_foldr_n_impl;
      
      template <>
      struct select_iter_foldr_n_impl<true>
      {
        template<
            class Seq
          , class State
          , class StateOp
          , std::size_t N = sequence_size_t<Seq>::value
          >
        using apply =
          detail::iter_fold_n<
            detail::reverse_begin_t<Seq>
          , State
          , lambda<StateOp>
          , lambda< prior<_1> >
          , N
          >;
      };
      
      template <>
      struct select_iter_foldr_n_impl<false>
      {
        template<
            class Seq
          , class State
          , class StateOp
          , std::size_t N
          >
        using apply = 
          first<
            typename 
            detail::forward_iter_foldb_if<
              begin_t<Seq>
            , pair<State, size_type<N>>
            , identity_state_op
            , lambda< next<_1> >
            , lambda< not_<same_type<end_t<Seq>, _2>> >
            , iter_foldr_n_pair_first_lambda< StateOp >
            , iter_foldr_n_pred
            >::type
          >;
      };
      
      template <class Seq, class State, class StateOp, std::size_t N >
      using dispatch_iter_foldr_n = typename
        select_iter_foldr_n_impl<
            is_bidirectional_sequence<Seq>::value
          >::template
        apply< Seq, State, StateOp, N >;
    }                                                       // namespace detail
    
    
    template <
        class Seq
      , class State
      , class StateOp
      , std::size_t N = sequence_size_t<Seq>::value
      >
    struct iter_foldr_n 
      : detail::dispatch_iter_foldr_n< Seq, State, StateOp, N>
    {};
    
    
    template <
        class Seq
      , class State
      , class StateOp
      , std::size_t N = sequence_size_t<Seq>::value
      >
    using iter_foldr_n_t = typename 
      detail::dispatch_iter_foldr_n<Seq, State, StateOp, N>::type;
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_ALGORITHM_ITER_FOLD_N_HPP */