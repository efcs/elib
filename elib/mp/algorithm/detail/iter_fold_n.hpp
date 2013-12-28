#ifndef ELIB_MP_ALGORITHM_DETAIL_ITER_FOLD_N_HPP
# define ELIB_MP_ALGORITHM_DETAIL_ITER_FOLD_N_HPP

namespace elib 
{
  namespace mp
  {
    namespace detail
    {
      
      template <
          class Iter
        , class State
        , class StateOp
        , class IterOp
        , std::size_t N
        >
      struct iter_fold_n;
        
      
      template <
          class Iter
        , class State
        , class StateOp
        , class IterOp
        >
      struct iter_fold_n< Iter, State, StateOp, IterOp, 0>
      {
        using iterator = Iter;
        using state = State;
        using type = state;
      };
      
      template <
          class Iter
        , class State
        , class StateOp
        , class IterOp
        >
      struct iter_fold_n< Iter, State, StateOp, IterOp, 1 >
      {
        using iterator = apply_wrap_t<IterOp, Iter>;
        using state = apply_wrap_t<StateOp, State, Iter>;
        
        using type = state;
      };
      
      
      template <
          class Iter
        , class State
        , class StateOp
        , class IterOp
        >
      struct iter_fold_n< Iter, State, StateOp, IterOp, 2 >
      {
        using iterator1 = apply_wrap_t<IterOp, Iter>;
        using state1 = apply_wrap_t<StateOp, State, Iter>;
        
        using iterator = apply_wrap_t<IterOp, iterator1>;
        using state = apply_wrap_t<StateOp, state1, iterator1>;
        
        using type = state;
      };
      
      template <
          class Iter
        , class State
        , class StateOp
        , class IterOp
        >
      struct iter_fold_n< Iter, State, StateOp, IterOp, 3 >
      {
        using iterator1 = apply_wrap_t<IterOp, Iter>;
        using state1 = apply_wrap_t<StateOp, State, Iter>;
        
        using iterator2 = apply_wrap_t<IterOp, iterator1>;
        using state2 = apply_wrap_t<StateOp, state1, iterator1>;
        
        using iterator = apply_wrap_t<IterOp, iterator2>;
        using state = apply_wrap_t<StateOp, state2, iterator2>;
        
        using type = state;
      };
      
      template <
          class Iter
        , class State
        , class StateOp
        , class IterOp
        >
      struct iter_fold_n< Iter, State, StateOp, IterOp, 4 >
      {
        using iterator1 = apply_wrap_t<IterOp, Iter>;
        using state1 = apply_wrap_t<StateOp, State, Iter>;
        
        using iterator2 = apply_wrap_t<IterOp, iterator1>;
        using state2 = apply_wrap_t<StateOp, state1, iterator1>;
        
        using iterator3 = apply_wrap_t<IterOp, iterator2>;
        using state3 = apply_wrap_t<StateOp, state2, iterator2>;
        
        using iterator = apply_wrap_t<IterOp, iterator3>;
        using state = apply_wrap_t<StateOp, state3, iterator3>;
        
        using type = state;
      };
      
      template <
          class Iter
        , class State
        , class StateOp
        , class IterOp
        >
      struct iter_fold_n< Iter, State, StateOp, IterOp, 5 >
      {
        using iterator1 = apply_wrap_t<IterOp, Iter>;
        using state1 = apply_wrap_t<StateOp, State, Iter>;
        
        using iterator2 = apply_wrap_t<IterOp, iterator1>;
        using state2 = apply_wrap_t<StateOp, state1, iterator1>;
        
        using iterator3 = apply_wrap_t<IterOp, iterator2>;
        using state3 = apply_wrap_t<StateOp, state2, iterator2>;
        
        using iterator4 = apply_wrap_t<IterOp, iterator3>;
        using state4 = apply_wrap_t<StateOp, state3, iterator3>;
        
        using iterator = apply_wrap_t<IterOp, iterator4>;
        using state = apply_wrap_t<StateOp, state4, iterator4>;
        
        using type = state;
      };
      
      
      template <
          class Iter
        , class State
        , class StateOp
        , class IterOp
        , std::size_t N
        >
      struct iter_fold_n
      {
        using iterator1 = apply_wrap_t<IterOp, Iter>;
        using state1 = apply_wrap_t<StateOp, State, Iter>;
        
        using iterator2 = apply_wrap_t<IterOp, iterator1>;
        using state2 = apply_wrap_t<StateOp, state1, iterator1>;
        
        using iterator3 = apply_wrap_t<IterOp, iterator2>;
        using state3 = apply_wrap_t<StateOp, state2, iterator2>;
        
        using iterator4 = apply_wrap_t<IterOp, iterator3>;
        using state4 = apply_wrap_t<StateOp, state3, iterator3>;
        
        using iterator5 = apply_wrap_t<IterOp, iterator4>;
        using state5 = apply_wrap_t<StateOp, state4, iterator4>;
        
        using result_ = iter_fold_n<iterator5, state5, StateOp, IterOp, N - 5>;
        using iterator = typename result_::iterator;
        using state = typename result_::state;
        using type = state;
        
        static_assert( N >= 6,  "Sanity Check");
      };
      
      
    }                                                       // namespace detail
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_ALGORITHM_DETAIL_ITER_FOLD_N_HPP */