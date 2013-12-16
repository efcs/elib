#ifndef ELIB_MP_VARIADIC_GET_NTH_HPP
#define ELIB_MP_VARIADIC_GET_NTH_HPP

# include <elib/mp/variadic/variadic_fwd.hpp>
# include <elib/mp/variadic/eat_pod.hpp>
# include <elib/mp/param_pack/param_pack.hpp>
# include <elib/mp/param_pack/make_param_pack.hpp>
# include <elib/mp/type_wrapper.hpp>

# include <cstddef>

namespace elib 
{
  namespace mp
  {
    
    namespace detail
    {
      template <class ...Ignored>
      struct get_nth_impl;
    }                                                       // namespace detail
    
    
    template <std::size_t N, class ...Args>
    struct get_nth
    {
      using type = decltype(
        detail::get_nth_impl<
          make_param_pack_t<decltype(nullptr), N>
        >::eval( (type_<Args>*)nullptr... )
      );
    };
    
    
    template <std::size_t N, class ...Args>
    using get_nth_t = typename get_nth<N, Args...>::type;
    
    
    namespace detail
    {
      
      template <class ...Ignored>
      struct get_nth_impl< param_pack<Ignored...> >
      {
        template <class T, class ...Rest>
        static unwrap_t<T> 
          eval(eat_pod<Ignored>...,  T*, Rest* ...);
      };
      
    }                                                       // namespace detail
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_VARIADIC_GET_NTH_HPP */