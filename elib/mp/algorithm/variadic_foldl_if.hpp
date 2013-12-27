#ifndef ELIB_MP_ALGORITHM_VARIADIC_FOLDL_IF_HPP
#define ELIB_MP_ALGORITHM_VARIADIC_FOLDL_IF_HPP

# include <elib/mp/apply_wrap.hpp>
# include <elib/mp/iterator.hpp>
# include <elib/mp/if.hpp>
# include <elib/mp/integral_constant.hpp>
# include <elib/mp/identity.hpp>
# include <elib/mp/sequence.hpp>
# include <elib/mp/sequence_traits.hpp>


namespace elib 
{
  namespace mp
  {
    namespace detail
    {
      
      template <bool> struct variadic_foldl_if_impl;
      
      
      template <class State, class F, class Pred, class First>
      using variadic_foldl_if_step = 
        eval_if_t<
            apply_wrap_t<Pred, State, First>
          , apply_wrap<F, State, First>
          , identity<State>
        >;
        
        
      template <class State, class F, class Pred, class First, class ...Rest>
      using variadic_foldl_if_apply = typename
        variadic_foldl_if_impl<
            sizeof...(Rest) != 0
            && apply_wrap_t<Pred, State, First>::value
        >::template 
        apply<
            variadic_foldl_if_step<State, F, Pred, First>
          , F, Pred
          , Rest...
        >;
      
      
      template <bool Good>
      struct variadic_foldl_if_impl
      {
        template <
            class State, class F, class Pred
          , class First, class ...Rest
        >
        using apply = 
          variadic_foldl_if_apply< State, F, Pred, First, Rest... >;
      };
      
      
      template <>
      struct variadic_foldl_if_impl<false>
      {
        template <class State, class F, class Pred, class ...Args>
        struct apply
        {
          using state = State;
          using type = State;
        };
      };
      
    }                                                       // namespace detail
    
    
    
    template <class Seq, class State, class F, class Pred>
    struct variadic_foldl_if;
    
    
    template <
        template <class...> class S
      , class State, class F, class Pred
    >
    struct variadic_foldl_if<S<>, State, F, Pred>
    {
      using type = State;
      
      static_assert(is_model_of<S<>, model::variadic>::type::value, 
                    "must be model of variadic");
    };
    
    
    template <
        template <class...> class S, class First, class ...Rest
      , class State, class F, class Pred
      >
    struct variadic_foldl_if<S<First, Rest...>, State, F, Pred>
    {
      
      using type = typename
        detail::variadic_foldl_if_apply<
            State
          , lambda<F>
          , lambda<Pred>
          , First, Rest...>::type;
      
      static_assert( is_model_of<S<First, Rest...>, model::variadic>::type::value, 
                    "must me model of variadic");
    };
    
    
    template <class Seq, class State, class F, class Pred>
    using variadic_foldl_if_t = 
      typename variadic_foldl_if<Seq, State, F, Pred>::type;
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_ALGORITHM_VARIADIC_FOLDL_IF_HPP */