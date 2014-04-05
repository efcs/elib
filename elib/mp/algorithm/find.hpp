#ifndef ELIB_MP_ALGORITHM_FIND_HPP
#define ELIB_MP_ALGORITHM_FIND_HPP

# include <elib/mp/algorithm/iter_fold_if.hpp>
# include <elib/mp/arg.hpp>
# include <elib/mp/apply_wrap.hpp>
# include <elib/mp/iterator.hpp>
# include <elib/mp/lambda.hpp>
# include <elib/mp/sequence.hpp>
# include <elib/aux.hpp>

namespace elib 
{
  namespace mp
  {
    
    template <class Seq, class Pred>
    using find_if = 
      iter_foldl_if<
          Seq
        , end_t<Seq>
        , if_< 
            apply_wrap<lambda<Pred>, deref<_2>>
            , _2 
            , _1
          >
        , aux::is_same<end_t<Seq>, _1>
      >;
    
    
    template <class Seq, class IfPred>
    using find_if_t = typename find_if<Seq, IfPred>::type;
    
    
    
    template <class Seq, class T>
    struct find : find_if<Seq, aux::is_same<T, _1>>
    {};
    
    template <class Seq, class T>
    using find_t = typename find<Seq, T>::type;
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_ALGORITHM_FIND_HPP */