#ifndef ELIB_MP_VARIADIC_JOIN_HPP
# define ELIB_MP_VARIADIC_JOIN_HPP

# include <elib/mp/variadic/fwd.hpp>


namespace elib 
{
  namespace mp
  {
    
    template <class LHS, class RHS>
    struct variadic_join;
    
    template <
        template <class...> class L0, class ...A0
      , template <class...> class L1, class ...A1
    >
    struct variadic_join< L0<A0...>, L1<A1...> >
    {
      using type = L0<A0..., A1...>;
    };
    
    template <
        template <class...> class L0, class ...A0
      , class L1, class ...A1
    >
    struct variadic_join< L0<A0...>, L1(A1...) >
    {
      using type = L0<A0..., A1...>;
    };
    
    template <
        class L0, class ...A0
      , template <class...> class L1, class ...A1
    >
    struct variadic_join< L0(A0...), L1<A1...> >
    {
      using type = L0(A0..., A1...);
    };
    
    template <
        class L0, class ...A0
      , class L1, class ...A1
    >
    struct variadic_join< L0(A0...), L1(A1...) >
    {
      using type = L0(A0..., A1...);
    };
    
    
    template <class LHS, class RHS>
    using variadic_join_t = typename variadic_join<LHS, RHS>::type;
    
  }
}                                                           // namespace elib
#endif /* ELIB_MP_VARIADIC_JOIN_HPP */