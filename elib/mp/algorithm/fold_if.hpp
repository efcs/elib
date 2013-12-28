#ifndef ELIB_MP_ALGORITHM_FOLD_IF_HPP
#define ELIB_MP_ALGORITHM_FOLD_IF_HPP

# include <elib/mp/algorithm/iter_fold_if.hpp>
# include <elib/mp/algorithm/detail/deref_lambda.hpp>
# include <elib/mp/algorithm/detail/variadic_foldl_if.hpp>
# include <elib/mp/always.hpp>
# include <elib/mp/if.hpp>
# include <elib/mp/lambda.hpp>
# include <elib/mp/sequence_traits.hpp>


namespace elib 
{
  namespace mp
  {
    
    namespace detail
    {
      
      template <bool IsVaridic>
      struct select_foldl_if_impl;
     
      template <>
      struct select_foldl_if_impl<true>
      {
        template <class Seq, class State, class F, class Pred>
        using apply = variadic_foldl_if<Seq, State, lambda<F>, lambda<Pred>>;
      };
      
      template <>
      struct select_foldl_if_impl<false>
      {
        template <class Seq, class State, class F, class Pred>
        using apply = 
          iter_foldl_if<
            Seq, State
            , deref_lambda<F>
            , deref_lambda<Pred>
          >;
      };
      
      template <class Seq, class State, class StateOp, class Pred>
      using dispatch_foldl_if = typename
        select_foldl_if_impl<
            is_variadic<Seq>::value
          >::template
        apply<
            Seq, State
          , StateOp, Pred
        >;
      
    }                                                       // namespace detail
    

    template <class Seq, class State, class F, class Pred = always_true>
    struct foldl_if  
      : detail::dispatch_foldl_if<Seq, State, F, Pred>
    {};
    
    
    template <class Seq, class State, class F, class Pred = always_true>
    using foldl_if_t = typename 
      detail::dispatch_foldl_if<Seq, State, F, Pred>::type;
    
    
    
    template <class Seq, class State, class StateOp, class Pred = always_true>
    struct foldr_if
      : iter_foldr_if<
          Seq, State
        , detail::deref_lambda<StateOp>
        , detail::deref_lambda<Pred>
        >
    {};
    
    template <class Seq, class State, class StateOp, class Pred = always_true>
    using foldr_if_t =
      iter_foldr_if_t<
          Seq, State
        , detail::deref_lambda<StateOp>
        , detail::deref_lambda<Pred>
        >;
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_ALGORITHM_FOLD_IF_HPP */