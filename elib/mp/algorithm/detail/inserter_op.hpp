#ifndef ELIB_MP_ALGORITHM_DETAIL_INSERTER_OP_HPP
#define ELIB_MP_ALGORITHM_DETAIL_INSERTER_OP_HPP

# include <elib/mp/algorithm/inserter.hpp>
# include <elib/mp/apply_wrap.hpp>
# include <elib/mp/if.hpp>
# include <elib/mp/identity.hpp>
# include <elib/mp/iterator.hpp>
# include <elib/mp/lambda.hpp>
# include <elib/mp/protect.hpp>

namespace elib 
{
  namespace mp
  {
    namespace detail
    {
      
      template <class In>
      struct inserter_op_impl
      {
        using Op = lambda<typename In::operation>;
        
        template <class State, class Iter>
        using apply = apply_wrap<Op, State, deref_t<Iter>>;
      };
      
      
      template <class In>
      using inserter_op = protect< inserter_op_impl<In> >;
      
      
      template <class In, class Pred>
      struct inserter_op_if_impl
      {
        using Op = lambda<typename In::operation>;
        
        template <class State, class Iter>
        using apply = 
          eval_if_<
              apply_wrap<Pred, deref_t<Iter>>
            , apply_wrap<Op, State, deref_t<Iter>>
            , identity< State >
          >;
      };
      
      
      template <class In, class Pred>
      using inserter_op_if = protect< inserter_op_if_impl<In, Pred> >;
    }                                                       // namespace detail
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_ALGORITHM_DETAIL_INSERTER_OP_HPP */