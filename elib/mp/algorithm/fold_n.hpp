#ifndef ELIB_MP_ALGORITHM_FOLD_N_HPP
#define ELIB_MP_ALGORITHM_FOLD_N_HPP

# include <elib/mp/algorithm/iter_fold_n.hpp>
# include <elib/mp/algorithm/detail/deref_lambda.hpp>
# include <elib/mp/algorithm/detail/variadic_foldl_n.hpp>
# include <elib/mp/if.hpp>
# include <elib/mp/sequence.hpp>
# include <elib/mp/sequence_traits.hpp>
# include <cstddef>

namespace elib 
{
  namespace mp
  {
    namespace detail
    {
      
      template <bool IsVariadic>
      struct select_foldl_n_impl;
      
      
      template <>
      struct select_foldl_n_impl<true>
      {
        template <class Seq, class State, class StateOp, std::size_t N>
        using apply =
          iter_foldl_n<
              Seq, State
            , deref_lambda<StateOp>
            , N
          >;
      };
      
      
      template <>
      struct select_foldl_n_impl<false>
      {
        template <class Seq, class State, class StateOp, std::size_t N>
        using apply = variadic_foldl_n<Seq, State, StateOp, N>; 
      };
      
      
      template <class Seq, class State, class StateOp, std::size_t N>
      using dispatch_foldl_n = typename
        select_foldl_n_impl<
          is_variadic<Seq>::value
          >::template
        apply<
            Seq
          , State
          , StateOp
          , N
        >;
    
    
    }                                                       // namespace detail
    
    
    template <class Seq, class State, class StateOp, std::size_t N>
    struct foldl_n 
      : detail::dispatch_foldl_n<Seq, State, StateOp, N>
    {};
    
    
    template <class Seq, class State, class StateOp, std::size_t N>
    using foldl_n_t = typename 
      detail::dispatch_foldl_n<Seq, State, StateOp, N>::type;
    
    
    
    template <class Seq, class State, class StateOp, std::size_t N>
    struct foldr_n 
      : iter_foldr_n<
            Seq, State
          , detail::deref_lambda<StateOp> 
          , N
        >
    {};
    
    
    template <class Seq, class State, class StateOp, std::size_t N>
    using foldr_n_t = typename
      iter_foldr_n<
          Seq, State
        , detail::deref_lambda<StateOp> 
        , N
      >::type;
     
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_ALGORITHM_FOLD_N_HPP */