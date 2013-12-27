#ifndef ELIB_MP_ALGORITHM_ITER_FOLDL_IF_HPP
#define ELIB_MP_ALGORITHM_ITER_FOLDL_IF_HPP

# include <elib/mp/apply_wrap.hpp>
# include <elib/mp/always.hpp>
# include <elib/mp/sequence.hpp>
# include <elib/mp/iterator.hpp>
# include <elib/mp/if.hpp>
# include <elib/mp/integral_constant.hpp>
# include <elib/mp/logical.hpp>
# include <elib/mp/same_type.hpp>
# include <elib/mp/lambda.hpp>


namespace elib 
{
  namespace mp
  {
    
    namespace detail
    {
      
      template <class Iter, class State, class F, class Pred>
      struct iter_foldl_if_impl;
      
      
      template <class Pred, class End>
      struct iter_foldl_if_pred
      {
        template <class State, class Iter>
        using apply = 
          and_<
              not_<same_type<Iter, End>>
            , apply_wrap<Pred, State, Iter>
          >;
      };
      
      
      template <
          class Iter, class State, class F, class Pred
        , bool = apply_wrap_t<Pred, State, Iter>::value
        >
      struct iter_foldl_if_step
      {
        using is_last = bool_<true>;
        
        using state = State;
        using iterator = Iter;
        
        using type = state;
      };
      
      
      template <
          class Iter, class State, class F, class Pred
        >
      struct iter_foldl_if_step<Iter, State, F, Pred, true>
      {
        using is_last = bool_<false>;
        
        using state = apply_wrap_t<F, State, Iter>;
        using iterator = next_t<Iter>;
      };
      
      
      template <class Last, class F, class Pred>
      using iter_foldl_if_next = 
        iter_foldl_if_step<
            typename Last::iterator
          , typename Last::state
          , F, Pred
        >; 
        
        
      template <class Last, class F, class Pred>
      using iter_foldl_if_rec =
        iter_foldl_if_impl<
            typename Last::iterator
          , typename Last::state
          , F, Pred
        >;
      
      
      template <class Iter, class State, class F, class Pred>
      struct iter_foldl_if_impl
      {
        using state1 = iter_foldl_if_step<Iter, State, F, Pred>;
        using state2 = iter_foldl_if_next<state1, F, Pred>;
        using state3 = iter_foldl_if_next<state2, F, Pred>;
        using state4 = iter_foldl_if_next<state3, F, Pred>;
        
        using result_ =
          if_t< 
            typename state4::is_last
          , state4
          , iter_foldl_if_rec<state4, F, Pred>
          >;
        
        using iterator = typename result_::iterator;
        using state = typename result_::state;
        using type = state;
      };
      
      
    }                                                       // namespace detail
    
    
    template <class Seq, class State, class F, class Pred = always<true_>>
    struct iter_foldl_if 
      : detail::iter_foldl_if_impl<
            begin_t<Seq>
          , State
          , lambda<F>
          , detail::iter_foldl_if_pred<lambda<Pred>, end_t<Seq>>
        >
    {};
    
    
    template <class Seq, class State, class F, class Pred = always<true_>>
    using iter_foldl_if_t = typename iter_foldl_if<Seq, State, F, Pred>::type;
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_ALGORITHM_ITER_FOLDL_IF_HPP */