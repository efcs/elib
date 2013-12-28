#ifndef ELIB_MP_ALGORITHM_DETAIL_DEREF_LAMBDA_HPP
#define ELIB_MP_ALGORITHM_DETAIL_DEREF_LAMBDA_HPP


# include <elib/mp/apply_wrap.hpp>
# include <elib/mp/iterator.hpp>
# include <elib/mp/lambda.hpp>
# include <elib/mp/protect.hpp>

namespace elib 
{
  namespace mp
  {
    namespace detail
    {
      
      template <class F>
      struct deref_lambda_impl
      {
        template <class State, class Iter>
        using apply = apply_wrap< lambda<F>, State, deref_t<Iter>>;
      };
      
      
      template <class F>
      using deref_lambda = protect< deref_lambda_impl<F> >;


      
      template <class F>
      struct binary_deref_lambda_impl
      {
        template <class State, class Iter>
        using apply = apply_wrap< lambda<F>, deref_t<State>, deref_t<Iter>>;
      };
      
      
      template <class F>
      using binary_deref_lambda = protect< binary_deref_lambda_impl<F> >;
      
      
      
      template <class F>
      struct first_deref_lambda_impl
      {
        template <class First, class Second>
        using apply = apply_wrap< lambda<F>, deref_t<First>, Second>;
      };
      
      
      template <class F>
      using first_deref_lambda = protect< first_deref_lambda_impl<F> >;
      
    }                                                       // namespace detail
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_ALGORITHM_DETAIL_DEREF_LAMBDA_HPP */