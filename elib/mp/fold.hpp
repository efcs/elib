#ifndef ELIB_MP_FOLD_HPP
#define ELIB_MP_FOLD_HPP

# include <elib/mp/algorithm_fwd.hpp>
# include <elib/mp/iter_fold.hpp>
# include <elib/mp/placeholders.hpp>
# include <elib/mp/apply_wrap.hpp>
# include <elib/mp/lambda.hpp>
# include <elib/mp/deref.hpp>
# include <elib/mp/next_prior.hpp>
# include <elib/mp/intrinsic/nested_size.hpp>
# include <elib/mp/intrinsic/begin_end.hpp>

namespace elib
{
  namespace mp
  {
  //////////////////////////////////////////////////////////////////////////////
  //                            Fold                                              
  //////////////////////////////////////////////////////////////////////////////
  namespace detail
  {
    template <long N, class First, class Last, class State, class ForwardOp>
    struct fold_impl
    {
      
      using step_ = 
        fold_impl<
            N - 1
          , next_t<First>
          , Last
          , apply_wrap_t<ForwardOp, State, deref_t<First>>
          , ForwardOp
        >;
        
      using iterator = typename step_::iterator;
      using state = typename step_::state;
      
      static_assert(N > 0, "Overload resolution check");
    };                                                      // struct fold_impl
    
    
    template <class First, class Last, class State, class ForwardOp>
    struct fold_impl<0, First, Last, State, ForwardOp>
    {
      using iterator = First;
      using state = State;
    };
    
  // partial specialization (no nested size)
  
    template <class First, class Last, class State, class ForwardOp>
    struct fold_impl<-1, First, Last, State, ForwardOp>
    {
      using step_ = 
        fold_impl<
            -1
          , next_t<First>
          , Last
          , apply_wrap_t<ForwardOp, State, deref_t<First>>
          , ForwardOp
        >;
        
      using iterator = typename step_::iterator;
      using state = typename step_::state;
    };                                                      // struct fold_impl
    
    
    template <class Last, class State, class ForwardOp>
    struct fold_impl<-1, Last, Last, State, ForwardOp>
    {
      using iterator = Last;
      using state = State;
    };
    
  }                                                         // namespace detail
    
  //-------------------------------- fold -----------------------------------// 
    
    template <class Seq, class State, class ForwardOp> 
    struct fold 
    {
      using type = typename 
        detail::fold_impl<
            nested_size_t<Seq>::value
          , begin_t<Seq>
          , end_t<Seq>
          , State
          , lambda_t<ForwardOp>
        >::state;
    };
    
        
    template <class Seq, class State, class ForwardOp>
    using fold_t = typename fold<Seq, State, ForwardOp>::type;
    
  //////////////////////////////////////////////////////////////////////////////
  //                            Reverse Fold                                              
  //////////////////////////////////////////////////////////////////////////////
    namespace detail
    {
    //-------------------------------- reverse_fold_impl --------------------// 
      
      template <long N, class First, class Last
        , class State
        , class BackwardOp, class ForwardOp
      >
      struct reverse_fold_impl
      {
        using step_ =
          reverse_fold_impl<
              N - 1
            , next_t<First>
            , Last
            , apply_wrap_t<ForwardOp, State, deref_t<First>>
            , BackwardOp
            , ForwardOp
          >;
        
        using iterator = typename step_::iterator;
        using state =
          apply_wrap_t<
              BackwardOp
            , typename step_::state
            , deref_t<First>
          >;
      };
      
      
      template <class First, class Last
        , class State
        , class BackwardOp, class ForwardOp
      >
      struct reverse_fold_impl<0, First, Last, State, BackwardOp, ForwardOp>
      {
        using iterator = First;
        using state = State;
      };
      
    // partial specialization ( no nested_size )
    
      template <class First, class Last
        , class State
        , class BackwardOp, class ForwardOp
      >
      struct reverse_fold_impl<-1, First, Last, State, BackwardOp, ForwardOp>
      {
        using step_ = 
          reverse_fold_impl<
              -1
            , next_t<First>
            , Last
            , apply_wrap_t<ForwardOp, State, deref_t<First>>
            , BackwardOp
            , ForwardOp
          >;
        
        using iterator = typename step_::iterator;
        
        using state = 
          apply_wrap_t<
              BackwardOp
            , typename step_::state
            , deref_t<First>
          >;
      };
      
      
      template <class Last
        , class State
        , class BackwardOp, class ForwardOp
      >
      struct reverse_fold_impl<-1, Last, Last, State, BackwardOp, ForwardOp>
      {
        using iterator = Last;
        using state = State;
      };
      
    }                                                       // namespace detail
    
  //-------------------------------- reverse_fold ---------------------------// 
    
    template <class Seq, class State, class BackwardOp, class ForwardOp=_1>
    struct reverse_fold
    {
      using type = typename
        detail::reverse_fold_impl<
            nested_size_t<Seq>::value
          , begin_t<Seq>
          , end_t<Seq>
          , State
          , lambda_t<BackwardOp>
          , lambda_t<ForwardOp>
        >::state;
    };
    
    template <class Seq, class State, class ForwardOp, class BackwardOp>
    using reverse_fold_t = 
      typename reverse_fold<Seq, State, ForwardOp, BackwardOp>::type;
    
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_FOLD_HPP */