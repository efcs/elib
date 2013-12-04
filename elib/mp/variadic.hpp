#ifndef ELIB_MP_VARIADIC_HPP
#define ELIB_MP_VARIADIC_HPP

# include <elib/mp/variadic_fwd.hpp>
# include <elib/mp/index_sequence.hpp>
# include <elib/mp/type_wrapper.hpp>
# include <elib/mp/integral_constant.hpp>

namespace elib 
{
  namespace mp
  {
    
    template <class ...Args>
    struct pack
    {
      using type = pack;
    };
    
    
    template <class T>
    struct is_pack : false_
    {};
    
    template <class ...Args>
    struct is_pack< pack<Args...> > : true_
    {};
    
    
    template <template <class...> class T, class ...Args>
    struct make_pack< T<Args...> >
    {
      using type = pack<Args...>;
    };
    
    
    template <class ...Args1, class ...Args2>
    struct concat< pack<Args1...>,  pack<Args2...> >
    { 
      using type = pack<Args1..., Args2...>; 
    };
    
    
    template <class ...Args, class ...ToAppend>
    struct append< pack<Args...>, ToAppend...>
    { 
      using type = pack<Args..., ToAppend...>; 
    };
    
    
    template <class ...Args, class ...ToPrepend>
    struct prepend< pack<Args...>,  ToPrepend...>
    { 
      using type = pack<ToPrepend..., Args...>; 
    };
    
    
    template <std::size_t N, class T>
    struct make_pack_of : detail::make_pack_of_impl<N, T>
    {};
    
    namespace detail
    {
      
      template <std::size_t N, class T>
      struct make_pack_of_impl
        : concat<
            typename make_pack_of_impl<N / 2, T>::type
          , typename make_pack_of_impl<N - (N / 2), T>::type
          >
      {};
      
      template <class T>
      struct make_pack_of_impl<0, T>
      { 
        using type = pack<>;
      };
      
      template <class T>
      struct make_pack_of_impl<1, T>
      {
        using type = pack<T>;
      };
      
      template <class T>
      struct make_pack_of_impl<2, T>
      {
        using type = pack<T, T>;
      };
      
      template <class T>
      struct make_pack_of_impl<3, T>
      {
        using type = pack<T, T, T>;
      };
      
      template <class T>
      struct make_pack_of_impl<4, T>
      {
        using type = pack<T, T, T, T>;
      };
      
      template <class T>
      struct make_pack_of_impl<5, T>
      {
        using type = pack<T, T, T, T, T>;
      };
      
      template <class T>
      struct make_pack_of_impl<6, T>
      {
        using type = pack<T, T, T, T, T, T>;
      };
      
      template <class T>
      struct make_pack_of_impl<7, T>
      {
        using type = pack<T, T, T, T, T, T, T>;
      };
      
      template <class T>
      struct make_pack_of_impl<8, T>
      {
        using type = pack<T, T, T, T, T, T, T, T>;
      };
      
      template <class T>
      struct make_pack_of_impl<9, T>
      {
        using type = pack<T, T, T, T, T, T, T, T, T>;
      };
      
      template <class T>
      struct make_pack_of_impl<10, T>
      {
        using type = pack<T, T, T, T, T, T, T, T, T, T>;
      };
      
    }                                                       // namespace detail
    
    
    template <std::size_t N, class ...Args>
    struct get_nth
    {
      using result_ = decltype(
        detail::get_nth_impl< make_pack_of_t<N, decltype(nullptr)> 
          >::eval((type_<Args>*)nullptr...)
      );
    
      using type = unwrap_t<result_>;
    };
    
    template <std::size_t N, class ...Args>
    struct drop_n
    {
      using type = decltype(
        detail::drop_n_impl< make_pack_of_t<N, decltype(nullptr)> 
          >::eval((type_<Args>*)nullptr...)
      );
    };
    
    
    namespace detail
    {
      
      template <class>
      struct eat_pod
      {
        eat_pod(...);
      };
      
      
      template <class ...Ignored>
      struct get_nth_impl< pack<Ignored...> >
      {
        template <class T, class ...Rest>
        static T eval(eat_pod<Ignored>...,  T*, Rest* ...);
      };
      
      template <class ...Ignored>
      struct drop_n_impl< pack<Ignored...> >
      {
        template <class ...Rest>
        static pack< unwrap_t<Rest...> > eval(eat_pod<Ignored>..., Rest*...);
      };
      
    }                                                       // namespace detail
    
    
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_VARIADIC_HPP */