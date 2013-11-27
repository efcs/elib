#ifndef ELIB_MP_ALGORITHM_ITER_FOLD_HPP
#define ELIB_MP_ALGORITHM_ITER_FOLD_HPP

# include <elib/mp/algorithm/algorithm_fwd.hpp>
# include <elib/mp/metafunction/apply_wrap.hpp>
# include <elib/mp/metafunction/lambda.hpp>
# include <elib/mp/sequence/begin_end.hpp>
# include <elib/mp/sequence/nested_size.hpp>
# include <elib/mp/iterator/next_prior.hpp>

namespace elib
{
  namespace mp
  {
  //////////////////////////////////////////////////////////////////////////////
  //                            Iterator Fold                                              
  //////////////////////////////////////////////////////////////////////////////
    namespace detail
    {
      
    //-------------------------------- iter_fold_impl -----------------------// 
  
      template <long N, class First, class Last, class State, class ForwardOp>
      struct iter_fold_impl
      {
        using rec_fold_ = iter_fold_impl<
            N-1
          , next_t<First>
          , Last
          , apply_wrap_t<ForwardOp, State, ForwardOp>
          , ForwardOp
        >;
        
        using iterator = typename rec_fold_::iterator;
        using state = typename rec_fold_::state;
        
        static_assert(N > 0, "Overload resolution check: N > 0");
      };
      
      template <class First, class Last, class State, class ForwardOp>
      struct iter_fold_impl<0, First, Last, State, ForwardOp>
      {
        using iterator = First;
        using state = State;
      };
      
    // No nested_size overload
    
      template <class First, class Last, class State, class ForwardOp>
      struct iter_fold_impl<-1, First, Last, State, ForwardOp>
      {
        using rec_fold_ = iter_fold_impl<
            -1
          , next_t<First>
          , Last
          , apply_wrap_t<ForwardOp, State, First>
          , ForwardOp
        >;
        
        using iterator = typename rec_fold_::iterator;
        using state = typename rec_fold_::state;
      };
      
      template <class Last, class State, class ForwardOp>
      struct iter_fold_impl<-1, Last, Last, State, ForwardOp>
      {
        using iterator = Last;
        using state = State;
      };
      
    }                                                       // namespace detail
    
  //-------------------------------- iter_fold ------------------------------// 
    
    template <class Seq, class State, class ForwardOp> 
    struct iter_fold
    {
      using type = typename 
        detail::iter_fold_impl<
            nested_size<Seq>::value
          , begin_t<Seq>
          , end_t<Seq>
          , State
          , lambda_t<ForwardOp>
        >::state;
    };
    
  //////////////////////////////////////////////////////////////////////////////
  //                            Reverse Iterator Fold                                              
  //////////////////////////////////////////////////////////////////////////////
    namespace detail
    {
      
      template <long N, class First, class Last
        , class State 
        , class BackwardOp, class ForwardOp
      >
      struct reverse_iter_fold_impl
      {
        using step_ = 
          reverse_iter_fold_impl<
              N - 1
            , next_t<First>
            , Last
            , apply_wrap_t<ForwardOp, State, First>
            , BackwardOp
            , ForwardOp
          >;
        
        using iterator = typename step_::iterator;
        
        using state = 
          apply_wrap_t<
              BackwardOp
            , typename step_::state
            , First
          >;
        
        static_assert(N > 0, "Overload Resolution check");
      };                                       // struct reverse_iter_fold_impl
      
      
      template <class First, class Last
        , class State
        , class BackwardOp, class ForwardOp
      >
      struct reverse_iter_fold_impl<
          0, First, Last
        , State
        , BackwardOp, ForwardOp 
      >
      {
        using iterator = First;
        using state = State;
      };                                       // struct reverse_iter_fold_impl
      
    // partial specialization ( no nested size )
    
      template <class First, class Last, class State
        , class BackwardOp, class ForwardOp
      >
      struct reverse_iter_fold_impl<
          -1, First, Last
        , State
        , BackwardOp, ForwardOp
      >
      {
        using rec_fold_ = 
          reverse_iter_fold_impl<
              -1
            , next_t<First>
            , Last
            , apply_wrap_t<ForwardOp, State, First>
            , BackwardOp
            , ForwardOp
          >;
        
        using iterator = typename rec_fold_::iterator;
        using state = 
          apply_wrap_t<
              BackwardOp
            , typename rec_fold_::state
            , First
          >;
      };                                       // struct reverse_iter_fold_impl
      
      
      template <class Last, class State, class BackwardOp, class ForwardOp>
      struct reverse_iter_fold_impl<
          -1, Last, Last
        , State
        , BackwardOp, ForwardOp
      >
      {
        using iterator = Last;
        using state = State;
      };                                       // struct reverse_iter_fold_impl
      
    }                                                       // namespace detail
    
  //-------------------------------- reverse_iter_fold ----------------------// 
  
    template <class Seq, class State
      , class BackwardOp, class ForwardOp = _1
    >
    struct reverse_iter_fold
    {
      using type = typename
        detail::reverse_iter_fold_impl<
            nested_size<Seq>::value
          , begin_t<Seq>
          , end_t<Seq>
          , State
          , lambda_t<BackwardOp>
          , lambda_t<ForwardOp>
        >::state;
    };
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_ALGORITHM_ITER_FOLD_HPP */