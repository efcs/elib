#ifndef ELIB_MP_ALGORITHM_UNIQUE_HPP
# define ELIB_MP_ALGORITHM_UNIQUE_HPP

# include <elib/mp/algorithm/copy.hpp>
# include <elib/mp/algorithm/inserter.hpp>
# include <elib/mp/algorithm/iter_fold.hpp>
# include <elib/mp/arg.hpp>
# include <elib/mp/apply.hpp>
# include <elib/mp/apply_wrap.hpp>
# include <elib/mp/if.hpp>
# include <elib/mp/iterator.hpp>
# include <elib/mp/lambda.hpp>
# include <elib/mp/logical.hpp>
# include <elib/mp/pair.hpp>
# include <elib/mp/na.hpp>
# include <elib/mp/same_type.hpp>
# include <elib/mp/sequence.hpp>

namespace elib 
{
  namespace mp
  {
    namespace detail
    {
      
      template <class In, class Pred>
      struct unique_op_impl
      {
        using Op = lambda<typename In::operation>;
        
        template <class State, class Iter>
        using apply =
          if_<
              or_<
                  is_na< second_t<State> >
                , apply_wrap<Pred, second_t<State>, deref_t<Iter>>
                >
            , pair<
                apply_wrap_t<Op, first_t<State>, deref_t<Iter>>
              , deref_t<Iter>
              >
            , State
            >;
      };
      
      
      template <class In, class Pred>
      using unique_op = protect< unique_op_impl<In, Pred> >;
      

    }                                                       // namespace detail
    
    template <
        class Seq
      , class Pred
      , typename In = back_inserter<clear_t<Seq>>
      >
    struct unique
      : first<
          iter_foldl_t<
              Seq
            , pair<typename In::state, na>
            , detail::unique_op< In, lambda<Pred> >
            >
        >
    {};
    
    
    template <
        class Seq
      , class Pred
      , typename In = back_inserter<clear_t<Seq>>
      >
    using unique_t = typename unique<Seq, Pred, In>::type; 
    
    
    template <
        class Seq
      , class Pred
      , typename In = front_inserter<clear_t<Seq>>
      >
    struct reverse_unique
      : first<
          iter_foldr_t<
            Seq
          , pair< typename In::state, na >
          , detail::unique_op< In, lambda<Pred> >
          >
        >
    {};
    
    
    template <
        class Seq
      , class Pred
      , typename In = front_inserter<clear_t<Seq>>
      >
    using reverse_unique_t = typename reverse_unique<Seq, Pred, In>::type; 
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_ALGORITHM_UNIQUE_HPP */