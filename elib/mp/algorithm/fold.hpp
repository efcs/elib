#ifndef ELIB_MP_ALGORITHM_FOLD_HPP
#define ELIB_MP_ALGORITHM_FOLD_HPP

# include <elib/mp/algorithm/iter_fold.hpp>
# include <elib/mp/algorithm/iter_fold_if.hpp>
# include <elib/mp/algorithm/iter_fold_n.hpp>
# include <elib/mp/algorithm/detail/deref_lambda.hpp>
# include <elib/mp/algorithm/detail/variadic_foldl.hpp>
# include <elib/mp/always.hpp>
# include <elib/mp/sequence_traits.hpp>


namespace elib 
{
  namespace mp
  {
    
    namespace detail
    {
      
      template <bool IsVariadic, bool HasO1Size>
      struct select_foldl_impl;
      
      
      template <bool HasO1Size>
      struct select_foldl_impl<true, HasO1Size>
      {
        template <class Seq, class State, class F>
        using apply = variadic_foldl<Seq, State, F>;
      };
      
      
      template <>
      struct select_foldl_impl<false, true>
      {
        template <class Seq, class State, class F>
        using apply = 
          iter_foldl_n<
            Seq, State
          , deref_lambda<F>
          >;
      };
      
      
      template <>
      struct select_foldl_impl<false, false>
      {
        template <class Seq, class State, class StateOp>
        using apply = 
          iter_foldl_if<
              Seq, State
            , deref_lambda<StateOp>
            , always_true
            >;
      };
      
      
      template <class Seq, class State, class StateOp>
      using dispatch_foldl = typename
        select_foldl_impl<
            is_variadic<Seq>::value
          , has_O1_size<Seq>::value
          >::template
        apply< Seq, State, StateOp >;
      
    }                                                       // namespace detail

    
    template <class Seq, class State, class F>
    struct foldl : detail::dispatch_foldl<Seq, State, F>
    {};
   
   
    template <class Seq, class State, class F>
    using foldl_t = typename detail::dispatch_foldl<Seq, State, F>::type;
    
    
    template <class Seq, class State, class StateOp>
    struct foldr : iter_foldr<Seq, State, detail::deref_lambda<StateOp>>
    {};
    
    template <class Seq, class State, class StateOp>
    using foldr_t = iter_foldr_t<Seq, State, detail::deref_lambda<StateOp>>;
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_ALGORITHM_FOLD_HPP */