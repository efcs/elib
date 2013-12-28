/* 
 * Thanks to github/Idionne for inspiring foldl impl
 */
#ifndef ELIB_MP_ALGORITHM_FOLDL_HPP
#define ELIB_MP_ALGORITHM_FOLDL_HPP

# include <elib/mp/sequence.hpp>
# include <elib/mp/iterator.hpp>
# include <elib/mp/sequence_traits.hpp>
# include <elib/mp/lambda.hpp>
# include <elib/mp/algorithm/variadic_foldl.hpp>
# include <elib/mp/algorithm/iter_foldl.hpp>
# include <elib/mp/algorithm/iter_fold_n.hpp>
# include <elib/mp/algorithm/deref_wrapper.hpp>

namespace elib 
{
  namespace mp
  {
    
    namespace detail
    {
      
      template <class Seq, class State, class F>
      using o1_size_foldl = 
        iter_foldl_n<
            Seq
          , State
          , deref_wrapper<lambda<F>>
          , sequence_size_t<Seq>::value
        >;
        
        
      template <class Seq, class State, class F>
      using other_foldl = 
        iter_foldl<
            Seq
          , State
          , deref_wrapper<lambda<F>>
        >;
        
        
      template <class Seq, class State, class F>
      using else_o1_size_t = 
        if_t<
          has_O1_size<Seq>
          , detail::o1_size_foldl<Seq, State, F>
          , detail::other_foldl<Seq, State, F>
        >;
      
      
      template <class Seq, class State, class F>
      using select_foldl_t =
        if_t<
          is_model_of<Seq, model::variadic>
          , variadic_foldl<Seq, State, F>
          , else_o1_size_t<Seq, State, F>
        >;
      
    }                                                       // namespace detail

    
    template <class Seq, class State, class F>
    struct foldl : detail::select_foldl_t<Seq, State, F>
    {};
   
   
    template <class Seq, class State, class F>
    using foldl_t = typename detail::select_foldl_t<Seq, State, F>::type;
   
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_ALGORITHM_FOLDL_HPP */