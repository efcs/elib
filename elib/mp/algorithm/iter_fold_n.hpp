#ifndef ELIB_MP_ALGORITHM_ITER_FOLD_N_HPP
#define ELIB_MP_ALGORITHM_ITER_FOLD_N_HPP

# include <elib/mp/algorithm/detail/iter_fold_n.hpp>
# include <elib/mp/algorithm/detail/reverse_begin.hpp>
# include <elib/mp/apply_wrap.hpp>
# include <elib/mp/arg.hpp>
# include <elib/mp/iterator.hpp>
# include <elib/mp/lambda.hpp>
# include <elib/mp/sequence.hpp>
# include <cstddef>

namespace elib 
{
  namespace mp
  {
    
    template <
        class Seq
      , class State
      , class StateOp
      , std::size_t N = sequence_size_t<Seq>::value
      >
    struct iter_foldl_n
      : detail::iter_fold_n<
          begin_t<Seq>
        , State
        , lambda<StateOp>
        , lambda< next<_1> >
        , N
        >
    {};
    
    
    template <
        class Seq
      , class State
      , class StateOp
      , std::size_t N = sequence_size_t<Seq>::value
      >
    using iter_foldl_n_t = typename iter_foldl_n<Seq, State, StateOp, N>::type;
    
    
    
    template<
        class Seq
      , class State
      , class StateOp
      , std::size_t N = sequence_size_t<Seq>::value
      >
    struct iter_foldr_n 
      : detail::iter_fold_n<
          detail::reverse_begin_t<Seq>
        , State
        , lambda<StateOp>
        , lambda< prior<_1> >
        , N
        >
    {};
    
    
    template <
        class Seq
      , class State
      , class StateOp
      , std::size_t N
      >
    using iter_foldr_n_t = typename iter_foldr_n<Seq, State, StateOp, N>::type;
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_ALGORITHM_ITER_FOLD_N_HPP */