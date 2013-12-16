#ifndef ELIB_MP_PARAM_PACK_INTRINSICS_HPP
#define ELIB_MP_PARAM_PACK_INTRINSICS_HPP

# include <elib/mp/param_pack/param_pack_fwd.hpp>
# include <elib/mp/param_pack/param_pack.hpp>
# include <elib/mp/param_pack/iterator.hpp>
# include <elib/mp/integral_constant.hpp>
# include <elib/mp/variadic.hpp>
# include <elib/mp/optimization.hpp>


namespace elib 
{
  namespace mp
  {
    namespace detail
    {
     
     
      struct param_pack_intrinsics
      {
        // fwd declarations
        template <class Pack> struct begin;
        template <class Pack> struct end;
        template <class Pack> struct size;
        template <class Pack> struct empty;
        template <class Pack> struct front;
        template <class Pack> struct back;
        template <class Pack, class N> struct at;
        // template <...> struct insert;
        // template <...> struct insert_range;
        // template <...> struct erase;
        template <class Pack> struct clear;
        template <class Pack, class T> struct push_back;
        template <class Pack> struct pop_back;
        template <class Pack, class T> struct push_front;
        template <class Pack> struct pop_front;
        
        // Optimizations
        using O1_SIZE_OPTIMIZATION = optimization_tag;
        
        // implementation
        
        template <class Pack>
        struct begin
        { 
          using type = param_pack_iterator<Pack, 0>; 
        };
        
        
        template <class ...Args>
        struct end< param_pack<Args...> >
        { 
          using type = param_pack_iterator< 
            param_pack<Args...>, sizeof...(Args)
          >;
        };
        
        
        template <class ...Args>
        struct size< param_pack<Args...> >
        {
          using type = size_type< sizeof...(Args) >;
        };
        
        
        template <class ...Args>
        struct empty< param_pack<Args...> >
        {
          using type = bool_< (sizeof...(Args) == 0) >;
        };
        
        
        template <class First, class ...Rest>
        struct front< param_pack<First, Rest...> >
        {
          using type = First;
        };
        
        
        template <class ...Args>
        struct back< param_pack<Args...> >
        {
          using type = get_nth_t<
              sizeof...(Args) - 1
            , param_pack<Args...>
          >;
        };
        
        template <class N, class ...Args>
        struct at< param_pack<Args...>, N >
        {
          using type = get_nth_t<
              N::type::value
            , param_pack<Args...>
          >;
        };
        
        
        template <class Pack>
        struct clear
        { 
          using type = param_pack<>;
        };
        
        
        template <class ...Args, class T>
        struct push_back< param_pack<Args...>, T >
        {
          using type = param_pack<Args..., T>;
        };
        
        
        template <class ...Args>
        struct pop_back< param_back<Args...> >
        {
          //TODO
        };
        
        
        template <class ...Args, class T>
        struct push_front< param_pack<Args...>, T >
        {
          using type = param_pack<T, Args...>;
        };
        
        
        template <class First, class ...Rest>
        struct pop_front< param_pack<First, Rest...> >
        {
          using type = param_pack<Rest...>;
        };
        
      };                                        // struct param_pack_intrinsics
      
      
    }                                                       // namespace detail
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_PARAM_PACK_INTRINSICS_HPP */