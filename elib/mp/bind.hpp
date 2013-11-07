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
      
      template <class T>
      struct resolver
      {
        template <class ...Args>
        struct apply
        {
          typedef T type;
        };
      };
      
      template <std::size_t N>
      struct resolver<arg<N>>
      {
        template <class ...Args>
        struct apply : apply_wrap<arg<N>, Args...>
        {};
      };
      
      template <class F, class ...Args>
      struct resolver<bind<F, Args...>>
      {
        template <class ...Args2>
        struct apply : apply_wrap<bind<F, Args...>, Args2...>
        {};
      };
      
      template <typename T, typename ...Args>
      struct resolve_bind_arg
      {
        typedef T type;
      };
      
      template <typename F, typename ...Args1, typename ...Args2>
      struct resolve_bind_arg<bind<F, Args1...>, Args2...>
      {
        typedef apply_wrap_t<bind<F, Args1...>, Args2...> type;
      };
      
      template <std::size_t N, typename ...Args>
      struct resolve_bind_arg<arg<N>, Args...>
      {
        typedef apply_wrap_t<arg<N>, Args...> type;
      };
      
      template <typename ...Args>
      using resolve_bind_arg_t = typename resolve_bind_arg<Args...>::type;
      
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