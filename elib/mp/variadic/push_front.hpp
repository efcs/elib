#ifndef ELIB_MP_VARIADIC_PUSH_FRONT_HPP
#define ELIB_MP_VARIADIC_PUSH_FRONT_HPP

# include <elib/mp/variadic/fwd.hpp>
# include <elib/mp/variadic/prepend.hpp>

namespace elib 
{
  namespace mp
  {
    
    template <class Seq, class T>
    struct variadic_push_front
      : variadic_prepend<Seq, T>
    {};
    
    template <class Seq, class T>
    using variadic_push_front_t = variadic_prepend_t<Seq, T>;
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_VARIADIC_PUSH_FRONT_HPP */