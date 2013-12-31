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
        template <class...> class Seq
      , class ...LHS
      , class ...RHS
      >
    struct variadic_join< Seq<LHS...>, Seq<RHS...> >
    {
      using type = Seq< LHS..., RHS... >;
    };
    
  }
}                                                           // namespace elib
#endif /* ELIB_MP_VARIADIC_JOIN_HPP */