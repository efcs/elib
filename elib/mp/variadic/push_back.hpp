#ifndef ELIB_MP_VARIADIC_PUSH_BACK_HPP
#define ELIB_MP_VARIADIC_PUSH_BACK_HPP

# include <elib/mp/variadic/fwd.hpp>
# include <elib/mp/variadic/append.hpp>

namespace elib 
{
  namespace mp
  {
    template <class Seq, class T>
    struct variadic_push_back
      : variadic_append<Seq, T>
    {};
    
    template <class Seq, class T>
    using variadic_push_back_t = variadic_append_t<Seq, T>;
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_VARIADIC_PUSH_BACK_HPP */