#ifndef ELIB_MP_VARIADIC_PREPEND_IMPL_HPP
#define ELIB_MP_VARIADIC_PREPEND_IMPL_HPP

# include <elib/mp/variadic/fwd.hpp>

namespace elib 
{
  namespace mp
  {
    namespace detail
    {
      
      template <template <class...> struct S, class ...SArgs, class ...ToPrepend>
      struct variadic_prepend_impl<S<SArgs...>, ToPrepend...>
      {
        using type = S<ToPrepend..., SArgs...>;
      };
      
    }                                                       // namespace detail
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_VARIADIC_PREPEND_IMPL_HPP */