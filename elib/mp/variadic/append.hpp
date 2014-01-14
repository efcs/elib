#ifndef ELIB_MP_VARIADIC_APPEND_HPP
# define ELIB_MP_VARIADIC_APPEND_HPP

# include <elib/mp/variadic/fwd.hpp>

namespace elib 
{
  namespace mp
  {
    
    template <class Seq, class ...Args>
    struct variadic_append;
    
    
    template <
        template <class...> class Seq
      , class ...SeqArgs
      , class ...Args
      >
    struct variadic_append< Seq<SeqArgs...>, Args... >
    {
      using type = Seq<SeqArgs..., Args...>;
    };
    
    template <class Seq, class ...As, class ...Args>
    struct variadic_append< Seq(As...), Args... >
    {
      using type = Seq(As..., Args...);
    };
    
    template <class Seq, class ...Args>
    using variadic_append_t = typename variadic_append<Seq, Args...>::type;
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_VARIADIC_APPEND_HPP */