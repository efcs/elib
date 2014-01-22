#ifndef ELIB_MP_ALGORITHM_SEQUENCE_EQUAL_HPP
#define ELIB_MP_ALGORITHM_SEQUENCE_EQUAL_HPP

# include <elib/mp/algorithm/iter_fold_if.hpp>
# include <elib/mp/algorithm/detail/deref_lambda.hpp>
# include <elib/mp/apply_wrap.hpp>
# include <elib/mp/arg.hpp>
# include <elib/mp/if.hpp>
# include <elib/mp/iterator.hpp>
# include <elib/mp/lambda.hpp>
# include <elib/mp/logical.hpp>
# include <elib/mp/pair.hpp>
# include <elib/mp/protect.hpp>
# include <elib/mp/sequence.hpp>
# include <elib/mp/same_type.hpp>
# include <elib/mp/integral_constant.hpp>

namespace elib 
{
  namespace mp
  {
    namespace detail
    {
      
      template <class Seq1, class Seq2, class Pred>
      struct sequence_equal_pred
      {
        template <class State, class Iter>
        using apply = 
          and_<
              not_< same_type<Iter, end_t<Seq1>> >
            , not_< same_type<State, end_t<Seq2>> >
            , apply_wrap< detail::binary_deref_lambda<Pred>, State, Iter >
          >;
      };
      
      template <
          class Seq1
        , class Seq2
        , class Pred
        >
      struct sequence_equal_impl
      {
        
        using result_ =
          iter_foldl_if<
            Seq1
          , begin_t<Seq2>
          , next<_1>
          , protect< sequence_equal_pred<Seq1, Seq2, Pred> >
          >;                       
        
        using type = 
          and_<
              same_type<typename result_::iterator, end_t<Seq1> >
            , same_type<typename result_::state, end_t<Seq2> >
            >;
      };
      
    }                                                       // namespace detail
    
    
    template <
        class Seq1
      , class Seq2
      , class Pred = same_type<_1, _2>
    >
    struct sequence_equal 
      : detail::sequence_equal_impl< Seq1, Seq2, Pred >::type
    {};
      
    
    template <
        class Seq1
      , class Seq2
      , class Pred = same_type<_1, _2>
      >
    using sequence_equal_t = typename
      detail::sequence_equal_impl<Seq1, Seq2, Pred>::type;
    
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_ALGORITHM_SEQUENCE_EQUAL_HPP */
