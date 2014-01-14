#ifndef ELIB_MP_VARIADIC_BACK_HPP
#define ELIB_MP_VARIADIC_BACK_HPP

# include <elib/mp/variadic/fwd.hpp>
# include <elib/mp/variadic/at.hpp>

namespace elib 
{
  namespace mp
  {
    
    template <template <class...> class Seq, class First, class ...Rest>
    struct variadic_back< Seq<First, Rest...> >
      : variadic_at< Seq<First, Rest...>, sizeof...(Rest)>
    {};
    
    template <class Seq, class First, class ...Rest>
    struct variadic_back< Seq(First, Rest...) >
      : variadic_at< Seq(First, Rest...), sizeof...(Rest) >
    {};
    
    template <class Seq>
    using variadic_back_t = typename variadic_back<Seq>::type;
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_VARIADIC_BACK_HPP */