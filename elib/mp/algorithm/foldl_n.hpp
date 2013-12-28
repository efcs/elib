#ifndef ELIB_MP_ALGORITHM_FOLDL_N_HPP
#define ELIB_MP_ALGORITHM_FOLDL_N_HPP

# include <elib/mp/sequence.hpp>
# include <elib/mp/sequence_traits.hpp>
# include <elib/mp/if.hpp>
# include <elib/mp/algorithm/iter_fold_n.hpp>
# include <elib/mp/algorithm/variadic_foldl_n.hpp>
# include <elib/mp/algorithm/deref_wrapper.hpp>
# include <cstddef>

namespace elib 
{
  namespace mp
  {
    
    
    template <class Seq, class State, class F, std::size_t N>
    using foldl_n =
      if_t<
        is_model_of<Seq, model::variadic>
        , variadic_foldl_n<Seq, State, F, N>
        , iter_foldl_n<Seq, State, deref_wrapper<lambda<F>>, N>
      >;
    
    
    template <class Seq, class State, class F, std::size_t N>
    using foldl_n_t = typename foldl_n<Seq, State, F, N>::type;
     
     
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_ALGORITHM_FOLDL_N_HPP */