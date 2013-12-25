#ifndef ELIB_MP_ALGORITHM_FIND_IF_HPP
#define ELIB_MP_ALGORITHM_FIND_IF_HPP

# include <elib/mp/algorithm/iter_foldl_if.hpp>
# include <elib/mp/iterator.hpp>
# include <elib/mp/metafunctions.hpp>
# include <elib/mp/sequence.hpp>

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
        , same_type<end_t<Seq>, _1>
      >;
    
    
    template <class Seq, class IfPred>
    using find_if_t = typename find_if<Seq, IfPred>::type;
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_ALGORITHM_FIND_IF_HPP */