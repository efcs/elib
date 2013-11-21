#ifndef ELIB_MP_BIND_HPP
# define ELIB_MP_BIND_HPP

# include <elib/mp/config.hpp>
# include <elib/mp/arg.hpp>
# include <elib/mp/apply_wrap.hpp>

# include <cstddef>

namespace elib 
{
  namespace mp
  {
    
    template <class F, class ...Args> struct bind;
    
    namespace detail
    {
      
      template <typename T, typename ...Args>
      struct resolve_bind_arg
      { using type = T; };
      
      template <typename F, typename ...Args1, typename ...Args2>
      struct resolve_bind_arg<bind<F, Args1...>, Args2...>
      {
        using type = 
          apply_wrap_t<
            bind<F, Args1...>
            , Args2...
          >;
      };
      
      template <std::size_t N, typename ...Args>
      struct resolve_bind_arg<arg<N>, Args...>
      {
        using type = apply_wrap_t<arg<N>, Args...>;
      };
      
      template <typename ...Args>
      using resolve_bind_arg_t =
        typename resolve_bind_arg<Args...>::type;
      
    }                                                       // namespace detail
    
    template <class F, class ...Args>
    struct bind
    {
      template <class ...Args2>
      struct apply
        : apply_wrap<
            detail::resolve_bind_arg_t<F, Args2...>
            , detail::resolve_bind_arg_t<Args, Args2...>...
          >
      {};
    };
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_BIND_HPP */