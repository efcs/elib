#ifndef ELIB_MP_VARIADIC_FRONT_HPP
#define ELIB_MP_VARIADIC_FRONT_HPP

# include <elib/mp/variadic/fwd.hpp>
# include <elib/mp/variadic/at.hpp>

namespace elib 
{
  namespace mp
  {
    template <class Seq>
    struct variadic_front 
      : variadic_at<Seq, 0>
    {};
    
    template <class Seq>
    using variadic_front_t = variadic_at_t<Seq, 0>;
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_VARIADIC_FRONT_HPP */