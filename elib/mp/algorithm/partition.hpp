#ifndef ELIB_MP_ALGORITHM_PARTITION_HPP
# define ELIB_MP_ALGORITHM_PARTITION_HPP

# include <elib/mp/algorithm/inserter.hpp>
# include <elib/mp/algorithm/iter_fold.hpp>
# include <elib/mp/apply_wrap.hpp>
# include <elib/mp/if.hpp>
# include <elib/mp/lambda.hpp>
# include <elib/mp/pair.hpp>
# include <elib/mp/protect.hpp>
# include <elib/mp/sequence.hpp>

namespace elib 
{
  namespace mp
  {
    namespace detail
    {
      
      
      template < class In1, class In2, class Pred>
      struct partition_op_impl
      {
        using Op1 = lambda<typename In1::operation>;
        using Op2 = lambda<typename In2::operation>;
        
        template <class State, class Iter>
        using apply = 
          if_< 
              apply_wrap<Pred, deref_t<Iter>>
            , pair<
                  apply_wrap_t<Op1, first_t<State>, deref_t<Iter>>
                , second_t<State>
                >
            , pair<
                  first_t<State>
                , apply_wrap_t<Op2, second_t<State>, deref_t<Iter>> 
                >
            >;
      };
      
      
      template <class In1, class In2, class Pred>
      using partition_op = protect< partition_op_impl<In1, In2, Pred> >;
      
      
    }                                                       // namespace detail
    
    
    template <
        class Seq
      , class Pred
      , class In1 = back_inserter<clear_t<Seq>>
      , class In2 = back_inserter<clear_t<Seq>>
      >
    struct partition
      : iter_foldl<
          Seq
        , pair< typename In1::state, typename In2::state >
        , detail::partition_op<In1, In2, lambda<Pred> >
        >
    {};
    
    
    template <
        class Seq
      , class Pred
      , class In1 = back_inserter<clear_t<Seq>>
      , class In2 = back_inserter<clear_t<Seq>>
      >
    using partition_t = typename partition<Seq, Pred, In1, In2>::type;
    
    
    template <
        class Seq
      , class Pred
      , class In1 = front_inserter<clear_t<Seq>>
      , class In2 = front_inserter<clear_t<Seq>>
      >
    struct reverse_partition
      : iter_foldr<
          Seq
        , pair< typename In1::state, typename In2::state >
        , detail::partition_op< In1, In2, lambda<Pred> >
        >
    {};
    
    
    template <
        class Seq
      , class Pred
      , class In1 = front_inserter<clear_t<Seq>>
      , class In2 = front_inserter<clear_t<Seq>>
      >
    using reverse_partition_t = typename
      reverse_partition<Seq, Pred, In1, In2>::type;
      
      
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_ALGORITHM_PARTITION_HPP */