#ifndef ELIB_MP_APPLY_WRAP_HPP
#define ELIB_MP_APPLY_WRAP_HPP

# include <elib/aux.hpp>

namespace elib 
{
  namespace mp
  {
    
    namespace detail
    {
      template <class F>
      auto detect_apply_type() -> typename F::apply;
      
      template <class F>
      auto detect_apply_type() -> typename F::template apply<>;
    }                                                       // namespace detail
    
    template <class F, class ...Args>
    struct apply_wrap;
    
    
    template <class F, class First, class ...Rest>
    struct apply_wrap<F, First, Rest...>
    {
      using type = typename F::template apply<First, Rest...>::type;
    };
    
    
    template <class F>
    struct apply_wrap<F>
    {
        using result = decltype(detail::detect_apply_type<F>());
        using type = typename result::type;
    };
    
    
    template <class F, class ...Args>
    using apply_wrap_t = typename apply_wrap<F, Args...>::type;
    
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_APPLY_WRAP_HPP */