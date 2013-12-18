#ifndef ELIB_MP_VARIADIC_DETAIL_DROP_IMPL_HPP
#define ELIB_MP_VARIADIC_DETAIL_DROP_IMPL_HPP

# include <elib/mp/variadic/fwd.hpp>
# include <elib/mp/detail/eat_pod.hpp>

namespace elib 
{
  namespace mp
  {
    namespace detail
    {
      
      template <template <class...> class Seq, class ...Ignored>
      struct variadic_drop_impl< Seq<Ignored...> >
      {
        template <class ...Back>
          static Seq<typename Back::type...>
        eval(eat_pod<Ignored>..., Back*...);
      };
      
      
      
    }                                                       // namespace detail
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_VARIADIC_DETAIL_DROP_IMPL_HPP */
