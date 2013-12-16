#ifndef ELIB_MP_VARIADIC_SLICE_HPP
#define ELIB_MP_VARIADIC_SLICE_HPP

# include <elib/mp/variadic/variadic_fwd.hpp>
# include <elib/mp/variadic/drop_front.hpp>
# include <elib/mp/variadic/drop_back.hpp>
# include <elib/mp/param_pack/param_pack.hpp>
# include <cstddef>

namespace elib 
{
  namespace mp
  {
    
    namespace detail
    {
      template <std::size_t N, class Pack>
      struct slice_drop_back_impl;
    }                                                       // namespace detail
   
   
    template <std::size_t First, std::size_t Last, class ...Args>
    struct slice
    {
      using without_front_ = drop_front_t<First, Args...>;
      using type = typename 
        detail::slice_drop_back_impl<Last - First, without_front_>::type;
    };
   
   
    namespace detail
    {
      
      template <std::size_t N, class ...PArgs>
      struct slice_drop_back_impl<N, param_pack<PArgs...>>
        : drop_back<N, PArgs...>
      {};
      
    }                                                       // namespace detail
   
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_VARIADIC_SLICE_HPP */