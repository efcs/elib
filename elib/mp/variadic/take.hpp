#ifndef ELIB_MP_VARIADIC_TAKE_HPP
#define ELIB_MP_VARIADIC_TAKE_HPP

# include <elib/mp/variadic/fwd.hpp>
# include <elib/mp/identity.hpp>
# include <cstddef>

namespace elib 
{
  namespace mp
  {

    template <class Seq, std::size_t N>
    struct variadic_take;
    
    
    template <
      template <class...> class Seq
    , class ...Args
    , std::size_t N
    >
    struct variadic_take<Seq<Args...>, N> 
      : detail::variadic_take_impl<Seq<>, N>::template
        apply<Args...>
    {};
    
    template <class Seq, class ...Args, std::size_t N>
    struct variadic_take<Seq(Args...), N>
      : detail::variadic_take_impl<Seq, N>::template apply<Args...>
    {};
    
    template <class Seq, std::size_t N>
    using variadic_take_t = typename variadic_take<Seq, N>::type;
    
    
    namespace detail
    {
      
      template <class Seq>
      struct variadic_take_impl<Seq, 0, false>
      {
        template <class...>
        using apply = identity<Seq>;
      };
      
      
      template <
          template <class...> class Seq
        , class ...SeqArgs
        >
      struct variadic_take_impl<Seq<SeqArgs...>, 1, false>
      {
        template <class A1, class ...Rest>
        using apply = identity< Seq<SeqArgs..., A1> >;
      };
      
      template <
          template <class...> class Seq
        , class ...SeqArgs
        >
      struct variadic_take_impl<Seq<SeqArgs...>, 2, false>
      {
        template <class A1, class A2, class ...Rest>
        using apply = identity< Seq<SeqArgs..., A1, A2> >;
      };
      
      template <
          template <class...> class Seq
        , class ...SeqArgs
        >
      struct variadic_take_impl<Seq<SeqArgs...>, 3, false>
      {
        template <class A1, class A2, class A3, class ...Rest>
        using apply = identity< Seq<SeqArgs..., A1, A2, A3> >;
      };
      
      template <
          template <class...> class Seq
        , class ...SeqArgs
        >
      struct variadic_take_impl<Seq<SeqArgs...>, 4, false>
      {
        template <class A1, class A2, class A3, class A4, class ...Rest>
        using apply = identity< Seq<SeqArgs..., A1, A2, A3, A4> >;
      };
      
      template <
          template <class...> class Seq
        , class ...SeqArgs
        , std::size_t N
        >
      struct variadic_take_impl<Seq<SeqArgs...>, N, true>
      {
        template <class A1, class A2, class A3, class A4, class A5, class ...Rest>
        using apply = typename
          variadic_take_impl<Seq<SeqArgs..., A1, A2, A3, A4, A5>, N - 5>
            ::template apply<Rest...>;
      };
      
      template <class Seq, class ...As>
      struct variadic_take_impl<Seq(As...), 1, false>
      {
        template <class A1, class ...>
        using apply = identity< Seq(As...) >;
      };
      
      template <class Seq, class ...As>
      struct variadic_take_impl< Seq(As...), 2, false>
      {
        template <class A1, class A2, class ...>
        using apply = identity< Seq(As..., A1, A2) >;
      };
      
      template <class Seq, class ...As>
      struct variadic_take_impl< Seq(As...), 3, false>
      {
        template <class A1, class A2, class A3, class...>
        using apply = identity< Seq(As..., A1, A2, A3) >;
      };
      
      template <class Seq, class ...As>
      struct variadic_take_impl< Seq(As...), 4, false>
      {
        template <class A1, class A2, class A3, class A4, class...>
        using apply = identity< Seq(As..., A1, A2, A3, A4) >;
      };
      
      template <class Seq, class ...As, std::size_t N>
      struct variadic_take_impl< Seq(As...), N, true >
      {
        template <class A1, class A2, class A3, class A4, class A5, class ...Rest>
        using apply = typename variadic_take_impl<Seq(As..., A1, A2, A3, A4, A5), N - 5>
          ::template apply<Rest...>;
      };
      
    }                                                       // namespace detail
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_VARIADIC_TAKE2_HPP */