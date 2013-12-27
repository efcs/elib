#ifndef ELIB_MP_ALGORITHM_VARIADIC_FOLDL_N_HPP
#define ELIB_MP_ALGORITHM_VARIADIC_FOLDL_N_HPP

# include <elib/mp/apply_wrap.hpp>
# include <cstddef>

namespace elib 
{
  namespace mp
  {
    namespace detail
    {
      
      template <bool Done>
      struct variadic_foldl_n_impl;
      
      
      template <>
      struct variadic_foldl_n_impl<true>
      {
        template < class State, class F, std::size_t N, class ...Args>
        struct apply 
        {
          using state = State;
          using type = State;
          static_assert(N == 0, "sanity check");
        };
      };
      
      
      template <>
      struct variadic_foldl_n_impl<false>
      {
        template <
            class State, class F
          , std::size_t N
          , class First, class ...Rest
        >
        using apply = typename variadic_foldl_n_impl<N - 1 == 0>
          ::template apply<apply_wrap_t<F, State, First>, F, N-1, Rest...>;
      };
      
      
    }                                                       // namespace detail
    
    
    template <class Seq, class State, class F, std::size_t N>
    struct variadic_foldl_n;
    
    
    template <
        template <class...> class S, class ...Args
      , class State, class F
      , std::size_t N
      >
    struct variadic_foldl_n<S<Args...>, State, F, N>
    {
      
      using type = typename 
        detail::variadic_foldl_n_impl<N == 0>::template 
          apply<State, F, N, Args...>;
          
          
      static_assert( is_model_of<S<Args...>, model::variadic>::value,
                    " must be model of variadic");
                    
      static_assert( N <= sizeof...(Args), "N must <= size<Seq>");
    };
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_ALGORITHM_VARIADIC_FOLDL_N_HPP */