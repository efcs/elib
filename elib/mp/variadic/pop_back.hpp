#ifndef ELIB_MP_VARIADIC_POP_BACK_HPP
#define ELIB_MP_VARIADIC_POP_BACK_HPP

# include <elib/mp/variadic/fwd.hpp>
# include <elib/mp/variadic/take.hpp>

namespace elib 
{
  namespace mp
  {
    template <class Seq>
    using variadic_pop_back_t = typename variadic_pop_back<Seq>::type;
    
    template <template <class...> class Seq, class First, class ...Rest>
    struct variadic_pop_back< Seq<First, Rest...> >
      : variadic_take<Seq<First, Rest...>, sizeof...(Rest)>
    {};
    
    template <class Seq, class First, class ...Rest>
    struct variadic_pop_back< Seq(First, Rest...) >
      : variadic_take<Seq(First, Rest...), sizeof...(Rest)>
    {};
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_VARIADIC_POP_BACK_HPP */