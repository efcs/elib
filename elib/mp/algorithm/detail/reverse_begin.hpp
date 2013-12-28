#ifndef ELIB_MP_ALGORITHM_DETAIL_REVERSE_BEGIN_HPP
#define ELIB_MP_ALGORITHM_DETAIL_REVERSE_BEGIN_HPP

# include <elib/mp/if.hpp>
# include <elib/mp/iterator.hpp>
# include <elib/mp/same_type.hpp>
# include <elib/mp/sequence.hpp>

namespace elib 
{
  namespace mp
  {
    namespace detail
    {
      
      template <class Seq>
      using reverse_begin_t = 
        eval_if_t<
              same_type<begin_t<Seq>, end_t<Seq>>
            , end<Seq>
            , prior< end_t<Seq> >
            >;
      
      
      template <class Seq>
      struct reverse_begin
      {
        using type = reverse_begin_t<Seq>;
      };
      
      
      
    }                                                       // namespace detail
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_ALGORITHM_DETAIL_REVERSE_BEGIN_HPP */
