#ifndef ELIB_MP_VARIADIC_DETAIL_APPEND_IMPL_HPP
#define ELIB_MP_VARIADIC_DETAIL_APPEND_IMPL_HPP

# include <elib/mp/variadic/fwd.hpp>

namespace elib 
{
  namespace mp
  {
    namespace detail
    {
      
      template <template <class...> class S, class ...SArgs, class ...ToAppend>
      struct variadic_append_impl< S<SArgs...>, ToAppend...>
      {
        using type = S<SArgs..., ToAppend...>;
      };
      
    }                                                       // namespace detail
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_VARIADIC_DETAIL_APPEND_IMPL_HPP */
