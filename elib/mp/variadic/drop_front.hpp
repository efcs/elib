#ifndef ELIB_MP_VARIADIC_DROP_FRONT_HPP
#define ELIB_MP_VARIADIC_DROP_FRONT_HPP

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
      struct drop_front_impl;
    }                                                       // namespace detail
    
    
    template <std::size_t N, class ...Args>
    struct drop_front
    {
      using type = decltype(
        detail::drop_front_impl<
          make_param_pack_t<decltype(nullptr), N>
        >::eval((type_<Args>*)nullptr...)
      );
    };
    
    
    template <std::size_t N, class ...Args>
    using drop_front_t = typename drop_front<N, Args...>::type;
    
    
    namespace detail
    {
      
      template <class ...Ignored>
      struct drop_front_impl< param_pack<Ignored...> >
      {
        template <class ...Rest>
        static param_pack< unwrap_t<Rest>... > 
          eval(eat_pod<Ignored>..., Rest*...);
      };
      
    }                                                       // namespace detail
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_VARIADIC_DROP_FRONT_HPP */