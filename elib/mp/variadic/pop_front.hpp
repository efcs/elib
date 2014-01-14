#ifndef ELIB_MP_VARIADIC_POP_FRONT_HPP
#define ELIB_MP_VARIADIC_POP_FRONT_HPP

# include <elib/mp/variadic/fwd.hpp>

namespace elib 
{
  namespace mp
  {
    
    template <class Seq>
    using variadic_pop_front_t = typename variadic_pop_front<Seq>::type;
    
    
    template <template <class...> class Seq, class First, class ...Rest>
    struct variadic_pop_front< Seq<First, Rest...> >
    {
      using type = Seq<Rest...>;
    };
    
    
    template <class Seq, class First, class ...Rest>
    struct variadic_pop_front< Seq(First, Rest...) >
    {
      using type = Seq(Rest...);
    };
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_VARIADIC_POP_FRONT_HPP */