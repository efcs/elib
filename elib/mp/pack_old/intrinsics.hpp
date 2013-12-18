#ifndef ELIB_MP_PACK_INTRINSICS_HPP
#define ELIB_MP_PACK_INTRINSICS_HPP

# include <elib/mp/pack/fwd.hpp>
# include <elib/mp/pack/pack.hpp>
# include <elib/mp/pack/iterator.hpp>
# include <elib/mp/pack/make_pack.hpp>
# include <elib/mp/sequence.hpp>
# include <elib/mp/identity.hpp>
# include <elib/mp/detail/eat_pod.hpp>

namespace elib 
{
  namespace mp
  {
    namespace detail
    {
      
      template <class ...Ignored>
      struct pack_at_impl< pack<Ignored...> >
      {
        template <class T, class ...Rest>
          static typename T::type
        eval(eat_pod<Ignored>..., T*, Rest*...);
      };
      
      
      template <class ...Ignored>
      struct pack_drop_impl< pack<Ignored...> >
      {
        template <class ...Rest>
          static pack<typename Rest::type...>
        eval(eat_pod<Ignored>..., Rest*...);
      };
      
      template <class Pack, class ...Rest>
      struct pack_take_impl<0, Pack, Rest...>
      {
        using type = Pack;
      };
      
      
      template <
          class ...PackArgs
        , class A1
        , class ...Rest
        >
      struct pack_take_impl<
          1
        , pack<PackArgs...>
        , A1
        , Rest...
        >
      {
        using type = pack<PackArgs..., A1>;
      };
      
      
      template <
          class ...PackArgs
        , class A1, class A2
        , class ...Rest
        >
      struct pack_take_impl<
          2
        , pack<PackArgs...>
        , A1, A2
        , Rest...
        >
      {
        using type = pack<PackArgs..., A1, A2>;
      };
      
      
      template <
          class ...PackArgs
        , class A1, class A2, class A3
        , class ...Rest
        >
      struct pack_take_impl<
          3
        , pack<PackArgs...>
        , A1, A2, A3
        , Rest...
        >
      {
        using type = pack<PackArgs..., A1, A2, A3>;
      };
      
      
      template <
          class ...PackArgs
        , class A1, class A2, class A3, class A4
        , class ...Rest
        >
      struct pack_take_impl<
          4
        , pack<PackArgs...>
        , A1, A2, A3, A4
        , Rest...
        >
      {
        using type = pack<PackArgs..., A1, A2, A3, A4>;
      };
      
      
      template <
          class ...PackArgs
        , class A1, class A2, class A3, class A4, class A5
        , class ...Rest
        >
      struct pack_take_impl<
          5
        , pack<PackArgs...>
        , A1, A2, A3, A4, A5
        , Rest...
        >
      {
        using type = pack<PackArgs..., A1, A2, A3, A4, A5>;
      };
      
      
      template <
          std::size_t N
        , class ...PackArgs
        , class A1, class A2, class A3, class A4, class A5, class A6
        , class ...Rest
        >
      struct pack_take_impl<
          N
        , pack<PackArgs...>
        , A1, A2, A3, A4, A5, A6
        , Rest...
        > : pack_take_impl<N - 5
              , pack<PackArgs...
              , A1, A2, A3, A4, A5>
              , A6, Rest...
          >
      {};
      
      
      struct pack_intrinsics
      {
        // fwd
        template <class S> struct front;
        template <class S> struct back;
        template <class S> struct sequence_size;
        template <class S> struct empty;
        //template <class S> struct begin;
        template <class S> struct end;
        //template <class S, class N> struct at;
        template <class S, std::size_t N> struct at_c;
        //template <class S> struct clear;
        template <class S, class T> struct push_back;
        template <class S> struct pop_back;
        template <class S, class T> struct push_front;
        template <class S> struct pop_front;
        template <class S, std::size_t N> struct drop;
        template <class S, std::size_t N> struct take;
        template <class S, std::size_t First, std::size_t Last> struct slice;
        template <class Left, class Right> struct concat;
        
        // TODO
        // template <...> struct erase;
        // template <...> struct insert;
        
        template <class First, class ...Rest>
        struct front< pack<First, Rest...> >
        {
          using type = First;
        };
        
        template <class ...Args>
        struct back< pack<Args...> >
        {
          using type = typename at<
            pack<Args...>, size_type<sizeof...(Args)-1> 
          >::type;
        };
        
        template <class ...Args>
        struct sequence_size< pack<Args...> > 
          : size_type<sizeof...(Args)>
        {};
        
        template <class Seq>
        using O1_size = sequence_size<Seq>;
        
        template <class ...Args>
        struct empty< pack<Args...> >
          : bool_<sizeof...(Args) == 0>
        {};
        
        template <class Pack>
        using begin = pack_iterator<Pack, 0>;
      
        
        template <class ...Args>
        struct end< pack<Args...> >
        {
          using type = pack_iterator<pack<Args...>, sizeof...(Args)>;
        };
        
        template <class Pack, class N>
        using at = at_c<Pack, N::type::value>;
        
        template <class ...Args, std::size_t N>
        struct at_c<pack<Args...>, N>
        {
          using type = decltype(
            pack_at_impl<make_pack_t<decltype(nullptr), N>>
              ::eval((identity<Args>*)nullptr...)
          );
        };
        
        template <class Pack>
        using clear = pack<>;
        
        template <class ...Args, class T>
        struct push_back< pack<Args...>, T>
        {
          using type = pack<Args..., T>;
        };
        
        template <class ...Args>
        struct pop_back< pack<Args...> >
        {
          using type = typename take<pack<Args...>, sizeof...(Args)-1>::type;
        };
        
        template <class ...Args, class T>
        struct push_front< pack<Args...>, T >
        {
          using type = pack<T, Args...>;
        };
        
        template <class First, class ...Rest>
        struct pop_front< pack<First, Rest...> >
        {
          using type = pack<Rest...>;
        };
        
        
        template <class ...Args, std::size_t N>
        struct drop< pack<Args...>, N>
        {
          using type = decltype(
            pack_drop_impl<make_pack_t<decltype(nullptr), N>>
              ::eval((identity<Args>*)nullptr...)
          );
        };
        
        
        template <class ...Args, std::size_t N>
        struct take< pack<Args...>, N> 
          : pack_take_impl<N, pack<>, Args...>
        {};
        
        
        template <class Pack, std::size_t First, std::size_t Last>
        struct slice
        {
          using after_drop_ = typename drop<Pack, First>::type;
          using type = typename take<after_drop_, Last - First>::type;
        };
        
        
        template <class ...Left, class ...Right>
        struct concat< pack<Left...>, pack<Right...> >
        {
          using type = pack<Left..., Right...>;
        };
        
      };                                              // struct pack_intrinsics
      
    }                                                       // namespace detail
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_PACK_INTRINSICS_HPP */