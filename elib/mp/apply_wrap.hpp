#ifndef ELIB_MP_APPLY_WRAP_HPP
# define ELIB_MP_APPLY_WRAP_HPP

# include <elib/mp/config.hpp>
# include <elib/mp/integral_constant.hpp>
# include <elib/mp/detail/has_apply.hpp>

namespace elib 
{
  namespace mp
  {
    namespace detail
    {
      
      template <class F, class = typename has_apply<F>::type >
      struct apply_wrap0 : F::template apply<>
      {};
      
      template <class F>
      struct apply_wrap0<F, true_> : F::apply
      {};
      
    }                                                       // namespace detail
    
    /* Base template: used in case where Args is empty */
    template <class F, class ...Args>
    struct apply_wrap
    {
      static_assert(sizeof...(Args) == 0, "param pack must be empty");
      typedef typename detail::apply_wrap0<F>::type type;
    };
    
    
    /* overload for 1 or more args */
    template <class F, class T, class ...Args>
    struct apply_wrap<F, T, Args...>
    {
      typedef typename F::template apply<T, Args...>::type type;
    };
    
    
    template <class F, class ...Args>
    using apply_wrap_t = typename apply_wrap<F, Args...>::type;
    
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_APPLY_WRAP_HPP */