#ifndef ELIB_MP_VARIADIC_EMPTY_HPP
#define ELIB_MP_VARIADIC_EMPTY_HPP

# include <elib/mp/variadic/fwd.hpp>
# include <elib/aux.hpp>

namespace elib 
{
  namespace mp
  {
    template <class Seq>
    using variadic_empty_t = typename variadic_empty<Seq>::type;
    
    template <template <class...> class Seq, class ...As>
    struct variadic_empty< Seq<As...> >
      : bool_< sizeof...(As) == 0 >
    {};
    
    template <class Seq, class ...As>
    struct variadic_empty< Seq(As...) >
      : bool_< sizeof...(As) == 0 >
    {};
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_VARIADIC_EMPTY_HPP */