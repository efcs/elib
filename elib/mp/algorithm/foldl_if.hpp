#ifndef ELIB_MP_ALGORITHM_FOLDL_IF_HPP
#define ELIB_MP_ALGORITHM_FOLDL_IF_HPP

# include <elib/mp/sequence_traits.hpp>
# include <elib/mp/if.hpp>
# include <elib/mp/lambda.hpp>
# include <elib/mp/algorithm/deref_wrapper.hpp>
# include <elib/mp/algorithm/variadic_foldl_if.hpp>
# include <elib/mp/algorithm/iter_fold_if.hpp>


namespace elib 
{
  namespace mp
  {
    
    namespace detail
    {
      
      template <class Seq, class State, class F, class Pred>
      using select_foldl_if_t = 
        if_t< 
          is_model_of<Seq, model::variadic>
          , variadic_foldl_if<Seq, State, F, Pred>
          , iter_foldl_if<Seq, State
              , deref_wrapper<lambda<F>>
              , deref_wrapper<lambda<Pred>>
            >
        >;
      
    }                                                       // namespace detail
    

    template <class Seq, class State, class F, class Pred>
    struct foldl_if  
      : detail::select_foldl_if_t<Seq, State, F, Pred>
    {};
    
    
    template <class Seq, class State, class F, class Pred>
    using foldl_if_t = typename 
      detail::select_foldl_if_t<Seq, State, F, Pred>::type;
    
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_ALGORITHM_FOLDL_IF_HPP */