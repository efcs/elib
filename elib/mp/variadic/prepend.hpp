#ifndef ELIB_MP_VARIADIC_PREPEND_HPP
# define ELIB_MP_VARIADIC_PREPEND_HPP

# include <elib/mp/variadic/fwd.hpp>

namespace elib 
{
  namespace mp
  {
    
    template <class Seq, class ...Args>
    struct variadic_prepend;
    
    
    template <
        template <class...> class Seq
      , class ...SeqArgs
      , class ...Args
      >
    struct variadic_prepend< Seq<SeqArgs...>, Args... >
    {
      using type = Seq<Args..., SeqArgs...>;
    };
    
    template <class Seq, class ...As, class ...Args>
    struct variadic_prepend< Seq(As...), Args... >
    {
      using type = Seq(Args..., As...);
    };
    
    
    template <class Seq, class ...Args>
    using variadic_prepend_t = typename variadic_prepend<Seq, Args...>::type;
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_VARIADIC_PREPEND_HPP */