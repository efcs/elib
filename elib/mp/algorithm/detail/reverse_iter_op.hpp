#ifndef ELIB_MP_ALGORITHM_DETAIL_REVERSE_ITER_OP_HPP
#define ELIB_MP_ALGORITHM_DETAIL_REVERSE_ITER_OP_HPP

# include <elib/mp/identity.hpp>
# include <elib/mp/if.hpp>
# include <elib/mp/iterator.hpp>
# include <elib/mp/logical.hpp>
# include <elib/mp/protect.hpp>
# include <elib/mp/same_type.hpp>


namespace elib 
{
  namespace mp
  {
    namespace detail
    {
      
      
      template <class Begin, class End>
      struct reverse_iter_op_impl 
      {
        template <class Iter>
        using apply = 
          eval_if_t<
              or_<
                  same_type<Begin, Iter>
                , same_type<End, Iter>
              >
            , identity< End >
            , prior< Iter >
            >;
      };
      
      
      template <class Begin, class End>
      using reverse_iter_op = protect< reverse_iter_op_impl<Begin, End> >;
      
    }                                                       // namespace detail
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_ALGORITHM_DETAIL_REVERSE_ITER_OP_HPP */