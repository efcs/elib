#ifndef ELIB_MP_VARIADIC_DETAIL_AT_IMPL_HPP
#define ELIB_MP_VARIADIC_DETAIL_AT_IMPL_HPP

# include <elib/mp/variadic/fwd.hpp>
# include <elib/mp/detail/eat_pod.hpp>

namespace elib 
{
  namespace mp
  {
    namespace detail
    {
      
      template <template <class...> class Seq, class ...Ignored>
      struct variadic_at_impl< Seq<Ignored...> >
      {
        template <class T, class ...Rest>
          static typename T::type 
        eval(eat_pod<Ignored>..., T*, Rest*...);
        
      };
      
      
      
    }                                                       // namespace detail
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_VARIADIC_DETAIL_AT_IMPL_HPP */