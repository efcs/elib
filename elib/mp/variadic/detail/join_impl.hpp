#ifndef ELIB_MP_VARIADIC_DETAIL_JOIN_IMPL_HPP
#define ELIB_MP_VARIADIC_DETAIL_JOIN_IMPL_HPP

# include <elib/mp/variadic/fwd.hpp>

namespace elib 
{
  namespace mp
  {
    namespace detail
    {
     
      template <template <class...> class S, class ...Left, class ...Right>
      struct variadic_join_impl<S<Left...>, S<Right...>>
      {
        using type = S<Left..., Right...>;
      };
      
    }                                                       // namespace detail
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_VARIADIC_DETAIL_JOIN_IMPL_HPP */