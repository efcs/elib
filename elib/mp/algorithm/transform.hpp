#ifndef ELIB_MP_ALGORITHM_TRANSFORM_HPP
#define ELIB_MP_ALGORITHM_TRANSFORM_HPP

# include <elib/mp/algorithm/copy.hpp>
# include <elib/mp/algorithm/inserter.hpp>
# include <elib/mp/algorithm/iter_fold.hpp>
# include <elib/mp/algorithm/iter_fold_if.hpp>
# include <elib/mp/algorithm/detail/reverse_begin.hpp>
# include <elib/mp/apply_wrap.hpp>
# include <elib/mp/iterator.hpp>
# include <elib/mp/lambda.hpp>
# include <elib/mp/pair.hpp>
# include <elib/mp/protect.hpp>
# include <elib/mp/sequence.hpp>
# include <elib/mp/sequence_traits.hpp>
# include <elib/mp/detail/na.hpp>
# include <elib/aux.hpp>

namespace elib 
{
  namespace mp
  {
    namespace detail
    {
      
      template <class In, class Transform>
      struct unary_transform_op_impl
      {
        using Op = lambda< typename In::operation >;
        
        template <class State, class Iter>
        using apply = 
          apply_wrap<
              Op
            , State
            , apply_wrap_t<Transform, deref_t<Iter>>
            >;
      };
    
    
      template <class In, class Transform>
      using unary_transform_op = 
        protect< unary_transform_op_impl<In, Transform> >;
        
        
      template <class In, class Transform>
      struct binary_transform_op_impl
      {
        using Op = lambda<typename In::operation>;
        
        template <class State, class Iter>
        using apply =
          pair<
              apply_wrap_t<
                  Op
                , first_t<State>
                , apply_wrap_t< 
                    Transform
                  , deref_t<Iter>
                  , deref_t<second_t<State>>
                  >
                >
              , next_t<second_t<State>>
            >;
            
      };
      
      template <class In, class Transform>
      using binary_transform_op = 
        protect< binary_transform_op_impl<In, Transform> >;
      
    
    }                                                       // namespace detail
    
    
    template <
        class Seq 
      , class Op
      , class In = back_inserter<clear_t<Seq>>
      >
    struct unary_transform
      : iter_foldl<
          Seq
        , typename In::state
        , detail::unary_transform_op<In, lambda<Op>>
        >
    {};
    
    
    template <
        class Seq 
      , class Op
      , class In = back_inserter<clear_t<Seq>>
      >
    using unary_transform_t = typename unary_transform<Seq, Op, In>::type;
    
    
    template <
        class Seq 
      , class Op
      , class In = front_inserter<clear_t<Seq>>
      >
    struct reverse_unary_transform
      : iter_foldr<
          Seq
        , typename In::state
        , detail::unary_transform_op<In, lambda<Op>>
        >
    {};
    
    
    template <
        class Seq 
      , class Op
      , class In = front_inserter<clear_t<Seq>>
      >
    using reverse_unary_transform_t = typename
      reverse_unary_transform<Seq, Op, In>::type;
    
    
    template <
        class Seq1
      , class Seq2
      , class Op
      , class In = back_inserter<clear_t<Seq1>>
      >
    struct binary_transform
      : first< 
          iter_foldl_t<
              Seq1
            , pair< typename In::state, begin_t<Seq2> >
            , detail::binary_transform_op< In, lambda<Op> >
            >
          >
    {};
    
    template <
        class Seq1
      , class Seq2
      , class Op
      , class In = back_inserter<clear_t<Seq1>>
      >
    using binary_transform_t = typename
      binary_transform<Seq1, Seq2, Op, In>::type;
    
    template <
        class Seq1
      , class Seq2
      , class Op
      , class In = front_inserter<clear_t<Seq1>>
      >
    struct reverse_binary_transform
      : first< 
          iter_foldr_t<
              Seq1
            , pair< typename In::state, begin_t<reverse_copy_t<Seq2>> >
            , detail::binary_transform_op< In, lambda<Op> >
            >
          >
    {};
    
    
    template <
        class Seq1
      , class Seq2
      , class Op
      , class In = front_inserter<clear_t<Seq1>>
      >
    using reverse_binary_transform_t = typename
      reverse_binary_transform<Seq1, Seq2, Op, In>::type;
      
    
    
    template <
        class Seq
      , class SeqOrOp
      , class OpOrIn = detail::na
      , class InOrNA = detail::na
      >
    using transform =
      eval_if_t<
          and_<
            is_sequence<Seq>
          , is_sequence<SeqOrOp>
          >
        , if_<
            detail::is_na<InOrNA>
          , binary_transform<Seq, SeqOrOp, OpOrIn>
          , binary_transform<Seq, SeqOrOp, OpOrIn, InOrNA>
          >
        , if_<
            detail::is_na<OpOrIn>
          , unary_transform<Seq, SeqOrOp>
          , unary_transform<Seq, SeqOrOp, OpOrIn>
          >
        >;
    
    
    template <
        class Seq
      , class SeqOrOp
      , class OpOrIn = detail::na
      , class InOrNA = detail::na
      >
    using transform_t = typename transform<Seq, SeqOrOp, OpOrIn, InOrNA>::type;
    
    
    template <
        class Seq
      , class SeqOrOp
      , class OpOrIn = detail::na
      , class InOrNA = detail::na
      >
    using reverse_transform =
      eval_if_t<
          and_<
            is_sequence<Seq>
          , is_sequence<SeqOrOp>
          >
        , if_<
            detail::is_na<InOrNA>
          , reverse_binary_transform<Seq, SeqOrOp, OpOrIn>
          , reverse_binary_transform<Seq, SeqOrOp, OpOrIn, InOrNA>
          >
        , if_<
            detail::is_na<OpOrIn>
          , reverse_unary_transform<Seq, SeqOrOp>
          , reverse_unary_transform<Seq, SeqOrOp, OpOrIn>
          >
        >;
    
    
    template <
        class Seq
      , class SeqOrOp
      , class OpOrIn = detail::na
      , class InOrNA = detail::na
      >
    using reverse_transform_t = typename 
      reverse_transform<Seq, SeqOrOp, OpOrIn, InOrNA>::type;
    
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_ALGORITHM_TRANSFORM_HPP */