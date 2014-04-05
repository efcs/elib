#ifndef ELIB_MP_ALGORITHM_DETAIL_ITER_FOLD_IF_PRED_HPP
# define ELIB_MP_ALGORITHM_DETAIL_ITER_FOLD_IF_PRED_HPP

# include <elib/mp/apply_wrap.hpp>
# include <elib/mp/logical.hpp>
# include <elib/mp/protect.hpp>
# include <elib/aux.hpp>

namespace elib 
{
  namespace mp
  {
    namespace detail
    {
      
      template <class Pred, class End>
      struct iter_fold_if_pred_impl
      {
        template <class State, class Iter>
        using apply = 
          and_<
              not_<aux::is_same<Iter, End>>
            , apply_wrap<Pred, State, Iter> 
          >;
      };
      
      
      template <class Pred, class End>
      using iter_fold_if_pred = 
        protect<
          iter_fold_if_pred_impl<
              Pred
            , End
            >
        >;
      
    }                                                       // namespace detail
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_ALGORITHM_DETAIL_ITER_FOLD_IF_PRED_HPP */
