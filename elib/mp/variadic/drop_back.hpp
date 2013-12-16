#ifndef ELIB_MP_VARIADIC_DROP_BACK_HPP
#define ELIB_MP_VARIADIC_DROP_BACK_HPP

# include <elib/mp/variadic/fwd.hpp>
# include <elib/mp/param_pack/param_pack.hpp>

# include <cstddef>

namespace elib 
{
  namespace mp
  {
    
    namespace detail
    {
      template <std::size_t N, class Pack, class ...Args>
      struct drop_back_impl;
    }                                                       // namespace detail
    
    
    template <std::size_t N, class ...Args>
    struct drop_back : detail::drop_back_impl<N, param_pack<>, Args...>
    {};
    
    
    template <std::size_t N, class ...Args>
    using drop_back_t = 
      typename detail::drop_back_impl<N, param_pack<>, Args...>::type;
    
    
    namespace detail
    {
      
      template <class Pack, class ...Args>
      struct drop_back_impl<0, Pack, Args...>
      {
        using type = Pack;
      };
      
      template <class ...PArgs
        , class A1
        , class ...Args
        >
      struct drop_back_impl<1, param_pack<PArgs...>
        , A1, Args...
        >
      {
        using type = param_pack<PArgs..., A1>;
      };
      
      
      template <class ...PArgs
        , class A1, class A2, class ...Args
        >
      struct drop_back_impl<2, param_pack<PArgs...>
        , A1, A2, Args...
        >
      {
        using type = param_pack<PArgs..., A1, A2>;
      };
      
      
      template <class ...PArgs
        , class A1, class A2, class A3, class ...Args
      >
      struct drop_back_impl<3, param_pack<PArgs...>
        , A1, A2, A3, Args...
        >
      {
        using type = param_pack<PArgs..., A1, A2, A3>;
      };
      
      
      template <class ...PArgs
        , class A1, class A2, class A3, class A4, class ...Args
      >
      struct drop_back_impl<5, param_pack<PArgs...>
        , A1, A2, A3, A4, Args...
        >
      {
        using type = param_pack<PArgs..., A1, A2, A3, A4>;
      };
      
      
      template <class ...PArgs
        , class A1, class A2, class A3, class A4, class A5
        , class ...Args
      >
      struct drop_back_impl<
          5
        , param_pack<PArgs...>
        , A1, A2, A3, A4, A5, Args...
        >
      {
        using type = param_pack<PArgs..., A1, A2, A3, A4, A5>;
      };
      
      
      template <std::size_t N, class ...PArgs 
        , class A1, class A2, class A3, class A4, class A5
        , class ...Args
      >
      struct drop_back_impl<
          N
        , param_pack<PArgs...>
        , A1, A2, A3, A4, A5
        , Args...
      > 
      : drop_back_impl<
          N-5
        , param_pack<PArgs..., A1, A2, A3, A4, A5>
        , Args...
      >
      {};
    }                                                       // namespace detail
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_VARIADIC_DROP_BACK_HPP */