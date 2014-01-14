#ifndef ELIB_MP_VARIADIC_CONCAT_HPP
#define ELIB_MP_VARIADIC_CONCAT_HPP

# include <elib/mp/variadic/fwd.hpp>


namespace elib 
{
  namespace mp
  {
    
    template <class LHS, class RHS>
    struct variadic_concat;
    
    template <
        template <class...> class L0, class ...A0
      , template <class...> class L1, class ...A1
    >
    struct variadic_concat< L0<A0...>, L1<A1...> >
    {
      using type = L0<A0..., A1...>;
    };
    
    template <
        template <class...> class L0, class ...A0
      , class L1, class ...A1
    >
    struct variadic_concat< L0<A0...>, L1(A1...) >
    {
      using type = L0<A0..., A1...>;
    };
    
    template <
        class L0, class ...A0
      , template <class...> class L1, class ...A1
    >
    struct variadic_concat< L0(A0...), L1<A1...> >
    {
      using type = L0(A0..., A1...);
    };
    
    template <
        class L0, class ...A0
      , class L1, class ...A1
    >
    struct variadic_concat< L0(A0...), L1(A1...) >
    {
      using type = L0(A0..., A1...);
    };
    
    
    template <class LHS, class RHS>
    using variadic_concat_t = typename variadic_concat<LHS, RHS>::type;
    
  }
}                                                           // namespace elib
#endif /* ELIB_MP_VARIADIC_CONCAT_HPP */