#ifndef ELIB_MP_ALGORITHM_DEREF_WRAPPER_HPP
#define ELIB_MP_ALGORITHM_DEREF_WRAPPER_HPP

# include <elib/mp/iterator.hpp>
# include <elib/mp/apply_wrap.hpp>

namespace elib 
{
  namespace mp
  {
    
    template <class F>
    struct deref_wrapper
    {
      template <class State, class Iter>
      using apply = apply_wrap<F, State, deref_t<Iter>>;
    };


    template <class F>
    struct binary_deref_wrapper
    {
      template <class State, class Iter>
      using apply = apply_wrap<F, deref_t<State>, deref_t<Iter>>;
    };
    
    
    template <class F>
    struct first_deref_wrapper
    {
      template <class First, class Second>
      using apply = apply_wrap<F, deref_t<First>, Second>;
    };
    
    
    template <class F>
    using second_deref_wrapper = deref_wrapper<F>;

  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_ALGORITHM_DEREF_WRAPPER_HPP */