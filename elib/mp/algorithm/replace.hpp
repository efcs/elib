#ifndef ELIB_MP_ALGORITHM_REPLACE_HPP
#define ELIB_MP_ALGORITHM_REPLACE_HPP

# include <elib/mp/algorithm/inserter.hpp>
# include <elib/mp/algorithm/iter_fold.hpp>
# include <elib/mp/arg.hpp>
# include <elib/mp/apply_wrap.hpp>
# include <elib/mp/iterator.hpp>
# include <elib/mp/lambda.hpp>
# include <elib/mp/protect.hpp>
# include <elib/mp/sequence.hpp>
# include <elib/aux.hpp>

namespace elib 
{
  namespace mp
  {
    namespace detail
    {
      
      template <class In, class Pred, class New>
      struct replace_if_op_impl
      {
        using Op = lambda< typename In::operation >;
        
        template <class State, class Iter>
        using apply = 
          eval_if<
              apply_wrap<Pred, deref_t<Iter>>
            , apply_wrap<Op, State, New>
            , apply_wrap<Op, State, deref_t<Iter>>
            >;
      };
      
      
      template <class In, class Pred, class New>
      using replace_if_op = protect< replace_if_op_impl<In, Pred, New> >;
      
    }                                                       // namespace detail
    
    
    template <
        class Seq
      , class Pred, class New
      , class In = back_inserter<clear_t<Seq>>
      >
    struct replace_if
      : iter_foldl<
            Seq 
          , typename In::state
          , detail::replace_if_op< In, lambda<Pred>, New > 
          >
    {};
    
    
    template <
        class Seq
      , class Pred, class New
      , class In = back_inserter<clear_t<Seq>>
      >
    using replace_if_t = typename replace_if<Seq, Pred, New, In>::type;
    
    
    template <
        class Seq
      , class Old, class New
      , class In = back_inserter<clear_t<Seq>>
      >
    struct replace
      : replace_if<Seq, aux::same_type<Old, _1>, New, In>
    {};
    
    
    template <
        class Seq
      , class Old, class New
      , class In = back_inserter<clear_t<Seq>>
      >
    using replace_t = typename replace<Seq, Old, New, In>::type;
    
    
    template <
        class Seq
      , class Pred, class New
      , class In = front_inserter<clear_t<Seq>>
      >
    struct reverse_replace_if
      : iter_foldr<
          Seq
        , typename In::state
        , detail::replace_if_op< In, lambda<Pred>, New >
        >
    {};
    
    
    template <
        class Seq
      , class Pred, class New
      , class In = front_inserter<clear_t<Seq>>
      >
    using reverse_replace_if_t = 
      typename reverse_replace_if<Seq, Pred, New, In>::type;
    
    
    template <
        class Seq
      , class Old, class New
      , class In = front_inserter<clear_t<Seq>>
      >
    struct reverse_replace
      : reverse_replace_if<Seq, aux::same_type<Old, _1>, New, In>
    {};
    
    
    template <
        class Seq
      , class Old, class New
      , class In = front_inserter<clear_t<Seq>>
      >
    using reverse_replace_t = typename reverse_replace<Seq, Old, New, In>::type;
    
  }
}                                                           // namespace elib
#endif /* ELIB_MP_ALGORITHM_REPLACE_HPP */