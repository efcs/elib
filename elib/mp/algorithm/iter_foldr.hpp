#ifndef ELIB_MP_ALGORITHM_ITER_FOLDR_IF_HPP
#define ELIB_MP_ALGORITHM_ITER_FOLDR_IF_HPP

# include <elib/mp/algorithm/detail/iter_foldb_if.hpp>
# include <elib/mp/algorithm/detail/iter_fold_if.hpp>
# include <elib/mp/always.hpp>
# include <elib/mp/apply_wrap.hpp>
# include <elib/mp/if.hpp>
# include <elib/mp/iterator.hpp>
# include <elib/mp/lambda.hpp>
# include <elib/mp/logical.hpp>
# include <elib/mp/same_type.hpp>
# include <elib/mp/sequence.hpp>
# include <elib/mp/sequence_traits.hpp>

namespace elib 
{
  namespace mp
  {
    namespace detail
    {
      template <bool IsForward, bool IsBidir>
      struct get_iter_foldr_impl;
      
      
      
      template <>
      struct get_iter_foldr_impl<true, false>
      {
        template <
            class Seq
          , class State
          , class StateOp
          , class IterOp
          , class Pred
          >
        using apply =
          
      };
      
      template <>
      struct get_iter_foldr_impl<true, true>
      {
        template <
            class Seq
          , class State
          , class StateOp
          , class IterOp
          , class Pred
          >
        using apply = 
          detail::iter_fold_if<
              eval_if_t<
                  same_type<begin_t<Seq>, end_t<Seq>>
                , end<Seq>
                , prior< end_t<Seq> >
                >
            , State
            , StateOp
            , IterOp
            , lambda< and_< not_<same_typePred
          >;
      };
      
    }                                                       // namespace detail
    
    template <
        class Seq
      , class State
      , class StateOp
      , class IterOp
      , class Pred
      >
    struct iter_foldr :
      detail::get_iter_foldr_impl<
          is_model_of<Seq, model::forward_sequence>::type::value
        , is_model_of<Seq, model::bidirectional_sequence>::type::value
      >::apply<
          Seq, State
        , lambda<StateOp>
        , lambda<IterOp>
        , lambda<Pred>
        >
    {};
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_ALGORITHM_ITER_FOLDR_IF_HPP */