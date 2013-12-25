#ifndef ELIB_MP_ALGORITHM_ITER_FOLDL_N_HPP
#define ELIB_MP_ALGORITHM_ITER_FOLDL_N_HPP

# include <elib/mp/apply_wrap.hpp>
# include <elib/mp/iterator.hpp>
# include <elib/mp/lambda.hpp>
# include <cstddef>


namespace elib 
{
  namespace mp
  {
    namespace detail
    {
      
      template <class iterator0, class state0, class F, std::size_t N>
      struct iter_foldl_n_impl 
      {
        static_assert(N >= 6, "N must be greater than chunking size");

        using chunk_ = iter_foldl_n_impl<iterator0,  state0, F, 5>;
        using result_ = 
          iter_foldl_n_impl<
              typename chunk_::iterator
            , typename chunk_::state
            , F
            , N - 5
          >;

        using iterator = typename result_::iterator;
        using state = typename result_::state;
        using type = typename result_::type;
      };

      
      template <class iterator0, class state0, class F>
      struct iter_foldl_n_impl<iterator0, state0, F, 0>
      {
        using state = state0;
        using iterator = iterator0;
        using type = state0;
      };


      template <class iterator0, class state0, class F>
      struct iter_foldl_n_impl<iterator0, state0, F, 1>
      {
        using state = apply_wrap_t<F, state0, iterator0>;
        using iterator = next_t<iterator0>;
        
        using type = state;
      };


      template <class iterator0, class state0, class F>
      struct iter_foldl_n_impl<iterator0,  state0, F, 2>
      {
        using state1 = apply_wrap_t<F, state0, iterator0>;
        using iterator1 = next_t<iterator0>;
        
        using state = apply_wrap_t<F, state1, iterator1>;
        using iterator = next_t<iterator1>;
        
        using type = state;
      };


      template <class iterator0, class state0, class F>
      struct iter_foldl_n_impl<iterator0, state0, F, 3>
      {
        using state1 = apply_wrap_t<F, state0, iterator0>;
        using iterator1 = next_t<iterator0>;
        
        using state2 = apply_wrap_t<F, state1, iterator1>;
        using iterator2 = next_t<iterator1>;
        
        using state = apply_wrap_t<F, state2, iterator2>;
        using iterator = next_t<iterator2>;

        using type = state;
      };

      
      template <class iterator0, class state0, class F>
      struct iter_foldl_n_impl<iterator0,  state0, F, 4>
      {
        using state1 = apply_wrap_t<F, state0, iterator0>;
        using iterator1 = next_t<iterator0>;
        
        using state2 = apply_wrap_t<F, state1, iterator1>;
        using iterator2 = next_t<iterator1>;
        
        using state3 = apply_wrap_t<F, state2, iterator2>;
        using iterator3 = next_t<iterator2>;
        
        using state = apply_wrap_t<F, state3, iterator3>;
        using iterator = next_t<iterator3>;
        
        using type = state;
      };

      
      template <class iterator0, class state0, class F>
      struct iter_foldl_n_impl<iterator0,  state0, F, 5>
      {
        using state1 = apply_wrap_t<F, state0, iterator0>;
        using iterator1 = next_t<iterator0>;
        
        using state2 = apply_wrap_t<F, state1, iterator1>;
        using iterator2 = next_t<iterator1>;
        
        using state3 = apply_wrap_t<F, state2, iterator2>;
        using iterator3 = next_t<iterator2>;
        
        using state4 = apply_wrap_t<F, state3, iterator3>;
        using iterator4 = next_t<iterator3>;
        
        using state = apply_wrap_t<F, state4, iterator4>;
        using iterator = next_t<iterator4>;
        
        using type = state;
      };
    
    }                                                       // namespace detail
    
    
    template <class Seq, class State, class F, std::size_t N>
    struct iter_foldl_n 
      : detail::iter_foldl_n_impl<
          begin_t<Seq>
        , State, lambda<F>, N
      >
    {};
    
    
    template <class Seq, class State, class F, std::size_t N>
    using iter_foldl_n_t = typename iter_foldl_n<Seq, State, F, N>::type;
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_ALGORITHM_ITER_FOLDL_N_HPP */