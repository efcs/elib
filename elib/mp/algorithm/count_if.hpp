#ifndef ELIB_MP_ALGORITHM_COUNT_IF_HPP
#define ELIB_MP_ALGORITHM_COUNT_IF_HPP

# include <elib/mp/algorithm/foldl.hpp>
# include <elib/mp/iterator.hpp>
# include <elib/mp/metafunctions.hpp>
# include <elib/mp/sequence.hpp>
# include <elib/mp/integral_constant.hpp>

namespace elib 
{
  namespace mp
  {
    
    template <class Seq, class Pred>
    struct count_if 
      : foldl<
            Seq
          , ulong_<0>
          , if_< apply_wrap<lambda<Pred>, _2>
                , next<_1>
                , _1 
            >
        >
  {};
  
    template <class Seq, class Pred>
    using count_if_t = typename 
        foldl<
            Seq, ulong_<0>
          , if_< 
              apply_wrap<lambda<Pred>, _2>
            , next<_1>
            , _1 
            >
          >::type;
  
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_ALGORITHM_COUNT_IF_HPP */