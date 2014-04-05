#ifndef ELIB_MP_ALGORITHM_REMOVE_HPP
#define ELIB_MP_ALGORITHM_REMOVE_HPP

# include <elib/mp/algorithm/inserter.hpp>
# include <elib/mp/algorithm/iter_fold.hpp>
# include <elib/mp/algorithm/detail/inserter_op.hpp>
# include <elib/mp/arg.hpp>
# include <elib/mp/lambda.hpp>
# include <elib/mp/logical.hpp>
# include <elib/mp/sequence.hpp>

namespace elib 
{
  namespace mp
  {
   
   
    template <
        class Seq
      , class Pred
      , class In = back_inserter<clear_t<Seq>>
      >
    struct remove_if
      : iter_foldl<
          Seq
        , typename In::state
        , detail::inserter_op_if<In, lambda<not_<Pred>> >
        >
    {};
    
    
    template <
        class Seq
      , class Pred
      , class In = back_inserter<clear_t<Seq>>
      >
    using remove_if_t = typename remove_if<Seq, Pred, In>::type;
    
    
    template <
        class Seq
      , class Pred
      , class In = front_inserter<clear_t<Seq>>
      >
    struct reverse_remove_if
      : iter_foldr<
          Seq
        , typename In::state
        , detail::inserter_op_if<In, lambda<not_<Pred>> >
        >
    {};
    
    
    template <
        class Seq
      , class Pred
      , class In = front_inserter<clear_t<Seq>>
      >
    using reverse_remove_if_t = typename reverse_remove_if<Seq, Pred, In>::type;
    
    
    
    template <
        class Seq
      , class T
      , class In = back_inserter<clear_t<Seq>>
      >
    struct remove
      : remove_if<Seq, aux::is_same<_1, T>, In>
    {};
    
    
    template <
        class Seq, 
        class T
      , class In = back_inserter<clear_t<Seq>>
      >
    using remove_t = typename remove<Seq, T, In>::type;
    
    
    template <
        class Seq
      , class T
      , class In = front_inserter<clear_t<Seq>>
      >
    struct reverse_remove
      : reverse_remove_if<Seq, aux::is_same<_1, T>, In>
    {};
    
   
    template <
        class Seq, 
        class T
      , class In = front_inserter<clear_t<Seq>>
      >
    using reverse_remove_t = typename reverse_remove<Seq, T, In>::type;
   
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_ALGORITHM_REMOVE_HPP */