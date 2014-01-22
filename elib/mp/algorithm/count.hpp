#ifndef ELIB_MP_ALGORITHM_COUNT_HPP
#define ELIB_MP_ALGORITHM_COUNT_HPP

# include <elib/mp/algorithm/fold.hpp>
# include <elib/mp/arg.hpp>
# include <elib/mp/apply_wrap.hpp>
# include <elib/mp/iterator.hpp>
# include <elib/mp/lambda.hpp>
# include <elib/mp/same_type.hpp>
# include <elib/aux.hpp>

namespace elib 
{
  namespace mp
  {

    template <class Seq, class Pred>
    struct count_if 
      : foldl<
          Seq, aux::ulong_<0>
        , if_< 
            apply_wrap<lambda<Pred>, _2>
          , next<_1>, _1
          >
        >
    {};

    
    template <class Seq, class Pred>
    using count_if_t = typename 
      foldl<
          Seq, aux::ulong_<0>
        , if_< 
            apply_wrap<lambda<Pred>, _2>
          , next<_1>, _1
          >
        >
      ::type;
            

    template <class Seq, class T>
    struct count : count_if<Seq, same_type<T, _1>>
    {};

    template <class Seq, class T>
    using count_t = typename count_if<Seq, same_type<T, _1>>::type;

  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_ALGORITHM_COUNT_HPP */